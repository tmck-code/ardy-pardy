// A basic everyday NeoPixel strip test program.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif

#define LED_PIN   13
#define LED_COUNT 50
#define SLEEP 250
int PIXEL_OFFSET = 0;

#define WHITE  0
#define RED    1
#define YELLOW 2
#define GREEN  3

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Green, Yellow
uint32_t COLOURS[] = {
  strip.Color(255, 255, 255),
  strip.Color(255,   0, 0),
  strip.Color(255, 255, 0),
  strip.Color(0,   255, 0)
};

int N_COLOURS = sizeof(COLOURS)/sizeof(COLOURS[0]);
uint32_t XMAS_DUO[2] = {RED, GREEN};

void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(50);
  strip.show();

  Serial.println("Starting XMAS display with " + String(N_COLOURS) + " colours:");
}

void loop() {
  for (int i=0; i<N_COLOURS; i++) {
    colorWipe(COLOURS[i], SLEEP);
    xmas(XMAS_DUO, sizeof(XMAS_DUO)/sizeof(XMAS_DUO[0]), YELLOW);
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

void xmas(uint32_t repeat_colours[], int n_colours, int highlight_colour) {
  for (int i=1; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, COLOURS[highlight_colour]);
    strip.setPixelColor(i-1, COLOURS[repeat_colours[i % n_colours]]);
    strip.show();
    delay(SLEEP);
  }
}
