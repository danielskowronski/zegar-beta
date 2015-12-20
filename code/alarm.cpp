#include "alarm.h"
#include "config.h"
#include "display.h" //jasnosc_val

extern bool budzik=false;
extern int alarmHH=0, alarmMM=0; 
extern bool alarmENABLED=false, alarmSNOOZE=false, alarmCOMPLETED=false, alarmACTIVE=false;
extern volatile bool alarmINT=false;

void enableAlarm() { alarmENABLED=true; alarmCOMPLETED=false; }
void disableAlarm() { alarmENABLED=false; alarmCOMPLETED=true; }
void completeAlarm() { alarmCOMPLETED=true; }

void parseAlarm(){
  if (! (rtc.getHour()==alarmHH && rtc.getMinute()==alarmMM)){
    alarmCOMPLETED=false;
  }
  if (!alarmCOMPLETED && alarmENABLED && rtc.getHour()==alarmHH && rtc.getMinute()==alarmMM){
    analogWrite(LCD_BACKLIGHT, 255);
    delay(25);
    analogWrite(LCD_BACKLIGHT, 20);
    alarmINT=true;
    alarmACTIVE=true;
  }
  else{
    analogWrite(LCD_BACKLIGHT, jasnosc_val*10);
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
