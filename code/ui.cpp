#include "tools.h"
#include "ui.h"
#include "display.h"
#include "config.h"
#include "alarm.h"

extern char cha[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //general use temp char array

extern int x=0, y=0, b=0;
void readJoystick(){
  x= 512-analogRead(JOYSTICK_X);
  y= 512-analogRead(JOYSTICK_Y);
  b= not (digitalRead(JOYSTICK_B));
}

bool isUp(){ return y>200; }
bool isDown(){ return y<-200; }
bool isLeft(){ return x<-200; }
bool isRight(){ return x>200; }
bool isPressed() { return b==1; }

extern int mode=0;
extern bool modechanged=false;
extern int pos_menu=0, pos_setClock=0, pos_setDisp=0;

extern bool PAR = true;
extern int lastsec = 0;

void displayClock(){
  PAR = not PAR;
  
  char* clock = rtc.formatTime(); int p=-14/*+7*/;
  LcdCharacterBig(p+=14,0,clock[0],false);
  LcdCharacterBig(p+=14,0,clock[1],false);
  LcdCharacterBig(p+=14,0,'-',false);
  LcdCharacterBig(p+=14,0,clock[3],false);
  LcdCharacterBig(p+=14,0,clock[4],false);
  
  gotoXY(70,2); sprintf (cha, "%02i", rtc.getSecond());LcdString(cha,true);
  
  gotoXY(0,4);
  sprintf (cha, "%02i/%02i/2016", rtc.getDay(), rtc.getMonth());LcdString(cha);

  gotoXY(0,5);
  sprintf (cha, "%02i'C | %02i%%", (int)(dht.readTemperature()), (int)(dht.readHumidity()));LcdString(cha);
  
  if (alarmENABLED){
   sprintf(cha, "#");
   gotoXY(77,4); LcdString(cha,true); 
   gotoXY(77,5); LcdString(cha,true);  
  }
  else{
   sprintf(cha, " ");
   gotoXY(77,4); LcdString(cha,false); 
   gotoXY(77,5); LcdString(cha,false);  
  }
  
  if (alarmACTIVE){
    sprintf(cha, "   budzik   ");
    gotoXY(0,3);LcdString(cha, PAR);
  }
  else if (alarmSNOOZE){
    sprintf(cha, "   drzemka  ");
    gotoXY(0,3);LcdString(cha, PAR);
  }
  else{
    sprintf(cha, EMPTY_LINE);
    gotoXY(0,3);LcdString(cha);
  }

  if (alarmINT){
    if(b){
      alarmCOMPLETED=true;
      alarmACTIVE=false;
      alarmINT=false;
      alarmSNOOZE=true;
      alarmTmp.addMinutes(SNOOZE_TIME);
    }
  }
  else{
    if (b){mode=1;modechanged=true;LcdClear();return;}
    if (isRight()&&isUp()){
      enableAlarm();
    }
  }
  if (isLeft()&&isDown()){
    if (alarmACTIVE) alarmCOMPLETED=true;
    else disableAlarm();
    alarmSNOOZE=false;
    alarmTmp=alarm;
    alarmINT=false;
    alarmACTIVE=false;
    alarmENABLED=false;
  }
}

void showMenu(){
  if (isPressed()) {
    mode=pos_menu+2;
    modechanged=true;
    if (mode==5) mode=0; 
    LcdClear();
    return;  
  }

  gotoXY(0,0);
  sprintf(cha, " Menu glowne ");LcdString(cha, true);
  gotoXY(0,1);
  sprintf(cha, "    "); LcdString(cha, false);
  gotoXY(20,1);
  sprintf(cha, "budzik"); LcdString(cha, (pos_menu==0));
  gotoXY(0,2);
  sprintf(cha, "ust."); LcdString(cha, (pos_menu==1));
  gotoXY(30,2);
  sprintf(cha, " ^  "); LcdString(cha, false);
  gotoXY(50,2);
  sprintf(cha, "ust."); LcdString(cha, (pos_menu==2));
  gotoXY(0,3);
  sprintf(cha, "czas"); LcdString(cha, (pos_menu==1));
  gotoXY(30,3);
  sprintf(cha, "< > "); LcdString(cha, false);
  gotoXY(50,3);
  sprintf(cha, "wysw"); LcdString(cha, (pos_menu==2));
  gotoXY(0,4);
  sprintf(cha, "     v"); LcdString(cha, false);
  gotoXY(0,5);
  sprintf(cha, "    "); LcdString(cha, false);
  gotoXY(20,5);
  sprintf(cha, "powrot"); LcdString(cha, (pos_menu==3));
  
  if (isUp()) pos_menu=0;
  if (isDown()) pos_menu=3;
  if (isRight()) pos_menu=2;
  if (isLeft()) pos_menu=1;
}
void setClock(bool isClock){
  char hh[3];
  if (isClock)
    sprintf(hh, "%02i", rtc.getHour());
  else
    sprintf(hh, "%02i", alarm.h);
  char mm[3];
  if (isClock)
    sprintf(mm, "%02i", rtc.getMinute());
  else
    sprintf(mm, "%02i", alarm.m);
  char day[3]; char month[3];
  if (isClock){
    sprintf(day,   "%02i", rtc.getDay());
    sprintf(month, "%02i", rtc.getMonth());   
  }

  if (modechanged){
    if (isClock){ sprintf(cha, " Ustaw czas ");}
    else        { sprintf(cha, "Ustaw budzik");}
    gotoXY(0,0);
    LcdString(cha, true);
    gotoXY(0,1);
    sprintf(cha, EMPTY_LINE);LcdString(cha, false);
  }
  
  gotoXY(0,1);
  LcdString(hh,(pos_setClock==0));
  gotoXY(15,1);
  sprintf(cha, ":"); LcdString(cha, false);
  gotoXY(20,1);
  LcdString(mm,(pos_setClock==1));
  gotoXY(70,1);
  sprintf(cha, "OK");LcdString(cha,(pos_setClock==2));  

  if (isClock){
    gotoXY(0,2);
    LcdString(day,(pos_setClock==3));
    gotoXY(15,2);
    sprintf(cha, "/"); LcdString(cha, false);
    gotoXY(20,2);
    LcdString(month,(pos_setClock==4));
    gotoXY(35,2);
    sprintf(cha, "/2016");LcdString(cha);  
  }

  if (modechanged){
    gotoXY(0,3);
    sprintf(cha, EMPTY_LINE);LcdString(cha, false);
    gotoXY(0,4);
    sprintf(cha, "<> poprz/nast");LcdString(cha);
    gotoXY(0,5);
    sprintf(cha, "^v wart +/-");LcdString(cha);
    
    modechanged=false;
  }
  
  if (isClock){
    if (pos_setClock==0){
      if (isUp())   rtc.setTime(obetnij(rtc.getHour()+1, 23), rtc.getMinute(), rtc.getSecond());
      if (isDown()) rtc.setTime(obetnij(rtc.getHour()-1, 23), rtc.getMinute(), rtc.getSecond());
    }
    if (pos_setClock==1){
      if (isUp())   rtc.setTime(rtc.getHour(), obetnij(rtc.getMinute()+1,59), rtc.getSecond());
      if (isDown()) rtc.setTime(rtc.getHour(), obetnij(rtc.getMinute()-1,59), rtc.getSecond());   
    }
    if (pos_setClock==3){
      if (isUp())   rtc.setDate(obetnij(rtc.getDay()+1,31), 1, rtc.getMonth(), 21, 16);
      if (isDown()) rtc.setDate(obetnij(rtc.getDay()-1,31), 1, rtc.getMonth(), 21, 16);
    }
    if (pos_setClock==4){
      if (isUp())   rtc.setDate(rtc.getDay(), 1, obetnij(rtc.getMonth()+1,12), 21, 16);   
      if (isDown()) rtc.setDate(rtc.getDay(), 1, obetnij(rtc.getMonth()-1,12), 21, 16);   
    }
  }
  else{
    if (pos_setClock==0){
      if (isUp())   alarm.h = obetnij(alarm.h+1, 23);
      if (isDown()) alarm.h = obetnij(alarm.h-1, 23);
    }
    if (pos_setClock==1){
      if (isUp())   alarm.m = obetnij(alarm.m+1,59);
      if (isDown()) alarm.m = obetnij(alarm.m-1,59);
    }    
  }
  
  if (pos_setClock==2){
    if (isPressed()) {
      mode=1;
      modechanged=true;
      LcdClear();
      return;
    }
  }

  alarmTmp = alarm;
  
  if (isRight())  pos_setClock++;
  if (isLeft())   pos_setClock--;
  if (isClock){
    if (pos_setClock>4) pos_setClock=0;
    if (pos_setClock<0) pos_setClock=4;
  }
  else {
    if (pos_setClock>2) pos_setClock=0;
    if (pos_setClock<0) pos_setClock=2;
  }
}

void setDisplay(){
  if (modechanged){
    gotoXY(0,0);
    sprintf(cha, " Ustaw. wysw.");LcdString(cha, true);
    gotoXY(0,1);
    sprintf(cha, EMPTY_LINE);LcdString(cha, false);
  }
  gotoXY(0,1);
  sprintf(cha, "kontrast:");LcdString(cha,false);
  gotoXY(60,1);
  sprintf(cha, "%02i", contrast_val);LcdString(cha, (pos_setDisp==0));
  gotoXY(0,2);
  sprintf(cha, "jasnosc:");LcdString(cha,false);
  gotoXY(60,2);
  sprintf(cha, "%02i", jasnosc_val);LcdString(cha, (pos_setDisp==1));
  gotoXY(0,3);
  sprintf(cha, "OK");LcdString(cha,(pos_setDisp==2));  
  if (modechanged){
    gotoXY(0,4);
    sprintf(cha, "<> poprz/nast");LcdString(cha);
    gotoXY(0,5);
    sprintf(cha, "^v wart +/-");LcdString(cha);

    modechanged=false;
  }
  
  if (pos_setDisp==0){
    if (isUp())  { contrast_val=obetnij(contrast_val+1, 10, true); LcdInitialise(); }
    if (isDown()) { contrast_val=obetnij(contrast_val-1, 10, true); LcdInitialise(); }
  }
  else if (pos_setDisp==1){
    if (isUp())   { jasnosc_val=obetnij(jasnosc_val+1, 50); analogWrite(11, jasnosc_val); }
    if (isDown()) { jasnosc_val=obetnij(jasnosc_val-1, 50); analogWrite(11, jasnosc_val); }
  }
  if (pos_setDisp==2){
    if (isPressed()) {
      mode=1;
      modechanged=true;
      LcdClear();
      return;
    }
  }
  
  if (isRight())  pos_setDisp++;
  if (isLeft()) pos_setDisp--;
  if (pos_setDisp>2) pos_setDisp=0;
  if (pos_setDisp<0) pos_setDisp=2;
}

