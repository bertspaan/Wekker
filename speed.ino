#define SPEED_MILLIS_THRESHOLD 100
#define SPEED_COUNTER_THRESHOLD 40

#define SPEED_MULTIPLIER 20

#define SPEED_MIN 0.1
#define SPEED_MAX 10.0

unsigned long _speed_millis_last = 0;
int _speed_counter_last = 0;

double _speed = SPEED_MIN;

double computeSpeed(int counter) {
  
  int counter_diff = abs(counter - _speed_counter_last);
  unsigned long millis_diff = abs(millis() - _speed_millis_last);
  
  // WAAROM? Nu is het nodig. Snap niet. Worden anders variabelen tijdelijk weggeoptimaliseerd? Uitzoeken!
  counter_diff += 0.0;
  millis_diff += 0.0;


// Serial.println(millis_diff);
  ///Serial.println(counter_diff);
  //if ( counter_diff > SPEED_COUNTER_THRESHOLD) {
  if ( (millis_diff > SPEED_MILLIS_THRESHOLD) && (counter_diff > 0) ) {

    _speed = abs((counter_diff * 1.0) / millis_diff * SPEED_MULTIPLIER);
  
    if (_speed < SPEED_MIN) {
      _speed = SPEED_MIN;
    }

    if (_speed > SPEED_MAX) {
      _speed = SPEED_MAX + (1.0 * random(100) / 100);
    }

    _speed_millis_last = millis();
    _speed_counter_last = counter;
  debugSpeed(_speed); 
  }

  return _speed;

}

