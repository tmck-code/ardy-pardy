// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 4
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

void setPixelByIndex(int idx, int r, int g, int b) {
  int curr = 0;
  for (int y = 0; y<HEIGHT; y++) {
    for (int x = 0; x<WIDTH; x++) {
      if (curr == idx) {
        matrix.drawPixel(x, y, matrix.Color(r, g, b));
        return;
      }
      curr++;
    }
  }
}

void makeColorGradient(float frequency1, float frequency2, float frequency3,
                            float phase1, float phase2, float phase3,
                            float center, int width, int len)
{
  if (center == 0)   center = 128;
  if (width == 0)    width = 127;
  if (len == 0)      len = 50;

  for (int i = 0; i < len; ++i)
  {
      int r = sin(frequency1*i + phase1) * width + center;
      int g = sin(frequency2*i + phase2) * width + center;
      int b = sin(frequency3*i + phase3) * width + center;
      Serial.println(String(r)+","+String(g)+","+String(b));
      // setColour(r,g,b);
      setPixelByIndex(i, r, g, b);

      if (i % 2 == 0) {
        matrix.show();
      }
  }
  matrix.show();
}

void setColour(int r, int g, int b) {
  for (int y = 0; y<HEIGHT; y++) {
    for (int x = 0; x<WIDTH; x++) {
      matrix.drawPixel(x, y, matrix.Color(r, g, b));
    }
  }
  matrix.show();
}
int r = 0;
int g = 0;
int b = 0;

int current = 0;
String line = "";

void readRGB() {
  if (Serial.available() > 0) {
    line = Serial.readString();
    if (current == 0) {
      r = line.toInt();
      Serial.println("r:"+line);
    }
    if (current == 1) {
      g = line.toInt();
      Serial.println("g:"+line);
    }
    if (current == 2) {
      b = line.toInt();
      Serial.println("rgb:"+String(r)+","+String(g)+","+String(b));
      setColour(r, g, b);
    }
    current = (current+1)%3;
  }
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

int SLEEP = 3000;

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(true);
  matrix.setBrightness(5);
}

void loop() {
  setColour(100, 0, 0);
  makeColorGradient(.05,.1,.15,0,2,4,192,64,256);
  delay(SLEEP);
}
