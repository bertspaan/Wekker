#include "Arduino.h"
#include "Display.h"

#include <SoftwareSerial.h>

Display::Display()/* : 
displaySerial(rx, tx)*/ {
  

}


void Display::begin(SoftwareSerial *serialPtr) {

  displaySerial = serialPtr;
  
  displaySerial->begin(9600);
  
  setBaud9600();
  
  displaySerial->write(0x76);
  displaySerial->write(0x7A);
  displaySerial->write(1);


  resetDisplay();

}

void Display::setBaud9600() {
  //displaySerial->write(0x7F);  
  //displaySerial->write(2);
}

void Display::updateTime(int counter) {

  int counter_diff = abs( _display_counter_last - counter);
  unsigned long millis_diff = abs(millis() - _display_millis_last);

  if ((counter_diff > 0) && (millis_diff > (1000.0 / DISPLAY_REFRESH_RATE))) {  

    Serial.print("DISPLAY!!eed: ");
    Serial.println(getMinutes(counter));

    resetDisplay();
    writeMinutes(getMinutes(counter));

    _display_millis_last = millis();
    _display_counter_last = counter;

  }

}

void Display::writeMinutes(int minutes) 
{

  char buf[4];
  sprintf(buf, "%04d", minutes);
Serial.println(buf);
  // remove leading zero for all times before 10:00 am.
  // minutes is in display notation, ie. 1000 = 10:00 am.
  if (minutes <  1000) {
    buf[0] = 0x78;
  }

  displaySerial->print(buf);
}

int Display::getMinutes(int counter) {
  int minutes = ((int) counter + MINUTES_PER_DAY) % MINUTES_PER_DAY;
  int hour = minutes / 60;
  minutes = minutes % 60;
  return hour * 100 + minutes;
}

/*
 * Sets brightness of display.
 * Value between 0 and 254;
 * The lower the number the
 * brighter the display.
 */
void Display::setBrightness(byte brightness) {
  displaySerial->write(0x7A);
  displaySerial->write(brightness);
}

void Display::resetDisplay() {
 
  displaySerial->write(0x76);
   // Zet dubbele punt aan:
   displaySerial->write(0x77);
   displaySerial->write(16);
}




