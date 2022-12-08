#include <WiFi.h>

// ROTEADOR
#define rtrssid "iphone-de-mateus"
#define rtrpassword "0213122004"

//ESP WI-FI ACCESS POINT
#define apssid "esp32-beacon3"
#define appassword "12345678ab"

const String serverName = "http://10.254.17.92:8080/beacons";

String macAddress;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);

  WiFi.begin(rtrssid, rtrpassword);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("Connected to WiFi Network");

  WiFi.softAP(apssid, appassword, 1, 0, 4, true);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  macAddress = WiFi.macAddress();

  Serial.print("Beacon MacAddress: ");
  Serial.println(macAddress);
}

void loop() {

  

}