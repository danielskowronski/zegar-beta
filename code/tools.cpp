#include "tools.h"
#include "config.h"


int obetnij(int wejscie, int max, bool symetric){
  if (symetric){
    if (wejscie<0-max) return max;
    if (wejscie>max) return 0-max;
  }
  else{
    if (wejscie<0) return max;
    if (wejscie>max) return 0;
  }
  return wejscie;
}

extern int lastSec=0;
void transmitThm(){
  int currSec = rtc.getSecond();
  if (currSec%2==0) return;
  
  if (currSec!=lastSec){
    Serial.print(rtc.formatTime());
    Serial.print(" -> ");
    Serial.print(dht.readTemperature());
    Serial.println("'C");
  }
  lastSec=currSec;
}

