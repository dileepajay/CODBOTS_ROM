#ifndef ii_ROM_h
#define ii_ROM_h

#include <Arduino.h>
#include <EEPROM.h>
#include <ROMSLOT.h>

class ii_ROM
{
public:
  int _eepromSize; // rom memory size in bytes default : 4096
  int _dataLen;    // size of datasets example: 10

  // Constructor
  ii_ROM();

  /**
   * @brief Initializes the ROM library with specified parameters.
   *
   * @param dataLen Size of datasets (e.g., number of slots).
   * @param eepromSize Size of the EEPROM memory in bytes.
   */
  void begin(int dataLen, int eepromSize);

  /**
   * @brief Copies the specified parameters for internal use.
   *
   * @param dataLen Size of datasets.
   * @param eepromSize Size of the EEPROM memory in bytes.
   */
  void copy(int dataLen, int eepromSize);

  /**
   * @brief Creates a ROM slot at the specified index with a given length.
   *
   * @param slotindex Index of the ROM slot.
   * @param length Length of the ROM slot.
   */
  void createSlot(int slotindex, int length);

  /**
   * @brief Writes a String to the specified ROM slot.
   *
   * @param data String data to be written.
   * @param slotindex Index of the ROM slot.
   */
  void writeSlot(String data, int slotindex);

  /**
   * @brief Writes a byte array to the specified ROM slot.
   *
   * @param data Byte array data to be written.
   * @param slotindex Index of the ROM slot.
   */
  void writeSlot(byte data[], int slotindex);

  /**
   * @brief Clears the contents of the specified ROM slot.
   *
   * @param slotindex Index of the ROM slot to be cleared.
   */
  void clearSlot(int slotindex);

  /**
   * @brief Reads data from EEPROM at the specified address.
   *
   * @param address EEPROM memory address.
   * @return String containing the read data.
   */
  String read(int address);

  /**
   * @brief Checks if the EEPROM contains the library signature.
   *
   * @return True if the signature is present, false otherwise.
   */
  bool checkSignature();

  /**
   * @brief Clears the entire EEPROM memory.
   */
  void clearMemory();

  /**
   * @brief Clears a portion of the EEPROM memory.
   *
   * @param start Starting address to clear.
   * @param length Length of the memory to clear.
   */
  void clearMemory(int start, int length);

  /**
   * @brief Prints the contents of the EEPROM memory within the specified range.
   *
   * @param start Starting address for printing.
   * @param end Ending address for printing.
   */
  void print(int start, int end);

  /**
   * @brief Gets the length of the ROM slot at the specified index.
   *
   * @param slotindex Index of the ROM slot.
   * @return Length of the ROM slot.
   */
  int getSlotLength(int slotindex);

  /**
   * @brief Gets the length of the ROM slot index array.
   *
   * @param slotindex Index of the ROM slot.
   * @return Length of the ROM slot index array.
   */
  int getSlotLenIndex(int slotindex);

  /**
   * @brief Gets the starting index of the ROM slot at the specified index.
   *
   * @param slotindex Index of the ROM slot.
   * @return Starting index of the ROM slot.
   */
  int getSlotStartIndex(int slotindex);

  /**
   * @brief Reads values from EEPROM to a byte array at the specified slot index.
   *
   * @param data Byte array to store the read values.
   * @param slotindex Index of the ROM slot.
   * @return True if read successful, false otherwise.
   */
  bool readValues(byte data[], int slotindex);

  /**
   * @brief Reads values from EEPROM to a String at the specified slot index.
   *
   * @param slotindex Index of the ROM slot.
   * @return String containing the read values.
   */
  String readValues(int slotindex);

  /**
   * @brief Checks if the specified ROM slot is empty.
   *
   * @param slotindex Index of the ROM slot.
   * @return True if the ROM slot is empty, false otherwise.
   */
  bool isEmpty(int slotindex);

private:
  const int lib_signature_len = 4;
  int lib_signature[4] = {93, 10, 29, 0};
};

#endif
