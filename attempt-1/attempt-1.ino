#include <WiFi.h>
#include <Wire.h>
// #include "DFRobot_SHT20.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
// #include <OneWire.h>
// #include <DallasTemperature.h>

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



#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// const int oneWireBus = 17; 
// OneWire oneWire(oneWireBus);
// DallasTemperature dsSensors(&oneWire);

// DFRobot_SHT20 sht20;


#define uint8_t 



// MServer mServer;

Triggers triggers[10];

void initVars(){
  triggers[0] = {"1", 1, 16, "", "air conditioner", 18.0, 20.0, 0x1, 0x0, 0};
  triggers[1] = {"2", 2, 15, "", "Humidifier", 80.0, 90.0, 0x1, 0x0, 0};
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

  Serial.begin(115200);delay(10);


  // connectToWifi(ssid, password);

  // sht20.initSHT20();
  // delay(100);
  // sht20.checkSHT20();

  dht.begin();

  // dsSensors.begin();

  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay();
  display.setTextColor(WHITE);


  // mServer.setBaseUrl("http://172.16.51.161:8005");
  // mServer.setToken("test1");

  initVars();

  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
}

void loop()
{
  // mServer.sendTempHum(sht20.readTemperature(), sht20.readHumidity());

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  displayTempAndHumidity(temperature, humidity);
  
  for (Triggers trigger : triggers) {
    if(trigger.name[0] != '\0'){
      // pinMode(trigger.pinNum, OUTPUT);
      Serial.println("-------------------------------------------");
      Serial.print("[TRIGGER] name => ");Serial.println(trigger.name);

      // cooler
      if(trigger.type == 1){
        if(!isnan(temperature)){
          Serial.print("[dht22] temp => ");Serial.println(temperature);
          bool A = temperature > trigger.min;
          bool B = temperature > trigger.max;
          bool C = digitalRead(trigger.pinNum) & 1;

          if((A && B) || (A && C)){
            digitalWrite(trigger.pinNum, trigger.activeState);
          }else{
            digitalWrite(trigger.pinNum, trigger.defaultState);
          }
        }
      }
      // humidifier
      if(trigger.type == 2){
        if(!isnan(humidity)){
          Serial.print("[dht22] humidity => ");Serial.println(humidity);
          bool A = humidity > trigger.min;
          bool B = humidity > trigger.max;
          bool C = digitalRead(trigger.pinNum) & 1;
          
          if((!B && C) || (!B && !A)){
            digitalWrite(trigger.pinNum, trigger.activeState);
          }else{
            digitalWrite(trigger.pinNum, trigger.defaultState);
          }

        }
        
      }
    }
  }


  delay(2000);   
}
