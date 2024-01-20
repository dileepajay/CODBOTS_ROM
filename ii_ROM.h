#ifndef ii_ROM_h
#define ii_ROM_h

#include <Arduino.h>
#include <EEPROM.h>
#include <ROMSLOT.h>

class ii_ROM
{
public:
  int _eepromSize; // Total size of the EEPROM in bytes (default: 4096 bytes).
  int _dataLen;    // Length of data sets (e.g., 10 bytes per set).

  // Default constructor for ii_ROM class.
  ii_ROM();

  // Initialize the ROM object with the number of data slots and the size of accessible ROM data.
  void begin(int dataLen, int eepromSize);

  // Create a specific data slot with an identity index (e.g., 0, 1, 2, ...) and its expected data length.
  void createSlot(int slotindex, int length);

  // Get the length of data stored in a specific slot.
  int getLength(int slotindex);

  // Write a String to a specific slot.
  void write(String data, int slotindex);

  // Write a byte array to a specific slot.
  // Ensure that the length of the data array matches the length of the slot.
  void write(byte data[], int datalength, int slotindex);

  // WARNING: Critical function - Clears all data in the ROM.
  void clear();

  // Clear data in a specific slot.
  void clear(int slotindex);

  // Clear a specific area in the ROM given by start and length parameters.
  void clear(int start, int length);

  // Check if a specific slot is empty.
  bool isEmpty(int slotindex);

  // Read data from a specific slot as a String.
  String read(int slotindex);

  // Read data from a specific slot into a provided byte array.
  // WARNING: Ensure that the length of the provided array equals the slot length.
  bool read(byte data[], int slotindex);

  // Print data in a specified range (start to end) of the ROM.
  void print(int start, int end);

  // Print data from a specific slot as a string.
  void print(int slotindex);

  // Check for the presence of a predefined signature in the ROM.
  bool checkSignature();

private:
  const int lib_signature_len = 4;        // Length of the library signature.
  int lib_signature[4] = {93, 10, 29, 0}; // Predefined library signature.

  // Get the index in EEPROM where the length of a slot is stored.
  int getSlotLenIndex(int slotindex);

  // Get the starting index in EEPROM of a particular slot.
  int getSlotStartIndex(int slotindex);

  // Copy constructor helper to set data length and EEPROM size.
  void copy(int dataLen, int eepromSize);
};

#endif
