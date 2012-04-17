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
    
    boolean changed = (snoozePressed && !_snoozePressed) || 
      (alarmSet != _alarmSet) || 
      (functionPressed != _functionPressed);

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

boolean Buttons::getFunctionPressed() {
  return _functionPressed;
}

boolean Buttons::getSnoozePressed() {
  return _snoozePressed;
}



