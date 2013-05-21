#ifndef Button_h
#define Button_h

#include "Arduino.h"

#define BUTTONS_MILLIS_THRESHOLD 20

class Buttons
{
public:
  Buttons(int pinAlarm, int pinSnooze, int pinFunction);
  boolean read();
  
  boolean getAlarmSet();
  boolean getFunctionPressed();
  boolean getSnoozePressed();
  
private:
  unsigned long _read_previous_millis;
  
  void initialize(int pin);
  int _pinSnooze;
  int _pinAlarm;
  int _pinFunction;
  
  boolean _alarmSet;
  boolean _functionPressed;
  boolean _snoozePressed;
  
};

#endif



