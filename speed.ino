#define SPEED_MILLIS_THRESHOLD 100
#define SPEED_COUNTER_THRESHOLD 40

#define SPEED_MULTIPLIER 30

#define SPEED_MIN 0.2
#define SPEED_MAX 10

unsigned long _speed_millis_last = 0;
double _speed_counter_last = 0;

double computeSpeed(int counter) {
  
 
  
  unsigned long millis_diff = abs(millis() - _speed_millis_last);
  double counter_diff = abs(counter - _speed_counter_last);
  
  // WAAROM? Nu is het nodig. Snap niet. Worden anders variabelen tijdelijk weggeoptimaliseerd? Uitzoeken!
  counter_diff += 0.0;
  millis_diff += 0.0;
  
  //if ( counter_diff > SPEED_COUNTER_THRESHOLD) {
  if ( millis_diff > SPEED_MILLIS_THRESHOLD && counter_diff > 0 ) {
    
    double speed = abs(counter_diff / millis_diff * SPEED_MULTIPLIER);
      
    if (speed < SPEED_MIN) {
      speed = SPEED_MIN;
    }
    
    if (speed > SPEED_MAX) {
      speed = SPEED_MAX;
    }
    
    _speed_millis_last = millis();
    _speed_counter_last = counter;


    Serial.print("spieeed: ");
  Serial.println(speed);
  return speed;    
  }

  return SPEED_MIN;
  
}
