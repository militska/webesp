#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "DHT.h"


const int ledGreen = 2;
const int ledRed = 14;
const int DHTPin = 5;



ESP8266WebServer server(80);

#define DHTTYPE DHT11  
DHT dht(DHTPin, DHTTYPE);

  
static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];
#include "config/connect.h"
#include "route/root.h"
#include "route/info.h"
#include "route/not_found.h"

  


void handleNotFound(){
   digitalWrite(ledRed, HIGH);
   digitalWrite(ledGreen, LOW);

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


void inlineUrl(){
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);

  server.send(200, "text/plain", "this works as well"); 
}

void setup(void){

  pinMode(ledGreen, OUTPUT); 
  pinMode(ledRed, OUTPUT); 
    dht.begin();

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  route();
  server.begin();
}



void route(){
  server.on("/", handleRoot);
  server.on("/inline", inlineUrl);
  server.onNotFound(handleNotFound);
}

void loop(void){
  server.handleClient();
}


