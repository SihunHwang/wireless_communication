#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
String textToBinary(const String& text);

float f0 = 10.0 * 1e3 ; //frequency(Hz) representing 0 
float f1 = 20.0 * 1e3; //frequency(Hz) representing 1
const int OutputPin0 = 10; // PWM output pin
const int OutputPin1 = 8; // PWM output pin
const int n = 2; // number of waves per second
const float T = 1.0 * 1e-3; // time per one bit of signal

void setup() 
{
    pinMode(OutputPin0, OUTPUT); // Set the pin as an output
    pinMode(OutputPin1, OUTPUT);
    Serial.begin(6e8);

    while (!Serial.available()); //wait for user input
    delay(100);  // Wait for complete input

    String text = Serial.readStringUntil('\n'); //read user input
    text.trim();  // Remove leading/trailing whitespaces

    String binary = textToBinary(text); // convert text to binary

    //generating signal
    float frequency;
    int OutputPin;
    for (int i = 0; i < binary.length(); i++) 
    {
        if (binary[i] == '0') 
        {
            frequency = f0;
            OutputPin = OutputPin0;
        }
        else 
        {
            frequency = f1;
            OutputPin = OutputPin1;
        }

        float period = 1 / frequency;

        for (int j = 0; j < n; j++) {
            digitalWrite(OutputPin, HIGH);
            delay(period * 0.5 * 1e3);          
            digitalWrite(OutputPin, LOW); 
            delay(period * 0.5 * 1e3);   
        }
        delayMicroseconds((T - (period * n)) * 1e6 );
    } 
}

void loop() {}

String textToBinary(const String& text) {
    String binary;
    size_t length = text.length();
    for (size_t i = 0; i < length; i++) {
        char currentChar = text.charAt(i);
        for (int j = 7; j >= 0; j--) {
            binary += (currentChar & (1 << j)) ? '1' : '0';
        }
    }
    return binary;
}
