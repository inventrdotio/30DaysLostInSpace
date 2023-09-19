// Code written by Alexander Eschenauer for the 30 Day Adventure Kit
// Learn more at https://inventr.io/adventure
 
int PHOTORESISTOR_PIN = A0;   // select the input pin for the photoresistor
 
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set onboard LED as an OUTPUT
  Serial.begin(9600); // Talk to computer over baud rate 9600
}
 
void loop() {
  int ROOM_BRIGHTNESS = analogRead(PHOTORESISTOR_PIN); // Read value from photoresistor

  digitalWrite(LED_BUILTIN, HIGH); // Turn onboard LED on
  delay(ROOM_BRIGHTNESS); // wait
  digitalWrite(LED_BUILTIN, LOW); // Turn onboard LED off
  delay(ROOM_BRIGHTNESS); // wait

  Serial.println(ROOM_BRIGHTNESS); // print value back to computer
  delay(50); // short delay to help de-clutter serial monitor
}
