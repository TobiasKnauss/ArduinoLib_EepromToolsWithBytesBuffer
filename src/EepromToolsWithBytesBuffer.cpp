#include <EEPROM.h>
#include <FastCRC.h>

#include "EepromToolsWithBytesBuffer.h"

//--------------------------------------------------------------------
bool EepromToolsWithBytesBuffer::ReadBytesAndMovePtr (uint16_t&     io_Address,
                                                      uint16_t      i_ByteCount,
                                                      BytesBuffer*  i_pDestination,
                                                      bool          i_InvertByteOrder)
{
  if (i_pDestination == nullptr)
    return false;
  if (!EepromTools::CheckAddressRange (io_Address, i_ByteCount))
    return false;
  if (i_ByteCount == 0)
    return true;
  if (i_ByteCount > i_pDestination->get_Length ())
    return false;

  uint16_t bytesUntilEndInDestination = i_pDestination->get_Length () - i_pDestination->get_CurrentWriteAddress ();
  if (!i_pDestination->get_IsRingBuffer ()
  &&  i_ByteCount > bytesUntilEndInDestination)
    return false;

  if (i_InvertByteOrder)
  {
    for (uint16_t index = 1; index <= i_ByteCount; index++)
    {
      if (!i_pDestination->WriteValueAndMovePtr (EEPROM.read (io_Address + i_ByteCount - index)))
        return false;  // should not happen because of previous check
    }
    io_Address += i_ByteCount;
    return true;
  }

  for (uint16_t index = 0; index < i_ByteCount; index++)
  {
    if (!i_pDestination->WriteValueAndMovePtr (EEPROM.read (io_Address++)))
      return false;  // should not happen because of previous check
  }
  return true;
}

//--------------------------------------------------------------------
bool EepromToolsWithBytesBuffer::WriteBytesAndMovePtr ( uint16_t&     io_Address,
                                                        uint16_t      i_ByteCount,
                                                        BytesBuffer*  i_pSource,
                                                        bool          i_InvertByteOrder)
{
  if (i_pSource == nullptr)
    return false;
  if (!EepromTools::CheckAddressRange (io_Address, i_ByteCount))
    return false;
  if (i_ByteCount == 0)
    return true;
  if (i_ByteCount > i_pSource->get_Length ())
    return false;

  uint16_t bytesUntilEndInSource = i_pSource->get_Length () - i_pSource->get_CurrentReadAddress ();
  if (!i_pSource->get_IsRingBuffer ()
  &&  i_ByteCount > bytesUntilEndInSource)
    return false;

  if (i_InvertByteOrder)
  {
    for (uint16_t index = 1; index <= i_ByteCount; index++)
    {
      uint8_t valueUI8;
      if (!i_pSource->ReadValueAndMovePtr (valueUI8))
        return false;  // should not happen because of previous check
      EEPROM.update (io_Address + i_ByteCount - index, valueUI8);
    }
    io_Address += i_ByteCount;
    return true;
  }

  for (uint16_t index = 0; index < i_ByteCount; index++)
  {
    uint8_t valueUI8;
    if (!i_pSource->ReadValueAndMovePtr (valueUI8))
      return false;  // should not happen because of previous check
    EEPROM.update (io_Address++, valueUI8);
  }
  return true;
}
