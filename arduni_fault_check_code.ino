void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  Serial.begin(9600);
  while(!Serial);   // GIGA needs this
}

void loop() {
  Serial.print("A=");
  Serial.print(digitalRead(2));
  Serial.print("  B=");
  Serial.println(digitalRead(3));
  delay(200);
}
