/**************************************************************************/
/*!
    @brief  Display data
    @param  Number of current display to show
*/
/**************************************************************************/
void _display_data(unsigned char ucScreenNo)
{
  unsigned int uiTmpCur = 0;
  unsigned int uiTmpCount = 0;
  unsigned int uiTmp = 0;

  lcDispMM.clearMatrix();
  lcDispSM.clearMatrix();

  switch (ucScreenNo)
  {
    case 0: // Zero point
      lcDispMM.setChar(0, 7, 'n', false);
      lcDispMM.setChar(0, 6, 'u', false);
      lcDispMM.setChar(0, 5, 'l', false);
      lcDispMM.setChar(0, 4, 'l', false);
      lcDispMM.setChar(0, 3, 'p', false);
      lcDispMM.setChar(0, 2, 'k', false);
      lcDispMM.setChar(0, 1, 't', false);

      if (ucActionActive < 2) // (Only if no running action)
      {
        lcDispSM.setChar(0, 6, 'a', false);
        lcDispSM.setChar(0, 5, 'k', false);
        lcDispSM.setChar(0, 4, 't', false);
        lcDispSM.setChar(0, 3, 'i', false);
        lcDispSM.setChar(0, 2, 'v', false);
        lcDispSM.setDigit(0, 0, ucZeroPoint, false);
      }
      else
      {
        lcDispSM.setChar(0, 6, 'b', false);
        lcDispSM.setChar(0, 5, 'l', false);
        lcDispSM.setChar(0, 4, 'o', false);
        lcDispSM.setChar(0, 3, 'c', false);
        lcDispSM.setChar(0, 2, 'k', false);
        lcDispSM.setChar(0, 1, 'e', false);
        lcDispSM.setChar(0, 0, 'r', false);
      }
      break;
    case 1: // find center of path
      lcDispMM.setChar(0, 7, 'm', false);
      lcDispMM.setChar(0, 6, 'i', false);
      lcDispMM.setChar(0, 5, 't', false);
      lcDispMM.setChar(0, 4, 't', false);
      lcDispMM.setChar(0, 3, 'e', false);
      lcDispMM.setChar(0, 2, 'l', false);
      lcDispMM.setChar(0, 1, 'p', false);
      lcDispMM.setChar(0, 0, 't', false);

      // State of function (0=inactive, 1=first point, 2=second point, 3=result)
      switch (tCoP.ucState)
      {
        case 0: // Status of function
          if (ucActionActive < 2) // (Only if no running action)
          {
            lcDispSM.setChar(0, 6, 'i', false);
            lcDispSM.setChar(0, 5, 'n', false);
            lcDispSM.setChar(0, 4, 'a', false);
            lcDispSM.setChar(0, 3, 'k', false);
            lcDispSM.setChar(0, 2, 't', false);
            lcDispSM.setChar(0, 1, 'i', false);
            lcDispSM.setChar(0, 0, 'v', false);
          }
          else
          {
            lcDispSM.setChar(0, 6, 'b', false);
            lcDispSM.setChar(0, 5, 'l', false);
            lcDispSM.setChar(0, 4, 'o', false);
            lcDispSM.setChar(0, 3, 'c', false);
            lcDispSM.setChar(0, 2, 'k', false);
            lcDispSM.setChar(0, 1, 'e', false);
            lcDispSM.setChar(0, 0, 'r', false);
          }
          break;
        case 1: // running
          lcDispSM.setChar(0, 6, 'p', false);
          lcDispSM.setChar(0, 5, 'k', false);
          lcDispSM.setChar(0, 4, 't', false);
          switch (tCoP.uiCurrent) // check, which measurement of axis to take
          {
            case 0: // First measurement X
              lcDispSM.setChar(0, 1, 'x', false);
              lcDispSM.setDigit(0, 0, 1, false);
              break;
            case 1: // Second measurement X
              lcDispSM.setChar(0, 1, 'x', false);
              lcDispSM.setDigit(0, 0, 2, false);
              break;
            case 2: // First measurement Y
              lcDispSM.setChar(0, 1, 'y', false);
              lcDispSM.setDigit(0, 0, 1, false);
              break;
            case 3: // Second measurement Y
              lcDispSM.setChar(0, 1, 'y', false);
              lcDispSM.setDigit(0, 0, 2, false);
              break;
            default:
              break;
          }
          break;
        case 2: // finished
          lcDispSM.setChar(0, 6, 'f', false);
          lcDispSM.setChar(0, 5, 'e', false);
          lcDispSM.setChar(0, 4, 'r', false);
          lcDispSM.setChar(0, 3, 't', false);
          lcDispSM.setChar(0, 2, 'i', false);
          lcDispSM.setChar(0, 1, 'g', false);
          break;
        default:
          break;
      }
      break;
    case 2: // linear pattern (X and Y)
      lcDispMM.setChar(0, 7, 'm', false);
      lcDispMM.setChar(0, 6, 'u', false);
      lcDispMM.setChar(0, 5, 's', false);
      lcDispMM.setChar(0, 4, 't', false);

      lcDispMM.setChar(0, 2, 'l', false);
      lcDispMM.setChar(0, 1, 'i', false);
      lcDispMM.setChar(0, 0, 'n', false);

      // State of function (0=inactive, 1=first point, 2=second point, 3=result)
      switch (tLinP.ucState)
      {
        case 0: // Status of function
          if (ucActionActive < 2) // (Only if no running action)
          {
            lcDispSM.setChar(0, 6, 'i', false);
            lcDispSM.setChar(0, 5, 'n', false);
            lcDispSM.setChar(0, 4, 'a', false);
            lcDispSM.setChar(0, 3, 'k', false);
            lcDispSM.setChar(0, 2, 't', false);
            lcDispSM.setChar(0, 1, 'i', false);
            lcDispSM.setChar(0, 0, 'v', false);
          }
          else
          {
            lcDispSM.setChar(0, 6, 'b', false);
            lcDispSM.setChar(0, 5, 'l', false);
            lcDispSM.setChar(0, 4, 'o', false);
            lcDispSM.setChar(0, 3, 'c', false);
            lcDispSM.setChar(0, 2, 'k', false);
            lcDispSM.setChar(0, 1, 'e', false);
            lcDispSM.setChar(0, 0, 'r', false);
          }
          break;
        case 1: // running
          if (tLinP.uiCurrentNo == 0)
          {
            lcDispSM.setChar(0, 6, 'a', false);
            lcDispSM.setChar(0, 5, 'n', false);
            lcDispSM.setChar(0, 4, 'f', false);
            lcDispSM.setChar(0, 3, 'a', false);
            lcDispSM.setChar(0, 2, 'h', false);
            lcDispSM.setChar(0, 1, 'r', false);
            lcDispSM.setChar(0, 0, 't', false);
          }
          else
          {
            // summarize current and final number of iterations
            uiTmpCur = tLinP.uiCurrentNo;
            uiTmpCount = (tLinP.uiCountX * tLinP.uiCountY);

            lcDispSM.setDigit(0, 4, uiTmpCur % 10, false); uiTmpCur /= 10;
            lcDispSM.setDigit(0, 5, uiTmpCur % 10, false); uiTmpCur /= 10;
            lcDispSM.setDigit(0, 6, uiTmpCur % 10, false); uiTmpCur /= 10;
            lcDispSM.setRow(0, 3, B00100101); // slash symbol
            lcDispSM.setDigit(0, 0, uiTmpCount % 10, false); uiTmpCount /= 10;
            lcDispSM.setDigit(0, 1, uiTmpCount % 10, false); uiTmpCount /= 10;
            lcDispSM.setDigit(0, 2, uiTmpCount % 10, false); uiTmpCount /= 10;
          }
          break;
        /*
          case 2: // finished
          lcDispSM.setChar(0, 6, 'f', false);
          lcDispSM.setChar(0, 5, 'e', false);
          lcDispSM.setChar(0, 4, 'r', false);
          lcDispSM.setChar(0, 3, 't', false);
          lcDispSM.setChar(0, 2, 'i', false);
          lcDispSM.setChar(0, 1, 'g', false);
          break;
        */
        default:
          break;
      }
      break;
    case 3: // circular pattern
      lcDispMM.setChar(0, 7, 'm', false);
      lcDispMM.setChar(0, 6, 'u', false);
      lcDispMM.setChar(0, 5, 's', false);
      lcDispMM.setChar(0, 4, 't', false);

      lcDispMM.setChar(0, 2, 'k', false);
      lcDispMM.setChar(0, 1, 'r', false);
      lcDispMM.setChar(0, 0, 's', false);

      // State of function (0=inactive, 1=first point, 2=second point, 3=result)
      switch (tCirP.ucState)
      {
        case 0: // Status of function
          if (ucActionActive < 2) // (Only if no running action)
          {
            lcDispSM.setChar(0, 6, 'i', false);
            lcDispSM.setChar(0, 5, 'n', false);
            lcDispSM.setChar(0, 4, 'a', false);
            lcDispSM.setChar(0, 3, 'k', false);
            lcDispSM.setChar(0, 2, 't', false);
            lcDispSM.setChar(0, 1, 'i', false);
            lcDispSM.setChar(0, 0, 'v', false);
          }
          else
          {
            lcDispSM.setChar(0, 6, 'b', false);
            lcDispSM.setChar(0, 5, 'l', false);
            lcDispSM.setChar(0, 4, 'o', false);
            lcDispSM.setChar(0, 3, 'c', false);
            lcDispSM.setChar(0, 2, 'k', false);
            lcDispSM.setChar(0, 1, 'e', false);
            lcDispSM.setChar(0, 0, 'r', false);
          }
          break;
        case 1: // running
          if (tCirP.uiCurrent == 0)
          {
            lcDispSM.setChar(0, 6, 'a', false);
            lcDispSM.setChar(0, 5, 'n', false);
            lcDispSM.setChar(0, 4, 'f', false);
            lcDispSM.setChar(0, 3, 'a', false);
            lcDispSM.setChar(0, 2, 'h', false);
            lcDispSM.setChar(0, 1, 'r', false);
            lcDispSM.setChar(0, 0, 't', false);
          }
          else
          {
            // summarize current and final number of iterations
            uiTmpCur = tCirP.uiCurrent;
            uiTmpCount = tCirP.uiCount;

            lcDispSM.setDigit(0, 4, uiTmpCur % 10, false); uiTmpCur /= 10;
            lcDispSM.setDigit(0, 5, uiTmpCur % 10, false); uiTmpCur /= 10;
            lcDispSM.setDigit(0, 6, uiTmpCur % 10, false); uiTmpCur /= 10;
            lcDispSM.setRow(0, 3, B00100101); // slash symbol
            lcDispSM.setDigit(0, 0, uiTmpCount % 10, false); uiTmpCount /= 10;
            lcDispSM.setDigit(0, 1, uiTmpCount % 10, false); uiTmpCount /= 10;
            lcDispSM.setDigit(0, 2, uiTmpCount % 10, false); uiTmpCount /= 10;
          }
          break;
        /*
          case 2: // finished
          lcDispSM.setChar(0, 6, 'f', false);
          lcDispSM.setChar(0, 5, 'e', false);
          lcDispSM.setChar(0, 4, 'r', false);
          lcDispSM.setChar(0, 3, 't', false);
          lcDispSM.setChar(0, 2, 'i', false);
          lcDispSM.setChar(0, 1, 'g', false);
          break;
        */
        default:
          break;
      }
      break;
    case 4: // Setup
      lcDispMM.setChar(0, 7, 'e', false);
      lcDispMM.setChar(0, 6, 'i', false);
      lcDispMM.setChar(0, 5, 'n', false);
      lcDispMM.setChar(0, 4, 's', false);
      lcDispMM.setChar(0, 3, 't', false);
      lcDispMM.setChar(0, 2, 'l', false);
      lcDispMM.setChar(0, 1, 'l', false);
      lcDispMM.setChar(0, 0, 'g', false);

      if (ucActionActive < 2) // (Only if no running action)
      {
        lcDispSM.setChar(0, 6, 'o', false);
        lcDispSM.setChar(0, 5, 'e', false);
        lcDispSM.setChar(0, 4, 'f', false);
        lcDispSM.setChar(0, 3, 'f', false);
        lcDispSM.setChar(0, 2, 'n', false);
        lcDispSM.setChar(0, 1, 'e', false);
        lcDispSM.setChar(0, 0, 'n', false);
      }
      else
      {
        lcDispSM.setChar(0, 6, 'b', false);
        lcDispSM.setChar(0, 5, 'l', false);
        lcDispSM.setChar(0, 4, 'o', false);
        lcDispSM.setChar(0, 3, 'c', false);
        lcDispSM.setChar(0, 2, 'k', false);
        lcDispSM.setChar(0, 1, 'e', false);
        lcDispSM.setChar(0, 0, 'r', false);
      }
      break;
    default:
      break;
  }
}

/**************************************************************************/
/*!
    @brief  Display menu
    @param  Number of current setting to show
*/
/**************************************************************************/
void _display_setting(unsigned char ucSettingNo)
{

  unsigned int uiTmpCount = 0;
  unsigned int uiTmp = 0;

  lcDispMM.clearMatrix();
  lcDispSM.clearMatrix();

  switch (ucMenuLevel)
  {
    case 1:
      // show one bar if we are switching through the main menu
      lcDispMM.setRow(0, 7, B00001000);
      break;
    case 2:
      // show two bars if we are in the current parameters menu
      lcDispMM.setRow(0, 7, B00001001);
      break;
    default:
      break;
  }


  switch (ucDataToShow) // depends on current ucScreenNo
  {
    case 0: // Zero point
      switch (ucSettingNo)
      {
        case 0: // select zero point
          lcDispMM.setChar(0, 5, 'n', false);
          lcDispMM.setChar(0, 4, 'u', false);
          lcDispMM.setChar(0, 3, 'l', false);
          lcDispMM.setChar(0, 2, 'l', false);
          lcDispMM.setChar(0, 1, 'p', false);

          lcDispSM.setChar(0, 6, 'w', false);
          lcDispSM.setChar(0, 5, 'a', false);
          lcDispSM.setChar(0, 4, 'h', false);
          lcDispSM.setChar(0, 3, 'l', false);
          lcDispSM.setDigit(0, 0, ucZeroPoint, false);
          break;
        case 1: // save zero point
          lcDispMM.setChar(0, 5, 'n', false);
          lcDispMM.setChar(0, 4, 'u', false);
          lcDispMM.setChar(0, 3, 'l', false);
          lcDispMM.setChar(0, 2, 'l', false);
          lcDispMM.setChar(0, 1, 'p', false);

          lcDispSM.setChar(0, 6, 's', false);
          lcDispSM.setChar(0, 5, 'p', false);
          lcDispSM.setChar(0, 4, 'e', false);
          lcDispSM.setChar(0, 3, 'i', false);
          lcDispSM.setChar(0, 2, 'c', false);

          lcDispSM.setDigit(0, 0, ucZeroPoint, false);
          break;
        case 2: // abort
          lcDispMM.setChar(0, 5, 'a', false);
          lcDispMM.setChar(0, 4, 'b', false);
          lcDispMM.setChar(0, 3, 'b', false);
          lcDispMM.setChar(0, 2, 'r', false);
          lcDispMM.setChar(0, 1, 'c', false);
          lcDispMM.setChar(0, 0, 'h', false);
          break;
        default:
          break;
      }
      break;
    case 1: // find center of path
      switch (ucSettingNo)
      {
        case 0: // diameter
          lcDispMM.setChar(0, 5, 'd', false);
          lcDispMM.setChar(0, 4, 'u', false);
          lcDispMM.setChar(0, 3, 'r', false);
          lcDispMM.setChar(0, 2, 'c', false);
          lcDispMM.setChar(0, 1, 'h', false);
          lcDispMM.setChar(0, 0, 'm', false);

          _display_float(&lcDispSM, tCoP.fToolDia, 2);
          lcDispSM.setChar(0, 6, 'w', false);
          lcDispSM.setChar(0, 5, 'k', false);
          lcDispSM.setChar(0, 4, 'z', false);
          break;
        case 1: // run
          if (tCoP.ucState == 0) // State of function
          {
            lcDispMM.setChar(0, 5, 's', false);
            lcDispMM.setChar(0, 4, 't', false);
            lcDispMM.setChar(0, 3, 'a', false);
            lcDispMM.setChar(0, 2, 'r', false);
            lcDispMM.setChar(0, 1, 't', false);
          }
          else
          {
            lcDispMM.setChar(0, 5, 'f', false);
            lcDispMM.setChar(0, 4, 'o', false);
            lcDispMM.setChar(0, 3, 'r', false);
            lcDispMM.setChar(0, 2, 't', false);
            lcDispMM.setChar(0, 1, 's', false);
            lcDispMM.setChar(0, 0, 'z', false);
          }
          break;
        case 2: // stop
          lcDispMM.setChar(0, 5, 'a', false);
          lcDispMM.setChar(0, 4, 'b', false);
          lcDispMM.setChar(0, 3, 'b', false);
          lcDispMM.setChar(0, 2, 'r', false);
          lcDispMM.setChar(0, 1, 'c', false);
          lcDispMM.setChar(0, 0, 'h', false);
          break;
        default:
          break;
      }
      break;
    case 2: // linear pattern (X and Y)
      switch (ucSettingNo)
      {
        case 0: // length X
          lcDispMM.setChar(0, 5, 'l', false);
          lcDispMM.setChar(0, 4, 'a', false);
          lcDispMM.setChar(0, 3, 'e', false);
          lcDispMM.setChar(0, 2, 'n', false);
          lcDispMM.setChar(0, 1, 'g', false);
          lcDispMM.setChar(0, 0, 'e', false);

          _display_float(&lcDispSM, tLinP.fLengthX, 2);
          lcDispSM.setChar(0, 6, 'x', false);

          break;
        case 1: // count X
          lcDispMM.setChar(0, 5, 'a', false);
          lcDispMM.setChar(0, 4, 'n', false);
          lcDispMM.setChar(0, 3, 'z', false);
          lcDispMM.setChar(0, 2, 'a', false);
          lcDispMM.setChar(0, 1, 'h', false);
          lcDispMM.setChar(0, 0, 'l', false);

          lcDispSM.setChar(0, 6, 'x', false);
          uiTmpCount = tLinP.uiCountX;
          lcDispSM.setDigit(0, 0, uiTmpCount % 10, false); uiTmpCount /= 10;
          lcDispSM.setDigit(0, 1, uiTmpCount % 10, false); uiTmpCount /= 10;
          lcDispSM.setDigit(0, 2, uiTmpCount % 10, false); uiTmpCount /= 10;
          break;
        case 2: // length Y
          lcDispMM.setChar(0, 5, 'l', false);
          lcDispMM.setChar(0, 4, 'a', false);
          lcDispMM.setChar(0, 3, 'e', false);
          lcDispMM.setChar(0, 2, 'n', false);
          lcDispMM.setChar(0, 1, 'g', false);
          lcDispMM.setChar(0, 0, 'e', false);

          _display_float(&lcDispSM, tLinP.fLengthY, 2);
          lcDispSM.setChar(0, 6, 'y', false);
          break;
        case 3: // count Y
          lcDispMM.setChar(0, 5, 'a', false);
          lcDispMM.setChar(0, 4, 'n', false);
          lcDispMM.setChar(0, 3, 'z', false);
          lcDispMM.setChar(0, 2, 'a', false);
          lcDispMM.setChar(0, 1, 'h', false);
          lcDispMM.setChar(0, 0, 'l', false);

          lcDispSM.setChar(0, 6, 'y', false);
          uiTmpCount = tLinP.uiCountY;
          lcDispSM.setDigit(0, 0, uiTmpCount % 10, false); uiTmpCount /= 10;
          lcDispSM.setDigit(0, 1, uiTmpCount % 10, false); uiTmpCount /= 10;
          lcDispSM.setDigit(0, 2, uiTmpCount % 10, false); uiTmpCount /= 10;
          break;
        case 4: // run
          if (tLinP.ucState == 0) // State of function
          {
            lcDispMM.setChar(0, 5, 's', false);
            lcDispMM.setChar(0, 4, 't', false);
            lcDispMM.setChar(0, 3, 'a', false);
            lcDispMM.setChar(0, 2, 'r', false);
            lcDispMM.setChar(0, 1, 't', false);
          }
          else
          {
            lcDispMM.setChar(0, 5, 'f', false);
            lcDispMM.setChar(0, 4, 'o', false);
            lcDispMM.setChar(0, 3, 'r', false);
            lcDispMM.setChar(0, 2, 't', false);
            lcDispMM.setChar(0, 1, 's', false);
            lcDispMM.setChar(0, 0, 'z', false);
          }
          break;
        case 5: // stop
          lcDispMM.setChar(0, 5, 'a', false);
          lcDispMM.setChar(0, 4, 'b', false);
          lcDispMM.setChar(0, 3, 'b', false);
          lcDispMM.setChar(0, 2, 'r', false);
          lcDispMM.setChar(0, 1, 'c', false);
          lcDispMM.setChar(0, 0, 'h', false);
          break;
        default:
          break;
      }
      break;
    case 3: // circular pattern
      switch (ucSettingNo)
      {
        case 0: // radius
          lcDispMM.setChar(0, 5, 'r', false);
          lcDispMM.setChar(0, 4, 'a', false);
          lcDispMM.setChar(0, 3, 'd', false);
          lcDispMM.setChar(0, 2, 'i', false);
          lcDispMM.setChar(0, 1, 'u', false);
          lcDispMM.setChar(0, 0, 's', false);

          _display_float(&lcDispSM, tCirP.fRadius, 2);
          lcDispSM.setChar(0, 6, 'm', false);
          lcDispSM.setChar(0, 5, 'm', false);
          break;
        case 1: // number of points on circle
          lcDispMM.setChar(0, 5, 'a', false);
          lcDispMM.setChar(0, 4, 'n', false);
          lcDispMM.setChar(0, 3, 'z', false);
          lcDispMM.setChar(0, 2, 'a', false);
          lcDispMM.setChar(0, 1, 'h', false);
          lcDispMM.setChar(0, 0, 'l', false);

          lcDispSM.setChar(0, 6, 'p', false);
          lcDispSM.setChar(0, 5, 'k', false);
          lcDispSM.setChar(0, 4, 't', false);

          uiTmpCount = tCirP.uiCount;
          lcDispSM.setDigit(0, 0, uiTmpCount % 10, false); uiTmpCount /= 10;
          lcDispSM.setDigit(0, 1, uiTmpCount % 10, false); uiTmpCount /= 10;
          lcDispSM.setDigit(0, 2, uiTmpCount % 10, false); uiTmpCount /= 10;
          break;
        case 2: // angle offset
          lcDispMM.setChar(0, 5, 'v', false);
          lcDispMM.setChar(0, 4, 'e', false);
          lcDispMM.setChar(0, 3, 'r', false);
          lcDispMM.setChar(0, 2, 's', false);
          lcDispMM.setChar(0, 1, 't', false);
          lcDispMM.setChar(0, 0, 'z', false);

          _display_float(&lcDispSM, tCirP.fAngleOffset, 2);
          lcDispSM.setRow(0, 6, B01100011); // degree symbol
          break;
        case 3: // run
          if (tCirP.ucState == 0) // State of function
          {
            lcDispMM.setChar(0, 5, 's', false);
            lcDispMM.setChar(0, 4, 't', false);
            lcDispMM.setChar(0, 3, 'a', false);
            lcDispMM.setChar(0, 2, 'r', false);
            lcDispMM.setChar(0, 1, 't', false);
          }
          else
          {
            lcDispMM.setChar(0, 5, 'f', false);
            lcDispMM.setChar(0, 4, 'o', false);
            lcDispMM.setChar(0, 3, 'r', false);
            lcDispMM.setChar(0, 2, 't', false);
            lcDispMM.setChar(0, 1, 's', false);
            lcDispMM.setChar(0, 0, 'z', false);
          }
          break;
        case 4: // stop
          lcDispMM.setChar(0, 5, 'a', false);
          lcDispMM.setChar(0, 4, 'b', false);
          lcDispMM.setChar(0, 3, 'b', false);
          lcDispMM.setChar(0, 2, 'r', false);
          lcDispMM.setChar(0, 1, 'c', false);
          lcDispMM.setChar(0, 0, 'h', false);
          break;
        default:
          break;
      }
      break;
    case 4: // Setup
      switch (ucSettingNo)
      {
        case 0: // brightness
          lcDispMM.setChar(0, 5, 'h', false);
          lcDispMM.setChar(0, 4, 'e', false);
          lcDispMM.setChar(0, 3, 'l', false);
          lcDispMM.setChar(0, 2, 'l', false);
          lcDispMM.setChar(0, 1, 'i', false);
          lcDispMM.setChar(0, 0, 'g', false);

          lcDispSM.setChar(0, 6, 'w', false);
          lcDispSM.setChar(0, 5, 'e', false);
          lcDispSM.setChar(0, 4, 'r', false);
          lcDispSM.setChar(0, 3, 't', false);
          lcDispSM.setDigit(0, 0, ucLdBright, false);
          break;
        case 1: // set fast/slow mode on caliper
          lcDispMM.setChar(0, 5, 'm', false);
          lcDispMM.setChar(0, 4, 'o', false);
          lcDispMM.setChar(0, 3, 'd', false);
          lcDispMM.setChar(0, 2, 'u', false);
          lcDispMM.setChar(0, 1, 's', false);

          lcDispSM.setChar(0, 6, 'a', false);
          lcDispSM.setChar(0, 5, 'c', false);
          lcDispSM.setChar(0, 4, 'h', false);
          lcDispSM.setChar(0, 3, 's', false);
          lcDispSM.setChar(0, 2, 'e', false);

          switch (ucSelectedAxis)
          {
            case 0:
              lcDispSM.setChar(0, 0, 'x', false);
              break;
            case 1:
              lcDispSM.setChar(0, 0, 'y', false);
              break;
            case 2:
              lcDispSM.setChar(0, 0, 'z', false);
              break;
            default:
              break;
          }
          break;
        case 2: // set zero on caliper
          lcDispMM.setChar(0, 5, 'n', false);
          lcDispMM.setChar(0, 4, 'u', false);
          lcDispMM.setChar(0, 3, 'l', false);
          lcDispMM.setChar(0, 2, 'l', false);
          lcDispMM.setChar(0, 1, 'e', false);
          lcDispMM.setChar(0, 0, 'n', false);

          lcDispSM.setChar(0, 6, 'a', false);
          lcDispSM.setChar(0, 5, 'c', false);
          lcDispSM.setChar(0, 4, 'h', false);
          lcDispSM.setChar(0, 3, 's', false);
          lcDispSM.setChar(0, 2, 'e', false);

          switch (ucSelectedAxis)
          {
            case 0:
              lcDispSM.setChar(0, 0, 'x', false);
              break;
            case 1:
              lcDispSM.setChar(0, 0, 'y', false);
              break;
            case 2:
              lcDispSM.setChar(0, 0, 'z', false);
              break;
            default:
              break;
          }
          break;

        case 3: // scale factor x
          lcDispMM.setChar(0, 5, 's', false);
          lcDispMM.setChar(0, 4, 'k', false);
          lcDispMM.setChar(0, 3, 'a', false);
          lcDispMM.setChar(0, 2, 'l', false);
          lcDispMM.setChar(0, 0, 'x', false);

          // summarize current and final number of iterations
          uiTmp = tScaleX.fScaleFactorVal * 10000.0;

          if (uiTmp >= 10000)
          {
            lcDispSM.setRow(0, 4, B10110000); // one with dot
          }
          else
          {
            lcDispSM.setRow(0, 4, B11111110); // zero with dot
          }
          lcDispSM.setDigit(0, 0, uiTmp % 10, false); uiTmp /= 10;
          lcDispSM.setDigit(0, 1, uiTmp % 10, false); uiTmp /= 10;
          lcDispSM.setDigit(0, 2, uiTmp % 10, false); uiTmp /= 10;
          lcDispSM.setDigit(0, 3, uiTmp % 10, false); uiTmp /= 10;
          break;

        case 4: // scale factor y
          lcDispMM.setChar(0, 5, 's', false);
          lcDispMM.setChar(0, 4, 'k', false);
          lcDispMM.setChar(0, 3, 'a', false);
          lcDispMM.setChar(0, 2, 'l', false);
          lcDispMM.setChar(0, 0, 'y', false);

          // summarize current and final number of iterations
          uiTmp = tScaleY.fScaleFactorVal * 10000.0;

          if (uiTmp >= 10000)
          {
            lcDispSM.setRow(0, 4, B10110000); // one with dot
          }
          else
          {
            lcDispSM.setRow(0, 4, B11111110); // zero with dot
          }
          lcDispSM.setDigit(0, 0, uiTmp % 10, false); uiTmp /= 10;
          lcDispSM.setDigit(0, 1, uiTmp % 10, false); uiTmp /= 10;
          lcDispSM.setDigit(0, 2, uiTmp % 10, false); uiTmp /= 10;
          lcDispSM.setDigit(0, 3, uiTmp % 10, false); uiTmp /= 10;
          break;

        case 5: // scale factor z
          lcDispMM.setChar(0, 5, 's', false);
          lcDispMM.setChar(0, 4, 'k', false);
          lcDispMM.setChar(0, 3, 'a', false);
          lcDispMM.setChar(0, 2, 'l', false);
          lcDispMM.setChar(0, 0, 'z', false);

          // summarize current and final number of iterations
          uiTmp = tScaleZ.fScaleFactorVal * 10000.0;

          if (uiTmp >= 10000)
          {
            lcDispSM.setRow(0, 4, B10110000); // one with dot
          }
          else
          {
            lcDispSM.setRow(0, 4, B11111110); // zero with dot
          }
          lcDispSM.setDigit(0, 0, uiTmp % 10, false); uiTmp /= 10;
          lcDispSM.setDigit(0, 1, uiTmp % 10, false); uiTmp /= 10;
          lcDispSM.setDigit(0, 2, uiTmp % 10, false); uiTmp /= 10;
          lcDispSM.setDigit(0, 3, uiTmp % 10, false); uiTmp /= 10;
          break;

        case 6: // back
          lcDispMM.setChar(0, 5, 'a', false);
          lcDispMM.setChar(0, 4, 'b', false);
          lcDispMM.setChar(0, 3, 'b', false);
          lcDispMM.setChar(0, 2, 'r', false);
          lcDispMM.setChar(0, 1, 'c', false);
          lcDispMM.setChar(0, 0, 'h', false);
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}


/**************************************************************************/
/*!
    @brief  Init displays
*/
/**************************************************************************/
void _display_init()
{
  DBG_P(F("Init LED Display... "));

  //initilize a ledcontroller with a hardware spi and one row
  lcDispX.init(CS1);
  lcDispY.init(CS2);
  lcDispZ.init(CS3);
  lcDispMM.init(CS4);
  lcDispSM.init(CS5);

  // Set initial brightness
  lcDispX.setIntensity(ucLdBright);
  lcDispY.setIntensity(ucLdBright);
  lcDispZ.setIntensity(ucLdBright);
  lcDispMM.setIntensity(ucLdBright);
  lcDispSM.setIntensity(ucLdBright);

  //clear the matrix just to be sure there is nothing on it
  lcDispX.clearMatrix();
  lcDispY.clearMatrix();
  lcDispZ.clearMatrix();
  lcDispMM.clearMatrix();
  lcDispSM.clearMatrix();

  // Init axis description
  lcDispX.setChar(0, 7, 'x', false);
  lcDispY.setChar(0, 7, 'y', false);
  lcDispZ.setChar(0, 7, 'z', false);

  DBG_P(F("Done\n"));
}


/**************************************************************************/
/*!
    @brief  This function can display a float on a 7-Segment display.
            Inspired by https://noah1510.github.io/LedController/english/d5/ddd/7-_segment-_d_h_t-temp-humid_8ino-example.html
    @parm   the display to be used
    @parm   the value to display
    @parm   used to specify how many digits you want to after the decimal Place.
*/
/**************************************************************************/

void _display_float(LedController<1, 1> *lc, float fValue, unsigned int uiDecPlaces)
{
  const unsigned int uiMaxNoDisplay = 6; // The maximum number of digits the display is capable to display
  unsigned int uiTotalLength = 6; // The maximum number of digits used to display each float
  if (uiTotalLength < uiDecPlaces) return; // assertion

  // remove leading zeroes
  if (fValue < 0)
  {
    uiTotalLength = 7;
    // remove leading zeroes
    if (fValue > -1000) uiTotalLength = 6;
    if (fValue > -100) uiTotalLength = 5;
    if (fValue > -10) uiTotalLength = 4;
  }
  else
  {
    if (fValue < 1000) uiTotalLength = 5;
    if (fValue < 100) uiTotalLength = 4;
    if (fValue < 10) uiTotalLength = 3;
  }

  // clear unneeded digits
  for (unsigned int uiTemp = uiMaxNoDisplay; uiTemp >= uiTotalLength; uiTemp--) lc->setRow(0, uiTemp, 0x00);

  // Set minus symbol
  if (fValue < 0)
  {
    lc->setChar(0, uiTotalLength - 1, '-', false);
    uiTotalLength--;
  }

  // print values after comma digit per digit
  for (unsigned int uiTemp = 0; uiTemp < uiDecPlaces; uiTemp++) fValue *= 10.0f;

  // print value digit per digit
  unsigned int uiValue = (unsigned int) (fValue < 0 ? -fValue : fValue);
  for (unsigned int uiTemp = 0; uiTemp < uiTotalLength; uiTemp++)
  {
    lc->setDigit(0, uiTemp, uiValue % 10, uiTemp == uiDecPlaces);
    uiValue /= 10;
  }
}
