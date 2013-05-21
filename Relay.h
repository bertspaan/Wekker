#ifndef Relay_h
#define Relay_h

#include "Arduino.h"

class Relay
{
  public:
    Relay(int pin);
    void setState(int state);
  private:
    int _state;
    int _pin;
};

#endif
