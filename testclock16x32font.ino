// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.
/*
 * Created by Pi BOTS MakerHub
 *
 * Email: pibotsmakerhub@gmail.com
 * 
 * Github: https://github.com/pibotsmakerhub
 *
 * Join Us on Telegram : https://t.me/pibots 
 * Copyright (c) 2020 Pi BOTS MakerHub
*/

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11

#include <RGBmatrixPanel.h>
#include "Wire.h"
#define DS3231_I2C_ADDRESS 0x68
#include <Adafruit_GFX.h>    // Core graphics library
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeMono9pt7b.h>

GFXcanvas1 canvas(16, 32); // 128x32 pixel canvas

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val){
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val){
  return( (val/16*10) + (val%16) );
}
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

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
{
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}
  matrix.begin();

  Wire.begin();
  Serial.begin(9600);
  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
 setDS3231time(30,36,17,6,26,3,12);
}
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year){
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year){
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
void displayTime(){
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor / rgb



  
  matrix.setTextColor(matrix.Color333(7,0,0));  //set text to red
    
  matrix.setCursor(0, 1);  // start at top left, with no pixel of spacing
  matrix.setTextSize(1);   // size 1 == 8 pixels high
  matrix.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
   matrix.print(":");
  if (minute<10){
     matrix.print("0");
  }
  matrix.print(minute, DEC);
 //matrix.print(":");
 if (second<10){
  //   matrix.print("0");
  }
 matrix.setCursor(0, 9);  // next line
  matrix.setTextSize(1);   // size 1 == 8 pixels high
  
//matrix.print(" ");
 //  matrix.print(dayOfMonth, DEC);
 // matrix.print("/");
  // matrix.print(month, DEC);
      // matrix.setTextColor(matrix.Color333(7,0,0));  
  float t = dht.readTemperature();
    float h = dht.readHumidity();
  float f = dht.readTemperature(true);

    // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
 matrix.print(t);

  // matrix.print(second, DEC);
//Serial.print("/");
  //  Serial.print(year, DEC);
 // Serial.print(" Day of week: ");
 // switch(dayOfWeek){
 // case 1:
 //   Serial.println("Sunday");
  //  break;
 // case 2:
 //   Serial.println("Monday");
//    break;
 // case 3:
 //   Serial.println("Tuesday");
 //   break;
//  case 4:
 //   Serial.println("Wednesday");
//    break;
//  case 5:
 //   Serial.println("Thursday");
 //   break;
 // case 6:
 //   Serial.println("Friday");
 //   break;
 // case 7:
  //  Serial.println("Saturday");
 //   break;
//  }



  // draw an 'X' in red
 //matrix.drawLine(0, 0, 31, 15, matrix.Color333(7, 0, 0));
 //matrix.drawLine(31, 0, 0, 15, matrix.Color333(7, 0, 0));
 // delay(500);



}

void loop(){
  // Wait a few seconds between measurements.
  //delay(2000);

 
   displayTime(); // display the real-time clock data on the Serial Monitor,
  delay(60000); // every min
 matrix.fillScreen(matrix.Color333(0, 0, 0));   // fill the screen with black
  // Do nothing -- image doesn't change
}
