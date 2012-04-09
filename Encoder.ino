

Encoder::Encoder(int pinLow, int pinHigh) {
  _pinLow = pinLow;
  _pinHigh = pinHigh;
  
  pinMode(_pinLow, INPUT);
  pinMode(_pinHigh, INPUT);
  
  digitalWrite(_pinLow, HIGH);
  digitalWrite(_pinHigh, HIGH);
  
  _prevState = 0;
  
  int encoderStates[4][4] = {
   {  0, -1,  1,  0 }, 
   {  1,  0,  0, -1 }, 
   { -1,  0,  0,  1 }, 
   {  0,  1, -1,  0 }, 
  };
  
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      _encoderStates[i][j] = encoderStates[i][j];
    }
  }  

  _speed_millis_last = 0;
  _speed_counter_last = 0;
  
  _speed = SPEED_MIN;
}

int Encoder::read() { 
  
  int state = (digitalRead(_pinHigh) << 1) | digitalRead(_pinLow);
  int result = _encoderStates[_prevState][state];
  _prevState = state;
  return result;
}


double Encoder::computeSpeed(int counter) {
  
  int counter_diff = abs(counter - _speed_counter_last);
  unsigned long millis_diff = abs(millis() - _speed_millis_last);
 
  //if ( counter_diff > SPEED_COUNTER_THRESHOLD) {
  if ( (millis_diff > SPEED_MILLIS_THRESHOLD) && (counter_diff > 0) ) {
    
   /* Serial.print("counter: ");
    Serial.print(counter);
    Serial.print(" countrlast: ");
    Serial.print(_speed_counter_last);
    Serial.print(" milllisdif: ");
    Serial.print(counter_diff);
    Serial.print(" milllisdif: ");
    Serial.println(millis_diff);*/
    
    _speed = log10((counter_diff * 1.0) / millis_diff * SPEED_MULTIPLIER);
  
    if (_speed < SPEED_MIN) {
      _speed = SPEED_MIN;
    } else if (_speed > SPEED_MAX) {
      _speed = SPEED_MAX + (1.0 * random(100) / 100);
    }

    _speed_millis_last = millis();
    _speed_counter_last = counter;
    //debugDouble("Speed", _speed); 
  } else if (millis_diff > 10 * SPEED_MILLIS_THRESHOLD) {
    _speed = SPEED_MIN;
  }

  return _speed;

}



