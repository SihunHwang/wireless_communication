#include <stdio.h>
#include <string.h>
const int outputPin = 9;  // Pin connected to the output

// Constants for sine wave generation
const float offset = 127.5;      // Offset to center the sine wave
float f0 = 1 ; //frequency(Hz) representing 0 
float f1 = 5.0 * 1e3; //frequency(Hz) representing 1
//Without Loss of Generality, we may assume f0 < f1

void setup() {
  // put your setup code here, to run once:
  pinMode(outputPin, OUTPUT);  // Set the output pin as an OUTPUT
  Serial.begin(600 * 1e6);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //ask for signal to send
  Serial.println("Signal: ");
  String output_signal;
  if(Serial.available()){
    output_signal = Serial.readStringUntil('\n');
    //get length of output signal
    int len = 0;
    while(output_signal[len] != '\0') {
        Serial.println(output_signal);
        len++;
    }

    for (int i = 0; i < len; i++) {
      float frequency;
      if (int(output_signal[i]) == 0) {
        frequency = f0;
      }
      else {
        frequency = f1;
      }
      float halfPeriod = 1.0 / (2 * frequency);
      digitalWrite(11, LOW);
      delay(halfPeriod);

      digitalWrite(11, HIGH);
      delay(halfPeriod);
      
    }
  }
}
