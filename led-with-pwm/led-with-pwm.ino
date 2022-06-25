#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define username "nodemcu"
#define password "abc123456"
#define LED D5

ESP8266WebServer server(80);

void handleRoot () {
    String pwm_str = server.arg("pwm");
    int pwm = pwm_str.toInt();
    Serial.println(pwm_str);

    digitalWrite(LED, HIGH);
    analogWrite(LED, pwm);   

    server.send(200, "text/plain", String(pwm));
}


void setup() {
    Serial.begin(9600);
    WiFi.softAP(username, password);
    Serial.print("\nYOUR IP: ");
    Serial.print(WiFi.softAPIP());
    Serial.println();
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    server.on("/", handleRoot);
    server.begin();
    Serial.println("Server started!");
}

void loop() {
    server.handleClient();
}
