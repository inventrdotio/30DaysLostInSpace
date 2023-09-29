/*
 * 30 Days - Lost in Space
 * Day 12 - Can you hear us?
 *
 * Learn more at https://inventr.io/adventure
 *
 * 
 * Today we will use the Keypad from Day 11 to control musical tones using a
 * small speaker.  To do this we will show how to take the characters returned
 * by the Keypad library and convert them to musical notes played by our speaker.
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - libraries: Code provided by others that we can use in our sketches
 * - char type: Represents a single character like 'A', 'd', '4' or '*'.
 * - arrays:    Variables of the same type arranged as a list where each item
 *              can be accessed using an index.  Arrays can be one dimensional
 *              like a list (with one index) or two dimensional like a spreadsheet
 *              table with rows and columns (using row and column indexes).
 *
 * Parts and electronics concepts introduced in this lesson.
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// Include Keypad library
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

byte rowPins[ROWS] = { 5, 4, 3, 2 };
byte colPins[COLS] = { 6, 7, 8, 9 };

char buttons[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  // 1st row
  { '4', '5', '6', 'B' },  // 2nd row
  { '7', '8', '9', 'C' },  // 3rd row
  { '*', '0', '#', 'D' }   // 4th row
};

Keypad myAwesomePad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS);

int tones[ROWS][COLS] = {  // a frequency tone for each button
  { 31, 93, 147, 208 },
  { 247, 311, 370, 440 },
  { 523, 587, 698, 880 },
  { 1397, 2637, 3729, 0 }
};

int buzzer = 10;  // pin 10 drives the buzzer

void setup() {
  Serial.begin(9600);  // Begin monitoring via the serial monitor
}


void loop() {
  /*
   * The first way we could 
   */
  // put your main code here, to run repeatedly:

  int toneFreq = 0;
  char result = myAwesomePad.getKey();

  if (result) {  // if a button is pressed

    for (byte j = 0; j < ROWS; j++) {
      for (byte i = 0; i < COLS; i++) {
        if (result == buttons[j][i]) {  // found it, get the corresponding tone
          toneFreq = tones[j][i];
        }

      }  // end i loop
    }    // end j loop

    Serial.print("Key: ");  //   send the result to serial...
    Serial.print(result);
    Serial.print("   Freq: ");
    Serial.println(toneFreq);

    if (toneFreq) {
    tone(buzzer, toneFreq);  // ... and play the tone for a half second
    } else {
      noTone(buzzer);
    }
    
    // tone(buzzer, toneFreq, 500);  // ... and play the tone for a half second
    // delay(500);
    // noTone(buzzer);
  }
}
