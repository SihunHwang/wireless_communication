#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int OutputPin = 9; // PWM output pin

const int n = 1; // number of waves per second
const float T = 3e1; // time per one bit of signal
const float sampling_rate = 600.0 * 1e6;
const float frequency = 12 * 1e6;

void setup() {
  // put your setup code here, to run once:
  // pinMode(OutputPin0, OUTPUT); // Set the pin as an output

    pinMode(OutputPin, OUTPUT); // Set the pin as an output
    Serial.begin(6e8);
    analogWriteFrequency(OutputPin, frequency); // Set the PWM frequency to 13.5MHz


    while (!Serial.available()); //wait for user input
    delay(100);  // Wait for complete input

    String text = Serial.readStringUntil('\n'); //read user input
    text.trim();  // Remove leading/trailing whitespaces

    String binary = textToBinary(text); // convert text to binary

    //generating signal
    
    int onoff;
    for (int i = 0; i < binary.length(); i++) 
    {
        if (binary[i] == '0') 
        {
            onoff = 0;
        }
        else 
        {
            onoff = 128;
        }

        float period = 1 / frequency;

        
        
        analogWrite(OutputPin, onoff); // Generate a square wave with 50% duty cycle   
        
        delayMicroseconds((T  * 1e6 ));
    } 
    analogWrite(OutputPin, 0);
}

void loop() {
  // put your main code here, to run repeatedly:


    
   //analogWriteFrequency(OutputPin0, f0); // Set the PWM frequency to 13.5MHz
   // analogWrite(OutputPin0, 128); // Generate a square wave with 50% duty cycle
    
    
}

String textToBinary(const String& text) {
    String binary = '1';
    size_t length = text.length();
    for (size_t i = 0; i < length; i++) {
        char currentChar = text.charAt(i);
        for (int j = 7; j >= 0; j--) {
            binary += (currentChar & (1 << j)) ? '1' : '0';
        }
    }
    binary += '1';
    return binary;
}
