// A basic everyday NeoPixel strip test program.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif

#define LED_PIN   13
#define LED_COUNT 50
int PIXEL_OFFSET = 0;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

long COLOURS[] = {strip.Color(255, 0, 0), strip.Color(255, 255, 0)};

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(255);
}

void loop() {
  int sleep = 200;
  for (int i=0; i<sizeof(COLOURS)-1; i++) {
    colorWipe(COLOURS[i], sleep);
    xmas(sleep);
  }
}

// Fill strip pixels one after another with a color, and delay in ms.
// Strip is NOT cleared first; anything there will be covered pixel by pixel
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void xmas(int wait) {
  strip.setPixelColor(0, strip.Color(150, 150, 0));
  for(int i=PIXEL_OFFSET; i<strip.numPixels(); i+=4) {
    strip.setPixelColor(i, strip.Color(255, 255, 0));
    strip.setPixelColor(i+1, strip.Color(255, 255, 0));
    strip.show();
    delay(wait);
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.setPixelColor(i+2, strip.Color(255, 255, 0));
    strip.show();
    delay(wait);
    strip.setPixelColor(i+1, strip.Color(0, 255, 0));
    strip.setPixelColor(i+3, strip.Color(255, 255, 0));
    strip.show();
    delay(wait);
    strip.setPixelColor(i+2, strip.Color(255, 0, 0));
    strip.setPixelColor(i+3, strip.Color(0, 255, 0));
  }
  if (PIXEL_OFFSET == 0) {
    PIXEL_OFFSET = 1;
  } else {
    PIXEL_OFFSET = 0;
  }
}
