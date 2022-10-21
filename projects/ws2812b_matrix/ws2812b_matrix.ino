// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <SerialPrintf.h>

#define PIN 6
#define WIDTH 16
#define HEIGHT 16

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
  WIDTH, HEIGHT, PIN,
  NEO_MATRIX_BOTTOM  + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_AXIS
);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setBrightness(10);
}

void loop() {
  matrix.fillScreen(matrix.Color(0, 0, 0));
  Serial.println("looping main");
  delay(1000);
  for (int y = 0; y<HEIGHT; y++) {
    for (int x = 0; x<WIDTH; x++) {
      matrix.drawPixel(x, y, matrix.Color(255, 0, 0));
      matrix.show();
      delay(200);
    }
  }
}
