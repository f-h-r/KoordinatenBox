// Libraries
#include <SPI.h>
#include <TimerOne.h>
#include <Arduino.h>
#include <RotaryEncoder.h>
#include <Keypad.h>
#include <EEPROM.h>
#include <Math.h>

#include <LedController.hpp>
/*
  ! IMPORTANT !
  You need to set a fixed speed for SPI in libraries\LedController\src\LedController_config.hpp
  at line 121:

  uint64_t spiTransferSpeed = SPI_CLOCK_DIV16;

  which sets the SPI clock to 1/16 the frequency of the system clock (1 Mhz for boards at 16 MHz)
*/

// Debugging routines
//#define DBG_ENABLE
#define SERIAL_BAUD 38400
#ifdef DBG_ENABLE
#define DBG_P(...) { Serial.print(__VA_ARGS__); }
#else
#define DBG_P(...) {}
#endif

// Timer-Interrupt-specific, Bitmasks
#define TIMER_INT_US 200000 // Triggers every x us
#define TIMER_UPDATE 0 // Toggle-Bit in ucTimerInterruptMask signalling update
volatile unsigned char ucTimerInterruptMask = 0; // Interruptable Char for storing bit masks and counters

// LEDController / Maxim MAX7219 specific
// 7-Segment Layout - Bits 0-7
//
//
//     ---
//  1 | 6 | 5
//     ---
//  2 | 0 | 4
//     ---  o
//      3   7
//


// the pins where the chip select is connected to
#define CS1 47 // First display (top) - X-Axis
#define CS2 45 // Second display - Y-Axis
#define CS3 43 // Third display - Z-Axis
#define CS4 41 // Fourth display - Main menu
#define CS5 39 // Fifth display - Sub menu
#define DATA_COUNT 4 // Number of data items do display
unsigned char ucLdBright = 2; // current LED brightness (0-9)
unsigned char ucDataToShow = 0; // current data item to show on the screen
unsigned char ucActionActive = 0; // indicates an active action - animates first char of submenu if set to "2"

// the uninitilized LED controller object
LedController<1, 1> lcDispX = LedController<1, 1>();
LedController<1, 1> lcDispY = LedController<1, 1>();
LedController<1, 1> lcDispZ = LedController<1, 1>();
LedController<1, 1> lcDispMM = LedController<1, 1>();
LedController<1, 1> lcDispSM = LedController<1, 1>();


// Rotary encoder specific
// Main
#define ENC_MAIN_A A12
#define ENC_MAIN_B A8
#define ENC_MAIN_COM A10
#define ENC_MAIN_BTN_IN A14
#define ENC_MAIN_BTN_COM 32

// Aux
#define ENC_AUX_A A9
#define ENC_AUX_B A13
#define ENC_AUX_COM A11
#define ENC_AUX_BTN_IN A15
#define ENC_AUX_BTN_COM 33

// A pointer to the dynamic created rotary encoder instance.
// This will be done in setup()
RotaryEncoder *main_encoder = nullptr;
RotaryEncoder *aux_encoder = nullptr;
int main_pos = 0; // init position of encoder to zero
int aux_pos = 0; // init position of encoder to zero


// Keypad specific
// 1-button-Keypad for master encoder
const byte MAIN_ROWS = 1;
const byte MAIN_COLS = 1;
char main_keys[MAIN_ROWS][MAIN_COLS] = {{'M'},};
byte main_rowPins[MAIN_ROWS] = {ENC_MAIN_BTN_COM}; //connect to the row pinouts of the keypad
byte main_colPins[MAIN_COLS] = {ENC_MAIN_BTN_IN}; //connect to the column pinouts of the keypad
Keypad main_keypad = Keypad( makeKeymap(main_keys), main_rowPins, main_colPins, MAIN_ROWS, MAIN_COLS );

//// 1-button-Keypad for aux encoder
const byte AUX_ROWS = 1;
const byte AUX_COLS = 1;
char aux_keys[AUX_ROWS][AUX_COLS] = {{'A'},};
byte aux_rowPins[AUX_ROWS] = {ENC_AUX_BTN_COM}; //connect to the row pinouts of the keypad
byte aux_colPins[AUX_COLS] = {ENC_AUX_BTN_IN}; //connect to the column pinouts of the keypad
Keypad aux_keypad = Keypad( makeKeymap(aux_keys), aux_rowPins, aux_colPins, AUX_ROWS, AUX_COLS );

// 6 keys Axis Input - Note common ground!
#define AXIS_COM 22
#define AXIS_ZERO_X 23
#define AXIS_ZERO_Y 24
#define AXIS_ZERO_Z 25
#define AXIS_REL_X 26
#define AXIS_REL_Y 27
#define AXIS_REL_Z 28

#define AXIS_LED_COM 20
#define AXIS_LED_X 29
#define AXIS_LED_Y 30
#define AXIS_LED_Z 31

const byte AXIS_ROWS = 6;
const byte AXIS_COLS = 1;
char axis_keys[AXIS_ROWS][AXIS_COLS] = {{'1'}, {'2'}, {'3'}, {'x'}, {'y'}, {'z'},};
byte axis_rowPins[AXIS_ROWS] = {AXIS_ZERO_X, AXIS_ZERO_Y, AXIS_ZERO_Z, AXIS_REL_X, AXIS_REL_Y, AXIS_REL_Z}; //connect to the row pinouts of the keypad
byte axis_colPins[AXIS_COLS] = {AXIS_COM}; //connect to the column pinouts of the keypad
Keypad axis_keypad = Keypad( makeKeymap(axis_keys), axis_rowPins, axis_colPins, AXIS_ROWS, AXIS_COLS );

// configuration menu specific
unsigned char ucMenuLevel = 0; // current menu level. 0 = normal display
unsigned char ucSettingsItem = 0; // current settings item
unsigned char ucSelectedAxis = 0; // Selected axis (0=X, 1=Y, 2=Z)



// EEPROM specific
#define EE_CONFIG 0 // starting address in EEPROM for config byte (1 byte size)
#define EE_LEDBRIGHT 1  // starting address in EEPROM for LED brightness (1 byte size)
#define EE_RELVAL_X 2  // starting address in EEPROM for relative value for x-axis (4 byte size)
#define EE_RELVAL_Y 6  // starting address in EEPROM for relative value for x-axis (4 byte size)
#define EE_RELVAL_Z 10  // starting address in EEPROM for relative value for x-axis (4 byte size)
#define EE_VZEROVAL_X 14  // starting address in EEPROM for virtual zero value for x-axis (4 byte size)
#define EE_VZEROVAL_Y 18  // starting address in EEPROM for virtual zero value for x-axis (4 byte size)
#define EE_VZEROVAL_Z 22  // starting address in EEPROM for virtual zero value for x-axis (4 byte size)
#define EE_ZEROPOINT 26  // starting address in EEPROM for selected zero point (1 byte size)
#define EE_ZP_TABLE 40  // starting address in EEPROM for zero point arrays table (3x float (4 byte) per axis (12 byte) x 10 entries = 120 byte size)
#define EE_SCALEVAL_X 180  // starting address in EEPROM for scale factor value for x-axis (4 byte size)
#define EE_SCALEVAL_Y 184  // starting address in EEPROM for virtual zero value for y-axis (4 byte size)
#define EE_SCALEVAL_Z 188  // starting address in EEPROM for virtual zero value for z-axis (4 byte size)

volatile unsigned char ucEepromConfig = 0; // variable to hold bit fields for EE_CONFIG
#define BF_REL_X 0 // bit state in ucEepromConfig (EE_CONFIG)
#define BF_REL_Y 1 // bit state in ucEepromConfig (EE_CONFIG)
#define BF_REL_Z 2 // bit state in ucEepromConfig (EE_CONFIG)


// Definitions for scale data
// Serial port settings
#define SCALE_X_SERIALPORT Serial3
#define SCALE_Y_SERIALPORT Serial2
#define SCALE_Z_SERIALPORT Serial1
#define SCALE_SERIAL_BAUD 38400

// Unified scale value
typedef union
{
  long lVal;
  unsigned char chrs[4];
} ufScaleValue1_t;

// Scale struct, containing all needed settings per scale
struct scale_t
{
  ufScaleValue1_t  ufValue; // Value that is used for live readout - will change on read, don't use!
  float fRealVal; // scale value - will be set atomically based on final readout of ufScaleValue
  float fVirtualZeroVal; // contains offset for virtual set to zero
  float fRelativeVal; // contains scale offset for relative positions
  float fVal; // contains final value of scale
  unsigned char ucIsRelative; // Indicates absolute (0) or relative (1) position
  int iByteCounter; // incoming byte counter
  int iInByte; // incoming serial byte
  unsigned char ucNewData; // Indicates new (1) position
  float fScaleFactorVal; // contains scale factor value
};

// Zero point to select
#define MAX_NO_OF_ZERO_POINTS 9
unsigned char ucZeroPoint = 0; // Selected zero point (0 .. MAX_NO_OF_ZERO_POINTS)

// Set up scales
scale_t tScaleX = {0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 1.0};
scale_t tScaleY = {0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 1.0};
scale_t tScaleZ = {0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 1.0};


// Function definitions
// Function "Center of Path" struct, containing all needed settings
struct centerofpath_t
{
  float fToolDia; // tool diameter in mm
  float fFirstXVal; // first value X
  float fSecondXVal; // second value X
  float fFirstYVal; // first value Y
  float fSecondYVal; // second value Y
  unsigned int uiCurrent; // current iteration of cycle
  unsigned char ucState; // Indicates state of function (0=inactive, 1=running, 2=finish)
};
centerofpath_t tCoP = {0.0, 0.0, 0.0, 0.0, 0.0, 0, 0};


// Function "Pattern linear" struct, containing all needed settings
struct linearpattern_t
{
  unsigned int uiCountX; // number of iterations X-Axis
  unsigned int uiCountY; // number of iterations Y-Axis
  float fLengthX; // Length of path X
  float fLengthY; // Length of path X
  float fStartPtX; // Starting point X
  float fStartPtY; // Starting point Y
  float fLineAngle; // rotate linear Pattern, -90° - +90° ,starting at 0°
  unsigned int uiCurrentX; // current iterations X-Axis
  unsigned int uiCurrentY; // current iterations Y-Axis
  unsigned int uiCurrentNo; // current iteration of cycle
  unsigned char ucState; // Indicates state of function (0=inactive, 1=running, 2=finish)
};
linearpattern_t tLinP = {1, 1, 1.0, 1.0, 0.0, 0.0, 0.0, 0, 0, 0, 0};


// Function "Pattern circular" struct, containing all needed settings
struct circularpattern_t
{
  float fRadius; // Radius of circle
  unsigned int uiCount; // number of iterations on circle
  float fCurrentAngle; // Current angle, starting at 0°
  float fAngleOffset; // Offset of angle
  float fStartPtX; // Starting point X
  float fStartPtY; // Starting point Y
  unsigned int uiCurrent; // current iteration
  unsigned char ucState; // Indicates state of function (0=inactive, 1=running, 2=finish)
};
circularpattern_t tCirP = {10.0, 4, 0.0, 0.0, 0.0, 0.0, 0, 0};
