/* <-- Hi there! The lines of text inside these symbols are just notes for us humans to read.
 * They help us understand what the code is doing. The Arduino doesn't read these notes at all.
 * 
 * Our project: "30 Days - Lost in Space"
 * Today's mission: "Day 2 - It's Really Dark in Here"
 * 
 * Learn more at: https://inventr.io/adventure
 * 
 * Today, we're going to learn about LEDs (Light Emitting Diodes). These are tiny lights
 * that can glow when we pass electricity through them. They are very small but very strong 
 * and can last a long time. You can find them in different colors and sizes.
 *
 * Teachers: Alex Eschenauer & David Schmidt
 */

/*
 * Here, we'll list a few important ideas and parts that we'll learn about today:
 * - A Circuit: It's like a circle that electricity travels around. It needs to be closed, with no breaks.
 * - Current: It's the flow of electricity.
 * - Voltage: It's the force pushing the electricity.
 * - Resistance: It's something that slows down the electricity.
 * 
 * And here are some things we'll use with our Arduino HERO:
 * - Breadboard: A tool that helps us build our circuit without any soldering.
 * - 5V pins: These are the pins on our HERO that give 5 volts of power.
 * - GND pins: These pins are connected to the ground, they complete our circuit.
 * 
 * We'll also learn about these programming ideas:
 * - Arduino language: A special programming language that helps us talk to our HERO.
 * - Comments: Notes in the code, like this one, that help us understand what is going on.
 * - Variables and Constants: These are places where we can store information.
 * - Functions: These are chunks of code that perform a specific task.
 */

// We start by including this line of code, which helps our HERO work properly with the Arduino program.
#include "Arduino.h"

/*
 * Today we are going to make a big light turn on to light up our lander! We'll use an LED for now to 
 * test our setup. We will use a digital pin on our HERO to control our lander's light.
 * 
 * In our code, we often use constants. These are like nicknames that we give to specific values. This
 * makes our code easier to read and change later if needed. For example, instead of remembering a pin
 * number, we can just give it a nickname like CABIN_LIGHTS_PIN.
 *
 * One way to define constants is by using a command called #define.  Using this we can give a name
 * (or nickname) to the value that follows the name. You'll notice that the nickname is in capital letters,
 * which is a way to remind us that it's a constant and can't change.
 *
 * In this #define we give the name "CABIN_LIGHTS_PIN" the value of "12".  Whenever you see
 * in this sketch it will have the value of "12".
 */
#define CABIN_LIGHTS_PIN 12   // This is the nickname for the pin connected to our LED.

/*
 * The setup function is where we prepare everything before we start. We only run this function once each
 * time we turn on our HERO or reset it. Here, we are setting up our CABIN_LIGHTS_PIN as an output pin, so
 * we can control our light with it.
 */
void setup() {
  pinMode(CABIN_LIGHTS_PIN, OUTPUT);    // We will control our lander's lights as an OUTPUT.
}

/*
 * After the setup function, the loop function starts. This function keeps repeating over and over, like
 * a circle. Here, we are making our light turn on and off in a repeating pattern.
 */
void loop() {
  digitalWrite(CABIN_LIGHTS_PIN, HIGH);  // This line turns the lander's light ON.
  delay(1000);                           // Wait for one second (1000 milliseconds) with the light ON.
  digitalWrite(CABIN_LIGHTS_PIN, LOW);   // This line turns the lander's light OFF.
  delay(100);                            // Wait for a tenth of a second (100 milliseconds) with the light OFF.
}
