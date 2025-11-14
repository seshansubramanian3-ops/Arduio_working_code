const int pinA = 2;
const int pinB = 3;

int lastA = HIGH;
int lastB = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  Serial.println("Encoder Alive Test Started");
}

void loop() {
  int a = digitalRead(pinA);
  int b = digitalRead(pinB);

  if (a != lastA || b != lastB) {   // Detect any change
    Serial.println("Encoder is alive!");
    lastA = a;
    lastB = b;
  }
  delay(50);
}
