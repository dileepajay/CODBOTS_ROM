#include <ii_ROM.h>

ii_ROM rom; // Create an instance of the ii_ROM class.

void setup()
{
  rom.begin(10, 4096); // Initialize ROM with data length and EEPROM size.

  // Create multiple slots in the ROM for storing different data sets.
  rom.createSlot(0, 10); // Slot 0 with length 10
  rom.createSlot(1, 15); // Slot 1 with length 15

  // Writing different data to the slots.
  rom.write("Data for slot 0", 0);           // Writing to slot 0
  rom.write("Different data for slot 1", 1); // Writing to slot 1

  // Reading and printing data from the slots.
  String data0 = rom.read(0); // Read from slot 0
  String data1 = rom.read(1); // Read from slot 1
  Serial.println(data0);
  Serial.println(data1);
}

void loop()
{
  // Code for loop, if required.
}
