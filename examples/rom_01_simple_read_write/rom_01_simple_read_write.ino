#include <ii_ROM.h>

ii_ROM rom; // Create an instance of the ii_ROM class.

void setup()
{
  Serial.begin(115200);
  // Initialize the ROM with a specific data length and EEPROM size.
  // This configuration depends on your specific hardware and requirements.
  rom.begin(10, 4096);

  // Create a slot in ROM to store data.
  // Slot index is set to 0 and the length of data to be stored is defined.
  rom.createSlot(0, 10);

  // Writing data to the slot.
  // Here, we're writing a simple string to slot 0.
  rom.write("Hello, ROM", 0);

  // Reading and printing data from the slot.
  // The data read from slot 0 is printed to the serial monitor.
  String data = rom.read(0);
  Serial.println(data);
}

void loop()
{
  // Regular operations or additional functionality can be added here.
}
