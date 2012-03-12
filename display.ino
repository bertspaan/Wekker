#define DISPLAY_REFRESH_RATE 25

unsigned long _display_millis_last = 0;
int _display_counter_last = 0;


void updateTime(int counter) {

  int counter_diff = abs( _display_counter_last - counter);
  unsigned long millis_diff = abs(millis() - _display_millis_last);
  
  // WAAROM? Nu is het nodig. Snap niet. Worden anders variabelen tijdelijk weggeoptimaliseerd? Uitzoeken!
  counter_diff += 0.0;
  millis_diff += 0.0;
  if ((counter_diff > 0) && (millis_diff > (1000.0 / DISPLAY_REFRESH_RATE))) {  

    resetDisplay();
    writeMinutes(getMinutes(counter));

    _display_millis_last = millis();
    _display_counter_last = counter;

  }

}

void writeMinutes(int minutes) {
  char buf[4];
  sprintf(buf, "%04d", minutes);
  displaySerial.print(buf);
}

void resetDisplay() {
  displaySerial.write(0x76);
  // Zet dubbele punt aan:
  displaySerial.write(0x77);
  displaySerial.write(16);
}


