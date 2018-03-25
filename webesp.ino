#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);

const int ledGreen = 2;
const int ledRed = 14;

#include "config/connect.h"
#include "route/root.h"
#include "route/info.h"
#include "route/not_found.h"

void setup(void){
  pinMode(ledGreen, OUTPUT); 
  pinMode(ledRed, OUTPUT); 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  route();
  server.begin();
}


void route(){
  server.on("/", handleRoot);
  server.on("/info", info);
  server.onNotFound(handleNotFound);
}

void loop(void){
  server.handleClient();
}


