#include "Arduino.h"
#include "Buttons.h"

Buttons::Buttons(int pinAlarm, int pinSnooze, int pinFunction) {

  _pinSnooze = pinSnooze;
  _pinAlarm = pinAlarm;
  _pinFunction = pinFunction;  

  initialize(_pinSnooze);
  initialize(_pinAlarm);
  initialize(_pinFunction);

  _alarmSet = false;

  _functionPressed = false;
  _functionTimesPressed = 0;
  _functionTimesPressing = 0;
  _functionPressing = false;
  _functionPressingPreviousMillis = 0;

  _snoozePressed = false;

}

void Buttons::initialize(int pin) {
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
}

boolean Buttons::read() {

  unsigned long millis_diff = abs(millis() - _read_previous_millis);

  if (millis_diff > BUTTONS_MILLIS_THRESHOLD) {

    boolean snoozePressed = digitalRead(_pinSnooze);
    boolean alarmSet = digitalRead(_pinAlarm);
    boolean functionPressed = !digitalRead(_pinFunction);

    int functionTimesPressed = _functionTimesPressed;
    unsigned long pressing_millis_diff = abs(millis() - _functionPressingPreviousMillis);
    if (_functionPressing && (pressing_millis_diff > BUTTONS_FUNCTION_THRESHOLD)) {
      _functionTimesPressed = _functionTimesPressing;
           
      _functionTimesPressing = 0;
      _functionPressing = false;
    }
    
    if (!functionPressed && _functionPressed) {
      _functionTimesPressed = 0;
      
      _functionPressing = true; 
      _functionTimesPressing++;
      _functionTimesPressing = _functionTimesPressing % (BUTTONS_FUNCTION_PRESSED_MAX + 1);
      
      _functionPressingPreviousMillis = millis();
    }
    
    boolean changed = (snoozePressed && !_snoozePressed) || 
      (alarmSet != _alarmSet) || 
      (functionTimesPressed != _functionTimesPressed);

    _alarmSet = alarmSet;
    _snoozePressed = snoozePressed;
    
    _functionPressed = functionPressed;

    _read_previous_millis = millis();
    
    return changed;
  }

  return false;
}

boolean Buttons::getAlarmSet() {
  return _alarmSet;
}

int Buttons::getFunctionTimesPressed() {
  return _functionTimesPressed;
}

boolean Buttons::getSnoozePressed() {
  return _snoozePressed;
}



