/*
 * 30 Days - Lost in Space
 * Day 22 - Hello New World!
 *
 * Even our new OLED display is a bit small if we have large amounts of
 * information to display.  But this new display isn't limited to JUST
 * text!  It is a 128x64 pixel display and we can turn any of them on/off
 * to display whatever we like, including graphics.
 *
 * Today we'll run a "readiness check" on our new display to test out its
 * full capabilities.
 *
 * Learn more at https://inventr.io/adventure
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - 
 * - 
 * - 
 *
 * Parts and electronics concepts introduced in this lesson.
 * - 
 */

// Explicitly include Arduino.h
#include "Arduino.h"
#include "Wire.h"

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

/*
 * For our main loop() we will cycle through each test page, displaying
 * 8 frames for each test (which allows animation on each page).
 *
 * Rather than use two variables, one to track the page and one to track
 * the frame, we will demonstrate the use of the "bitshift" operators (">>"
 * and "<<") in conjunction with the bitwise and" to use a single variable.
 *
 * While this method is less clear, it is sometimes used when memory is very
 * tight since it uses less data storage.
 */
void loop(void) {
  const byte TEST_PAGE_COUNT = 13;
  for (unsigned int display_frame = 0; display_frame < (TEST_PAGE_COUNT * 8); display_frame++) {
    lander_display.clearBuffer();  // clear the internal memory

    // setCursor() will set the x/y location of the upper left bit of each string
    lander_display.setFont(u8g_font_6x10);
    lander_display.setFontRefHeightExtendedText();
    lander_display.setFontPosTop();

    // Title line for our display displayed on each screen
    drawCenteredString(0, 0, "Exploration Lander");  // Center title at top of display

    // To leave the title above each display we offset the y starting point
    // by the maximum character height of our selected font.
    byte y_offset = lander_display.getMaxCharHeight();  // maximum height of current font

    display_frame = (display_frame & 7) | (1 << 3);
    switch (display_frame >> 3) {
      case 0: display_test_ready(y_offset, display_frame & 7); break;
      case 1: display_test_box_frame(y_offset, display_frame & 7); break;
      case 2: display_test_circles(y_offset, display_frame & 7); break;
      case 3: display_test_r_frame(y_offset, display_frame & 7); break;
      case 4: display_test_string(y_offset, display_frame & 7); break;
      case 5: display_test_line(y_offset, display_frame & 7); break;
      case 6: display_test_triangle(y_offset, display_frame & 7); break;
      case 7: display_test_ascii_1(y_offset); break;
      case 8: display_test_ascii_2(y_offset); break;
      case 9: display_test_extra_page(y_offset, display_frame & 7); break;
      case 10: display_test_bitmap_modes(y_offset, display_frame & 7, false); break;
      case 11: display_test_bitmap_modes(y_offset, display_frame & 7, true); break;
      case 12: display_test_bitmap_overlay(y_offset, display_frame & 7); break;
    }
    lander_display.sendBuffer();
    delay(50);
  }
}

// Use the .drawStr() method to draw a string in the display centered
// horizontally between the given X coordinate and the maximum X.
// Y coordinate is unchanged and text is displayed relative to the
// current font positioning mode (Top, Center, Bottom).
byte drawCenteredString(byte x, byte y, char *string) {
  byte centered_x = x + ((lander_display.getDisplayWidth() - x) - lander_display.getStrWidth(string)) / 2;
  lander_display.drawStr(centered_x, y, string);
}

const byte LANDER_HEIGHT = 25;    // height of our lander image, in bits
const byte LANDER_WIDTH = 20;     // width of our lander image, in bits

// Draw an image of our lander drawn with frames and triangles
// at location x_location, y_location (relative to the upper left corner).
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

// Page 0: Display lander drawing and blinking begin message
void display_test_ready(byte y_offset, byte frame) {
  // Y value halfway between top and bottom of drawable area
  const byte Y_CENTER = y_offset + ((lander_display.getDisplayHeight() - y_offset) / 2);

  // Since our lander drawing's location is set using the upper-left
  // coordinates we will subtract half our drawing's height to center
  // it vertically.
  //
  // We will also shift it right by adding a "padding" amount to the
  // lander's X coordinate.
  const byte LANDER_PADDING = LANDER_WIDTH;   // shift lander right by its width
  const byte LANDER_Y_CENTER = Y_CENTER - (LANDER_HEIGHT / 2);
  display_lander(LANDER_PADDING, LANDER_Y_CENTER);

  // Blink the "ready" message by only displaying it every other frame
  // by extracting the rightmost bit of our frame number and only displaying
  // the message if the bit is 0 (frames 0, 2, 4, 6).
  if ((frame & 0b00000001) == 0) {
    // Determine remaining space to the right of our lander for our message.
    // The lander image extends from its starting X position plus its width.
    const byte X_OFFSET = LANDER_PADDING + LANDER_WIDTH;

    // get the height of each text line since it's used multiple times below
    byte text_height = lander_display.getMaxCharHeight();

    lander_display.setFontPosCenter();  // Y coordinate relative to center of font height
    // Display line 1 on display, one line above center
    drawCenteredString(X_OFFSET, Y_CENTER - text_height, "Begin");

    // Display line 2, vertically centered in space below title
    drawCenteredString(X_OFFSET, Y_CENTER, "Hardware");

    // Display line 3 on display, one line below center
    drawCenteredString(X_OFFSET, Y_CENTER + text_height, "Test");
  }
}

// Page 1: Display filled and hollow boxes with one moving every frame.

// Here we define constants for our box size and coordinates.  This is
// done so they can be changed in one place, and it also makes it clear
// what the MEANINGS of each number are in the code below.  It changes
// code like:
// .drawBox(5,10,20,10);
// to:
// .drawBox(BOX1_X_OFFSET, y_offset, BOX1_WIDTH, BOX1_HEIGHT);
const byte BOX1_WIDTH = 20;
const byte BOX1_HEIGHT = 10;
const byte BOX1_X_OFFSET = 5;
const byte BOX2_X_OFFSET = BOX1_X_OFFSET * 2;
const byte BOX2_Y_OFFSET = BOX1_HEIGHT / 2;

void display_test_box_frame(byte y_offset, byte frame) {
  drawCenteredString(0, y_offset, "drawBox");
  y_offset += lander_display.getMaxCharHeight();
  // Draw a line around a box at coordinates x, y with width and height.
  lander_display.drawBox(BOX1_X_OFFSET, y_offset, BOX1_WIDTH, BOX1_HEIGHT);
  lander_display.drawBox(BOX2_X_OFFSET + frame, y_offset + BOX2_Y_OFFSET,
                         BOX1_WIDTH + 10, BOX1_HEIGHT - 2);

  y_offset += BOX1_HEIGHT + (BOX1_HEIGHT - 2);
  drawCenteredString(0, y_offset, "drawFrame");
  y_offset += lander_display.getMaxCharHeight();
  lander_display.drawFrame(BOX1_X_OFFSET, y_offset, 20, 10);
  lander_display.drawFrame(BOX2_X_OFFSET + frame, y_offset + BOX2_Y_OFFSET,
                           BOX1_WIDTH + 10, BOX1_HEIGHT - 2);
}

// Page 2: Display filled and hollow circles with one moving every frame.
void display_test_circles(byte y_offset, byte frame) {
  drawCenteredString(0, y_offset, "drawDisc");
  lander_display.drawDisc(10, y_offset + 18, 8);
  lander_display.drawDisc(24 + frame, y_offset + 16, 7);

  drawCenteredString(0, y_offset + 27, "drawCircle");
  lander_display.drawCircle(10, y_offset + 18 + 27, 8);
  lander_display.drawCircle(24 + frame, y_offset + 18 + 25, 6);
}

// Display filled and hollow boxes with rounded corners
void display_test_r_frame(byte y_offset, byte frame) {
  drawCenteredString(0, y_offset, "drawRFrame/Box");
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
  drawCenteredString(0, y_offset, "drawLine");
  int test_offset = y_offset + lander_display.getMaxCharHeight();
  lander_display.drawLine(7 + frame, test_offset, 40, 55);
  lander_display.drawLine(7 + frame * 2, test_offset, 60, 55);
  lander_display.drawLine(7 + frame * 3, test_offset, 80, 55);
  lander_display.drawLine(7 + frame * 4, test_offset, 100, 55);
}

void display_test_triangle(byte y_offset, byte frame) {
  drawCenteredString(0, y_offset, "drawTriangle");

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
  drawCenteredString(0, y_offset, "ASCII page 1");
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
  drawCenteredString(0, y_offset, "ASCII page 2");
  int test_offset = y_offset + lander_display.getMaxCharHeight();
  for (y = 0; y < 6; y++) {
    for (x = 0; x < 16; x++) {
      s[0] = y * 16 + x + 160;
      lander_display.drawStr(x * 7, y * lander_display.getMaxCharHeight() + test_offset, s);
    }
  }
}

void display_test_extra_page(byte y_offset, byte frame) {
  drawCenteredString(0, y_offset, "Unicode");
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
    drawCenteredString(0, y_offset, "Solid bitmap");
  } else {
    lander_display.setBitmapMode(true /* transparent*/);
    drawCenteredString(0, y_offset, "Transparent bitmap");
  }

  int test_offset = y_offset + lander_display.getMaxCharHeight();
  const byte frame_size = CROSS_HEIGHT + 4;
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

  drawCenteredString(0, y_offset, "Bitmap overlay");

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
