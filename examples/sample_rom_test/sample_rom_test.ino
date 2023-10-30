#include "CODBOTS_ROM.h"

CODBOTS_ROM rom;

#define ROM_WIFI_SSID 0
#define ROM_WIFI_PASSWORD 1
#define ROM_DATASET 2 

void setup() {
  Serial.begin(115200);
  rom.begin(10,4096);
  //rom.clearMemory();
  rom.createSlot(ROM_WIFI_SSID,16);
  rom.writeSlot("DJAY",ROM_WIFI_SSID);

  rom.createSlot(ROM_WIFI_PASSWORD,16);
  rom.writeSlot("andhrgsn#h123",ROM_WIFI_PASSWORD);

  byte dataset[17];
  //

  rom.createSlot(ROM_DATASET,17);
  //rom.writeSlot(dataset,ROM_DATASET);
  


  String ssid=rom.readValues(ROM_WIFI_SSID);
  Serial.println(ssid);

  String password=rom.readValues(ROM_WIFI_PASSWORD);
  Serial.println(password);

  rom.readValues(dataset,ROM_DATASET);
  for(int n=0;n<17;n++){
    Serial.println(String(n) + "(" + dataset[n] + ")");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
