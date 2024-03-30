#include "server.h"


MServer::MServer(String base_url, String token)
{
  _base_url = base_url;
  _token = token;
}


String MServer::httpGETRequest(String path) {
  WiFiClient client;
  HTTPClient http;

  String serverName = _base_url + path;

  http.begin(client, serverName);
  
  http.addHeader("token", _token);

  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP to: ");
    Serial.print(path);
    Serial.print(" ==> ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}




void MServer::setBaseUrl(String base_url){
  _base_url = base_url;
}

void MServer::setToken(String token){
  _token = token;
}

bool MServer::sendTempHum(float temp, float humidity){
  String path = URL_UPDATE_TEMPHUM + "?temperature=" + String(temp) + "&humidity=" + String(humidity);
  
  httpGETRequest(path);

  return true;
} 