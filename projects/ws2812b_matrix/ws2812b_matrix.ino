// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

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

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(true);
  matrix.setBrightness(5);
}

void horizontal(int r, int g, int b, int delay_ms = 20) {
  Serial.println(String(r)+","+String(g)+","+String(b)+",");
  for (int y = 0; y<HEIGHT; y++) {
    for (int x = 0; x<WIDTH; x++) {
      matrix.drawPixel(x, y, matrix.Color(r, g, b));
    }
    matrix.show();
    delay(delay_ms);
  }
}

void solid(int r, int g, int b, int delay_ms = 20) {
  Serial.println(String(r)+","+String(g)+","+String(b)+",");
  for (int y = 0; y<HEIGHT; y++) {
    for (int x = 0; x<WIDTH; x++) {
      matrix.drawPixel(x, y, matrix.Color(r, g, b));
    }
  }
  matrix.show();
}

void strip(int r, int g, int b, int xs, int width) {
  Serial.println(String(r)+","+String(g)+","+String(b)+","+String(xs)+","+String(width));
  for (int y = 0; y<HEIGHT; y++) {
    for (int x = 0; x<width; x++) {
      matrix.drawPixel(x+xs, y, matrix.Color(r, g, b));
    }
  }
  matrix.show();
}


void loop() {
  for (int r = 110; r<255; r+=10) {
    for (int g = 110; g<255; g+=10) {
      for (int b = 110; b<255; b+=10) {
        strip(r, g, b, 3, 2);
        delay(200);
      }
    }
  }
}
