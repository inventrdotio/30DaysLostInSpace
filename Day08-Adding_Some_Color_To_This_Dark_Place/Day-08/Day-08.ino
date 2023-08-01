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
  RGB_color(125, 0, 0); // Red
  delay(500);
  RGB_color(0, 125, 0); // Green
  delay(500);
  RGB_color(0, 0, 125); // Blue
  delay(500);
  RGB_color(0, 125, 125); // yellow
  delay(500);
  RGB_color(125, 0, 125); // purple
  delay(500);
  RGB_color(125, 125, 125); // white
  delay(500);
}

void RGB_color(int red_value, int green_value, int blue_value)
{
  analogWrite(red, red_value);
  analogWrite(green, green_value);
  analogWrite(blue, blue_value);
}