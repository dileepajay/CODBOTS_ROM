#include <ii_ROM.h>

// Define constants for different ROM data slots
#define ROM_USER_DATA 0
#define ROM_SYSTEM_DATA 1

ii_ROM rom; // Create an instance of the ii_ROM class

void setup() {
  Serial.begin(115200);
  rom.begin(20, 4096); // Initialize ROM with 20 data slots and 4096 bytes of EEPROM.

  // Create slots for user and system data
  rom.createSlot(ROM_USER_DATA, 20); // Slot for user data with a length of 20 bytes
  rom.createSlot(ROM_SYSTEM_DATA, 30); // Slot for system data with a length of 30 bytes

  // Write data to the slots only if they are empty
  if (rom.isEmpty(ROM_USER_DATA)) {
    rom.write("UserData123", ROM_USER_DATA);
  }
  if (rom.isEmpty(ROM_SYSTEM_DATA)) {
    rom.write("SystemData456", ROM_SYSTEM_DATA);
  }

  // Read and print the stored data
  String userData = rom.read(ROM_USER_DATA);
  String systemData = rom.read(ROM_SYSTEM_DATA);
  Serial.println("User Data: " + userData);
  Serial.println("System Data: " + systemData);

  // Print the entire ROM data for inspection
  Serial.println("Printing ROM content:");
  rom.print(0, 4096); // Print data from start to end of ROM

  // Clear specific slots or data areas if necessary
  rom.clear(ROM_USER_DATA); // Clear only the user data slot
  rom.clear(100, 200); // Clear a specific area in the ROM (from address 100 to 300)
}

void loop() {
  // Code for loop - this could include further data manipulation or periodic checks.
}
