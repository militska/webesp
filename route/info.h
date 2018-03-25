void info(){
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);

  server.send(200, "text/plain", "this works as well"); 
}

