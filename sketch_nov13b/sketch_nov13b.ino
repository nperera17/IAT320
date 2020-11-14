///
// Circuit Playground Slouch Detector v3
//
// Push button(s) to set a target angle.
// Compute current angle using accelerometer and compare
// to preset slouch angle. Sound alarm if slouching after
// a preset period of time.
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)
 
#include <Adafruit_CircuitPlayground.h>

#define COLOR         0x0BFFFF    // change this to your favorite color    
#define SPIN_RATE     100         // lower is faster
 
int pixel1;
int pixel2;
 
#define SLOUCH_ANGLE        10.0      // allowable slouch angle (deg)
#define SLOUCH_TIME         3000      // allowable slouch time (secs) 
#define GRAVITY             9.80665   // standard gravity (m/s^s)
#define RAD2DEG             52.29578  // convert radians to degrees
 
float currentAngle;
float targetAngle;
unsigned long slouchStartTime;
bool slouching;
 
///////////////////////////////////////////////////////////////////////////////
void setup() {
  // Initialize Circuit Playground
  CircuitPlayground.begin();

    // Make it bright!
  CircuitPlayground.setBrightness(255);
 
  // Can be any two pixels
  pixel1 = 0;
  pixel2 = 5;
 
  // Initialize target angle to zero.
  targetAngle = 0;
}
 
///////////////////////////////////////////////////////////////////////////////
void loop() {
   // Turn off all the NeoPixels
  CircuitPlayground.clearPixels();
 
  // Turn on two pixels to COLOR
  CircuitPlayground.setPixelColor(pixel1, COLOR);
  CircuitPlayground.setPixelColor(pixel2, COLOR);
 
  // Increment pixels to move them around the board
  pixel1 = pixel1 + 1;
  pixel2 = pixel2 + 1;
 
  // Check pixel values
  if (pixel1 > 9) pixel1 = 0;
  if (pixel2 > 9) pixel2 = 0;
 
  // Wait a little bit so we don't spin too fast
  delay(SPIN_RATE);
  
  
  // Compute current angle
  currentAngle = RAD2DEG * asin(-CircuitPlayground.motionZ() / GRAVITY);
 
  // Set target angle on button press
  if ((CircuitPlayground.leftButton()) || (CircuitPlayground.rightButton())) {
    targetAngle = currentAngle;
    CircuitPlayground.playTone(900,100);
    delay(100);
    CircuitPlayground.playTone(900,100);
    delay(100);
  }
  
  // Check for slouching
  if (currentAngle - targetAngle > SLOUCH_ANGLE) {
    if (!slouching) slouchStartTime = millis();
    slouching = true;
  } else {
    slouching = false;
  }
 
  // If we are slouching
  if (slouching) {
    // Check how long we've been slouching
    if (millis() - slouchStartTime > SLOUCH_TIME) {
      // Play a tone
      CircuitPlayground.playTone(800, 500);    
    }    
  }
}
