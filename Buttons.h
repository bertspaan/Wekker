#ifndef Button_h
#define Button_h

#include "Arduino.h"

#define BUTTONS_MILLIS_THRESHOLD 20

#define BUTTONS_FUNCTION_PRESSED_MAX 3
#define BUTTONS_FUNCTION_THRESHOLD 500

#define BUTTONS_THRESHOLD 50

class Buttons
{
public:
  Buttons(int pinAlarm, int pinSnooze, int pinFunction);
  boolean read();
  
  boolean getAlarmSet();
  int getFunctionTimesPressed();
  boolean getSnoozePressed();
  
private:
  unsigned long _read_previous_millis;
  
  void initialize(int pin);
  int _pinSnooze;
  int _pinAlarm;
  int _pinFunction;
  
  boolean _alarmSet;

  boolean _functionPressed;
  int _functionTimesPressed;
  int _functionTimesPressing;
  boolean _functionPressing;
  unsigned long _functionPressingPreviousMillis;
  
  boolean _snoozePressed;
  
  
};

#endif



