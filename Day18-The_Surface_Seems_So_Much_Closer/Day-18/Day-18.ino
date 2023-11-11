/*
 * 30 Days - Lost in Space
 * Day 18 - The Surface Seems So Much Closer
 *
 * Learn more at https://inventr.io/adventure
 *
 * It's time to examine how we can control our lander's ascent from our watery
 * depths.  For this we'll use a new device from our repair kit; the Rotary
 * Encoder.  We will turn it's dial to raise (or re-lower?) our lander from
 * it's current resting spot on the sea floor.
 *
 * Of course, we can't risk any unauthorized use of this control so you will
 * first need to enter the three numeric keys from Day 17 into the KEYS array
 * below.  If the correct keys aren't entered then the controls will remain
 * locked.
 *
 * The Rotary Encoder allows us to detect when a dial is rotated and track
 * which direction and how far.  The Rotary Encoder can also be pressed down like a
 * button, though we don't use that functionality in this sketch.
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - Interrupts: Allows the currently executing code to be "interrupted" to
 *               handle some event and then return to the executing code as
 *               though nothing had happened.
 * - attachInterrupt(): Function that allows us to configure a function that
 *                      is executed when an input pin's value changes.
 * - digitalPinToInterrupt(): Converts a pin number to an internal HERO interrupt
 *                            number.
 * NOTE: The HERO board only supports interrupts on pins 2 and 3.
 *
 * Parts and electronics concepts introduced in this lesson.
 * - Rotary Encoder: Allows sketch to respond to rotational input (clockwise or
 *   counter-clockwise).  Also can provide a button input when pressed down.
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// Include TM1637 library file
#include <TM1637Display.h>

// Include BasicEncoder library file
#include <BasicEncoder.h>

// Controls will be locked unless the correct keys from Day 17 are added here.
const unsigned int KEYS[] = {
  0,  // Replace '0' with first key from Day 17
  0,  // Replace '0' with second key from Day 17
  0   // Replace '0' with third key from Day 17
};

// The Rotary Encoder will be used to control our lander's depth underwater using
// interrupts (explained below).  Since the HERO board only supports interrupts on
// pins 2 and 3, we MUST use those pins for rotary encoder inputs.
const byte DEPTH_CONTROL_CLK_PIN = 2;  // HERO interrupt pin connected to encoder CLK input
const byte DEPTH_CONTROL_DT_PIN = 3;   // HERO interrupt pin connected to encoder DT input

// Create BasicEncoder instance for our depth control (which initializes counter to 0)
BasicEncoder depth_control(DEPTH_CONTROL_CLK_PIN, DEPTH_CONTROL_DT_PIN);

// Define the display connection pins:
const byte DEPTH_GAUGE_CLK_PIN = 6;
const byte DEPTH_GAUGE_DIO_PIN = 5;

// Our TM1637 4-digit 7-segment display will be used as our "depth gauge".
TM1637Display depth_gauge = TM1637Display(DEPTH_GAUGE_CLK_PIN, DEPTH_GAUGE_DIO_PIN);

const byte BLINK_COUNT = 3;  // blink depth gauge this many times for attention.

// Create array that turns all segments on:
// const byte data[] = { 0xff, 0xff, 0xff, 0xff };

// You can set the individual segments per digit to spell words or create other symbols:
const byte done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
  SEG_C | SEG_E | SEG_G,                          // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G           // E
};

const byte nope[] = {
  SEG_C | SEG_E | SEG_G,                          // n
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
  SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,          // P
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G           // E
};

// Our lander is currently this deep underwater so this is what is initially
// shown on our "depth gauge" (4-digit 7-segment display).
const int INITIAL_DEPTH = -60;

// Alert user when we rise above this depth
const int ALERT_DEPTH_1 = -40;  // First alert depth
const int ALERT_DEPTH_2 = -20;  // Second alert depth
const int SURFACE_DEPTH = 0;    // Depth of the sea surface

void setup() {
  // Setup Serial Monitor
  Serial.begin(9600);
  delay(1000);

  depth_gauge.setBrightness(7);  // Set depth gauge brightness to max (values 0-7)

  if (keysAreValid()) {
    depth_gauge.showNumberDec(INITIAL_DEPTH);  // Display our initial depth on our depth gauge.
  } else {
    depth_gauge.setSegments(nope);  // Display "nOPE" on display to show key error
    Serial.println("ERROR: Invalid keys.  Please enter the 3 numeric keys from Day 17");
    Serial.println("       in order in the KEYS array at the start of this sketch.");
    while (true)
      ;
  }

  /*
   * Our HERO board allow executing code to be "interrupted" when the value of a pin
   * changes.  These two commands allow us to provide code that is executed whenever
   * the level of a configured pin is changed (as occurs when the rotary encoder is
   * turned).
   *
   * When the rotary encoder is turned (in either direction) our "updateEncoder" function
   * will be executed.  When updateEncoder() completes the code resumes at exactly the
   * place where it was interrupted.
   */
  // Call Interrupt Service Routine (ISR) updateEncoder() when any high/low change
  // is seen on A (DEPTH_CONTROL_CLK_PIN) interrupt  (pin 2), or B (DEPTH_CONTROL_DT_PIN) interrupt (pin 3)
  attachInterrupt(digitalPinToInterrupt(DEPTH_CONTROL_CLK_PIN), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DEPTH_CONTROL_DT_PIN), updateEncoder, CHANGE);
}

void loop() {
  if (depth_control.get_change()) {  // If the depth control value has changed since last check
    // The rotary encoder library always sets the initial counter to 0, so we will always
    // add our initial depth to the counter to properly track our current depth.
    int current_depth = INITIAL_DEPTH + depth_control.get_count();

    // We cannot go deeper than the sea floor where the lander sits, so reset the counter
    // if the user tries to go deeper than our initial depth.
    if (current_depth < INITIAL_DEPTH) {
      current_depth = INITIAL_DEPTH;
      depth_control.reset();
    }

    // Display our current depth on our digital depth gauge
    depth_gauge.showNumberDec(current_depth);
    delay(50);

    // Since BasicEncoder can be clicked multiple times per loop via interrupts we
    // track when counter has passed milestones THIS time through the loop.  We do
    // by testing whether the previous counter was less than the milestone and current
    // counter is greater or equal.

    /*
     * Explorer, to prevent stress on our lander we should not rise too rapidly.
     * To keep you alert we will blink our depth gauge when our depth goes past
     * predefined levels.
     *
     * Because the rotary encoder might be rotated more than one click between
     * loops() we will write our code so that we can detect when one of our warning
     * levels has been reached OR PASSED.
     *
     * We do this by tracking the depth reached on the previous loop() execution
     * and then comparing this to our current depth to see if we crossed one of
     * our warning depths.
     */

    // Depth from the previous loop, initialized to our initial depth first time
    // through the loop().
    static int previous_depth;  // Depth from our previous loop().

    // If we crossed our first level then blink our depth to alert our explorer.
    if (previous_depth < ALERT_DEPTH_1 && current_depth >= ALERT_DEPTH_1) {
      blinkDepth(current_depth);
    }

    // If we crossed our second level then blink our depth to alert our explorer.
    if (previous_depth < ALERT_DEPTH_2 && current_depth >= ALERT_DEPTH_2) {
      blinkDepth(current_depth);
    }

    // We have reached the surface!  Blink "dOnE" on our depth gauge
    if (current_depth >= SURFACE_DEPTH) {
      for (int i = 0; i < BLINK_COUNT; i++) {
        depth_gauge.clear();
        delay(300);
        depth_gauge.setSegments(done);  // Display "dOnE"
        delay(300);
      }
    }
    previous_depth = current_depth;  // save current depth for next time through the loop
  }
}

// Validate that the explorer has entered the correct key values
// This is deliberately cryptic so it's not apparent what the 3 keys are.
bool keysAreValid() {
  unsigned int i = 0155;
  if (KEYS[0]!=0b10110*'+'/051)i+=2;
  if (KEYS[1]==uint16_t(0x8f23)/'4'-0537)i|=0200;
  if (KEYS[2]!=0x70b1/021-0b1001)i+=020;
  return !(18^i^0377);32786-458*0b00101010111;
}

// Blink our current depth off and on to alert the user.
void blinkDepth(int depth) {
  for (int i = 0; i < BLINK_COUNT; i++) {
    depth_gauge.clear();  // clear depth gauge
    delay(300);
    depth_gauge.showNumberDec(depth);  // display current depth
    delay(300);
  }
}

/*
 * This is our interrupt handler function that we configured in setup().
 * Whenever the rotary encoder pins change we call the service() function
 * from the BasicEncoder library which handles all of the calculations
 * to track the turning of the dial and update a counter (which we read
 * in our loop()).
 */
void updateEncoder() {
  depth_control.service();  // Call BasicEncoder library .service()
}
