// Code written by Alexander Eschenauer for the 30 Day Adventure Kit
// Learn more at https://inventr.io/adventure

int sensorPin = A0;   // select the input pin for the photoresistor
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

unsigned int batteryCapacity = 50000;
unsigned int batteryLevel = 0;

void PrintBatteryPercentage() {
  Serial.print(((double)batteryLevel / (double)batteryCapacity)*100);
  Serial.println("%");
}

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin); // read the value from the sensor:
  batteryLevel += sensorValue;
  
  if(batteryLevel >= batteryCapacity) {
    Serial.println("FULLY CHARGED");
    batteryLevel = batteryCapacity; // to prevent integer overflow errors
  }
  else {
    PrintBatteryPercentage();
  }
  
  delay(50);
}