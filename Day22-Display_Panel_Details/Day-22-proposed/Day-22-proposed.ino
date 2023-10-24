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

  // Uncomment the next line if your display shows the text upside down.
  // lander_display.setDisplayRotation(U8G2_R2);
}

const byte VIEWS = 13;

void loop(void) {
  for (unsigned int draw_state = 0; draw_state < (VIEWS * 8); draw_state++) {
    lander_display.clearBuffer();  // clear the internal memory

    // setCursor() will set the x/y location of the upper left bit of each string
    lander_display.setFont(u8g_font_6x10);
    lander_display.setFontRefHeightExtendedText();
    lander_display.setFontPosTop();

    // Title line for our display displayed on each screen
    // const char DISPLAY_TITLE[] = "Exploration Lander";
    drawCenteredString(0, "Exploration Lander");  // Center title at top of display
    // lander_display.print(DISPLAY_TITLE);

    // To leave the title above each display we offset the y starting point
    // by the maximum character height of our selected font.
    byte y_offset = lander_display.getMaxCharHeight();

    // draw_state = (draw_state & 7) | (12 << 3);
    switch (draw_state >> 3) {
      case 0: display_test_ready(y_offset, draw_state & 7); break;
      case 1: display_test_box_frame(y_offset, draw_state & 7); break;
      case 2: display_test_circles(y_offset, draw_state & 7); break;
      case 3: display_test_r_frame(y_offset, draw_state & 7); break;
      case 4: display_test_string(y_offset, draw_state & 7); break;
      case 5: display_test_line(y_offset, draw_state & 7); break;
      case 6: display_test_triangle(y_offset, draw_state & 7); break;
      case 7: display_test_ascii_1(y_offset); break;
      case 8: display_test_ascii_2(y_offset); break;
      case 9: display_test_extra_page(y_offset, draw_state & 7); break;
      case 10: display_test_bitmap_modes(y_offset, draw_state & 7, false); break;
      case 11: display_test_bitmap_modes(y_offset, draw_state & 7, true); break;
      case 12: display_test_bitmap_overlay(y_offset, draw_state & 7); break;
    }
    lander_display.sendBuffer();
    delay(50);
  }
}

// Use the .drawStr() method to draw the current string centered on
// the current display.
byte drawCenteredString(byte y, char *string) {
  byte centered_x = (lander_display.getDisplayWidth() - lander_display.getStrWidth(string)) / 2;
  lander_display.drawStr(centered_x, y, string);
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
  drawCenteredString(y_offset, "drawBox");
  // lander_display.drawStr(0, y_offset, "drawBox");
  lander_display.drawBox(5, y_offset + 10, 20, 10);
  lander_display.drawBox(10 + frame, y_offset + 15, 30, 7);
  drawCenteredString(y_offset + 30, "drawFrame");
  // lander_display.drawStr(0, y_offset + 30, "drawFrame");
  lander_display.drawFrame(5, y_offset + 10 + 30, 20, 10);
  lander_display.drawFrame(10 + frame, y_offset + 15 + 30, 30, 7);
}

// Display filled and hollow circles.
void display_test_circles(byte y_offset, byte frame) {
  drawCenteredString(y_offset, "drawDisc");
  // lander_display.drawStr(0, y_offset, "drawDisc");
  lander_display.drawDisc(10, y_offset + 18, 8);
  lander_display.drawDisc(24 + frame, y_offset + 16, 7);
  drawCenteredString(y_offset + 27, "drawCircle");
  // lander_display.drawStr(0, y_offset + 27, "drawCircle");
  lander_display.drawCircle(10, y_offset + 18 + 27, 8);
  lander_display.drawCircle(24 + frame, y_offset + 18 + 25, 6);
}

// Display filled and hollow boxes with rounded corners
void display_test_r_frame(byte y_offset, byte frame) {
  drawCenteredString(y_offset, "drawRFrame/Box");
  // lander_display.drawStr(0, y_offset, "drawRFrame/Box");
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
  drawCenteredString(y_offset, "drawLine");
  // lander_display.drawStr(0, y_offset, "drawLine");
  int test_offset = y_offset + lander_display.getMaxCharHeight();
  lander_display.drawLine(7 + frame, test_offset, 40, 55);
  lander_display.drawLine(7 + frame * 2, test_offset, 60, 55);
  lander_display.drawLine(7 + frame * 3, test_offset, 80, 55);
  lander_display.drawLine(7 + frame * 4, test_offset, 100, 55);
}

void display_test_triangle(byte y_offset, byte frame) {
  drawCenteredString(y_offset, "drawTriangle");
  // lander_display.drawStr(0, y_offset, "drawTriangle");
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

void display_test_ascii_1(byte y_offset) {
  char s[2] = " ";
  byte x, y;
  drawCenteredString(y_offset, "ASCII page 1");
  // lander_display.drawStr(0, y_offset, "ASCII page 1");
  int test_offset = y_offset + lander_display.getMaxCharHeight();
  for (y = 0; y < 6; y++) {
    for (x = 0; x < 16; x++) {
      s[0] = y * 16 + x + 32;
      lander_display.drawStr(x * 7, y * lander_display.getMaxCharHeight() + test_offset, s);
    }
  }
}

void display_test_ascii_2(byte y_offset) {
  char s[2] = " ";
  byte x, y;
  drawCenteredString(y_offset, "ASCII page 2");
  // lander_display.drawStr(0, y_offset, "ASCII page 2");
  int test_offset = y_offset + lander_display.getMaxCharHeight();
  for (y = 0; y < 6; y++) {
    for (x = 0; x < 16; x++) {
      s[0] = y * 16 + x + 160;
      lander_display.drawStr(x * 7, y * lander_display.getMaxCharHeight() + test_offset, s);
    }
  }
}

void display_test_extra_page(byte y_offset, byte frame) {
  drawCenteredString(y_offset, "Unicode");
  // lander_display.drawStr(0, y_offset, "Unicode");
  int test_offset = y_offset + lander_display.getMaxCharHeight();
  lander_display.setFont(u8g2_font_unifont_t_symbols);
  lander_display.setFontPosTop();
  lander_display.drawUTF8(0, test_offset, "☀ ☁");
  switch (frame) {
    case 0:
    case 1:
    case 2:
    case 3:
      lander_display.drawUTF8(frame * 3, test_offset + 20, "☂");
      break;
    case 4:
    case 5:
    case 6:
    case 7:
      lander_display.drawUTF8(frame * 3, test_offset + 20, "☔");
      break;
  }
}

const byte CROSS_WIDTH = 24;
const byte CROSS_HEIGHT = 24;
static const unsigned char cross_bits[] U8X8_PROGMEM = {
  0x00, 0x18, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x42, 0x00, 
  0x00, 0x42, 0x00, 0x00, 0x42, 0x00, 0x00, 0x81, 0x00, 0x00, 0x81, 0x00, 
  0xC0, 0x00, 0x03, 0x38, 0x3C, 0x1C, 0x06, 0x42, 0x60, 0x01, 0x42, 0x80, 
  0x01, 0x42, 0x80, 0x06, 0x42, 0x60, 0x38, 0x3C, 0x1C, 0xC0, 0x00, 0x03, 
  0x00, 0x81, 0x00, 0x00, 0x81, 0x00, 0x00, 0x42, 0x00, 0x00, 0x42, 0x00, 
  0x00, 0x42, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x18, 0x00, };

const byte CROSS_FILL_WIDTH = 24;
const byte CROSS_FILL_HEIGHT = 24;
static const unsigned char cross_fill_bits[] U8X8_PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x18, 0x64, 0x00, 0x26, 
  0x84, 0x00, 0x21, 0x08, 0x81, 0x10, 0x08, 0x42, 0x10, 0x10, 0x3C, 0x08, 
  0x20, 0x00, 0x04, 0x40, 0x00, 0x02, 0x80, 0x00, 0x01, 0x80, 0x18, 0x01, 
  0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x40, 0x00, 0x02, 0x20, 0x00, 0x04, 
  0x10, 0x3C, 0x08, 0x08, 0x42, 0x10, 0x08, 0x81, 0x10, 0x84, 0x00, 0x21, 
  0x64, 0x00, 0x26, 0x18, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

const byte CROSS_BLOCK_WIDTH = 14;
const byte CROSS_BLOCK_HEIGHT = 14;
static const unsigned char cross_block_bits[] U8X8_PROGMEM = {
  0xFF, 0x3F, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 
  0xC1, 0x20, 0xC1, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 
  0x01, 0x20, 0xFF, 0x3F, };

void display_test_bitmap_modes(byte y_offset, byte frame, bool transparent) {
  if (!transparent) {
    lander_display.setBitmapMode(false /* solid */);
    drawCenteredString(y_offset, "Solid bitmap");
    // lander_display.drawStr(0, 0, "Solid bitmap");
  } else {
    lander_display.setBitmapMode(true /* transparent*/);
    drawCenteredString(y_offset, "Transparent bitmap");
    // lander_display.drawStr(0, 0, "Transparent bitmap");
  }

  int test_offset = y_offset + lander_display.getMaxCharHeight();
  // lander_display.setCursor(0, test_offset);
  // lander_display.print(test_offset);
  const byte frame_size = CROSS_HEIGHT + 4;
  // 0, 36, 60, 44
  // lander_display.drawBox(0, test_offset + frame_size * 0.5,
  //                        frame_size * 5, test_offset + frame_size);
  lander_display.drawBox(0, test_offset,
                         frame_size * 5, frame_size/2);
  lander_display.setDrawColor(0);  // Black
  lander_display.drawXBMP(frame_size * 0.5, test_offset + (frame_size/2)-(CROSS_HEIGHT/2),
                          CROSS_WIDTH, CROSS_HEIGHT, cross_bits);
  lander_display.setDrawColor(1);  // White
  lander_display.drawXBMP(frame_size * 2, test_offset + (frame_size/2)-(CROSS_HEIGHT/2),
                          CROSS_WIDTH, CROSS_HEIGHT, cross_bits);
  lander_display.setDrawColor(2);  // XOR
  lander_display.drawXBMP(frame_size * 3.5, test_offset + (frame_size/2)-(CROSS_HEIGHT/2),
                          CROSS_WIDTH, CROSS_HEIGHT, cross_bits);
  lander_display.setDrawColor(1);   // restore default color

  lander_display.drawStr(frame_size * 0.5, test_offset + frame_size, "Black");
  lander_display.drawStr(frame_size * 2, test_offset + frame_size, "White");
  lander_display.drawStr(frame_size * 3.5, test_offset + frame_size, "XOR");
  if (frame == 7) {
    delay(1000);
  }
}

void display_test_bitmap_overlay(byte y_offset, byte frame) {
  byte frame_size = CROSS_FILL_HEIGHT + 4;
  byte frame_padding = 5;

  drawCenteredString(y_offset, "Bitmap overlay");
  // lander_display.drawStr(0, 0, "Bitmap overlay");

  int test_offset = y_offset + lander_display.getMaxCharHeight();
  lander_display.setBitmapMode(false /* solid */);
  lander_display.drawFrame(0, test_offset, frame_size, frame_size);
  lander_display.drawXBMP((frame_size / 2) - (CROSS_FILL_WIDTH / 2),
                          test_offset + (frame_size / 2) - (CROSS_FILL_HEIGHT / 2),
                          CROSS_WIDTH, CROSS_HEIGHT, cross_bits);
  if (frame & 4)
    lander_display.drawXBMP((frame_size / 2) - (CROSS_BLOCK_WIDTH / 2),
                            test_offset + (frame_size / 2) - (CROSS_BLOCK_HEIGHT / 2),
                            CROSS_BLOCK_WIDTH, CROSS_BLOCK_HEIGHT, cross_block_bits);

  lander_display.setBitmapMode(true /* transparent*/);
  lander_display.drawFrame(frame_size + frame_padding, test_offset,
                           frame_size, frame_size);
  lander_display.drawXBMP(frame_size + frame_padding + (frame_size / 2) - (CROSS_FILL_WIDTH / 2),
                          test_offset + (frame_size / 2) - (CROSS_FILL_HEIGHT / 2),
                          CROSS_WIDTH, CROSS_HEIGHT, cross_bits);
  if (frame & 4)
    lander_display.drawXBMP(frame_size + frame_padding + (frame_size / 2) - (CROSS_BLOCK_WIDTH / 2),
                            test_offset + (frame_size / 2) - (CROSS_BLOCK_HEIGHT / 2),
                            CROSS_BLOCK_WIDTH, CROSS_BLOCK_HEIGHT, cross_block_bits);

  lander_display.drawStr(0, test_offset + frame_size, "Solid / transparent");
  if (frame == 7) {
    delay(1000);
  }
}
