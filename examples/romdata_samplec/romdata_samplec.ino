#include <CODBOTS_ROM.h>

#define ROM_WIFI_SSID 0
#define ROM_WIFI_PASSWORD 1
#define ROM_DATASET 2 

/*
in this constructor initialize EEPROM.h for 4096 length
Wtite 0th index value 64, if its not 64
1-64 addresses allocate for store length list of ROMDATA,
then we can identify length of first ROMDATA, 2nd ROM data start address and length
ex: 64,16,16,64,....
after 64th address store ROMData data[] values 
*/
CODBOTS_ROM rom;


void setup() {
  rom.createSlot(ROMDATA(ROM_WIFI_SSID,16));
  if(rom.isEmpty()){
    rom.write(ROM_WIFI_SSIDROM_WIFI_SSID,"DJAY");
  }

  rom.createSlot(ROMDATA(ROM_WIFI_PASSWORD,16));
  if(rom.isEmpty()){
    rom.write(ROM_WIFI_SSIDROM_WIFI_SSID,"Ashder#");
  }

  rom.createSlot(ROMDATA(ROM_DATASET,64));

  byte dataset[]={2,3,44,5,2,34,4,445,87,95,123,4,5};
  rom.write(ROM_DATASET,dataset);




  String ssid=rom.getString(ROM_WIFI_SSID);
  String password=rom.getString(ROM_WIFI_PASSWORD);
  byte data[]=rom.getBytes(ROM_DATASET);

  Serial.println(ssid);
  Serial.println(password);

  for(int n=0;n<sizeOf(data);n++){
    Serial.print(data[n]);
    Serial.print(',');
  }

  rom.clear(ROM_DATASET);

}

void loop() {
  
}
