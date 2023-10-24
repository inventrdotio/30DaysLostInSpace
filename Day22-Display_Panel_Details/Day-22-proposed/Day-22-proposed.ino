/*
 * 30 Days - Lost in Space
 * Day 22 - Hello New World!
 *
 *
 * Learn more at https://inventr.io/adventure
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - I2C communications.
 * - Computer character fonts
 * - U8g2 graphics library for monochrome displays
 *
 * Parts and electronics concepts introduced in this lesson.
 * - SH1106 monochrome 128x64 pixel OLED display.
 * - HERO I2C pins (A5 and A4)
 */

// Explicitly include Arduino.h
#include "Arduino.h"

/*
 * Refer to the Day 21 lesson for instructions on how to install the U8g2
 * library into the Arduino IDE.  We will use this library to display messages
 * on our OLED display.
 *
 * Extensive documentation for this library can be found at https://github.com/olikraus/u8g2
 * for those wanting to dive deeper, but we will explain all of the functions
 * used in these lessons.
 */
#include <U8g2lib.h>  // Include file for the U8g2 library.

// Construct our lander_display handle using the same constructor from Day 21
U8G2_SH1106_128X64_NONAME_F_HW_I2C lander_display(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void setup(void) {
  lander_display.begin();  // Initialize display library

  lander_display.setFont(u8g_font_6x10);
  lander_display.setFontRefHeightExtendedText();
  lander_display.setFontPosTop();

  // Uncomment the next line if your display shows the text upside down.
  // lander_display.setDisplayRotation(U8G2_R2);
}

const byte VIEWS = 7;

void loop(void) {
  for (unsigned int draw_state = 0; draw_state < (VIEWS * 8); draw_state++) {
    lander_display.clearBuffer();  // clear the internal memory

    // setCursor() will set the x/y location of the upper left bit of each string
    lander_display.setFontPosTop();

    // Title line for our display displayed on each screen
    const char DISPLAY_TITLE[] = "Exploration Lander";
    lander_display.setCursor(center_string(DISPLAY_TITLE), 0);  // Center title at top of display
    lander_display.print(DISPLAY_TITLE);

    // To leave the title above each display we offset the y starting point
    // by the maximum character height of our selected font.
    byte y_offset = lander_display.getMaxCharHeight();

    switch (draw_state >> 3) {
      case 0: display_test_ready(y_offset, draw_state & 7); break;
      case 1: display_test_box_frame(y_offset, draw_state & 7); break;
      case 2: display_test_circles(y_offset, draw_state & 7); break;
      case 3: display_test_r_frame(y_offset, draw_state & 7); break;
      case 4: display_test_string(y_offset, draw_state & 7); break;
      case 5: display_test_line(y_offset, draw_state & 7); break;
      case 6: display_test_triangle(y_offset, draw_state & 7); break;
    }
    lander_display.sendBuffer();
    delay(50);
  }
}

// Return starting X position that will center the given string
byte center_string(char *string) {
  return (lander_display.getDisplayWidth() - lander_display.getStrWidth(string)) / 2;
}

const byte LANDER_HEIGHT = 25;
const byte LANDER_WIDTH = 20;

void display_test_ready(byte y_offset, byte frame) {
  // Y value halfway between top and bottom of drawable area
  byte y_center = y_offset + ((lander_display.getDisplayHeight() - y_offset) / 2);

  // Center lander Y location in center of space below title
  byte lander_y_offset = y_center - (LANDER_HEIGHT / 2);
  display_lander(0, lander_y_offset);

  // Serial.print("display_test_ready Frame: ");
  // Serial.println(frame);
  // Now display ready message every other frame
  if ((frame & 1) == 0) {
    // Serial.println ("display");
    byte x_offset = LANDER_WIDTH;  // display to right of lander image

    byte text_height = lander_display.getMaxCharHeight();

    // Display line 1 on display
    byte line_1_y_offset = y_center - text_height - (text_height / 2);
    const char READY_LINE_1[] = "Begin";
    byte line_1_x_center = x_offset + ((lander_display.getDisplayWidth() - x_offset) / 2)
                           - (lander_display.getStrWidth(READY_LINE_1) / 2);
    lander_display.drawStr(line_1_x_center, line_1_y_offset, READY_LINE_1);

    // Display line 2 on display
    byte line_2_y_offset = line_1_y_offset + text_height;
    const char READY_LINE_2[] = "Hardware";
    byte line_2_x_center = x_offset + ((lander_display.getDisplayWidth() - x_offset) / 2)
                           - (lander_display.getStrWidth(READY_LINE_2) / 2);
    lander_display.drawStr(line_2_x_center, line_2_y_offset, READY_LINE_2);

    // Display line 3 on display
    byte line_3_y_offset = line_2_y_offset + text_height;
    const char READY_LINE_3[] = "Test";
    byte line_3_x_center = x_offset + ((lander_display.getDisplayWidth() - x_offset) / 2)
                           - (lander_display.getStrWidth(READY_LINE_3) / 2);
    lander_display.drawStr(line_3_x_center, line_3_y_offset, READY_LINE_3);
  }
}

// Display an image of our lander drawn with frames and triangles
// at location x_location, y_location for upper left corner.
void display_lander(byte x_location, byte y_location) {
  lander_display.drawFrame(x_location + 7, y_location, 6, 5);        // ship top
  lander_display.drawFrame(x_location + 5, y_location + 4, 10, 20);  // ship center
  lander_display.drawFrame(x_location, y_location + 6, 6, 16);       // left pod
  lander_display.drawFrame(x_location + 14, y_location + 6, 6, 16);  // right pod
  lander_display.drawTriangle(x_location + 2, y_location + 21,
                              x_location, y_location + 25,
                              x_location + 4, y_location + 25);  // left nozzle
  lander_display.drawTriangle(x_location + 18, y_location + 21,
                              x_location + 15, y_location + 25,
                              x_location + 20, y_location + 25);  // right nozzle
}

// Display filled and hollow boxes.
void display_test_box_frame(byte y_offset, byte frame) {
  lander_display.drawStr(0, y_offset, "drawBox");
  lander_display.drawBox(5, y_offset + 10, 20, 10);
  lander_display.drawBox(10 + frame, y_offset + 15, 30, 7);
  lander_display.drawStr(0, y_offset + 30, "drawFrame");
  lander_display.drawFrame(5, y_offset + 10 + 30, 20, 10);
  lander_display.drawFrame(10 + frame, y_offset + 15 + 30, 30, 7);
}

// Display filled and hollow circles.
void display_test_circles(byte y_offset, byte frame) {
  lander_display.drawStr(0, y_offset, "drawDisc");
  lander_display.drawDisc(10, y_offset + 18, 8);
  lander_display.drawDisc(24 + frame, y_offset + 16, 7);
  lander_display.drawStr(0, y_offset + 27, "drawCircle");
  lander_display.drawCircle(10, y_offset + 18 + 27, 8);
  lander_display.drawCircle(24 + frame, y_offset + 18 + 25, 6);
}

// Display filled and hollow boxes with rounded corners
void display_test_r_frame(byte y_offset, byte frame) {
  lander_display.drawStr(0, y_offset, "drawRFrame/Box");
  lander_display.drawRFrame(5, y_offset + 10, 40, 30, frame + 1);
  lander_display.drawRBox(50, y_offset + 10, 25, 40, frame + 1);
}

void display_test_string(byte y_offset, byte frame) {
  int test_offset = y_offset + 31;
  lander_display.drawStr(30 + frame, test_offset, " 0");
  lander_display.setFontDirection(1);
  lander_display.drawStr(30, test_offset + frame, " 90");
  lander_display.setFontDirection(2);
  lander_display.drawStr(30 - frame, test_offset, " 180");
  lander_display.setFontDirection(3);
  lander_display.drawStr(30, test_offset - frame, " 270");
  lander_display.setFontDirection(0);
}

void display_test_line(byte y_offset, byte frame) {
  lander_display.drawStr(0, y_offset, "drawLine");
  int test_offset = y_offset + lander_display.getMaxCharHeight();
  lander_display.drawLine(7 + frame, test_offset, 40, 55);
  lander_display.drawLine(7 + frame * 2, test_offset, 60, 55);
  lander_display.drawLine(7 + frame * 3, test_offset, 80, 55);
  lander_display.drawLine(7 + frame * 4, test_offset, 100, 55);
}

void display_test_triangle(byte y_offset, byte frame) {
  lander_display.drawStr(0, y_offset, "drawTriangle");
  int test_offset = y_offset + lander_display.getMaxCharHeight();

  lander_display.drawTriangle(14, test_offset + 7,
                              45, test_offset + 20,
                              10, test_offset + 30);
  lander_display.drawTriangle(14 + frame, test_offset + 7 - frame,
                              45 + frame, test_offset + 20 - frame,
                              57 + frame, test_offset + 00 - frame);
  lander_display.drawTriangle(57 + frame * 2, test_offset + 0,
                              45 + frame * 2, test_offset + 20,
                              96 + frame * 2, test_offset + 43);
  lander_display.drawTriangle(10 + frame, test_offset + 30 + frame,
                              45 + frame, test_offset + 20 + frame,
                              96 + frame, test_offset + 43 + frame);
}

// void u8g_ascii_1() {
//   char s[2] = " ";
//   uint8_t x, y;
//   lander_display.drawStr( 0, 0, "ASCII page 1");
//   for( y = 0; y < 6; y++ ) {
//     for( x = 0; x < 16; x++ ) {
//       s[0] = y*16 + x + 32;
//       lander_display.drawStr(x*7, y*10+10, s);
//     }
//   }
// }

// void u8g_ascii_2() {
//   char s[2] = " ";
//   uint8_t x, y;
//   lander_display.drawStr( 0, 0, "ASCII page 2");
//   for( y = 0; y < 6; y++ ) {
//     for( x = 0; x < 16; x++ ) {
//       s[0] = y*16 + x + 160;
//       lander_display.drawStr(x*7, y*10+10, s);
//     }
//   }
// }

// void u8g_extra_page(uint8_t a)
// {
//   if ( lander_display.getMode() == U8G_MODE_HICOLOR || lander_display.getMode() == U8G_MODE_R3G3B2) {
//     /* draw background (area is 128x128) */
//     u8g_uint_t r, g, b;
//     b = a << 5;
//     for( g = 0; g < 64; g++ )
//     {
//       for( r = 0; r < 64; r++ )
//       {
// 	lander_display.setRGB(r<<2, g<<2, b );
// 	lander_display.drawPixel(g, r);
//       }
//     }
//     lander_display.setRGB(255,255,255);
//     lander_display.drawStr( 66, 0, "Color Page");
//   }
//   else if ( lander_display.getMode() == U8G_MODE_GRAY2BIT )
//   {
//     lander_display.drawStr( 66, 0, "Gray Level");
//     lander_display.setColorIndex(1);
//     lander_display.drawBox(0, 4, 64, 32);
//     lander_display.drawBox(70, 20, 4, 12);
//     lander_display.setColorIndex(2);
//     lander_display.drawBox(0+1*a, 4+1*a, 64-2*a, 32-2*a);
//     lander_display.drawBox(74, 20, 4, 12);
//     lander_display.setColorIndex(3);
//     lander_display.drawBox(0+2*a, 4+2*a, 64-4*a, 32-4*a);
//     lander_display.drawBox(78, 20, 4, 12);
//   }
//   else
//   {
//     lander_display.drawStr( 0, 12, "setScale2x2");
//     lander_display.setScale2x2();
//     lander_display.drawStr( 0, 6+a, "setScale2x2");
//     lander_display.undoScale();
//   }
// }
