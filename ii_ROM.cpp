#include "ii_ROM.h"

ii_ROM::ii_ROM() {}

void ii_ROM::begin(int dataLen, int eepromSize)
{
  _eepromSize = eepromSize;
  _dataLen = dataLen;
  EEPROM.begin(_eepromSize);

  // Check if the ROM signature matches, clear memory if not.
  if (!checkSignature())
  {
    clear();
  }
}

void ii_ROM::copy(int dataLen, int eepromSize)
{
  _eepromSize = eepromSize;
  _dataLen = dataLen;

  if (!checkSignature())
  {
    clear();
  }
}

void ii_ROM::clear()
{
  // Write the library signature to the first 4 bytes.
  for (int n = 0; n < 4; n++)
  {
    EEPROM.write(n, lib_signature[n]);
  }

  Serial.println("ii_ROM: Clear memory");

  // Set the rest of the EEPROM to 0.
  for (int n = 4; n < _eepromSize; n++)
  {
    EEPROM.write(n, 0);
  }

  Serial.println("ii_ROM: Memory Cleared");
  EEPROM.commit();
}

void ii_ROM::clear(int start, int length)
{
  for (int n = start; n < start + length; n++)
  {
    EEPROM.write(n, 0);
  }
  EEPROM.commit();
}

void ii_ROM::print(int start, int end)
{
  for (int n = start; n < end; n++)
  {
    Serial.println(String(n) + "(" + String(EEPROM.read(n)) + ")");
  }
}

void ii_ROM::print(int slotindex)
{
  Serial.println(read(slotindex));
}

bool ii_ROM::checkSignature()
{
  lib_signature[3] = _dataLen;

  // Check if each byte of the signature matches.
  for (int n = 0; n < 4; n++)
  {
    if (EEPROM.read(n) != (byte)lib_signature[n])
    {
      Serial.println("ii_ROM: Signature unmatched!");
      return false;
    }
  }
  return true;
}

void ii_ROM::createSlot(int slotindex, int length)
{
  if (length > 255)
  {
    Serial.println("SLOTINDEX:" + String(slotindex) + " must be less than 255.");
    return;
  }
  if (slotindex > _dataLen)
  {
    Serial.println("SLOTINDEX:" + String(slotindex) + " must be less than _dataLen.");
    return;
  }

  // Update the slot length in the ROM memory.
  if (getLength(slotindex) != (byte)length)
  {
    EEPROM.write(getSlotLenIndex(slotindex), (byte)length);
    clear(getSlotStartIndex(slotindex), length);
    EEPROM.commit();
  }
}

void ii_ROM::clear(int slotindex)
{
  clear(getSlotStartIndex(slotindex), getLength(slotindex));
}

int ii_ROM::getSlotLenIndex(int slotindex)
{
  return lib_signature_len + slotindex;
}

int ii_ROM::getLength(int slotindex)
{
  return EEPROM.read(getSlotLenIndex(slotindex));
}

int ii_ROM::getSlotStartIndex(int slotindex)
{
  int total = lib_signature_len + _dataLen;
  for (int n = 0; n < slotindex; n++)
  {
    total += EEPROM.read(getSlotLenIndex(slotindex));
  }
  return total;
}

void ii_ROM::write(String data, int slotindex)
{
  int startindex = getSlotStartIndex(slotindex);
  for (int i = 0; i < getLength(slotindex); i++)
  {
    if (i < data.length())
    {
      EEPROM.write(startindex + i, data[i]);
    }
    else
    {
      EEPROM.write(startindex + i, 0); // Null-terminate the string
    }
  }
  EEPROM.commit();
}

void ii_ROM::write(byte data[], int datalength, int slotindex)
{

  int startindex = getSlotStartIndex(slotindex);
  for (int i = 0; i < getLength(slotindex); i++)
  {
    if (i < datalength)
    {
      EEPROM.write(startindex + i, data[i]);
    }
    else
    {
      EEPROM.write(startindex + i, 0); // Null-terminate the string
    }
  }
  EEPROM.commit();
}

bool ii_ROM::read(byte data[], int slotindex)
{
  int startAddress = getSlotStartIndex(slotindex);
  int endAddress = startAddress + getLength(slotindex);

  bool available = false;
  for (int i = startAddress; i < endAddress; i++)
  {
    data[i - startAddress] = EEPROM.read(i);
    if (data[i - startAddress] != 0)
    {
      available = true;
    }
  }
  return available;
}

String ii_ROM::read(int slotindex)
{
  int startAddress = getSlotStartIndex(slotindex);
  int endAddress = startAddress + getLength(slotindex);
  String data = "";

  for (int i = startAddress; i <= endAddress; i++)
  {
    byte v = EEPROM.read(i);
    if (v != 0)
    {
      data += (char)EEPROM.read(i);
    }
    else
    {
      return data;
    }
  }
  return data;
}

bool ii_ROM::isEmpty(int slotindex)
{
  byte datset[getLength(slotindex)];
  return !read(datset, slotindex);
}
