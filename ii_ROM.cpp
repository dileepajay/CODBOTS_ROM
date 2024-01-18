#include "ii_ROM.h"

ii_ROM::ii_ROM() {}

/**
 * @brief Initializes the ii_ROM object.
 *
 * @param dataLen Size of datasets.
 * @param eepromSize ROM memory size in bytes.
 */
void ii_ROM::begin(int dataLen, int eepromSize)
{
  _eepromSize = eepromSize;
  _dataLen = dataLen;
  EEPROM.begin(_eepromSize);

  // Check if the ROM signature matches, clear memory if not.
  if (!checkSignature())
  {
    clearMemory();
  }
}

/**
 * @brief Copies ROM settings.
 *
 * @param dataLen Size of datasets.
 * @param eepromSize ROM memory size in bytes.
 */
void ii_ROM::copy(int dataLen, int eepromSize)
{
  _eepromSize = eepromSize;
  _dataLen = dataLen;

  // Check if the ROM signature matches, clear memory if not.
  if (!checkSignature())
  {
    clearMemory();
  }
}

/**
 * @brief Clears the entire ROM memory.
 */
void ii_ROM::clearMemory()
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

/**
 * @brief Clears a specified portion of the ROM memory.
 *
 * @param start Starting address.
 * @param length Length of the memory to clear.
 */
void ii_ROM::clearMemory(int start, int length)
{
  for (int n = start; n < start + length; n++)
  {
    EEPROM.write(n, 0);
  }
  EEPROM.commit();
}

/**
 * @brief Prints values from a specified range in the ROM memory to Serial.
 *
 * @param start Starting address.
 * @param end Ending address.
 */
void ii_ROM::print(int start, int end)
{
  for (int n = start; n < end; n++)
  {
    Serial.println(String(n) + "(" + String(EEPROM.read(n)) + ")");
  }
}

/**
 * @brief Checks if the ROM signature matches.
 *
 * @return true if the signature matches, false otherwise.
 */
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

/**
 * @brief Creates a slot in the ROM memory with specified length.
 *
 * @param slotindex Index of the slot.
 * @param length Length of the slot.
 */
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
  if (getSlotLength(slotindex) != (byte)length)
  {
    EEPROM.write(getSlotLenIndex(slotindex), (byte)length);
    clearMemory(getSlotStartIndex(slotindex), length);
    EEPROM.commit();
  }
}

/**
 * @brief Clears the content of a specified slot.
 *
 * @param slotindex Index of the slot.
 */
void ii_ROM::clearSlot(int slotindex)
{
  clearMemory(getSlotStartIndex(slotindex), getSlotLength(slotindex));
}

/**
 * @brief Gets the index in the EEPROM where the length of a slot is stored.
 *
 * @param slotindex Index of the slot.
 * @return Index in EEPROM.
 */
int ii_ROM::getSlotLenIndex(int slotindex)
{
  return lib_signature_len + slotindex;
}

/**
 * @brief Gets the length of a specified slot.
 *
 * @param slotindex Index of the slot.
 * @return Length of the slot.
 */
int ii_ROM::getSlotLength(int slotindex)
{
  return EEPROM.read(getSlotLenIndex(slotindex));
}

/**
 * @brief Gets the starting index in EEPROM where a slot begins.
 *
 * @param slotindex Index of the slot.
 * @return Starting index in EEPROM.
 */
int ii_ROM::getSlotStartIndex(int slotindex)
{
  int total = lib_signature_len + _dataLen;
  for (int n = 0; n < slotindex; n++)
  {
    total += EEPROM.read(getSlotLenIndex(slotindex));
  }
  return total;
}

/**
 * @brief Writes a String to a specified slot in the ROM memory.
 *
 * @param data String to write.
 * @param slotindex Index of the slot.
 */
void ii_ROM::writeSlot(String data, int slotindex)
{
  int startindex = getSlotStartIndex(slotindex);
  for (int i = 0; i < getSlotLength(slotindex); i++)
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

/**
 * @brief Writes an array of bytes to a specified slot in the ROM memory.
 *
 * @param data Array of bytes to write.
 * @param slotindex Index of the slot.
 */
void ii_ROM::writeSlot(byte data[], int slotindex)
{
  int elementCount = 17;

  int startindex = getSlotStartIndex(slotindex);
  for (int i = 0; i < getSlotLength(slotindex); i++)
  {
    if (i < elementCount)
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

/**
 * @brief Reads values from a specified slot in the ROM memory into an array of bytes.
 *
 * @param data Array to store the values.
 * @param slotindex Index of the slot.
 * @return true if values are available, false otherwise.
 */
bool ii_ROM::readValues(byte data[], int slotindex)
{
  int startAddress = getSlotStartIndex(slotindex);
  int endAddress = startAddress + getSlotLength(slotindex);
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

/**
 * @brief Reads values from a specified slot in the ROM memory as a String.
 *
 * @param slotindex Index of the slot.
 * @return String containing the values.
 */
String ii_ROM::readValues(int slotindex)
{
  int startAddress = getSlotStartIndex(slotindex);
  int endAddress = startAddress + getSlotLength(slotindex);
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

/**
 * @brief Checks if a specified slot in the ROM memory is empty.
 *
 * @param slotindex Index of the slot.
 * @return true if the slot is empty, false otherwise.
 */
bool ii_ROM::isEmpty(int slotindex)
{
  byte datset[getSlotLength(slotindex)];
  return readValues(datset, slotindex);
}
