//Programmable Ring Light
//Uses a button to sycle through colors and special effect sequanses.
//code by Richard Albritton

#include <Adafruit_NeoPixel.h>

#define PIN 0
#define BUTTON 1
#define PHOTOCELL 1    // CdS photocell on GPIO #2 (A1)
#define POT_PIN 3  // 10K potentiometer on GPIO #3 (A3)
#define Pixels 24
Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);

int MODE = 1; // Current display mode.

// ############### For Fire Flicker Mode.
int alpha; // Current value of the pixels.
int dir = 1; // Direction of the pixels... 1 = getting brighter, 0 = getting dimmer
int flip; // Randomly flip the direction every once in a while
int minAlpha = 35; // Min value of brightness
int maxAlpha = 200; // Max value of brightness
int alphaDelta = 5; // Delta of brightness between times through the loop
// ############### End Fire Flicker Mode.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  if(digitalRead(BUTTON) == HIGH) {
    delay(300);
    MODE += 1;
  }
  if(MODE > 5) {
    MODE = 1;
  }
  
// Change the line below to alter the color of the lights
// The numbers represent the Red, Green, and Blue values
// of the lights, as a value between 0(off) and 1(max brightness)

switch (MODE) {
    case 1:
      // ############### Flash Activated - Solid White
      if (analogRead(PHOTOCELL) > 800) {
        colorWipe(strip.Color(250, 250, 250)); // White
        delay(100);
      }
      colorWipe(strip.Color(0, 0, 0)); // off
      break;
    case 2:
      // ############### Solid White
        colorWipe(strip.Color(200, 200, 200)); // White
      break;
    case 3:
      // ############### Solid Orange
      colorWipe(strip.Color(0, 100, 200)); // Orange
      break;
    case 4:
      // ############### Solid Purple
      colorWipe(strip.Color(100, 0, 200)); // Purple
      break;
    case 5:
      // ############### Fire light flicker.
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
    break;
    //default: 
      // statements
  }
  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
  }
}
