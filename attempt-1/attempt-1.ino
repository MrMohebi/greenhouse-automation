#include <WiFi.h>
#include <Wire.h>
// #include "DFRobot_SHT20.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// #include "WifiConnect.h"
// #include "server.h"

#include "interfaces.h"


// const char* ssid = "zoodex-front";
// const char* password = "-------";

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int oneWireBus = 17; 
OneWire oneWire(oneWireBus);
DallasTemperature dsSensors(&oneWire);

// DFRobot_SHT20 sht20;


#define uint8_t;


#define PIN_AIRCONDITIONER_ABI 14
#define PIN_AIRCONDITIONER_GAZI 27
#define PIN_HUMIDIFIER_DISKY 26
#define PIN_HUMIDIFIER_PUMPY 25
#define PIN_WATER_PUMP 33


// MServer mServer;

Triggers triggers[10];

void initVars(){
  triggers[0] = {"11", 1, 12, "", "outer temp", 20.0, 22.0, 0x0, 0x1, 0};
  triggers[1] = {"22", 2, 26, "", "Humidifier", 65.0, 75.0, 0x0, 0x1, 0};
  // triggers[2] = {"33", 3, 18, "", "inner temp", 23.0, 25.0, 0x1, 0x0, 0};
}


void displayTempAndHumidity(float temperature, float humidity);



void setup()
{
  Wire.begin();

  Serial.begin(115200);delay(10);


  // connectToWifi(ssid, password);

  // sht20.initSHT20();
  // delay(100);
  // sht20.checkSHT20();

  dht.begin();

  dsSensors.begin();

  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay();
  display.setTextColor(WHITE);

  // mServer.setBaseUrl("http://172.16.51.161:8005");
  // mServer.setToken("test1");

  initVars();

  pinMode(PIN_AIRCONDITIONER_ABI, OUTPUT);
  pinMode(PIN_AIRCONDITIONER_GAZI, OUTPUT);
  pinMode(PIN_HUMIDIFIER_DISKY, OUTPUT);
  pinMode(PIN_HUMIDIFIER_PUMPY, OUTPUT);
  pinMode(PIN_WATER_PUMP, OUTPUT);

  digitalWrite(PIN_AIRCONDITIONER_ABI, triggers[0].defaultState);
  digitalWrite(PIN_AIRCONDITIONER_GAZI, triggers[0].defaultState);
  digitalWrite(PIN_HUMIDIFIER_DISKY, triggers[0].defaultState);
  digitalWrite(PIN_HUMIDIFIER_PUMPY, triggers[0].defaultState);
  digitalWrite(PIN_WATER_PUMP, triggers[0].defaultState);
  
  
}

void loop()
{
  // mServer.sendTempHum(sht20.readTemperature(), sht20.readHumidity());

  dsSensors.requestTemperatures();

  float temperatureInner = dsSensors.getTempCByIndex(0);
  float temperatureOuter = dht.readTemperature();


  float humidity = dht.readHumidity();

  displayTempAndHumidity(temperatureOuter, humidity);
  
  for (Triggers trigger : triggers) {
    if(trigger.name[0] != '\0'){
      // pinMode(trigger.pinNum, OUTPUT);
      Serial.println("-------------------------------------------");
      Serial.print("[TRIGGER] name => ");Serial.println(trigger.name);

      // cooler outer temp
      if(trigger.type == 1){
        if(!isnan(temperatureOuter)  && temperatureOuter > 0 && temperatureOuter  < 110){
          Serial.print("[dht22] temp outer => ");Serial.println(temperatureOuter);
          bool A = temperatureOuter > trigger.min;
          bool B = temperatureOuter > trigger.max;
          bool C = digitalRead(PIN_AIRCONDITIONER_ABI) == trigger.activeState;

          if((A && B) || (A && C) || B){
            digitalWrite(PIN_AIRCONDITIONER_ABI, trigger.activeState);
            Serial.println("[dht22] temp outer => active air conditioner");
          }else{
            digitalWrite(PIN_AIRCONDITIONER_ABI, trigger.defaultState);
          }
        }
      }

      // cooler inner temp
      // if(trigger.type == 3){
      //   if(!isnan(temperatureInner)  && temperatureInner > 0 && temperatureInner  < 110){
      //     Serial.print("[ds18b20] temp inner => ");Serial.println(temperatureInner);
      //     bool A = temperatureInner > trigger.min;
      //     bool B = temperatureInner > trigger.max;
      //     bool C = digitalRead(trigger.pinNum) & 1;

      //     if((A && B) || (A && C) || B){
      //       digitalWrite(trigger.pinNum, trigger.activeState);
      //       Serial.println("[ds18b20] temp inner => active air conditioner");
      //     }else{
      //       digitalWrite(trigger.pinNum, trigger.defaultState);
      //     }
      //   }
      // }

      // humidifier
      if(trigger.type == 2){
        if(!isnan(humidity) && humidity > 0 && humidity  < 110){
          Serial.print("[dht22] humidity => ");Serial.println(humidity);
          bool A = humidity > trigger.min;
          bool B = humidity > trigger.max;
          bool C = digitalRead(PIN_HUMIDIFIER_PUMPY) == trigger.activeState;
          
          if((!B && C) || (!B && !A)){
            digitalWrite(PIN_HUMIDIFIER_DISKY, trigger.activeState);
            digitalWrite(PIN_HUMIDIFIER_PUMPY, trigger.activeState);
            Serial.println("[dht22] humidity => active Humidifier");
          }else{
            digitalWrite(PIN_HUMIDIFIER_DISKY, trigger.defaultState);
            digitalWrite(PIN_HUMIDIFIER_PUMPY, trigger.defaultState);
          }

        }
        
      }
    }
  }


  delay(2000);   
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

