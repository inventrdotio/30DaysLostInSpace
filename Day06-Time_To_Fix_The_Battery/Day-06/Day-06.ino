// Code written by Alexander Eschenauer for the 30 Day Adventure Kit
// Learn more at https://inventr.io/adventure
 
#define PHOTORESISTOR_PIN = A0;   // select the input pin for the photoresistor

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set onboard LED as an OUTPUT
  Serial.begin(9600); // Talk to computer over baud rate 9600
}

void loop() {
  int roomBrightness = analogRead(PHOTORESISTOR_PIN); // Read value from photoresistor
  roomBrightness = roomBrightness * 10; // Make the delay longer so you can actually see the change in blinking delays
  
  digitalWrite(LED_BUILTIN, HIGH); // Turn onboard LED on
  delay(roomBrightness); // wait
  digitalWrite(LED_BUILTIN, LOW); // Turn onboard LED off
  delay(roomBrightness); // wait
  
  Serial.println(roomBrightness); // print value back to computer
}
