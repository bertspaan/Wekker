#include "Encoder.h"
#include "Clock.h"
#include "Buttons.h"
#include "Relay.h"

#define MINUTES_PER_DAY (24 * 60)

#define ALARM_WAIT_TIME (2000) // Time in milliseconds before display goes back from alarm time to current time

#define PIN_FUNCTION_BUTTON (4)
#define PIN_BIG_RED_BUTTON (5)
#define PIN_ALARM_BUTTON (6)

#define PIN_RELAY (7)

/*
 * Clock op analog in 4 & 5
 * (en dat kan niet anders: http://bildr.org/2011/03/ds1307-arduino/)
 * SDA = 4
 * SCL = 5
 */

//Encoder
#define PIN_ROTARY_LOWBIT  (14) // A. Analog 0
#define PIN_ROTARY_HIGHBIT (15) // B. Analog 1

enum DisplayStates {
  dsTime              =  1,
  dsSettingTime       =  2,
  dsSettingAlarm      =  4
};

volatile boolean alarmSet = false;
volatile boolean alarmOn = false;

// TODO: to int, let speed module handle fractions
volatile double minutesAlarm = 8 * 60; // Defaults to 8 am. when reset
volatile double minutesTime = 0;

volatile char displayState = dsTime;

volatile unsigned long previousMillis = 0;

volatile double brightness = 0;
volatile double snoozeMinutes = 10;

Clock clock;
Buttons buttons(PIN_ALARM_BUTTON, PIN_BIG_RED_BUTTON, PIN_FUNCTION_BUTTON);
Encoder encoder(PIN_ROTARY_LOWBIT, PIN_ROTARY_HIGHBIT);
Relay relay(PIN_RELAY);

void setup() {  
  displayBegin();  
}

void loop() {
  readButtons();

  if (displayState == dsSettingAlarm) {
    unsigned long diffMillis = millis() - previousMillis;
    if (diffMillis > ALARM_WAIT_TIME) {
      displayState = dsTime;
    }
  }

  int difference = encoder.read();
  
  if (difference) { 
    if (displayState == dsSettingTime) {
      
      double speed = encoder.computeSpeed(minutesTime);
      
      alarmOn = false;
      relay.setState(false);
      minutesTime += difference * speed;
      displayMinutes(minutesTime);
      
    } else { // displayState == dsSettingAlarm
      
      double speed = encoder.computeSpeed(minutesAlarm);
      displayState = dsSettingAlarm;
      
      alarmOn = false;
      relay.setState(false);
      minutesAlarm += difference * speed;
      displayMinutes(minutesAlarm);
      
    }
    
    previousMillis = millis();
    
  } else if (displayState == dsTime) {
    minutesTime = clock.readTimeTimed();
    displayMinutes(minutesTime);
  }

  if ((alarmSet) && (displayState == dsTime) && displayGetMinutes(minutesTime) == displayGetMinutes(minutesAlarm)) {
    alarmOn = true;
    relay.setState(true);
  }

}

void readButtons() {
  if (buttons.read()) {
    
    alarmSet = buttons.getAlarmSet();
    
    boolean functionButtonPressed = buttons.getFunctionPressed();
    boolean snoozePressed = buttons.getSnoozePressed();
    
    if (functionButtonPressed) {
      displayState = dsSettingTime;
    } else if (!functionButtonPressed) {

      if (displayState == dsSettingTime) {
        clock.setTime(minutesTime);
      }
      displayState = dsTime;      
    }    
    
    if (alarmSet && alarmOn && snoozePressed) {
      minutesAlarm = minutesTime + snoozeMinutes;    
      
      // Make function:
      alarmOn = false;
      relay.setState(false);
    } else if (!alarmSet && (alarmOn || snoozePressed)) {
      alarmOn = false;
      relay.setState(false);
    }
  }
}

/*
 * =============================================================================================================
 * =============================================================================================================
 * DISPLAY
 * =============================================================================================================
 * =============================================================================================================
 */

#define DISPLAY_REFRESH_RATE 25

void displayBegin() {
  Serial.begin(9600);  
  Serial.print("v");  
  displayResetDisplay();
}

void displayMinutes(int display_counter) {
  static unsigned long _display_previous_millis;
  static int _display_previous_counter;
  
  volatile int display_counter_diff = abs(_display_previous_counter - display_counter);
  unsigned long display_millis_diff = abs(millis() - _display_previous_millis);

  if ((display_counter_diff > 0) && (display_millis_diff > (1000.0 / DISPLAY_REFRESH_RATE))) {

    displayWriteMinutes(displayGetMinutes(display_counter));

    _display_previous_millis = millis();
    _display_previous_counter = display_counter;
  }
}

void displayWriteMinutes(int display_minutes) {
  char display_buf[4];
  sprintf(display_buf, "%04d", display_minutes);
  // remove leading zero for all times before 10:00 am.
  // minutes is in display notation, ie. 1000 = 10:00 am.
  if (display_minutes <  1000) {
    display_buf[0] = 0x78;
  }
  Serial.print(display_buf);  
}

int displayGetMinutes(int display_counter) {
  int display_minutes = ((int) display_counter + MINUTES_PER_DAY) % MINUTES_PER_DAY;
  int display_hour = display_minutes / 60;
  display_minutes = display_minutes % 60;
  return display_hour * 100 + display_minutes;
}

/*
 * Sets brightness of display. Value between 0 and 254;
 * The lower the number the brighter the display.
 */
void displaySetBrightness(int newBrightness) {
  byte byteBrightness = (byte) ((newBrightness + 255) % 255);
  
  Serial.write(0x7A);
  Serial.write(byteBrightness);
}

void displayResetDisplay() {
  Serial.write(0x76);
  // Zet dubbele punt aan:
  Serial.write(0x77);
  Serial.write(16);
  displaySetBrightness(0);
}

