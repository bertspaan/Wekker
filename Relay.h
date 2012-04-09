/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
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
