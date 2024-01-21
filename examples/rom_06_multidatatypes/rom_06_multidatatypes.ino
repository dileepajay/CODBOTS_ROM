#include <ii_ROM.h>

ii_ROM rom;  // Create an instance of the ii_ROM class.

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud rate.

  // Initialize the ROM with 10 data slots and 4096 bytes of EEPROM space.
  rom.begin(10, 4096);

  // Create slots in the ROM for different data types.
  // The SIZE_* constants should be defined according to the size of each data type.
  rom.createSlot(0, SIZE_INT);     // Slot for an integer value
  rom.createSlot(1, SIZE_LONG);    // Slot for a long integer value
  rom.createSlot(2, SIZE_FLOAT);   // Slot for a float value
  rom.createSlot(3, SIZE_DOUBLE);  // Slot for a double value
  rom.createSlot(4, 16);           // Slot for a String with a maximum length of 16 characters

  // Define and initialize variables with sample data.
  int a = 26374;           // Sample integer
  long b = millis();       // Current time in milliseconds
  float c = 33.55f;     // Sample float
  double d = 1233.56;   // Sample double
  String e = "HELLO";      // Sample String

  // Writing data to the created slots in the ROM.
  rom.write(a, 0); // Write integer 'a' to slot 0
  rom.write(b, 1); // Write long 'b' to slot 1
  rom.write(c, 2); // Write float 'c' to slot 2
  rom.write(d, 3); // Write double 'd' to slot 3
  rom.write(e, 4); // Write String 'e' to slot 4

  // Reading and printing the data from each slot to the serial monitor.
  Serial.println(rom.readInt(0));    // Read and print integer from slot 0
  Serial.println(rom.readLong(1));   // Read and print long from slot 1
  Serial.println(rom.readFloat(2));  // Read and print float from slot 2
  Serial.println(rom.readDouble(3)); // Read and print double from slot 3
  Serial.println(rom.read(4));       // Read and print String from slot 4
}

void loop() {
  // Regular operations or additional functionality can be added here.
  // This sketch doesn't use the loop function.
}
