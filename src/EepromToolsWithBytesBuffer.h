#ifndef EepromToolsWithBytesBuffer_h
#define EepromToolsWithBytesBuffer_h

#include <Arduino.h>

#include <EepromTools.h>
#include <BytesBuffer.h>

class EepromToolsWithBytesBuffer
{
private:

  EepromToolsWithBytesBuffer () = delete;

public:

  // Read the specified number of bytes from the EEPROM to the given destination buffer and move the address forward.
  static bool ReadBytesAndMovePtr ( uint16_t&     io_Address,
                                    uint16_t      i_ByteCount,
                                    BytesBuffer*  i_pDestination,
                                    bool          i_InvertByteOrder);

  // Write the specified number of bytes from the given source buffer to the EEPROM and move the address forward.
  static bool WriteBytesAndMovePtr (uint16_t&     io_Address,
                                    uint16_t      i_ByteCount,
                                    BytesBuffer*  i_pSource,
                                    bool          i_InvertByteOrder);
};

#endif
