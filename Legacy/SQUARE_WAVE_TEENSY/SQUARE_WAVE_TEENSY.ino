#include <Arduino.h>
float f0 = 1 ; //frequency(Hz) representing 0 
float f1 = 5.0 * 1e3; //frequency(Hz) representing 1
const int OutputPin = 9; // PWM output pin

void setup() {
  pinMode(OutputPin, OUTPUT); // Set the pin as an output
  Serial.begin(6e8);
}

void loop() {
  //user input in text
  Serial.println("Signal: ");
  String output_signal;
  if(Serial.available()){
    output_signal = Serial.readStringUntil('\n');

    //convert text to binary
    String binaryString = "";
    //text to ASCII
    for (size_t i = 0; i < output_signal.length(); i++) {
      char character = output_signal.charAt(i);
      int asciiCode = int(character);
    
      // Convert ASCII code to binary representation
      for (int j = 7; j >= 0; j--) {
        binaryString += ((asciiCode >> j) & 1) ? '1' : '0';
      }
    }
    
    
    //generating signal
    float frequency;
    for (int i = 0; i < binaryString.length(); i++) {
      if (int(binaryString[i]) == 0) {
        frequency = f0;
      }
      else {
        frequency = f1;
      }

      analogWriteFrequency(OutputPin, frequency); // Set the PWM frequency to 13.5MHz
      analogWrite(OutputPin, 128); // Generate a square wave with 50% duty cycle
     } 
   
  }
  delay(1000);
}
