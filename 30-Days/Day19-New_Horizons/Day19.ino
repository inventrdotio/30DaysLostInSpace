// Rotary Encoder Inputs
#define CLK2 2
#define DT2 3
// Include the library:
#include <TM1637Display.h>
// Define the connections pins:
#define CLK 6
#define DIO 5
// Create display object of type TM1637Display:
TM1637Display display = TM1637Display(CLK, DIO);
// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
// You can set the individual segments per digit to spell words or create other symbols:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};
int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
void setup() {
  // Set encoder pins as inputs
  pinMode(CLK2,INPUT);
  pinMode(DT2,INPUT);
  // Setup Serial Monitor
  Serial.begin(9600);
  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK2);
  // Clear the display:
  display.clear();
  delay(1000);
  display.setBrightness(7);
  // Call updateEncoder() when any high/low changed seen
  // on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
}
void loop() {
  display.showNumberDec(counter);
  delay(50);
  if(counter == 50) {
    display.setSegments(data);
    delay(3000);
    display.clear();
    counter += 5;
  }
 if(counter == 75) {
    display.setSegments(data);
    delay(3000);
    display.clear();
    counter += 5;
  }
  if(counter == 100) {
    display.setSegments(done);
    delay(1000000);
  }
}
void updateEncoder(){
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK2);
  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT2) != currentStateCLK) {
      counter --;
      currentDir ="CCW";
    } else {
      // Encoder is rotating CW so increment
      counter ++;
      currentDir ="CW";
    }
    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
  }
  // Remember last CLK state
  lastStateCLK = currentStateCLK;
}