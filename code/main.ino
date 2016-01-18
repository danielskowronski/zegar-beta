#include "data.h"
#include "config.h"
#include "display.h"
#include "ui.h"
#include "alarm.h"
#include "tools.h"

void setup(void) {
  Serial.begin(9600);  
  
  LcdInitialise();
  LcdClear();

  rtc.initClock();
  rtc.setDate(18, 1, 01, 21, 16);
  rtc.setTime(23, 12, 59);
  
  alarm = alarmTmp = timeObj(0,1);
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
  transmitThm();
  
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
  
  delay(125);
}
