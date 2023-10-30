
#include "CODBOTS_ROM.h"

CODBOTS_ROM::CODBOTS_ROM() {}


void CODBOTS_ROM::begin(int dataLen,int eepromSize) {
  _eepromSize = eepromSize;
  _dataLen = dataLen;
  EEPROM.begin(_eepromSize);
  if(!checkSignature()){
    clearMemory();
  }
}
void CODBOTS_ROM::copy(int dataLen,int eepromSize) {
  _eepromSize = eepromSize;
  _dataLen = dataLen;
  if(!checkSignature()){
    clearMemory();
  }
}

void CODBOTS_ROM::clearMemory(){
  for (int n = 0; n < 4;n++){
    EEPROM.write(n, lib_signature[n]);
  }
  Serial.println("CODBOTS_ROM:Clear memory");

  for (int n = 4; n < _eepromSize;n++){
    EEPROM.write(n, 0);
  }
  Serial.println("CODBOTS_ROM:Memory Cleared");
  EEPROM.commit();
}
void CODBOTS_ROM::clearMemory(int start,int length){
  for (int n = start; n < start+length;n++){
    EEPROM.write(n, 0);
  }
  EEPROM.commit();
}

void CODBOTS_ROM::print(int start,int end){
  for (int n = start; n < end;n++){
    Serial.println(String(n) + "(" + String(EEPROM.read(n)) + ")");
  }
}

bool CODBOTS_ROM::checkSignature(){
  lib_signature[3] = _dataLen;
  for (int n = 0; n < 4;n++){
    if(EEPROM.read(n)!=(byte)lib_signature[n]){
      Serial.println("CODBOTS_ROM:Signature unmached!");
      return false;
    }
  }
  return true;
}

void CODBOTS_ROM::createSlot(int slotindex, int length){
  if(length>255){
    Serial.println("SLOTINDEX:" + String(slotindex) + " must less than 255.");
    return;
  }
  if(slotindex>_dataLen){
    Serial.println("SLOTINDEX:" + String(slotindex) + " must less _dataLen.");
    return;
  }
 
  if(getSlotLength(slotindex)!=(byte)length){
    EEPROM.write(getSlotLenIndex(slotindex), (byte)length);
    clearMemory(getSlotStartIndex(slotindex),length);
    EEPROM.commit();
  }
}

void CODBOTS_ROM::clearSlot(int slotindex){
  clearMemory(getSlotStartIndex(slotindex),getSlotLength(slotindex));
}

int CODBOTS_ROM::getSlotLenIndex(int slotindex){
  return lib_signature_len + slotindex;
}

int CODBOTS_ROM::getSlotLength(int slotindex){
  return EEPROM.read(getSlotLenIndex(slotindex));
}

int CODBOTS_ROM::getSlotStartIndex(int slotindex){
  int total=lib_signature_len+_dataLen;
  for (int n = 0; n < slotindex;n++){
    total += EEPROM.read(getSlotLenIndex(slotindex));
  }
  return total;
}

void CODBOTS_ROM::writeSlot(String data, int slotindex){
  int startindex = getSlotStartIndex(slotindex);
  for (int i = 0; i < getSlotLength(slotindex); i++) {
    if (i < data.length()) {
      EEPROM.write(startindex + i, data[i]);
    } else {
      EEPROM.write(startindex + i, 0);  // Null-terminate the string
    }
  }
  EEPROM.commit();
}

void CODBOTS_ROM::writeSlot(byte data[], int slotindex){
  int elementCount = 17;

  int startindex = getSlotStartIndex(slotindex);
  for (int i = 0; i < getSlotLength(slotindex); i++) {
    if (i < elementCount) {
      EEPROM.write(startindex + i, data[i]);
      //Serial.println(String(startindex + i) + "(" + String(data[i]) + ")");
    } else {
      EEPROM.write(startindex + i, 0);  // Null-terminate the string
    }
  }
  EEPROM.commit();
}

bool CODBOTS_ROM::readValues(byte data[],int slotindex) {
  int startAddress=getSlotStartIndex(slotindex);
  int endAddress=startAddress+getSlotLength(slotindex);
  bool available = false;
  for (int i = startAddress; i < endAddress; i++)
  {
    data[i - startAddress] = EEPROM.read(i);
    if(data[i - startAddress]!=0){
      available = true;
    }
    // Serial.println(String(i) + "(" + String(data[i - startAddress]) + ")");
  }
  return available;
}

String CODBOTS_ROM::readValues(int slotindex) {
  int startAddress=getSlotStartIndex(slotindex);
  int endAddress=startAddress+getSlotLength(slotindex);
  String data = "";
 
    for (int i = startAddress; i <= endAddress; i++) {
      byte v = EEPROM.read(i);
      if(v!=0){
        data+=(char)EEPROM.read(i);
      }else{
        return data;
      }
    }
     return data;
}
bool CODBOTS_ROM::isEmpty(int slotindex){
     byte datset[getSlotLength(slotindex)];
     return readValues(datset,slotindex);
}

/*
void CODBOTS_ROM::write(int address,byte value){

}

void CODBOTS_ROM::write(String data, int address, int maxlen) {
  for (int i = 0; i < maxlen; i++) {
    if (i < data.length()) {
      EEPROM.write(address + i, data[i]);
    } else {
      EEPROM.write(address + i, 0);  // Null-terminate the string
    }
  }
  EEPROM.commit();
}

String CODBOTS_ROM::read(int address) {
  String data = "";
  for (int i = 0; i < _eepromSize; i++) {
    char c = EEPROM.read(address + i);
    if (c == 0) {
      break;  // End of string
    }
    data += c;
  }
  return data;
}
*/