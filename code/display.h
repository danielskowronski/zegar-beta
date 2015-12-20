#ifndef DISPLAY_H
#define DISPLAY_H

extern int contrast_val;
extern int jasnosc_val;

void LcdCharacter(char character, bool negate=false);
void LcdCharacterBig (int x, int y,char character, bool negate);
void LcdInitialise(void);
void LcdString(char *characters, bool negate=false);
void gotoXY(int x, int y);
void LcdClear(void);
void LcdWrite(char dc, char data);

#endif
