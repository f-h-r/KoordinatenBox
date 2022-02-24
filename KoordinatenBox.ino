/************************************************************************
  KoordinatenBox - Connect to caliper-converters, display data and calculate
  (c)2021 by Marian Neubert, Portions of code (c) Mario Zimmermann

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; version 2 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
************************************************************************/

// Read configuration
#include "config.h"


/**************************************************************************/
/*!
    @brief  Setup Routine
*/
/**************************************************************************/
void setup(void)
{
  // Set up debug serial interface
  Serial.begin(SERIAL_BAUD);

  // Set up scales serial interface
  SCALE_X_SERIALPORT.begin(SCALE_SERIAL_BAUD);
  SCALE_X_SERIALPORT.setTimeout(10);
  SCALE_Y_SERIALPORT.begin(SCALE_SERIAL_BAUD);
  SCALE_Y_SERIALPORT.setTimeout(10);
  SCALE_Z_SERIALPORT.begin(SCALE_SERIAL_BAUD);
  SCALE_Z_SERIALPORT.setTimeout(10);

  DBG_P(F("Init...\n"));
  _isr_init();

  // Encoder setup
  // Main encoder
  DBG_P(F("Encoder and buttons... "));
  pinMode(ENC_MAIN_COM, OUTPUT);
  digitalWrite(ENC_MAIN_COM, LOW);
  // Aux encoder
  pinMode(ENC_AUX_COM, OUTPUT);
  digitalWrite(ENC_AUX_COM, LOW);

  // 6-button Axis keypad LEDs
  pinMode(AXIS_LED_COM, OUTPUT);
  pinMode(AXIS_LED_X, OUTPUT);
  pinMode(AXIS_LED_Y, OUTPUT);
  pinMode(AXIS_LED_Z, OUTPUT);

  digitalWrite(AXIS_LED_COM, LOW);
  digitalWrite(AXIS_LED_X, LOW);
  digitalWrite(AXIS_LED_Y, LOW);
  digitalWrite(AXIS_LED_Z, LOW);

  // use FOUR3 mode when PIN signals are always HIGH in latch position.
  main_encoder = new RotaryEncoder(ENC_MAIN_B, ENC_MAIN_A, RotaryEncoder::LatchMode::FOUR3);
  aux_encoder = new RotaryEncoder(ENC_AUX_B, ENC_AUX_A, RotaryEncoder::LatchMode::FOUR3);
  DBG_P(F("Done\n"));


  // read EEPROM
  // bit fields:
  DBG_P(F("Read EEPROM... "));
  ucEepromConfig = EEPROM.read(EE_CONFIG);
  // LED brightness
  ucLdBright = EEPROM.read(EE_LEDBRIGHT);
  // selected zero point
  ucZeroPoint = EEPROM.read(EE_ZEROPOINT);
  // virtual zero value - if set
  for (unsigned int t = 0; t < sizeof(tScaleX.fVirtualZeroVal); t++) *((char*)&tScaleX.fVirtualZeroVal + t) = EEPROM.read(EE_VZEROVAL_X + t);
  for (unsigned int t = 0; t < sizeof(tScaleY.fVirtualZeroVal); t++) *((char*)&tScaleY.fVirtualZeroVal + t) = EEPROM.read(EE_VZEROVAL_Y + t);
  for (unsigned int t = 0; t < sizeof(tScaleZ.fVirtualZeroVal); t++) *((char*)&tScaleZ.fVirtualZeroVal + t) = EEPROM.read(EE_VZEROVAL_Z + t);
  // Relative values
  if (bitRead(ucEepromConfig, BF_REL_X))
  {
    for (unsigned int t = 0; t < sizeof(tScaleX.fRelativeVal); t++) *((char*)&tScaleX.fRelativeVal + t) = EEPROM.read(EE_RELVAL_X + t);
    digitalWrite(AXIS_LED_X, HIGH);
    tScaleX.ucIsRelative = 1;
  }
  if (bitRead(ucEepromConfig, BF_REL_Y))
  {
    for (unsigned int t = 0; t < sizeof(tScaleY.fRelativeVal); t++) *((char*)&tScaleY.fRelativeVal + t) = EEPROM.read(EE_RELVAL_Y + t);
    digitalWrite(AXIS_LED_Y, HIGH);
    tScaleY.ucIsRelative = 1;
  }
  if (bitRead(ucEepromConfig, BF_REL_Z))
  {
    for (unsigned int t = 0; t < sizeof(tScaleZ.fRelativeVal); t++) *((char*)&tScaleZ.fRelativeVal + t) = EEPROM.read(EE_RELVAL_Z + t);
    digitalWrite(AXIS_LED_Z, HIGH);
    tScaleZ.ucIsRelative = 1;
  }

  // Scale factors
  for (unsigned int t = 0; t < sizeof(tScaleX.fScaleFactorVal); t++) *((char*)&tScaleX.fScaleFactorVal + t) = EEPROM.read(EE_SCALEVAL_X + t);
  for (unsigned int t = 0; t < sizeof(tScaleY.fScaleFactorVal); t++) *((char*)&tScaleY.fScaleFactorVal + t) = EEPROM.read(EE_SCALEVAL_Y + t);
  for (unsigned int t = 0; t < sizeof(tScaleZ.fScaleFactorVal); t++) *((char*)&tScaleZ.fScaleFactorVal + t) = EEPROM.read(EE_SCALEVAL_Z + t);


  DBG_P(F("Done\n"));

  // Enable Maxim MAX7219
  _display_init();
  _display_data(ucDataToShow);

  DBG_P(F("Init done.\n"));
}

/**************************************************************************/
/*!
    @brief  Main loop
*/
/**************************************************************************/
void loop()
{

  // Read keypads and handle buttons
  _button_handle();

  // Handle encoder
  _encoder_handle();

  // Handle scale serial communication
  _serial_handle();

  // Check for new scale data and display it
  if (tScaleX.ucNewData)
  {
    _display_float(&lcDispX, tScaleX.fVal - tScaleX.fRelativeVal, 2);
    tScaleX.ucNewData = 0;
  }

  if (tScaleY.ucNewData)
  {
    _display_float(&lcDispY, tScaleY.fVal - tScaleY.fRelativeVal, 2);
    tScaleY.ucNewData = 0;
  }

  if (tScaleZ.ucNewData)
  {
    _display_float(&lcDispZ, tScaleZ.fVal - tScaleZ.fRelativeVal, 2);
    tScaleZ.ucNewData = 0;
  }

  // ISR timer flag is set
  if (bitRead(ucTimerInterruptMask, TIMER_UPDATE))
  {

    // animate status display - ucActionActive needs to be set to 2
    switch (ucActionActive)
    {
      case 0:
        lcDispSM.setRow(0, 7, 0); // turn off
        ucActionActive = 1; // turn off only once, avoid permanent overwrite of submenu display
        break;
      case 2:
      case 4:
      case 8:
      case 16:
      case 32:
        ucActionActive *= 2; // cycle through 7-segment-display bars
        lcDispSM.setRow(0, 7, ucActionActive);
        break;
      case 64:
        ucActionActive = 2; // repeat
        lcDispSM.setRow(0, 7, ucActionActive);
        break;
      default:
        break;
    }

    // Execute actions in variable timer intervals
    // if ((ucTimerExecutionCounter % uiVariableTimerInterval == 0)) {}

    // reset timer flag
    bitClear(ucTimerInterruptMask, TIMER_UPDATE);
  }
}
