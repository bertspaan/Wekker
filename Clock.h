#ifndef Clock_h
#define Clock_h

#include "Arduino.h"

class Clock
{
public:
  Clock();

  int readTimeTimed();
  int readTime();
  void setTime(int minutes);

private:
  byte bcdToDec(byte val);
  byte decToBcd(byte val);
  
  unsigned long _clock_millis_last;
  int _clock_minutes;
  int previousSetTime;
  
};

#endif



