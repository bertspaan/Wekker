#include <SoftwareSerial.h>

/* Rotary encoder read example */
#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC

#define MINUTES_PER_DAY (24 * 60)

#define DISPLAY_PIN 4

#define PIN_BIG_RED_BUTTON 2

double counter = 0;

SoftwareSerial displaySerial(DISPLAY_PIN, DISPLAY_PIN + 1);

void setup()
{
  /* Setup encoder pins as inputs */
  pinMode(ENC_A, INPUT);
  digitalWrite(ENC_A, HIGH);
  pinMode(ENC_B, INPUT);
  digitalWrite(ENC_B, HIGH);
  Serial.begin (115200);
  Serial.println("Start");

  pinMode(DISPLAY_PIN, OUTPUT);

  displaySerial.begin(9600);

  displaySerial.write(0x76);
  displaySerial.write(0x7A);
  displaySerial.write(1);

  resetDisplay();
  
  //setupClock();
  
  // Big red button
 /* digitalWrite(PIN_BIG_RED_BUTTON, HIGH);
  pinMode(PIN_BIG_RED_BUTTON, OUTPUT);
  attachInterrupt(0, blink, RISING);*/

}

void loop()
{

  int difference;

  double speed = computeSpeed(counter);

  difference = read_encoder();
  if( difference ) {

    debugCounter(counter);
    counter += difference * speed;
    //printDate();
  }

  updateTime(counter);

}

int getMinutes(int counter) {
  int minutes = ((int) counter + MINUTES_PER_DAY) % MINUTES_PER_DAY;
  int hour = minutes / 60;
  minutes = minutes % 60;
  return hour * 100 + minutes;
}

void blink() {
    Serial.println("KNOP!! ");
}


