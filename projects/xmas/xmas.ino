// A basic everyday NeoPixel strip test program.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif

#define LED_PIN   13
#define LED_COUNT 50
#define SLEEP     250
int PIXEL_OFFSET = 0;

#define WHITE   0
#define YELLOW  1
#define GREEN   2
#define RED     3
#define PINK    4
#define CYAN    5
#define MAGENTA 6
#define BLUE    7

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Green, Yellow
// colours are Green, Red, Blue
uint32_t COLOURS[][3] = {
  {255, 255, 255},
  {255, 255, 0},
  {0,   255, 0},
  {255,   0, 0},
  {0, 255, 255},
  {255, 0, 255},
  {0, 255, 100},
  {0, 0, 255},
};

int N_COLOURS = sizeof(COLOURS)/sizeof(COLOURS[0]);
uint32_t XMAS_DUO[2] = {RED, GREEN};
uint32_t XMAS_TRIO[3] = {RED, GREEN, YELLOW};

uint8_t mix(uint8_t a, uint8_t b, int pct, int range) {
    if (pct <= 0) return a;
    if (pct >= range) return b;
    return (((uint32_t)a * (range-pct)) / range) + (((uint32_t)b * pct) / range);
}

void grad(uint8_t red1, uint8_t green1, uint8_t blue1, uint8_t red2, uint8_t green2, uint8_t blue2) {
  for (int i = 0; i < LED_COUNT; i++) {
    uint8_t red = mix(red1, red2, i, LED_COUNT);
    uint8_t green = mix(green1, green2, i, LED_COUNT);
    uint8_t blue = mix(blue1, blue2, i, LED_COUNT);
    strip.setPixelColor(i, strip.Color(red, green, blue));
    delay(100);
    strip.show();
  }
}
void grad_rev(uint8_t red1, uint8_t green1, uint8_t blue1, uint8_t red2, uint8_t green2, uint8_t blue2) {
  for (int i = LED_COUNT; i >= 0; i--) {
    uint8_t red = mix(red1, red2, i, LED_COUNT);
    uint8_t green = mix(green1, green2, i, LED_COUNT);
    uint8_t blue = mix(blue1, blue2, i, LED_COUNT);
    strip.setPixelColor(i, strip.Color(red, green, blue));
    delay(100);
    strip.show();
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
    strip.setPixelColor(i, strip.Color(COLOURS[highlight_colour][0], COLOURS[highlight_colour][1], COLOURS[highlight_colour][2]));
    strip.setPixelColor(
      i-1,
      strip.Color(
        COLOURS[repeat_colours[i % n_colours]][0], COLOURS[repeat_colours[i % n_colours]][1], COLOURS[repeat_colours[i % n_colours]][2]
      )
    );
    strip.show();
    delay(SLEEP);
  }
}

void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(50);
  strip.show();

  Serial.println("Starting XMAS display with " + String(N_COLOURS) + " colours");
}

void loop() {
  for (int i=0; i<N_COLOURS; i++) {
    grad_rev(COLOURS[3][0], COLOURS[3][1], COLOURS[3][2], COLOURS[7][0], COLOURS[7][1], COLOURS[7][2]);
    grad(COLOURS[i][0], COLOURS[i][1], COLOURS[i][2], COLOURS[i+1][0], COLOURS[i+1][1], COLOURS[i+1][2]);
    colorWipe(COLOURS[i], SLEEP);
    for (int j=1; j<N_COLOURS; j++) {
      if (j % 2 == 0) {
        uint32_t colours_duo[2] = {i, (i+j)%(sizeof(COLOURS))};
        xmas(colours_duo, sizeof(colours_duo), YELLOW);
      } else {
        uint32_t colours_trio[3] = {i, (i+1)%(sizeof(COLOURS)), (i+j)%sizeof(COLOURS)};
        xmas(colours_trio, sizeof(XMAS_TRIO), WHITE);
      }
    }
  }
}