#include <WiFi.h>
#include "WifiConnect.h"
#include <Wire.h>
#include "DFRobot_SHT20.h"


char* ssid     = "zoodex";
char* password = "Zoodex@1234567890";

DFRobot_SHT20 sht20;


void setup()
{
    Wire.begin();
    Serial.begin(115200);
    delay(10);

    connectToWifi(ssid, password);

    // sht20.initSHT20(); // Init SHT20 Sensor
    // delay(100);
    // sht20.checkSHT20();

}

void loop()
{
 byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
      nDevices++;
    }
    else if (error==4) {
      Serial.print("Unknow error at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }
  delay(5000);     
}
