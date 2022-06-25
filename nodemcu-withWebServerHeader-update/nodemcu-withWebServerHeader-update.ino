#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define username "nodemcu"
#define password "abc123456"
#define LED D4
#define IB_LED D4

ESP8266WebServer server(80);
bool led_status = false;

void handleRoot () {
    String data;
    data = "<!DOCTYPE html>"
        "<html lang='en' dir='ltr'>"
        "<head>"
        "<meta charset='utf-8'>"
        "<title>ESP8266 LED program (async)</title>"
        "</head>"
        "<body>"
        "<h1>Turn On/Off LED using below program</h1>"
        "<button id='on' type='button'>Click-ON</button>"
        "<button id='off' type='button'>Click-OFF</button>"
        ""
        "<script type='text/javascript'>"
        "document.addEventListener('DOMContentLoaded', () => {"
        "const on = document.getElementById('on');"
        "const off = document.getElementById('off');"
        ""
        "on.addEventListener('click', (e) => {"
        "e.preventDefault();"
        "fetch('/ledon', (res) => {"
        "console.log(res.json());"
        "});"
        "});"
        ""
        "off.addEventListener('click', (e) => {"
        "e.preventDefault();"
        "fetch('/ledoff', (res) => {"
        "console.log(res.json());"
        "});"
        "});"
        "});"
        "</script>"
        "</body>"
        "</html>";
    server.send(200, "text/html", data);
}

void handleLEDon () {
    digitalWrite(LED, LOW);
    led_status = true;
    String s = led_status ? "ON" : "OFF";

    String data;
    data = "<DOCTYPE html>"
           "<html>"
           "<head><title>ESP Webserver.h</title></head>"
           "<body>"
           "<h1>ESP with WebServer.h library</h1>"
           "<p>LED IS ON</p>"
           "</body>"
           "</html>";
         
    server.send(200, "text/html", data);
}

void handleLEDoff () {
    digitalWrite(LED, HIGH);
    led_status = false;
    String s = led_status ? "ON" : "OFF";
    
    String data;
    data = "<DOCTYPE html>"
           "<html>"
           "<head><title>ESP Webserver.h</title></head>"
           "<body>"
           "<h1>ESP with WebServer.h library</h1>"
           "<p>LED IS OFF</p>"
           "</body>"
           "</html>";
    server.send(200, "text/html", data);
}

void setup() {
    Serial.begin(9600);
    WiFi.softAP(username, password);
    // WiFi.softAPConfig(local_ip, gateway, subnet);
    Serial.print("\nYOUR IP: ");
    Serial.print(WiFi.softAPIP());
    Serial.println();
    pinMode(LED, LOW);

    server.on("/", handleRoot);
    server.on("/ledon", handleLEDon);
    server.on("/ledoff", handleLEDoff);
    server.begin();
    Serial.println("Server started!");
    pinMode(IB_LED, OUTPUT);
    digitalWrite(IB_LED, LOW);
}

void loop() {
    server.handleClient();
}
