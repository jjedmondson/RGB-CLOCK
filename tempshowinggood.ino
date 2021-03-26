// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <RGBmatrixPanel.h>
#include <dht11.h>
#define DHT11PIN 2
// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
dht11 DHT11;

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  Serial.begin(9600);


}

void loop() 
{ 
  //matrix.println(); 
  int chk = DHT11.read(DHT11PIN);

  matrix.begin();
  matrix.fillRect(0, 0, 32, 16, matrix.Color333(0, 0, 0));
   // draw some text!
  matrix.setTextColor(matrix.Color333(1,0,0));
  matrix.setCursor(1, 0);  // start at top left, with one pixel of spacing
 // matrix.print('TEST');
   matrix.print((float)DHT11.humidity, 2);
 matrix.setTextSize(1);   // size 1 == 8 pixels high
  matrix.setCursor(1, 9);  // next line
 matrix.print((float)DHT11.temperature, 2);
 // Do nothing -- image doesn't change   
 delay(2000);

}
