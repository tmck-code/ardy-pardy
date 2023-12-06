// A basic everyday NeoPixel strip test program.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif

#define LED_PIN   13
#define LED_COUNT 50
#define SLEEP     250
int PIXEL_OFFSET = 0;

#define WHITE  0
#define YELLOW 1
#define GREEN  2
#define RED    3
#define PINK   4
#define CYAN   5
#define MAGENTA 6

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Green, Yellow
// colours are Green, Red, Blue
uint32_t COLOURS[] = {
  strip.Color(255, 255, 255),
  strip.Color(255, 255, 0),
  strip.Color(0,   255, 0),
  strip.Color(255,   0, 0),
  strip.Color(0, 255, 255),
  strip.Color(255, 0, 255),
  strip.Color(0, 255, 100),
};
int N_COLOURS = sizeof(COLOURS)/sizeof(COLOURS[0]);
uint32_t XMAS_DUO[2] = {RED, GREEN};
uint32_t XMAS_TRIO[3] = {RED, GREEN, YELLOW};

void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(50);
  strip.show();

  Serial.println("Starting XMAS display with " + String(N_COLOURS) + " colours");
}

void loop() {
  for (int i=0; i<N_COLOURS; i++) {
    colorWipe(COLOURS[i], SLEEP);
    for (int j=1; j<N_COLOURS; j++) {
      if (i % 2 == 0) {
        uint32_t colours_duo[2] = {i, (i+j)%(sizeof(COLOURS)/sizeof(COLOURS[0]))};
        xmas(colours_duo, sizeof(colours_duo)/sizeof(colours_duo[0]), YELLOW);
      } else {
        uint32_t colours_trio[3] = {i, (i+1)%(sizeof(COLOURS)/sizeof(COLOURS[0])), (i+j)%sizeof(COLOURS)/sizeof(COLOURS[0])};
        xmas(colours_trio, sizeof(XMAS_TRIO)/sizeof(XMAS_TRIO[0]), WHITE);
      }
    }
  }
}

// Fill strip pixels one after another with a color, and delay in ms.
// Strip is NOT cleared first; anything there will be covered pixel by pixel
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
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
