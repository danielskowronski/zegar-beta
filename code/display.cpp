#include <Wire.h>
#include "display.h"
#include "data.h"
#include "display.h"
#include "config.h"
#include "ui.h"

extern int contrast_val=0;
extern int jasnosc_val=5;

void LcdWrite(char dc, char data) {
  digitalWrite(LCD_PIN_DC, dc);
  digitalWrite(LCD_PIN_SCE, LOW);
  shiftOut(LCD_PIN_SDIN, LCD_PIN_SCLK, MSBFIRST, data);
  digitalWrite(LCD_PIN_SCE, HIGH);
}
void LcdInitialise(void) {
  pinMode(LCD_PIN_SCE, OUTPUT);
  pinMode(LCD_PIN_RESET, OUTPUT);
  pinMode(LCD_PIN_DC, OUTPUT);
  pinMode(LCD_PIN_SDIN, OUTPUT);
  pinMode(LCD_PIN_SCLK, OUTPUT);
  digitalWrite(LCD_PIN_RESET, LOW);
  digitalWrite(LCD_PIN_RESET, HIGH);
  LcdWrite(LCD_C, 0x21 );  // LCD Extended Commands.
  LcdWrite(LCD_C, 0xBA+contrast_val+7 );  // Set LCD Vop (Contrast). 
  LcdWrite(LCD_C, 0x04 );  // Set Temp coefficent. //0x04
  LcdWrite(LCD_C, 0x13 );  // LCD bias mode 1:48. //0x13
  LcdWrite(LCD_C, 0x20 );  // LCD Basic Commands
  LcdWrite(LCD_C, 0x0C );  // LCD in normal mode.
}

void LcdCharacter(char character, bool negate) {
  if (negate) LcdWrite(LCD_D, 0xff); else LcdWrite(LCD_D, 0x00);
  for (int index = 0; index < 5; index++)  {
    byte b=pgm_read_byte(&(ASCII[character - 0x20][index])); if (negate) b=~b;
    LcdWrite(LCD_D, b);
  }
  if (negate) LcdWrite(LCD_D, 0xff); else LcdWrite(LCD_D, 0x00);
}
void LcdCharacterBig (int x, int y,char character, bool negate){
  int c = character-48+3;
  if (character=='.') c=1;
  if (character=='-') c=0;

  for (int index = 0; index < 42; index++) {
    gotoXY(x+(index%14), y+index/14);
    byte b=pgm_read_byte(&(BigNumber[c][index])); if (negate) b=~b;
    LcdWrite(LCD_D, b);
  }
}

void gotoXY(int x, int y) {
  LcdWrite( 0, 0x80 | x);  // Column.
  LcdWrite( 0, 0x40 | y);  // Row.  
}

void LcdClear(void) {
  for (int i=0;i<6;i++){
    gotoXY(0,i);
    sprintf(cha, EMPTY_LINE);LcdString(cha, false);
  }  
}
void LcdString(char *characters, bool negate) {
  while (*characters)  {
    LcdCharacter(*characters++, negate);
  }
}

