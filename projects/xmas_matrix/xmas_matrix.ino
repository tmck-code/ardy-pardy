// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define WIDTH 16
#define HEIGHT 16

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
  WIDTH, HEIGHT, PIN,
  NEO_MATRIX_TOP  + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_AXIS
);

const uint32_t COLOURS[] = {
  matrix.Color(255, 255, 255),
  matrix.Color(255, 255, 0),
  matrix.Color(0,   255, 0),
  matrix.Color(255,   0, 0),
};

int N_COLOURS = sizeof(COLOURS)/sizeof(COLOURS[0]);

void setup() {
  matrix.begin();
  matrix.setTextWrap(true);
  matrix.setBrightness(1);
  Serial.begin(9600);
}

uint32_t parseStringToColour(String msg) {
  int rIndex = msg.indexOf(',');
  int gIndex = msg.lastIndexOf(',');

  int r = msg.substring(0, rIndex).toInt();
  int g = msg.substring(rIndex+1, gIndex).toInt();
  int b = msg.substring(gIndex+1, msg.length()-1).toInt();

  Serial.println(String(r) + ", " + String(g) + ", " + String(b));

  return matrix.Color(r, g, b);
}

void loop() {
  while (Serial.available() == 0) {} //wait for available data
  uint32_t colour = parseStringToColour(Serial.readString());
  matrix.fillScreen(0);
  matrix.show();

  for (int x = matrix.width(); x--; x>= -16) {
    matrix.setCursor(x, 0);
    matrix.fillScreen(0);
    matrix.print(F("HoHo!"));
    matrix.setTextColor(colour);
    matrix.show();
    delay(50);
  }

  delay(1000);
}
