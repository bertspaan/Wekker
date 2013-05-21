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
