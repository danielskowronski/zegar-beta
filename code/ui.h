#ifndef UI_H
#define UI_H

extern char cha[25]; //general use temp char array

//joystick handling - values are updated in main loop
extern int x, y, b;
void readJoystick();
bool isUp();
bool isDown();
bool isLeft();
bool isRight();
bool isPressed();

extern int mode;
extern bool modechanged;
extern int pos_menu, pos_setClock, pos_setDisp;

extern bool PAR;

void displayClock();
void showMenu();
void setClock(bool isClock);
void setDisplay();

#endif
