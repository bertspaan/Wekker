#include <SoftwareSerial.h>

/* Rotary encoder read example */
#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC

#define MINUTES_PER_DAY (24 * 60)


#define DISPLAY_PIN 4


double counter = 0;
double _speed = 1;

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
  
  // Zet dubbele punt aan:
  displaySerial.write(0x77);
  displaySerial.write(16);



}
 
void loop()
{


 int difference;


  
  _speed = computeSpeed(counter);
  _speed += 0.0;
  difference = read_encoder();
  if( difference ) {
   
    
    
    
    
    
    debugCounter(counter);
    debugSpeed(_speed);
    
    
    counter += difference ;//* speed;
  }
  
  updateTime(counter);
    
}

int getMinutes(double counter) {
  int minutes = ((int) counter + MINUTES_PER_DAY) % MINUTES_PER_DAY;
  int hour = minutes / 60;
  minutes = minutes % 60;
  return hour * 100 + minutes;
}

