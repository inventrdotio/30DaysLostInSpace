// DEFINES
#define numberOfSeconds(_time_) ((_time_ / 1000) % 60)  
#define numberOfMinutes(_time_) ((_time_ / 1000) / 60) 
#define ThrustersLever 8 //dip 1
#define SystemsLever 9 //dip 2
#define ConfirmLever 10 //dip 3
#define TakeoffAnnoucementSystem 11 //buzzer

//LIBRARIES
#include <TM1637Display.h>
#include "U8glib.h"

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI 

// CONSTANTS
const uint8_t OFF[] = {0, 0, 0, 0};

// GLOBALS
// Create a display object, specifying parameters (Clock pin, Data pin)
TM1637Display display(5, 4);

// 1000ms in 1sec, 60secs in 1min, 60mins in 1hr. So, 1000x60x60 = 3600000ms = 1hr
unsigned long timeLimit = 30000;
unsigned long lastPeriodStart;
int pause = 0;
int pause2 = 0;

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

  pinMode(ThrustersLever, INPUT);
  pinMode(SystemsLever, INPUT);
  pinMode(ConfirmLever, INPUT);
  u8g.setColorIndex(1); // pixel on
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

void playBeepBoop() {
  tone(TakeoffAnnoucementSystem, 476, 3000);
  delay(3000);
  noTone(TakeoffAnnoucementSystem);
}

void loop(){

  if(digitalRead(ThrustersLever) == 1 && 
     digitalRead(SystemsLever) == 1 &&
     digitalRead(ConfirmLever) == 1) {
      pause = 1;
  }
  if(pause == 1 && pause2 == 0) {
      playBeepBoop();
      pause2 = 1;
  }
  else if(pause2 == 1) {
    countdown();
  }
  
}
