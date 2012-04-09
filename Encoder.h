
#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

#define SPEED_MILLIS_THRESHOLD 20
#define SPEED_COUNTER_THRESHOLD 10

#define SPEED_MULTIPLIER 100

#define SPEED_MIN 0.1
#define SPEED_MAX 25.0

class Encoder
{
public:
  Encoder(int pinLow, int pinHigh);
  int read();
  double computeSpeed(int counter);

private:
  int _pinLow;
  int _pinHigh;
  int _prevState;
  int _encoderStates[4][4];

  /*
   * Speed:
   */
  unsigned long _speed_millis_last;
  int _speed_counter_last;
  double _speed;

};

#endif



