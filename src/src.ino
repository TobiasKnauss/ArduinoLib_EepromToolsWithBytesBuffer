#include "EepromToolsWithBytesBuffer.h"

BytesBuffer* m_pBuffer = nullptr;

void setup ()
{
  //--------------------------------------------------------------------
  uint16_t address = 0;

  EepromToolsWithBytesBuffer::ReadBytesAndMovePtr (address, 2, m_pBuffer, false);

  EepromToolsWithBytesBuffer::WriteBytesAndMovePtr (address, 2, m_pBuffer, false);
}

void loop ()
{
}
