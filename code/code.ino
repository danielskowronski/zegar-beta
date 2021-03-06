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
  rtc.setDate(5, 3, 03, 21, 16);
  rtc.setTime(21, 25, 59);
  
  alarm = alarmTmp = timeObj(21,26);
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
  //transmitThm();//not usable now
  
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
