// Code written by Alexander Eschenauer for the 30 Day Adventure Kit
// Learn more at https://inventr.io/adventure

int red = 4;
int green = 3;
int blue = 2;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  RGB_color(125, 0, 0);  // Red
  delay(500);
  RGB_color(0, 125, 0);  // Green
  delay(500);
  RGB_color(0, 0, 125);  // Blue
  delay(500);
  RGB_color(0, 125, 125);  // yellow
  delay(500);
  RGB_color(125, 0, 125);  // purple
  delay(500);
  RGB_color(125, 125, 125);  // white
  delay(500);
}

// If the RGB LED is a Common Anode (+5 on longest pin) then the value given is
// how much of the time (0-255) each pin should be GROUNDED.  Our loop() sets how
// intense each light should be, so here we will subtract each value from 255
// to get the GROUNDED time.
void RGB_color(byte red_value, byte green_value, byte blue_value) {
  analogWrite(red, 255 - red_value);
  analogWrite(green, 255 - green_value);
  analogWrite(blue, 255 - blue_value);
}