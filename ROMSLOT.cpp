#include "ROMSLOT.h"

ROMSLOT::ROMSLOT() {
  data_start = 0;
  data_length = 0;
  data = nullptr;
}

ROMSLOT::ROMSLOT(int start, int length) {
  data_start = start;
  data_length = length;
  data = new byte[data_length];
}

void ROMSLOT::setData(byte* data, int length) {
  if (data != nullptr && length <= data_length) {
    memcpy(this->data, data, length);
  }
}

void ROMSLOT::setDataString(String str) {
  if (data != nullptr) {
    str.getBytes(data, data_length);
  }
}

void ROMSLOT::setDataStart(int start) {
  data_start = start;
}

void ROMSLOT::setDataLength(int length) {
  data_length = length;
  delete[] data;  // Release the old data and allocate new memory
  data = new byte[data_length];
}

byte* ROMSLOT::getData() {
  return data;
}

int ROMSLOT::getDataStart() {
  return data_start;
}

int ROMSLOT::getDataLength() {
  return data_length;
}

String ROMSLOT::getString() {
  if (data != nullptr) {
    return String(reinterpret_cast<char*>(data));
  }
  return "";
}
