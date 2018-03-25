#include "DHT.h"

const int DHTPin = 5;
#define DHTTYPE DHT11  
DHT dht(DHTPin, DHTTYPE);

void handleRoot() {
	
   static char celsiusTemp[7];
   static char fahrenheitTemp[7];
   static char humidityTemp[7];

   digitalWrite(ledGreen, LOW);
   digitalWrite(ledRed, LOW);
 
   dht.begin();
   String message = "";
   
    while (true) {
		float h = dht.readHumidity();
		float t = dht.readTemperature();
		float f = dht.readTemperature(true);
			if (isnan(h) || isnan(t) || isnan(f)) {      
			  strcpy(celsiusTemp,"Failed");
			  strcpy(fahrenheitTemp, "Failed");
			  strcpy(humidityTemp, "Failed");  
			  continue;      
			}

		float hic = dht.computeHeatIndex(t, h, false);      
		dtostrf(hic, 6, 2, celsiusTemp);            
		float hif = dht.computeHeatIndex(f, h);
		dtostrf(hif, 6, 2, fahrenheitTemp);        
		dtostrf(h, 6, 2, humidityTemp);
				  
		message = "temp by C* : ";
		message = message + celsiusTemp;
	 
		break;
	}
  server.send(200, "text/plain",  "Its work, after refactoring; " + message );
}