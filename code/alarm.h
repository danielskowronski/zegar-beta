#ifndef ALARM_H
#define ALARM_H

#include "data.h"
#include "config.h"
#include <avr/interrupt.h>

class timeObj{
  public:
    timeObj(){};
    timeObj(int h, int m);
    bool isEqual(int h, int m);
    void addMinutes(int n);
    int h, m;
};

extern bool budzik;
extern timeObj alarm, alarmTmp; 
extern bool alarmENABLED, alarmSNOOZE, alarmCOMPLETED, alarmACTIVE;
extern volatile bool alarmINT;

void enableAlarm();
void disableAlarm();
void completeAlarm();

void parseAlarm();

void setupAlamrInterrupt();

extern volatile /*not unsigned - there is `=-125` !*/ long int tick, stepp, todo;

#endif
