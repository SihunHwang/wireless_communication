const int InputPin = A0; // PWM input pin
float data;
const float threshold_voltage = 70.0;
long c = 0;

const int n = 1; // number of waves per second
const float T = 1.0 * 1e-3; // time per one bit of signal
const float sampling_rate = 1 * 1e5;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(1000000);
  Serial.print("value");
  Serial.print(',');
  Serial.println("time");
}

void loop() {
  // put your main code here, to run repeatedly:
  data = analogRead(A0);
 
  //if (data > 0) {
     Serial.print(data);
     Serial.print(',');
     Serial.println(c);
  //}
  

  c++;
  
}
