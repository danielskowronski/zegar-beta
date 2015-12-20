#ifndef ALARM_H
#define ALARM_H

#include "data.h"
#include "config.h"
#include <avr/interrupt.h>

extern bool budzik;
extern int alarmHH, alarmMM; 
extern bool alarmENABLED, alarmSNOOZE, alarmCOMPLETED, alarmACTIVE;
extern volatile bool alarmINT;

void enableAlarm();
void disableAlarm();
void completeAlarm();

void parseAlarm();

void setupAlamrInterrupt();

extern volatile /*not unsigned - there is `=-125` !*/ long int tick, stepp, todo;

#endif
