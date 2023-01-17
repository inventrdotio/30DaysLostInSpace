// DEFINES
#define numberOfSeconds(_time_) ((_time_ / 1000) % 60)  
#define numberOfMinutes(_time_) ((_time_ / 1000) / 60) 

// 7 SEG
#define CLKsev 5
#define DIOsev 4

//LIBRARIES
#include <TM1637Display.h>
#include "U8glib.h"

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI 

// CONSTANTS
const uint8_t OFF[] = {0, 0, 0, 0};

// In this library, the byte order is .GFEDCBA
const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

// GLOBALS
// Create a display object, specifying parameters (Clock pin, Data pin)
TM1637Display display(5, 4);

// 1000ms in 1sec, 60secs in 1min, 60mins in 1hr. So, 1000x60x60 = 3600000ms = 1hr
unsigned long timeLimit = 10000;
unsigned long lastPeriodStart;

// OLED Display output
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 22, "LIFTOFF!!");
}

void setup(){
  Serial.begin(9600);
  // Set brightness
  display.setBrightness(7);
  // Clear the display
  display.setSegments(OFF);

  u8g.setColorIndex(1);
  
  pinMode(8, OUTPUT);
}

void countdown() {
  // Calculate the time remaining 
  
  unsigned long timeRemaining = timeLimit - millis();
   Serial.println("Countdown started..: ");
     
    Serial.println(timeRemaining);
    // To display the countdown in mm:ss format, separate the parts
    int seconds = numberOfSeconds(timeRemaining);
    int minutes = numberOfMinutes(timeRemaining); 
  
    // This displays the seconds in the last two places
    display.showNumberDecEx(seconds, 0, true, 2, 2);
    // Display the minutes in the first two places, with colon
    display.showNumberDecEx(minutes, 0x80>>3, true, 2, 0);

    // Update the time remaining
    timeRemaining = timeLimit - millis();
    if(timeRemaining < 50){
      Serial.println("BREAK!!");
        u8g.firstPage();  
        do {
          draw();
        } while( u8g.nextPage() );
        while(1);
    }
}

void loop(){
  countdown();
}
