// A basic everyday NeoPixel strip test program.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif

#define LED_PIN   13
#define LED_COUNT 50
int PIXEL_OFFSET = 0;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(10); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {
  int sleep = 600;
  for (int i=0; i<5; i++) {
    colorWipe(strip.Color(255,   0,   0), sleep); // Red
    xmas(sleep);
    colorWipe(strip.Color(  0, 255,   0), sleep); // Green
    xmas(sleep);
    colorWipe(strip.Color(  255, 255,   0), sleep); // Green
    xmas(sleep);
  }
  // rainbow(sleep);
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
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

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 65536/6; firstPixelHue < 65536/2; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}