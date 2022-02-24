/**************************************************************************/
/*!
    @brief  Handle scale serial communication
*/
/**************************************************************************/
void _serial_handle()
{

  // X scale
  if (SCALE_X_SERIALPORT.available() > 0)
  {
    // get incoming byte:
    tScaleX.iInByte = SCALE_X_SERIALPORT.read();
    if (tScaleX.iInByte != 0xAA)
    {
      if (tScaleX.iByteCounter < 4)
      {
        tScaleX.ufValue.chrs[tScaleX.iByteCounter] = tScaleX.iInByte;
        tScaleX.iByteCounter++;
      }
      if (tScaleX.iByteCounter == 4)
      {
        tScaleX.iByteCounter = 0;
        tScaleX.fRealVal = (float)tScaleX.ufValue.lVal / 100;
        //tScaleX.fRealVal = tScaleX.fRealVal * tScaleX.fScaleFactorVal;  // Scale factor
        tScaleX.fVal = tScaleX.fRealVal - tScaleX.fVirtualZeroVal;
        tScaleX.fVal *= tScaleX.fScaleFactorVal;  // Scale factor
        tScaleX.ucNewData = 1;
      }
    }
    else
    {
      // find start of packet
      tScaleX.iByteCounter = 0;
    }
  }

  // Y scale
  if (SCALE_Y_SERIALPORT.available() > 0)
  {
    // get incoming byte:
    tScaleY.iInByte = SCALE_Y_SERIALPORT.read();
    if (tScaleY.iInByte != 0xAA)
    {
      if (tScaleY.iByteCounter < 4)
      {
        tScaleY.ufValue.chrs[tScaleY.iByteCounter] = tScaleY.iInByte;
        tScaleY.iByteCounter++;
      }
      if (tScaleY.iByteCounter == 4)
      {
        tScaleY.iByteCounter = 0;
        tScaleY.fRealVal = (float)tScaleY.ufValue.lVal / 100;
        //tScaleY.fRealVal = tScaleY.fRealVal * tScaleY.fScaleFactorVal;  // Scale factor
        tScaleY.fVal = tScaleY.fRealVal - tScaleY.fVirtualZeroVal;
        tScaleY.fVal *= tScaleY.fScaleFactorVal;  // Scale factor
        tScaleY.ucNewData = 1;
      }
    }
    else
    {
      // find start of packet
      tScaleY.iByteCounter = 0;
    }
  }

  // Z scale
  if (SCALE_Z_SERIALPORT.available() > 0)
  {
    // get incoming byte:
    tScaleZ.iInByte = SCALE_Z_SERIALPORT.read();
    if (tScaleZ.iInByte != 0xAA)
    {
      if (tScaleZ.iByteCounter < 4)
      {
        tScaleZ.ufValue.chrs[tScaleZ.iByteCounter] = tScaleZ.iInByte;
        tScaleZ.iByteCounter++;
      }
      if (tScaleZ.iByteCounter == 4)
      {
        tScaleZ.iByteCounter = 0;
        tScaleZ.fRealVal = (float)tScaleZ.ufValue.lVal / 100;
        //tScaleZ.fRealVal = tScaleZ.fRealVal * tScaleZ.fScaleFactorVal;  // Scale factor
        tScaleZ.fVal = tScaleZ.fRealVal - tScaleZ.fVirtualZeroVal;
        tScaleZ.fVal *= tScaleZ.fScaleFactorVal;  // Scale factor
        tScaleZ.ucNewData = 1;
      }
    }
    else
    {
      // find start of packet
      tScaleZ.iByteCounter = 0;
    }
  }
}
