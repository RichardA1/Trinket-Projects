//Programmable Ring Light
//Uses a button to sycle through colors and special effect sequanses.
//code by Richard Albritton

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 0
#define Pixels 12
Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN);


//For Fire Flicker Mode.
int alpha; // Current value of the pixels.
int dir = 1; // Direction of the pixels... 1 = getting brighter, 0 = getting dimmer
int flip; // Randomly flip the direction every once in a while
int minAlpha = 35; // Min value of brightness
int maxAlpha = 200; // Max value of brightness
int alphaDelta = 5; // Delta of brightness between times through the loop


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  
    flip = random(32);
  if(flip > 20) {
    dir = 1 - dir;
  }
  // Some example procedures showing how to display to the pixels:
  if (dir == 1) {
    alpha += alphaDelta;
  }
  if (dir == 0) {
    alpha -= alphaDelta;
  }
  if (alpha < minAlpha) {
    alpha = minAlpha;
    dir = 1;
  }
  if (alpha > maxAlpha) {
    alpha = maxAlpha;
    dir = 0;
  }
  colorWipe(strip.Color(alpha, alpha/2, 0)); // Fire
  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
  }
}
