#define DISPLAY_REFRESH_RATE 25

// TODO: volatile?
volatile unsigned long _display_millis_last = 0;
volatile int _display_counter_last = 0;

void updateTime(int counter) {

  int counter_diff = abs( _display_counter_last - counter);
  unsigned long millis_diff = abs(millis() - _display_millis_last);

  if ((counter_diff > 0) && (millis_diff > (1000.0 / DISPLAY_REFRESH_RATE))) {  

    //resetDisplay();
    writeMinutes(getMinutes(counter));

    _display_millis_last = millis();
    _display_counter_last = counter;

  }

}

void writeMinutes(int minutes) 
{
  
  char buf[4];
  sprintf(buf, "%04d", minutes);
  
  // remove leading zero for all times before 10:00 am.
  // minutes is in display notation, ie. 1000 = 10:00 am.
  if (minutes <  1000) {
    buf[0] = 0x78;
  }
  
  displaySerial.print(buf);
}

void writeMinutesLos(int minutes) {
  char buf[4];
  sprintf(buf, "%04d", minutes);
  displaySerial.print(buf);

  // Zet dubbele punt aan:
  displaySerial.write(0x77);
  displaySerial.write(16);

  displaySerial.write(0x7B);
  displaySerial.write(buf[0]);

  displaySerial.write(0x7C);
  displaySerial.write(buf[1]);

  displaySerial.write(0x7D);
  displaySerial.write(buf[2]);

  displaySerial.write(0x7E);
  displaySerial.write(buf[3]);
}






void resetDisplay() {
  displaySerial.write(0x76);
  // Zet dubbele punt aan:
  displaySerial.write(0x77);
  displaySerial.write(16);
}



