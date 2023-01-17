// Code written by Alexander Eschenauer for the 30 Day Adventure Kit
// Learn more at https://inventr.io/adventure
 
int sensorPin = A0;   // select the input pin for the photoresistor
int onboardLED = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
 
void setup() {
  pinMode(onboardLED, OUTPUT);
  Serial.begin(9600);
}
 
void loop() {
  sensorValue = analogRead(sensorPin);
  digitalWrite(onboardLED, HIGH);
  delay(sensorValue);
  digitalWrite(onboardLED, LOW);
  delay(sensorValue);
  Serial.println(sensorValue);
  delay(500);
}