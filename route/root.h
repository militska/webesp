

void handleRoot() {
 digitalWrite(ledGreen, LOW);
 digitalWrite(ledRed, LOW);

dht.begin();
    String message = "";
    while (true) {
    float h = dht.readHumidity();
    // считываем температуру в Цельсиях (по умолчанию):
    float t = dht.readTemperature();
    // считываем температуру в Фаренгейтах
    // (isFahrenheit = true):
    float f = dht.readTemperature(true);
    // проверяем, корректны ли считанные данные,
    // и если нет, то выходим и начинаем заново:
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
                  // "Не удалось прочитать
                  // данные от датчика DHT"
      strcpy(celsiusTemp,"Failed");
      strcpy(fahrenheitTemp, "Failed");
      strcpy(humidityTemp, "Failed");  
      continue;      
    }

   // рассчитываем градусы в Цельсиях и Фаренгейтах,
              // а также влажность:
              float hic = dht.computeHeatIndex(t, h, false);      
              dtostrf(hic, 6, 2, celsiusTemp);            
              float hif = dht.computeHeatIndex(f, h);
              dtostrf(hif, 6, 2, fahrenheitTemp);        
              dtostrf(h, 6, 2, humidityTemp);

              
 message = "Temp by Celcies: ";
 message = message + celsiusTemp;
 
     break;
}
  server.send(200, "text/plain",  "Its work, after refactoring" + message );

}