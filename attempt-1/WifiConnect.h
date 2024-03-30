

#ifndef WIFICONNECT_H
#define WIFICONNECT_H

#include <Arduino.h>
#include <WiFi.h>

IPAddress connectToWifi(const char * ssid, const char * pass);

#endif
