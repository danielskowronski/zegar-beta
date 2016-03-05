#include "alarm.h"
#include "config.h"
#include "display.h" //jasnosc_val

timeObj::timeObj(int h, int m){ this->h=h; this->m=m; }
bool timeObj::isEqual(int h, int m){ return this->h==h&&this->m==m; }
void timeObj::addMinutes(int n){
  m+=n;
  while (m>=60){
    m-=60;
    h++;
  }
  h%=24; //there was &= instead of %= - tiny typo that caused snooze (only func that uses addMinutes) not to work
}

extern bool budzik=false;
extern timeObj alarm=timeObj(), alarmTmp=timeObj();
extern bool alarmENABLED=false, alarmSNOOZE=false, alarmCOMPLETED=false, alarmACTIVE=false;
extern volatile bool alarmINT=false;

void enableAlarm() { alarmENABLED=true; alarmCOMPLETED=false; }
void disableAlarm() { alarmENABLED=false; alarmCOMPLETED=true; }
void completeAlarm() { alarmCOMPLETED=true; }

void parseAlarm(){
  if (alarmENABLED && alarmTmp.isEqual(rtc.getHour(),rtc.getMinute())){
    alarmINT=true;
    alarmACTIVE=true;
  }
  if (alarmINT/* || alarmSNOOZE*/){
    analogWrite(LCD_BACKLIGHT, 255);
    delay(25);
    analogWrite(LCD_BACKLIGHT, 20);
    delay(25);
  }
  else{
    analogWrite(LCD_BACKLIGHT, jasnosc_val*2);
    alarmACTIVE=false;
    alarmINT=false;
  }
}

extern volatile /*not unsigned - there is `=-125` !*/ long int tick=0, stepp=0, todo=powt[stepp];

ISR(TIMER1_COMPA_vect){  //8kHz
  if (alarmINT){
    if (todo>=0){
      if (tick<czasy[stepp][0]) { digitalWrite(BUZZ_PIN, LOW);} 
      else if (tick>=czasy[stepp][0]&&tick<czasy[stepp][0]+czasy[stepp][1]) {digitalWrite(BUZZ_PIN, HIGH);}
      else  { digitalWrite(BUZZ_PIN, LOW);tick=-125;/*will be zeroed in next line!*/ todo--;}    
      tick+=125;
    }
    else{
      stepp++; if (stepp>10) stepp=0;
      todo=powt[stepp];
    }
  }
  else{
    tick=0; stepp=0; todo=powt[stepp];
    digitalWrite(BUZZ_PIN, LOW);
  }
}

void setupAlamrInterrupt(){
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 249;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS21);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}
