#include <Wire.h>
#define BUZZ_PIN 10
void setup() {
  pinMode(BUZZ_PIN, OUTPUT);
}

//you can use it to play piano eg. 
/* String wlazlKotekNaPlotek[] = { "G","E","E","F","D","D","C","E","G","C","E","G","G","E","E","F","D","D","C","E","C","C","E","C","G","E","E","F","D","D","C","E","G","C","E","G","G","E","E","F","D","D","C","E","C","C","E" };
for (int i=0;i<47;i++) playNote(wlazlKotekNaPlotek[i]); */
void playNote(String note, int octave=6, int time=500){
  String notes[] = {
    "C",    "C#",     "D",    "D#",    "E",    "F",   "F#",    "G",   "G#",    "A",   "A#",    "H",
  };
  int sounds[][12] = {
    33,   35,    37,    39,   41,   44,   47,   49,   52,   55,   59,   62,
    65,   69,    73,    78,   82,   87,   93,   98,  104,  110,  117,  123,
    131,  139,  147,   156,  165,  175,  186,  196,  208,  220,  234,  247,
    262,  278,  294,   312,  330,  349,  371,  392,  416,  440,  467,  494,
    523,  555,  587,   619,  659,  698,  741,  784,  832,  880,  934,  988,
    1047, 1111, 1175, 1247, 1319, 1397, 1483, 1568, 1664, 1760, 1868, 1976,
    2093, 2221, 2349, 2493, 2637, 2794, 2965, 3136, 3328, 3520, 3736, 3951,
  };

  int d=0;
  for (int i=0;i<12;i++){if (notes[i]==note) {d=i; break;} }
  tone(BUZZ_PIN, sounds[octave-1][d]);
  delay(time);
  noTone(BUZZ_PIN);    
}

// somehow emulates Polish CEMI MC1203/MC1206 embedded alarm clock mellody which was very irritating and could wake the dead ;)
// original recording is in /varia/mc1203_budzik.mp3
void mc1203(){
  for (int n=1;n<=11;n++){
    switch (n){
      case 1:
      case 5:
        for (int i=0;i<409;i++) { digitalWrite(BUZZ_PIN, LOW); delayMicroseconds(480); digitalWrite(BUZZ_PIN, HIGH); delayMicroseconds(750); digitalWrite(BUZZ_PIN, LOW); }
        break;
      case 2:
      case 6:
        for (int i=0;i<187;i++) { digitalWrite(BUZZ_PIN, LOW); delayMicroseconds(1210); digitalWrite(BUZZ_PIN, HIGH); delayMicroseconds(1470); digitalWrite(BUZZ_PIN, LOW); }
        break;
      case 3:
      case 7:
        //for (int i=0;i<187;i++) { digitalWrite(BUZZ_PIN, LOW); delayMicroseconds(500); digitalWrite(BUZZ_PIN, HIGH); delayMicroseconds(2170); digitalWrite(BUZZ_PIN, LOW); }
        for (int i=0;i<185;i++) { digitalWrite(BUZZ_PIN, LOW); delayMicroseconds(500); digitalWrite(BUZZ_PIN, HIGH); delayMicroseconds(2220); digitalWrite(BUZZ_PIN, LOW); }
        break;
      case 4:
      case 11:
        delay(500);
        break;
      case 8:
        for (int i=0;i<1064;i++) { digitalWrite(BUZZ_PIN, LOW); delayMicroseconds(230); digitalWrite(BUZZ_PIN, HIGH); delayMicroseconds(240); digitalWrite(BUZZ_PIN, LOW); }
        break;
      case 9:
        for (int i=0;i<515;i++) { digitalWrite(BUZZ_PIN, LOW); delayMicroseconds(250); digitalWrite(BUZZ_PIN, HIGH); delayMicroseconds(720); digitalWrite(BUZZ_PIN, LOW); }
        break;
      case 10:
        for (int i=0;i<187;i++) { digitalWrite(BUZZ_PIN, LOW); delayMicroseconds(1020); digitalWrite(BUZZ_PIN, HIGH); delayMicroseconds(1690); digitalWrite(BUZZ_PIN, LOW); }
        break;
    }
  }
}

void loop() {
  mc1203();
}