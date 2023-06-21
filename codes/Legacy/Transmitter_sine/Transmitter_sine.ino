#include <stdio.h>
#include <string.h>
const int outputPin = 9;  // Pin connected to the output

// Constants for sine wave generation
const float offset = 127.5;      // Offset to center the sine wave
float f0 = 13.5 * 1e6 ; //frequency(Hz) representing 0 
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
    int len = 0;
    while(output_signal[len] != '\0')
    {
        Serial.println(output_signal);
        len++;
    }

    for (int i = 0; i < len; i++) {
      float frequency;
      const float amplitude = 255.0;   // Amplitude of the sine wave
      
      if (int(output_signal[i]) == 0) {
        frequency = f0;
      }
      else {
        frequency = f1;
      }
      
      // Calculate the time period of each sample based on the desired frequency
      float timePeriod = 1.0 / frequency;

      // Generate the sine wave samples and output them through PWM
      for (float t = 0.0; t < timePeriod; t += (1.0 / (600 * 1e6))) {
        // Calculate the current amplitude of the sine wave
        float amplitudeValue = offset + amplitude * sin(2.0 * PI * frequency * t);

        // Convert the amplitude value to a 8-bit PWM duty cycle (0-255)
        int dutyCycle = int(amplitudeValue);

        // Output the duty cycle through PWM
        analogWrite(outputPin, dutyCycle);

        // Optional: Print the current amplitude value (0-255) to the serial monitor
        Serial.println(dutyCycle);
      }
    }
  }
  delay(1000);
}
