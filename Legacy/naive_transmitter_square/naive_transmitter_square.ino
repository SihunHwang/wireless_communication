const int outputPin = 9;  // Pin connected to the output
float frequency = 1.4 * 1e5; // Frequency of wave (Hz)

void setup() {
  // put your setup code here, to run once:
  pinMode(outputPin, OUTPUT);  // Set the output pin as an OUTPUT
  Serial.begin(600 * 1e6);
}

void loop() {
  // put your main code here, to run repeatedly:
  float halfPeriod = 1.0 / (2 * frequency);
  digitalWrite(9, LOW);
  delayMicroseconds(halfPeriod * 1e6);

  digitalWrite(9, HIGH);
  delayMicroseconds(halfPeriod * 1e6);
}
