  /*
 * Analog in 4 & 5
 * (en dat kan niet anders: http://bildr.org/2011/03/ds1307-arduino/)
 * SDA = 4
 * SCL = 5
 */

#include "Clock.h"

#include "Wire.h"
#define DS1307_ADDRESS 0x68

Clock::Clock() {
  Wire.begin();
   
   _clock_millis_last = 0;
   _clock_minutes = 0;
   previousSetTime = 0;
}

int Clock::readTimeTimed() {

  unsigned long millis_diff = millis() - _clock_millis_last;
  if (millis_diff > 1000) {  

    _clock_minutes = readTime();
    _clock_millis_last = millis();

  }
  return _clock_minutes;
}

// Convert binary coded decimal to normal decimal numbers
byte Clock::bcdToDec(byte val)  {
  return ( (val/16*10) + (val%16) );
}

// Convert normal decimal numbers to binary coded decimal
byte Clock::decToBcd(byte val) {
  return ( (val/10*16) + (val%10) );
}

int Clock::readTime() {
   // Reset the register pointer
  Wire.beginTransmission(DS1307_ADDRESS);

  byte zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  // Read everything, only keep hour and minute  
  
  bcdToDec(Wire.read());
  
  int minute = bcdToDec(Wire.read());
  int hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
  
  bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
  bcdToDec(Wire.read());
  bcdToDec(Wire.read());
  bcdToDec(Wire.read());
 
  return hour * 60 + minute;
}

void Clock::setTime(int minutes) {
  if (previousSetTime != minutes) {
    previousSetTime = minutes;
    int minute = ((int) minutes + MINUTES_PER_DAY) % MINUTES_PER_DAY;
    int hour = minute / 60;
    minute = minute % 60;  
    
    int second = 0;
    //int minute = 15;
    //int hour  = 12;
    int dayOfWeek = 1;
    int dayOfMonth = 1;
    int month = 1;
    int year= 10;
     
    Wire.beginTransmission(DS1307_ADDRESS);
    byte zero = 0x00;
    Wire.write (zero);
    Wire.write (decToBcd(second) & 0x7f);    // 0 to bit 7 starts the clock
    Wire.write (decToBcd(minute));
    Wire.write (decToBcd(hour));      // If you want 12 hour am/pm you need to set
                                     // bit 6 (also need to change readDateDs1307)
    Wire.write (decToBcd(dayOfWeek));
    Wire.write (decToBcd(dayOfMonth));
    Wire.write (decToBcd(month));
    Wire.write (decToBcd(year));
    Wire.endTransmission();
  }
}
