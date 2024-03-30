#ifndef SERVER_H
#define SERVER_H

#include <HTTPClient.h>
#include <Arduino.h>

const String BASE_URL = "http://127.0.0.1:8005";

const String URL_UPDATE_TEMPHUM = "/update-temphum";


class MServer {
public:

  MServer(String base_url = BASE_URL, String token = "NOT_SET");
  void setBaseUrl(String base_url);
  void setToken(String token);
  bool sendTempHum(float temp, float humidity);

protected:
  String httpGETRequest(String path);
private:
  String _base_url;
  String _token;
};

#endif