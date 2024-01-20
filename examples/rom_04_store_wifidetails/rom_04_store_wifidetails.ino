#include <ii_ROM.h>

// Define constants for the different ROM data slots
#define ROM_WIFI_SSID 0
#define ROM_WIFI_PASSWORD 1
#define ROM_DATASET 2

// ii_ROM class initialization
// This constructor initializes EEPROM with a length of 4096 bytes
// It also checks and sets the 0th index value to 64 (if it's not already 64)
// Addresses 1-64 are allocated for storing the length list of ROM data.
// This way, we can identify the length of the first ROM data, the start address of the second ROM data, etc.
// Data is stored after the 64th address.
ii_ROM rom;

void setup() {
  Serial.begin(115200);
  rom.begin(10, 4096); // Initialize the ROM with 10 data slots and 4096 bytes of EEPROM.

  // Create slots for storing WiFi SSID, password, and a data set.
  rom.createSlot(ROM_WIFI_SSID, 16); // Slot for WiFi SSID with a length of 16 bytes.
  rom.createSlot(ROM_WIFI_PASSWORD, 16); // Slot for WiFi password with a length of 16 bytes.
  rom.createSlot(ROM_DATASET, 17); // Slot for a data set with a length of 17 bytes.

  // Write default values to SSID and password slots if they are empty.
  if (rom.isEmpty(ROM_WIFI_SSID)) {
    rom.write("ii_wifi", ROM_WIFI_SSID); // Default SSID
  }
  if (rom.isEmpty(ROM_WIFI_PASSWORD)) {
    rom.write("ii12345", ROM_WIFI_PASSWORD); // Default password
  }

  // Example dataset to write to the ROM.
  byte dataset[17] = {2, 3, 44, 5, 2, 34, 4, 45, 87, 95, 123, 4, 5, 12, 34, 56, 78};
  rom.write(dataset, 17, ROM_DATASET); // Write the dataset to the ROM

  // Read and print the stored SSID and password.
  String ssid = rom.read(ROM_WIFI_SSID);
  String password = rom.read(ROM_WIFI_PASSWORD);
  Serial.println(ssid);
  Serial.println(password);

  // Read and print the dataset stored in the ROM.
  byte data[17];
  rom.read(data, ROM_DATASET);
  for (int n = 0; n < 17; n++) {
    Serial.print(data[n]);
    Serial.print(',');
  }

  // Clear the ROM data after usage.
  rom.clear();
}

void loop() {
  // Regular loop code or additional functionality goes here.
}
