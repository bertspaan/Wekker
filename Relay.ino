/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Relay.h"

Relay::Relay(int pin)
{
  _pin = pin;
  
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);  

}

void Relay::setState(int state)
{
  digitalWrite(_pin, state); 
}
