#include <WiFi.h>
#include <Wire.h>
#include "DFRobot_SHT20.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// #include "WifiConnect.h"
// #include "server.h"

#include "interfaces.h"

// const char* ssid = "zoodex-front";
// const char* password = "sigma-lifters-yohoho";

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define uint8_t 


DFRobot_SHT20 sht20;

// MServer mServer;

Triggers trigers[10];

void initVars(){
  trigers[0] = {"", 13, "", "air conditioner", 0, 22.0, true, false, 0};
  trigers[1] = {"", 14, "", "Humidifier", 70.0, 80.0, true, false, 0};
}


void displayTempAndHumidity(float temperature, float humidity){
  display.clearDisplay();
  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(String(temperature));
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(String(humidity));
  display.print(" %"); 
  
  display.display();
}


void setup()
{
  Wire.begin();

  Serial.begin(115200);
  delay(10);

  // connectToWifi(ssid, password);


  sht20.initSHT20();
  delay(100);
  sht20.checkSHT20();

  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(WHITE);


  // mServer.setBaseUrl("http://172.16.51.161:8005");
  // mServer.setToken("test1");

  pinMode(13, OUTPUT);

}

void loop()
{
  // mServer.sendTempHum(sht20.readTemperature(), sht20.readHumidity());

  displayTempAndHumidity(sht20.readTemperature(), sht20.readHumidity());
  


  delay(1000);   
}
