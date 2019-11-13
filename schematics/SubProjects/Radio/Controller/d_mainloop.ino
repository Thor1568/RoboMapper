
void loop() {
  joyX = analogRead(joyXPin);
  joyY = analogRead(joyYPin);
  joyB = digitalRead(joyBPin);

  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("OwO");
  delay(500);
}
