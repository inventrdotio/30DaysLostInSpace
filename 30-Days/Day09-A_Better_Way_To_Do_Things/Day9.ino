// Code written by Alexander Eschenauer for the 30 Day Adventure Kit
// Learn more at https://inventr.io/adventure

int sensorPin = A0;   // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
unsigned int batteryCapacity = 50000;
unsigned int batteryLevel = 0;

// RGB LED PINS
int red = 11;
int green = 10;
int blue = 9;

void RGB_color(int red_value, int green_value, int blue_value)
 {
  analogWrite(red, red_value);
  analogWrite(green, green_value);
  analogWrite(blue, blue_value);
}

double getBatteryPercentage() {
  return (((double)batteryLevel / (double)batteryCapacity)*100);
}

void setup() {
  // Declare the RGB LED pins as outputs:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  // Start serial monitor
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin); // read the value from the sensor:
  batteryLevel += sensorValue;

  double percentage = getBatteryPercentage();

  if (percentage >= 100) {
    RGB_color(0, 125, 0); // Green
    batteryLevel = batteryCapacity; // to prevent integer overflow errors
    percentage = 100; // to prevent from displaying over 100%
  } 
  else if (percentage > 0 && percentage <= 25)
  {
    RGB_color(125, 0, 0); // red
  }
  else if (percentage > 25 && percentage <= 50){
    RGB_color(125, 80, 0); // yellow-ish
  }
  else if (percentage > 50 && percentage <= 75) {
    RGB_color(0, 125, 125); // blue-ish
  }
  
  Serial.print(percentage);
  Serial.println("%");

  delay(100);
}