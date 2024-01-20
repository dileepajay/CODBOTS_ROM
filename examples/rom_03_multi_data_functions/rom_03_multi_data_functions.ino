#include <ii_ROM.h>

ii_ROM rom; // Create an instance of the ii_ROM class.

void setup()
{
  rom.begin(20, 4096); // Initialize ROM with larger data length and EEPROM size.

  // Create a slot for storing byte array.
  rom.createSlot(0, 10); // Slot 0 with length 10

  // Example byte array data.
  byte byteArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // Writing byte array to the slot.
  rom.write(byteArray, 10, 0); // Writing 10 bytes of byteArray to slot 0

  // Reading byte array from the slot.
  byte readArray[10];
  bool success = rom.read(readArray, 0); // Read into readArray from slot 0
  if (success)
  {
    for (int i = 0; i < 10; i++)
    {
      Serial.println(readArray[i]); // Print each byte
    }
  }
}

void loop()
{
  // Additional functionality can be added here.
}
