#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include<ArduinoJson.h>

#define username "nodemcu"
#define password "abc123456"

ESP8266WebServer server(80);
StaticJsonDocument<200> json;

void rootHandler () { 
    String key = server.arg("pressed_key");    

    
    json["key"] = key;

   

    serializeJson(json, Serial);
    Serial.println();
}

void setup() {
    Serial.begin(9600);
    WiFi.softAP(username, password);
    Serial.println(WiFi.softAPIP());
    pinMode(D4, OUTPUT);

    server.begin();
    server.on("/", rootHandler); 
}

void loop() {
    server.handleClient();
     if (json["key"] == "circle") {
        digitalWrite(D4, LOW);
    } else if (json["key"] == "null") {
        digitalWrite(D4, HIGH);
    }
}
