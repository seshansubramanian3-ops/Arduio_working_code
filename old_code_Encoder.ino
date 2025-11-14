const int pinA = 2;    // Encoder Channel A
const int pinB = 3;    // Encoder Channel B

volatile long encoderCount = 0;  // Tick count
int lastA = 0;
int lastB = 0;

const int PPR = 600;                 // Pulses per revolution
const int COUNTS_PER_REV = PPR * 4;  // 4x quadrature decoding

float lastAngle = 0;

void setup() {
  Serial.begin(9600);

  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  lastA = digitalRead(pinA);
  lastB = digitalRead(pinB);

  attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), updateEncoder, CHANGE);

  Serial.println("Pulley rotation measurement ready...");
}

// ------------------ Quadrature ISR ------------------
void updateEncoder() {
  int a = digitalRead(pinA);
  int b = digitalRead(pinB);

  if (a != lastA || b != lastB) {
    if (lastA == a) {
      // B changed → direction depends on A
      if (a == b) encoderCount++;
      else encoderCount--;
    } else {
      // A changed → direction depends on B
      if (a != b) encoderCount++;
      else encoderCount--;
    }
  }

  lastA = a;
  lastB = b;
}

// ------------------ Main loop ------------------
void loop() {
  static long lastCount = 0;
  long count;

  noInterrupts();
  count = encoderCount;
  interrupts();

  if (count != lastCount) {
    // Total cumulative rotation in degrees
    float totalAngle = ((float)count / COUNTS_PER_REV) * 360.0;

    // Delta angle since last reading
    float deltaAngle = totalAngle - lastAngle;

    Serial.print("Delta Angle: ");
    Serial.print(deltaAngle, 2);
    Serial.print("°  |  Total Angle: ");
    Serial.println(totalAngle, 2);

    lastAngle = totalAngle;
    lastCount = count;
  }
}








