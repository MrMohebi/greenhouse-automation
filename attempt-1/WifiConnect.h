

#ifndef ATTEMPT_1_CONNECTTOWIFI_H
#define ATTEMPT_1_CONNECTTOWIFI_H


IPAddress connectToWifi(char * ssid, char * pass){
    Serial.println();
    Serial.print("[WiFi] Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, pass);

    // Will try for about 10 seconds (20x 500ms)
    int tryDelay = 500;
    int numberOfTries = 20;

    // Wait for the WiFi event
    while (true) {
        switch(WiFi.status()) {
            case WL_DISCONNECTED:
                Serial.println("[WiFi] WiFi is disconnected");
                break;
            case WL_CONNECTED:
                Serial.println("[WiFi] WiFi is connected!");
                Serial.print("[WiFi] IP address: ");
                Serial.println(WiFi.localIP());
                return WiFi.localIP();
                break;
            default:
                Serial.print("[WiFi] WiFi Status: ");
                Serial.println(WiFi.status());
                break;
        }
        delay(tryDelay);

        if(numberOfTries <= 0){
            Serial.print("[WiFi] Failed to connect to WiFi!");
            WiFi.disconnect();
            return IPAddress{};
        } else {
            numberOfTries--;
        }
    }
}



#endif //ATTEMPT_1_CONNECTTOWIFI_H
