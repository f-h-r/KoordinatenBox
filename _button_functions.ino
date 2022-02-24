/**************************************************************************/
/*!
    @brief  Handle buttons
*/
/**************************************************************************/
void _button_handle()
{
  char axis_key = axis_keypad.getKey();
  char main_key = main_keypad.getKey();
  char aux_key = aux_keypad.getKey();

  // Button handling for 6 keys beneath axis displays
  if (axis_key)
  {
    DBG_P(F("Axis key: "));
    DBG_P(axis_key);
    DBG_P(F("\n"));

    switch (axis_key)
    {
      case '1': // Zero X-Axis
        if (ucActionActive < 2) // (Only if no running action)
        {
          tScaleX.fVirtualZeroVal = tScaleX.fRealVal;
          for (unsigned int t = 0; t < sizeof(tScaleX.fVirtualZeroVal); t++) EEPROM.write(EE_VZEROVAL_X + t, *((char*)&tScaleX.fVirtualZeroVal + t));
        }
        break;
      case '2': // Zero Y-Axis
        if (ucActionActive < 2) // (Only if no running action)
        {
          tScaleY.fVirtualZeroVal = tScaleY.fRealVal;
          for (unsigned int t = 0; t < sizeof(tScaleY.fVirtualZeroVal); t++) EEPROM.write(EE_VZEROVAL_Y + t, *((char*)&tScaleY.fVirtualZeroVal + t));
        }
        break;
      case '3': // Zero Z-Axis
        tScaleZ.fVirtualZeroVal = tScaleZ.fRealVal;
        for (unsigned int t = 0; t < sizeof(tScaleZ.fVirtualZeroVal); t++) EEPROM.write(EE_VZEROVAL_Z + t, *((char*)&tScaleZ.fVirtualZeroVal + t));
        break;
      case 'x': // Abs/Rel X-Axis
        if (ucActionActive < 2) // (Only if no running action)
        {
          if (tScaleX.ucIsRelative == 0)
          {
            tScaleX.fRelativeVal = tScaleX.fVal;
            for (unsigned int t = 0; t < sizeof(tScaleX.fRelativeVal); t++) EEPROM.write(EE_RELVAL_X + t, *((char*)&tScaleX.fRelativeVal + t));
            bitSet(ucEepromConfig, BF_REL_X);
            EEPROM.write(EE_CONFIG, ucEepromConfig);
            digitalWrite(AXIS_LED_X, HIGH);
            tScaleX.ucIsRelative = 1;
          }
          else
          {
            tScaleX.fRelativeVal = 0.0;
            bitClear(ucEepromConfig, BF_REL_X);
            EEPROM.write(EE_CONFIG, ucEepromConfig);
            digitalWrite(AXIS_LED_X, LOW);
            tScaleX.ucIsRelative = 0;
          }
        }
        break;
      case 'y': // Abs/Rel Y-Axis
        if (ucActionActive < 2) // (Only if no running action)
        {
          if (tScaleY.ucIsRelative == 0)
          {
            tScaleY.fRelativeVal = tScaleY.fVal;
            for (unsigned int t = 0; t < sizeof(tScaleY.fRelativeVal); t++) EEPROM.write(EE_RELVAL_Y + t, *((char*)&tScaleY.fRelativeVal + t));
            bitSet(ucEepromConfig, BF_REL_Y);
            EEPROM.write(EE_CONFIG, ucEepromConfig);
            digitalWrite(AXIS_LED_Y, HIGH);
            tScaleY.ucIsRelative = 1;
          }
          else
          {
            tScaleY.fRelativeVal = 0.0;
            bitClear(ucEepromConfig, BF_REL_Y);
            EEPROM.write(EE_CONFIG, ucEepromConfig);
            digitalWrite(AXIS_LED_Y, LOW);
            tScaleY.ucIsRelative = 0;
          }
        }
        break;
      case 'z': // Abs/Rel Z-Axis
        if (tScaleZ.ucIsRelative == 0)
        {
          tScaleZ.fRelativeVal = tScaleZ.fVal;
          for (unsigned int t = 0; t < sizeof(tScaleZ.fRelativeVal); t++) EEPROM.write(EE_RELVAL_Z + t, *((char*)&tScaleZ.fRelativeVal + t));
          bitSet(ucEepromConfig, BF_REL_Z);
          EEPROM.write(EE_CONFIG, ucEepromConfig);
          digitalWrite(AXIS_LED_Z, HIGH);
          tScaleZ.ucIsRelative = 1;
        }
        else
        {
          tScaleZ.fRelativeVal = 0.0;
          bitClear(ucEepromConfig, BF_REL_Z);
          EEPROM.write(EE_CONFIG, ucEepromConfig);
          digitalWrite(AXIS_LED_Z, LOW);
          tScaleZ.ucIsRelative = 0;
        }
        break;
      default:
        break;
    }
  }


  // Button handling for main encoder
  if (main_key)
  {
    DBG_P(F("Main key\n"));
    DBG_P(F("S - ucMenuLevel: ")); DBG_P(ucMenuLevel); DBG_P(F("\n"));
    DBG_P(F("S - ucSettingsItem: ")); DBG_P(ucSettingsItem); DBG_P(F("\n"));
    DBG_P(F("S - ucDataToShow: ")); DBG_P(ucDataToShow); DBG_P(F("\n"));

    switch (ucMenuLevel) // Check for current menu level (0=normal display, 1=select item, 2=configure item)
    {
      case 0: // menu level 0 - default view
        switch (ucDataToShow) // depends on current ucScreenNo
        {
          case 0: // Zero point
            if (ucActionActive < 2)
            {
              ucMenuLevel = 1; // display setup menu items
              _display_setting(ucSettingsItem);
            }
            break;
          case 1: // find center of path
            if (tCoP.ucState > 0 || ucActionActive < 2)
            {
              ucMenuLevel = 1; // display setup menu items
              _display_setting(ucSettingsItem);
            }
            break;
          case 2: // linear pattern (X and Y)
            if (tLinP.ucState > 0 || ucActionActive < 2)
            {
              ucMenuLevel = 1; // display setup menu items
              _display_setting(ucSettingsItem);
            }
            break;
          case 3: // circular pattern
            if (tCirP.ucState > 0 || ucActionActive < 2)
            {
              ucMenuLevel = 1; // display setup menu items
              _display_setting(ucSettingsItem);
            }
            break;
          case 4: // Setup
            if (ucActionActive < 2)
            {
              ucMenuLevel = 1; // display setup menu items
              _display_setting(ucSettingsItem);
            }
            break;
          default:
            break;
        }
        break;
      case 1: // menu level 1 - item selection / functions
        switch (ucDataToShow) // depends on current ucScreenNo
        {
          case 0: // Zero point
            switch (ucSettingsItem)
            {
              case 2: // back
                ucMenuLevel = 0; // back to status
                ucSettingsItem = 0;
                ucDataToShow = 0;
                _display_data(ucDataToShow);
                break;
              default:
                ucMenuLevel = 2;
                _display_setting(ucSettingsItem);
                break;
            }
            break;
          case 1: // find center of path
            switch (ucSettingsItem)
            {
              case 1: // run
                if (ucActionActive < 2)  // (Only if no running action)
                {
                  if (tScaleX.ucIsRelative == 0 && tScaleY.ucIsRelative == 0 ) // Only if relative mode is off
                  {
                    tCoP.ucState = 1; // State of function (0=inactive, 1=first point, 2=second point, 3=finished)
                    ucActionActive = 2; // enable animation
                  }
                }
                ucMenuLevel = 0; // back to status
                ucSettingsItem = 0;
                ucDataToShow = 1;
                _display_data(ucDataToShow);
                break;
              case 2: // stop
                ucMenuLevel = 0; // back to status
                ucSettingsItem = 0;
                ucDataToShow = 1;
                tCoP.ucState = 0; // State of function (0=inactive, 1=first point, 2=second point, 3=finished)
                ucActionActive = 0; // disable animation
                _display_data(ucDataToShow);
                break;
              default:
                ucMenuLevel = 2;
                _display_setting(ucSettingsItem);
                break;
            }
            break;
          case 2: // linear pattern (X and Y)
            switch (ucSettingsItem)
            {
              case 4: // run
                if (ucActionActive < 2)  // (Only if no running action)
                {
                  if (tScaleX.ucIsRelative == 0 && tScaleY.ucIsRelative == 0 ) // Only if relative mode is off
                  {
                    tLinP.ucState = 1; // State of function (0=inactive, 1=running, 2=finished)
                    ucActionActive = 2; // enable animation
                  }
                }
                ucMenuLevel = 0; // back to status
                ucSettingsItem = 0;
                ucDataToShow = 2;
                _display_data(ucDataToShow);
                break;
              case 5: // stop
                ucMenuLevel = 0; // back to status
                ucSettingsItem = 0;
                ucDataToShow = 2;
                tLinP.ucState = 0; // State of function (0=inactive, 1=running, 2=finished)
                ucActionActive = 0; // disable animation
                _display_data(ucDataToShow);
                break;
              default:
                ucMenuLevel = 2;
                _display_setting(ucSettingsItem);
                break;
            }
            break;
          case 3: // circular pattern
            switch (ucSettingsItem)
            {
              case 3: // run
                if (ucActionActive < 2)  // (Only if no running action)
                {
                  if (tScaleX.ucIsRelative == 0 && tScaleY.ucIsRelative == 0 ) // Only if relative mode is off
                  {
                    tCirP.ucState = 1; // State of function (0=inactive, 1=running, 2=finished)
                    ucActionActive = 2; // enable animation
                  }
                }
                ucMenuLevel = 0; // back to status
                ucSettingsItem = 0;
                ucDataToShow = 3;
                _display_data(ucDataToShow);
                break;
              case 4: // stop
                ucMenuLevel = 0; // back to status
                ucSettingsItem = 0;
                ucDataToShow = 3;
                tCirP.ucState = 0; // State of function (0=inactive, 1=running, 2=finished)
                ucActionActive = 0; // disable animation
                _display_data(ucDataToShow);
                break;
              default:
                ucMenuLevel = 2;
                _display_setting(ucSettingsItem);
                break;
            }
            break;
          case 4: // Setup
            switch (ucSettingsItem)
            {
              case 6: // back
                ucMenuLevel = 0; // back to status
                ucSettingsItem = 0;
                ucDataToShow = 0;
                _display_data(ucDataToShow);
                break;
              default:
                ucMenuLevel = 2;
                _display_setting(ucSettingsItem);
                break;
            }
            break;
          default:
            break;
        }
        break;
      case 2: // menu level 2 - item configuration
        switch (ucDataToShow) // depends on current ucScreenNo
        {
          case 0: // Zero point
            switch (ucSettingsItem)
            {
              case 0: // 1 select zero point
                // load selected zero point values for all axis
                for (unsigned int t = 0; t < 4; t++)
                {
                  *((char*)&tScaleX.fVirtualZeroVal + t) = EEPROM.read((EE_ZP_TABLE + (12 * ucZeroPoint)) + t);
                  *((char*)&tScaleY.fVirtualZeroVal + t) = EEPROM.read((EE_ZP_TABLE + (12 * ucZeroPoint) + 4) + t);
                  *((char*)&tScaleZ.fVirtualZeroVal + t) = EEPROM.read((EE_ZP_TABLE + (12 * ucZeroPoint) + 8) + t);
                }
                EEPROM.write(EE_ZEROPOINT, ucZeroPoint);
                break;
              case 1: // 1 save zero point
                // save selected zero point values for all axis
                for (unsigned int t = 0; t < 4; t++)
                {
                  EEPROM.write((EE_ZP_TABLE + (12 * ucZeroPoint)) + t, *((char*)&tScaleX.fVirtualZeroVal + t));
                  EEPROM.write((EE_ZP_TABLE + (12 * ucZeroPoint) + 4) + t, *((char*)&tScaleY.fVirtualZeroVal + t));
                  EEPROM.write((EE_ZP_TABLE + (12 * ucZeroPoint) + 8) + t, *((char*)&tScaleZ.fVirtualZeroVal + t));
                }
                EEPROM.write(EE_ZEROPOINT, ucZeroPoint);
                break;
              default:
                break;
            }
            ucMenuLevel = 1; // back to display setup menu items
            break;
          case 1: // find center of path
            switch (ucSettingsItem)
            {
              case 0: // dia tool
                break;
              case 1: // run
                break;
              case 2: // stop
                break;
              default:
                break;
            }
            ucMenuLevel = 1; // back to display setup menu items
            break;
          case 2: // linear pattern (X and Y)
            switch (ucSettingsItem)
            {
              case 0: // length X
                break;
              case 1: // count X
                break;
              case 2: // length Y
                break;
              case 3: // count Y
                break;
              case 4: // run
                break;
              case 5: // stop
                break;
              default:
                break;
            }
            ucMenuLevel = 1; // back to display setup menu items
            break;
          case 3: // circular pattern
            switch (ucSettingsItem)
            {
              case 0: // radius
                break;
              case 1: // count
                break;
              case 2: // shift degree
                break;
              case 3: // run
                break;
              case 4: // stop
              default:
                break;
            }
            ucMenuLevel = 1; // back to display setup menu items
            break;
          case 4: // Setup
            switch (ucSettingsItem)
            {
              case 0: // save brightness
                EEPROM.write(EE_LEDBRIGHT, ucLdBright);
                break;
              case 1: // mode change for scale
                switch (ucSelectedAxis)
                {
                  case 0:
                    SCALE_X_SERIALPORT.print("m");
                    break;
                  case 1:
                    SCALE_Y_SERIALPORT.print("m");
                    break;
                  case 2:
                    SCALE_Z_SERIALPORT.print("m");
                    break;
                  default:
                    break;
                }
                break;
              case 2: // zero scale
                switch (ucSelectedAxis)
                {
                  case 0:
                    SCALE_X_SERIALPORT.print("z");
                    break;
                  case 1:
                    SCALE_Y_SERIALPORT.print("z");
                    break;
                  case 2:
                    SCALE_Z_SERIALPORT.print("z");
                    break;
                  default:
                    break;
                }
                break;
              case 3: // 3 save scale factor X
                for (unsigned int t = 0; t < sizeof(tScaleX.fScaleFactorVal); t++) EEPROM.write(EE_SCALEVAL_X + t, *((char*)&tScaleX.fScaleFactorVal + t));
                break;
              case 4: // 4 save scale factor Y
                for (unsigned int t = 0; t < sizeof(tScaleY.fScaleFactorVal); t++) EEPROM.write(EE_SCALEVAL_Y + t, *((char*)&tScaleY.fScaleFactorVal + t));
                break;
              case 5: // 5 save scale factor Z
                for (unsigned int t = 0; t < sizeof(tScaleZ.fScaleFactorVal); t++) EEPROM.write(EE_SCALEVAL_Z + t, *((char*)&tScaleZ.fScaleFactorVal + t));
                break;
              default:
                break;
            }
            ucMenuLevel = 1; // back to display setup menu items
            break;
          default:
            break;
        }
        _display_setting(ucSettingsItem);
        break;
      default:
        break;
    }
    DBG_P(F("E - ucMenuLevel: ")); DBG_P(ucMenuLevel); DBG_P(F("\n"));
    DBG_P(F("E - ucSettingsItem: ")); DBG_P(ucSettingsItem); DBG_P(F("\n"));
    DBG_P(F("E - ucDataToShow: ")); DBG_P(ucDataToShow); DBG_P(F("\n\n"));

  }

  // Button handling for aux encoder
  if (aux_key)
  {
    DBG_P(F("Aux key\n"));
    DBG_P(F("S - ucMenuLevel: ")); DBG_P(ucMenuLevel); DBG_P(F("\n"));
    DBG_P(F("S - ucSettingsItem: ")); DBG_P(ucSettingsItem); DBG_P(F("\n"));
    DBG_P(F("S - ucDataToShow: ")); DBG_P(ucDataToShow); DBG_P(F("\n"));

    switch (ucMenuLevel) // Check for current menu level (0=normal display, 1=select item, 2=configure item)
    {
      case 0: // menu level 0 - active functions
        switch (ucDataToShow) // depends on current ucScreenNo
        {
          case 1: // find center of path
            switch (tCoP.ucState) // State of function
            {
              case 1: // 1=running
                switch (tCoP.uiCurrent) // check, which measurement of axis to take
                {
                  case 0: // First measurement X
                    tCoP.fFirstXVal = tScaleX.fVal; // save first value X
                    tCoP.uiCurrent = 1;
                    break;
                  case 1: // Second measurement X
                    tCoP.fSecondXVal = tScaleX.fVal; // save second value X
                    tCoP.uiCurrent = 2;
                    break;
                  case 2: // First measurement Y
                    tCoP.fFirstYVal = tScaleY.fVal; // save first value Y
                    tCoP.uiCurrent = 3;
                    break;
                  case 3: // Second measurement Y, last cycle, claculate and show values
                    tCoP.fSecondYVal = tScaleY.fVal; // save second value Y
                    // tScaleX.fRelativeVal = tCoP.fFirstXVal - (tCoP.fSecondXVal / 2) - (tCoP.fToolDia / 2); // calculate center of X with tool
                    // tScaleY.fRelativeVal = tCoP.fFirstYVal - (tCoP.fSecondYVal / 2) - (tCoP.fToolDia / 2); // calculate center of Y with tool

                    tScaleX.fRelativeVal = (tCoP.fFirstXVal + tCoP.fSecondXVal) / 2; // calculate X
                    tScaleY.fRelativeVal = (tCoP.fFirstYVal + tCoP.fSecondYVal) / 2; // calculate Y

                    // enable relative mode on X
                    digitalWrite(AXIS_LED_X, HIGH);
                    tScaleX.ucIsRelative = 1;
                    // enable relative mode on Y
                    digitalWrite(AXIS_LED_Y, HIGH);
                    tScaleY.ucIsRelative = 1;
                    tCoP.ucState = 2; // finish
                  default:
                    break;
                }
                break;
              case 2: // 2=finished
                ucMenuLevel = 0; // back to status
                ucSettingsItem = 0;
                ucDataToShow = 1;
                tCoP.ucState = 0; // State of function (0=inactive, 1=first point, 2=second point, 3=finished)
                tCoP.uiCurrent = 0;
                ucActionActive = 0; // disable animation

                // disable relative mode on X
                digitalWrite(AXIS_LED_X, LOW);
                tScaleX.ucIsRelative = 0;
                tScaleX.fRelativeVal = 0.0;
                // disable relative mode on Y
                digitalWrite(AXIS_LED_Y, LOW);
                tScaleY.ucIsRelative = 0;
                tScaleY.fRelativeVal = 0.0;
                break;
              default:
                break;
            }
            _display_data(ucDataToShow);
            break;
          case 2: // linear pattern (X and Y)
            switch (tLinP.ucState) // State of function
            {
              case 1: // 1=running
                switch (tLinP.uiCurrentNo) // check, in which iteration we are
                {
                  case 0: // First iterarion, save axis values
                    tLinP.fStartPtX = tScaleX.fVal; // save start value X
                    tLinP.fStartPtY = tScaleY.fVal; // save start value Y

                    // first pattern starts at current (zero) position
                    tLinP.uiCurrentX = 0;
                    tLinP.uiCurrentY = 0;
                    tScaleX.fRelativeVal = tLinP.fStartPtX;
                    tScaleY.fRelativeVal = tLinP.fStartPtY;

                    // enable relative mode on X
                    digitalWrite(AXIS_LED_X, HIGH);
                    tScaleX.ucIsRelative = 1;
                    // enable relative mode on Y
                    digitalWrite(AXIS_LED_Y, HIGH);
                    tScaleY.ucIsRelative = 1;

                    tLinP.uiCurrentNo = 1; // set to next iteration
                    break;
                  default: // all other iterations
                    if (tLinP.uiCurrentNo < tLinP.uiCountX * tLinP.uiCountY) // running
                    {
                      if (tLinP.uiCurrentX < tLinP.uiCountX - 1) // We start at zero, therefore substract one cycle
                      {
                        tLinP.uiCurrentX++; // next column
                      }
                      else
                      {
                        tLinP.uiCurrentY++; // next row
                        tLinP.uiCurrentX = 0; // start column from beginning
                      }
                    }
                    else // last iteration
                    {
                      tLinP.ucState = 2; // finish linear pattern function
                    }

                    tScaleX.fRelativeVal = tLinP.fStartPtX + (tLinP.uiCurrentX * tLinP.fLengthX); // calculate X position
                    tScaleY.fRelativeVal = tLinP.fStartPtY + (tLinP.uiCurrentY * tLinP.fLengthY); // calculate Y position

                    tLinP.uiCurrentNo++; // set to next iteration
                    break;
                }
                break;
              case 2: // 2=finished
                ucMenuLevel = 0; // back to status
                ucSettingsItem = 0;
                ucDataToShow = 2;
                tLinP.ucState = 0; // State of function (0=inactive, 1=running, 2=finished)
                tLinP.uiCurrentNo = 0;
                ucActionActive = 0; // disable animation

                // disable relative mode on X
                digitalWrite(AXIS_LED_X, LOW);
                tScaleX.ucIsRelative = 0;
                tScaleX.fRelativeVal = 0.0;
                // disable relative mode on Y
                digitalWrite(AXIS_LED_Y, LOW);
                tScaleY.ucIsRelative = 0;
                tScaleY.fRelativeVal = 0.0;
                break;
              default:
                break;
            }
            _display_data(ucDataToShow);
            break;
          case 3: // circular pattern
            DBG_P(F("S - tCirP.uiCurrent: ")); DBG_P(tCirP.uiCurrent); DBG_P(F("\n"));
            DBG_P(F("S - tCirP.ucState: ")); DBG_P(tCirP.ucState); DBG_P(F("\n"));
            DBG_P(F("S - tCirP.fCurrentAngle: ")); DBG_P(tCirP.fCurrentAngle); DBG_P(F("\n"));
            float fTempDeg2Rad = 0.0;
            switch (tCirP.ucState) // State of function
            {
              case 1: // 1=running
                switch (tCirP.uiCurrent) // check, in which iteration we are
                {
                  case 0: // First iterarion, save axis values
                    tCirP.fStartPtX = tScaleX.fVal; // save start value X
                    tCirP.fStartPtY = tScaleY.fVal; // save start value Y

                    // first pattern starts at 0° position plus offset
                    tCirP.fCurrentAngle = 0.0;
                    fTempDeg2Rad = (tCirP.fCurrentAngle + tCirP.fAngleOffset) / 360 * 2 * M_PI; // convert degree to radiants
                    tScaleX.fRelativeVal = tCirP.fStartPtX + (tCirP.fRadius * cos(fTempDeg2Rad)); // calculate X position
                    tScaleY.fRelativeVal = tCirP.fStartPtY + (tCirP.fRadius * sin(fTempDeg2Rad)); // calculate Y position

                    // enable relative mode on X
                    digitalWrite(AXIS_LED_X, HIGH);
                    tScaleX.ucIsRelative = 1;
                    // enable relative mode on Y
                    digitalWrite(AXIS_LED_Y, HIGH);
                    tScaleY.ucIsRelative = 1;

                    tCirP.uiCurrent = 1; // set to next iteration
                    break;
                  default: // all other iterations
                    if (tCirP.uiCurrent < tCirP.uiCount) // running
                    {
                      tCirP.fCurrentAngle = ((360.0 / (float)tCirP.uiCount) * (float)tCirP.uiCurrent);
                    }
                    else // last iteration
                    {
                      tCirP.ucState = 2; // finish linear pattern function
                    }

                    fTempDeg2Rad = (tCirP.fCurrentAngle + tCirP.fAngleOffset) / 360 * 2 * M_PI; // convert degree to radiants
                    tScaleX.fRelativeVal = tCirP.fStartPtX + (tCirP.fRadius * cos(fTempDeg2Rad)); // calculate X position
                    tScaleY.fRelativeVal = tCirP.fStartPtY + (tCirP.fRadius * sin(fTempDeg2Rad)); // calculate Y position

                    tCirP.uiCurrent++; // set to next iteration
                    break;
                }
                break;
              case 2: // 2=finished
                ucMenuLevel = 0; // back to status
                ucSettingsItem = 0;
                ucDataToShow = 3;
                tCirP.ucState = 0; // State of function (0=inactive, 1=running, 2=finished)
                tCirP.uiCurrent = 0;
                ucActionActive = 0; // disable animation

                // disable relative mode on X
                digitalWrite(AXIS_LED_X, LOW);
                tScaleX.ucIsRelative = 0;
                tScaleX.fRelativeVal = 0.0;
                // disable relative mode on Y
                digitalWrite(AXIS_LED_Y, LOW);
                tScaleY.ucIsRelative = 0;
                tScaleY.fRelativeVal = 0.0;
                break;
              default:
                break;
            }
            DBG_P(F("E - tCirP.uiCurrent: ")); DBG_P(tCirP.uiCurrent); DBG_P(F("\n"));
            DBG_P(F("E - tCirP.ucState: ")); DBG_P(tCirP.ucState); DBG_P(F("\n"));
            DBG_P(F("E - tCirP.fCurrentAngle: ")); DBG_P(tCirP.fCurrentAngle); DBG_P(F("\n\n"));
            _display_data(ucDataToShow);
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
    DBG_P(F("E - ucMenuLevel: ")); DBG_P(ucMenuLevel); DBG_P(F("\n"));
    DBG_P(F("E - ucSettingsItem: ")); DBG_P(ucSettingsItem); DBG_P(F("\n"));
    DBG_P(F("E - ucDataToShow: ")); DBG_P(ucDataToShow); DBG_P(F("\n\n"));
  }
}


void _encoder_handle()
{
  // Handle encoder
  int main_newPos = main_encoder->getPosition();
  int aux_newPos = aux_encoder->getPosition();

  if (main_pos != main_newPos || aux_pos != aux_newPos)
  {
    DBG_P(F("Main p:"));
    DBG_P(main_newPos);
    DBG_P(F("\n"));
    DBG_P(F("Aux p:"));
    DBG_P(aux_newPos);
    DBG_P(F("\n"));
    DBG_P(F("S - ucMenuLevel: ")); DBG_P(ucMenuLevel); DBG_P(F("\n"));
    DBG_P(F("S - ucSettingsItem: ")); DBG_P(ucSettingsItem); DBG_P(F("\n"));
    DBG_P(F("S - ucDataToShow: ")); DBG_P(ucDataToShow); DBG_P(F("\n"));

    if (main_newPos > 0)
    {
      switch (ucMenuLevel) // Check for current menu
      {
        case 0: // menu level 0
          ucDataToShow < DATA_COUNT ? ucDataToShow++ : ucDataToShow = 0;
          _display_data(ucDataToShow);
          break;
        case 1: // menu level 1
          // scroll menus forward
          switch (ucDataToShow) // depends on current ucScreenNo
          {
            case 0: // Zero point
              ucSettingsItem < 2 ? ucSettingsItem++ : ucSettingsItem = 0;
              break;
            case 1: // find center of path
              ucSettingsItem < 2 ? ucSettingsItem++ : ucSettingsItem = 0;
              break;
            case 2: // linear pattern (X and Y)
              ucSettingsItem < 5 ? ucSettingsItem++ : ucSettingsItem = 0;
              break;
            case 3: // circular pattern
              ucSettingsItem < 4 ? ucSettingsItem++ : ucSettingsItem = 0;
              break;
            case 4: // Setup
              ucSettingsItem < 6 ? ucSettingsItem++ : ucSettingsItem = 0;
              break;
            default:
              break;
          }
          _display_setting(ucSettingsItem);
          break;
        case 2: // menu level 2
          if (ucActionActive < 2)  // (Only if no running action)
          {
            switch (ucDataToShow) // depends on current ucScreenNo
            {
              case 0: // Zero point
                switch (ucSettingsItem)
                {
                  case 0:
                  case 1:
                    ucZeroPoint < MAX_NO_OF_ZERO_POINTS ? ucZeroPoint++ : ucZeroPoint = 0;
                    break;
                  default:
                    break;
                }
                break;
              case 1: // find center of path
                switch (ucSettingsItem)
                {
                  case 0:
                    if (tCoP.fToolDia < 30.0) tCoP.fToolDia += 1.0;
                  default:
                    break;
                }
                break;
              case 2: // linear pattern (X and Y)
                switch (ucSettingsItem)
                {
                  case 0: // Length X
                    if (tLinP.fLengthX < 500.0) tLinP.fLengthX += 1.0;
                    break;
                  case 1: // Iterations X
                    if (tLinP.uiCountX < 100) tLinP.uiCountX += 1;
                    break;
                  case 2: // Length Y
                    if (tLinP.fLengthY < 500.0) tLinP.fLengthY += 1.0;
                    break;
                  case 3: // Iterations Y
                    if (tLinP.uiCountY < 100) tLinP.uiCountY += 1;
                    break;
                  default:
                    break;
                }
                break;
              case 3: // circular pattern
                switch (ucSettingsItem)
                {
                  case 0: // Radius
                    if (tCirP.fRadius < 400.0) tCirP.fRadius += 1.0;
                    break;
                  case 1: // Number of Points
                    if (tCirP.uiCount < 100) tCirP.uiCount += 1;
                    break;
                  case 2: // Angle offset
                    if (tCirP.fAngleOffset < 500.0) tCirP.fAngleOffset += 1.0;
                    break;
                  default:
                    break;
                }
                break;
              case 4: // Setup
                switch (ucSettingsItem)
                {
                  case 0:
                    // increase LED brightness
                    ucLdBright < 9 ? ucLdBright++ : ucLdBright = 0;
                    lcDispX.setIntensity(ucLdBright);
                    lcDispY.setIntensity(ucLdBright);
                    lcDispZ.setIntensity(ucLdBright);
                    lcDispMM.setIntensity(ucLdBright);
                    lcDispSM.setIntensity(ucLdBright);
                    break;
                  case 1:
                  case 2:
                    ucSelectedAxis < 2 ? ucSelectedAxis++ : ucSelectedAxis = 0;
                    break;
                  case 3:
                    tScaleX.fScaleFactorVal < 1.0049 ? tScaleX.fScaleFactorVal += 0.0001 : tScaleX.fScaleFactorVal = 1.005;
                    break;
                  case 4:
                    tScaleY.fScaleFactorVal < 1.0049 ? tScaleY.fScaleFactorVal += 0.0001 : tScaleY.fScaleFactorVal = 1.005;
                    break;
                  case 5:
                    tScaleZ.fScaleFactorVal < 1.0049 ? tScaleZ.fScaleFactorVal += 0.0001 : tScaleZ.fScaleFactorVal = 1.005;
                    break;
                  default:
                    break;
                }
                break;
              default:
                break;
            }
          }
          _display_setting(ucSettingsItem); // Wert der aktuellen Einstellung ausgeben
          break;
        default:
          break;
      }
    }
    else if (main_newPos < 0)
    {
      // Scroll backward
      switch (ucMenuLevel) // Check for current menu
      {
        case 0: // menu level 0
          // scroll menus backward
          ucDataToShow > 0 ? ucDataToShow-- : ucDataToShow = DATA_COUNT;
          _display_data(ucDataToShow);
          break;
        case 1: // menu level 1
          // scroll menus backward
          switch (ucDataToShow) // depends on current ucScreenNo
          {
            case 0: // Zero point
              ucSettingsItem > 0 ? ucSettingsItem-- : ucSettingsItem = 2;
              break;
            case 1: // find center of path
              ucSettingsItem > 0 ? ucSettingsItem-- : ucSettingsItem = 2;
              break;
            case 2: // linear pattern (X and Y)
              ucSettingsItem > 0 ? ucSettingsItem-- : ucSettingsItem = 5;
              break;
            case 3: // circular pattern
              ucSettingsItem > 0 ? ucSettingsItem-- : ucSettingsItem = 4;
              break;
            case 4: // Setup
              ucSettingsItem > 0 ? ucSettingsItem-- : ucSettingsItem = 6;
              break;
            default:
              break;
          }
          _display_setting(ucSettingsItem);
          break;
        case 2: // menu level 2
          if (ucActionActive < 2)  // (Only if no running action)
          {
            switch (ucDataToShow) // depends on current ucScreenNo
            {
              case 0: // Zero point
                switch (ucSettingsItem)
                {
                  case 0:
                  case 1:
                    ucZeroPoint > 0 ? ucZeroPoint-- : ucZeroPoint = MAX_NO_OF_ZERO_POINTS;
                    break;
                  default:
                    break;
                }
                break;
              case 1: // find center of path
                switch (ucSettingsItem)
                {
                  case 0:
                    if (tCoP.fToolDia > 1.1) tCoP.fToolDia -= 1.0;
                  default:
                    break;
                }
                break;
              case 2: // linear pattern (X and Y)
                switch (ucSettingsItem)
                {
                  case 0: // Length X
                    if (tLinP.fLengthX > 1.1) tLinP.fLengthX -= 1.0;
                    break;
                  case 1: // Iterations X
                    if (tLinP.uiCountX > 1) tLinP.uiCountX -= 1;
                    break;
                  case 2: // Length Y
                    if (tLinP.fLengthY > 1.1) tLinP.fLengthY -= 1.0;
                    break;
                  case 3: // Iterations Y
                    if (tLinP.uiCountY > 1) tLinP.uiCountY -= 1;
                    break;
                  default:
                    break;
                }
                break;
              case 3: // circular pattern
                switch (ucSettingsItem)
                {
                  case 0: // Radius
                    if (tCirP.fRadius > 1.1) tCirP.fRadius -= 1.0;
                    break;
                  case 1: // Number of Points
                    if (tCirP.uiCount > 1) tCirP.uiCount -= 1;
                    break;
                  case 2: // Angle offset
                    if (tCirP.fAngleOffset > 1.1) tCirP.fAngleOffset -= 1.0;
                    break;
                  default:
                    break;
                }
                break;
              case 4: // Setup
                switch (ucSettingsItem)
                {
                  case 0:
                    // increase LED brightness
                    // decrease LED brightness
                    ucLdBright > 0 ? ucLdBright-- : ucLdBright = 9;
                    lcDispX.setIntensity(ucLdBright);
                    lcDispY.setIntensity(ucLdBright);
                    lcDispZ.setIntensity(ucLdBright);
                    lcDispMM.setIntensity(ucLdBright);
                    lcDispSM.setIntensity(ucLdBright);
                    break;
                  case 1:
                  case 2:
                    ucSelectedAxis > 0 ? ucSelectedAxis-- : ucSelectedAxis = 2;
                    break;
                  case 3:
                    tScaleX.fScaleFactorVal > 0.995 ? tScaleX.fScaleFactorVal -= 0.0001 : tScaleX.fScaleFactorVal = 0.995;
                    break;
                  case 4:
                    tScaleY.fScaleFactorVal > 0.995 ? tScaleY.fScaleFactorVal -= 0.0001 : tScaleY.fScaleFactorVal = 0.995;
                    break;
                  case 5:
                    tScaleZ.fScaleFactorVal > 0.995 ? tScaleZ.fScaleFactorVal -= 0.0001 : tScaleZ.fScaleFactorVal = 0.995;
                    break;
                  default:
                    break;
                }
                break;
              default:
                break;
            }
          }
          _display_setting(ucSettingsItem); // Wert der aktuellen Einstellung ausgeben
          break;
        default:
          break;
      }
    }

    if (aux_newPos > 0)
    {
      // Scroll forward
      switch (ucMenuLevel) // Check for current menu
      {
        case 2: // menu level 2
          if (ucActionActive < 2)  // (Only if no running action)
          {
            switch (ucDataToShow) // depends on current ucScreenNo
            {
              case 1: // find center of path
                switch (ucSettingsItem)
                {
                  case 0:
                    if (tCoP.fToolDia < 30.0) tCoP.fToolDia += 0.01;
                  default:
                    break;
                }
                break;
              case 2: // linear pattern (X and Y)
                switch (ucSettingsItem)
                {
                  case 0: // Length X
                    if (tLinP.fLengthX < 500.0) tLinP.fLengthX += 0.01;
                    break;
                  case 2: // Length Y
                    if (tLinP.fLengthY < 500.0) tLinP.fLengthY += 0.01;
                    break;
                  default:
                    break;
                }
                break;
              case 3: // circular pattern
                switch (ucSettingsItem)
                {
                  case 0: // Radius
                    if (tCirP.fRadius < 400.0) tCirP.fRadius += 0.01;
                    break;
                  case 2: // Angle offset
                    if (tCirP.fAngleOffset < 500.0) tCirP.fAngleOffset += 0.01;
                    break;
                  default:
                    break;
                }
                break;
              default:
                break;
            }
          }
          _display_setting(ucSettingsItem); // Wert der aktuellen Einstellung ausgeben
          break;
        default:
          break;
      }
    }
    else if (aux_newPos < 0)
    {
      // Scroll backward
      switch (ucMenuLevel) // Check for current menu
      {
        case 2: // menu level 2
          if (ucActionActive < 2)  // (Only if no running action)
          {
            switch (ucDataToShow) // depends on current ucScreenNo
            {
              case 1: // find center of path
                switch (ucSettingsItem)
                {
                  case 0:
                    if (tCoP.fToolDia > 0.1) tCoP.fToolDia -= 0.01 ;
                  default:
                    break;
                }
                break;
              case 2: // linear pattern (X and Y)
                switch (ucSettingsItem)
                {
                  case 0: // Length X
                    if (tLinP.fLengthX > 0.1) tLinP.fLengthX -= 0.01;
                    break;
                  case 2: // Length Y
                    if (tLinP.fLengthY > 0.1) tLinP.fLengthY -= 0.01;
                    break;
                  default:
                    break;
                }
                break;
              case 3: // circular pattern
                switch (ucSettingsItem)
                {
                  case 0: // Radius
                    if (tCirP.fRadius > 0.1) tCirP.fRadius -= 0.01;
                    break;
                  case 2: // Angle offset
                    if (tCirP.fAngleOffset > 0.1) tCirP.fAngleOffset -= 0.01;
                    break;
                  default:
                    break;
                }
                break;
              default:
                break;
            }
          }
          _display_setting(ucSettingsItem); // Wert der aktuellen Einstellung ausgeben
          break;
        default:
          break;
      }
    }

    DBG_P(F("E - ucMenuLevel: ")); DBG_P(ucMenuLevel); DBG_P(F("\n"));
    DBG_P(F("E - ucSettingsItem: ")); DBG_P(ucSettingsItem); DBG_P(F("\n"));
    DBG_P(F("E - ucDataToShow: ")); DBG_P(ucDataToShow); DBG_P(F("\n\n"));

    main_encoder->setPosition(0);
    aux_encoder->setPosition(0);
    main_pos = 0;
    aux_pos = 0;
  }

}
