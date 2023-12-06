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

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(true);
  matrix.setBrightness(5);
}

void loop() {
  for (int r = 50; r<255; r+=10) {
    for (int g = 50; g<255; g+=10) {
      for (int b = 50; b<255; b+=10) {
        serial_printf(Serial, "r: %d, g: %d, b: %d\n", r, g, b);
        for (int y = 0; y<HEIGHT; y++) {
          for (int x = 0; x<WIDTH; x++) {
            matrix.drawPixel(x, y, matrix.Color(r, g, b));
          }
          matrix.show();
          delay(20);
        }
      }
    }
  }
}
