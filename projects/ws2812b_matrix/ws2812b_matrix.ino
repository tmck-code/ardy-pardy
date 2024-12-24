// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <SerialPrintf.h>

#define PIN 6
#define WIDTH 16
#define HEIGHT 16
char *choice;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
  WIDTH, HEIGHT, PIN,
  NEO_MATRIX_TOP  + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_AXIS
);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

const char* xmas_tree[][16] = {
  {" ", " ", " ", " ", " ", " ", " ", "Z", " ", " ", " ", " ", " ", " ", " ", " "},
  {" ", " ", " ", " ", " ", " ", "Y", "X", "Y", " ", " ", " ", " ", " ", " ", " "},
  {" ", " ", " ", " ", " ", "Z", "X", "X", "X", "Z", " ", " ", " ", " ", " ", " "},
  {" ", " ", " ", " ", " ", "Y", "X", "X", "X", "X", " ", " ", " ", " ", " ", " "},
  {" ", " ", " ", " ", "Z", "X", "Z", "X", "X", "X", "Z", " ", " ", " ", " ", " "},
  {" ", " ", " ", " ", "X", "X", "X", "X", "X", "X", "X", " ", " ", " ", " ", " "},
  {" ", " ", " ", "Z", "X", "X", "X", "X", "X", "X", "X", "Z", " ", " ", " ", " "},
  {" ", " ", " ", "X", "X", "X", "X", "X", "Z", "Y", "X", "X", " ", " ", " ", " "},
  {" ", " ", "Z", "X", "X", "Y", "X", "X", "X", "X", "X", "X", "Z", " ", " ", " "},
  {" ", " ", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", " ", " ", " "},
  {" ", "Z", "X", "X", "X", "Z", "X", "X", "X", "X", "X", "X", "X", "Z", " ", " "},
  {" ", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", " ", " "},
  {"Z", "X", "X", "X", "X", "Y", "X", "X", "X", "X", "Z", "X", "X", "X", "Z", " "},
  {" ", " ", " ", " ", " ", " ", " ", "O", " ", " ", " ", " ", " ", " ", " ", " "},
  {" ", " ", " ", " ", " ", " ", " ", "O", " ", " ", " ", " ", " ", " ", " ", " "},
  {" ", " ", " ", " ", " ", " ", " ", "O", " ", " ", " ", " ", " ", " ", " ", " "},
};

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setBrightness(5);
}

void drawXmasTree(int x_offset, int y_offset, bool flash) {
  for (int y = 0; y<HEIGHT; y++) {
    for (int x = 0; x<WIDTH; x++) {
      if (xmas_tree[y][x] == " ") {
        matrix.drawPixel((x+x_offset)%16, (y+y_offset)%16, matrix.Color(0, 0, 0));
      } else if (xmas_tree[y][x] == "X") {
        matrix.drawPixel((x+x_offset)%16, (y+y_offset)%16, matrix.Color(0, 255, 0));
      } else if (xmas_tree[y][x] == "O") {
        matrix.drawPixel((x+x_offset)%16, (y+y_offset)%16, matrix.Color(255, 0, 0));
      } else if (xmas_tree[y][x] == "Z") {
        if (flash == true) {
          matrix.drawPixel((x+x_offset)%16, (y+y_offset)%16, matrix.Color(255, 255, 0));
        } else {
          matrix.drawPixel((x+x_offset)%16, (y+y_offset)%16, matrix.Color(255, 0, 0));
        }
      } else if (xmas_tree[y][x] == "Y") {
        if (flash == true) {
          matrix.drawPixel((x+x_offset)%16, (y+y_offset)%16, matrix.Color(0, 255, 0));
        } else {
          matrix.drawPixel((x+x_offset)%16, (y+y_offset)%16, matrix.Color(0, 0, 255));
        }
      }
    }
  }
  matrix.show();
  delay(100);
}

void loop() {
  for (int x = 0; x<=16; x++) {
    drawXmasTree(x, 0, true);
  }
  bool flash = true;
  for (int i=0; i<4; i++) {
    drawXmasTree(0, 0, flash);
    flash = !flash;
    delay(300);
  }
  delay(600);
  for (int y = 0; y<=16; y++) {
    drawXmasTree(0, y, false);
  }
  flash = false;
  for (int i = 0; i <4; i++) {
    drawXmasTree(0, 0, flash);
    flash = !flash;
    delay(300);
  }
  delay(600);
  for (int y = 0; y<=32; y++) {
    if (y <= 16) {
      drawXmasTree(y, y, true);
    } else {
      drawXmasTree(y, y, false);
    }
  }
  delay(600);
  flash = true;
  for (int i = 0; i <3; i++) {
    drawXmasTree(0, 0, flash);
    flash = !flash;
    delay(300);
  }
  delay(600);
}
