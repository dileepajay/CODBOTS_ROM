#ifndef ROMSLOT_h
#define ROMSLOT_h

#include <Arduino.h>

class ROMSLOT {
public:
  ROMSLOT();
  ROMSLOT(int start, int length);

  // Setters
  void setData(byte* data, int length);
  void setDataString(String str);
  void setDataStart(int start);      // Setter for data_start
  void setDataLength(int length);    // Setter for data_length

  // Getters
  byte* getData();
  int getDataStart();
  int getDataLength();
  String getString();

private:
  byte* data;
  int data_start;
  int data_length;
};

#endif
