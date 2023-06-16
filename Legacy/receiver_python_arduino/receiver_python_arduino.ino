#include <Arduino.h>
const int InputPin = 9; // PWM input pin
float data;
const int n = 1; // number of waves per second
const float T = 1.0 * 1e-3; // time per one bit of signal


void setup() {
  // put your setup code here, to run once:
  pinMode(InputPin, INPUT);
  Serial.begin(6e8);
}

void loop() {
  // put your main code here, to run repeatedly:
  data = analogRead(InputPin);
  

   Serial.println(data);
   delay(1);
   
}
