
#ifndef CODBOTS_ROM_h
#define CODBOTS_ROM_h

#include <Arduino.h>
#include <EEPROM.h>
#include <ROMSLOT.h>

class CODBOTS_ROM {
public:
    int _eepromSize;// rom memory size in bytes default : 4096
  int _dataLen;// size of datasets example: 10  

  CODBOTS_ROM();

  void begin(int dataLen,int eepromSize);
  void copy(int dataLen, int eepromSize);
  void createSlot(int slotindex, int length);

  void writeSlot(String data, int slotindex);
  void writeSlot(byte data[], int slotindex);
  void clearSlot(int slotindex);


  String read(int address);
  bool checkSignature();
  void clearMemory();
  void clearMemory(int start, int length);
  void print(int start,int end);

  int getSlotLength(int slotindex);
  int getSlotLenIndex(int slotindex);
  int getSlotStartIndex(int slotindex);

  bool readValues(byte data[],int slotindex) ;
  String readValues(int slotindex) ;
  bool isEmpty(int slotindex);

private:

  const int lib_signature_len = 4;
int lib_signature[4] = {93, 10, 29, 0};

};

#endif
