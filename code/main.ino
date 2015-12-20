#include "data.h"
#include "config.h"
#include "display.h"
#include "ui.h"
#include "alarm.h"

void setup(void) {
  Serial.begin(9600);  
  
  LcdInitialise();
  LcdClear();

  rtc.initClock();
  rtc.setDate(30, 1, 12, 0, 15);
  rtc.setTime(0, 0, 59);
  
  alarmHH=0;alarmMM=1;
  enableAlarm();

  dht.begin();

  pinMode(JOYSTICK_B, INPUT);  
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(LCD_BACKLIGHT, OUTPUT);

  setupAlamrInterrupt();
}

void loop(void){    
  readJoystick();
  parseAlarm();
  
  if (mode==0)
    displayClock();
  else if (mode==1) 
     showMenu(); 
  else if (mode==2) 
     setClock(false); //setAlarm
  else if (mode==3) 
     setClock(true); //setClock
  else if (mode==4) 
     setDisplay(); 
  
  delay(75);
}
