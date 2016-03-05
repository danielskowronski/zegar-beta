#ifndef CONFIG_H
#define CONFIG_H

#define JOYSTICK_X 1
#define JOYSTICK_Y 0
#define JOYSTICK_B 12

#define LCD_BACKLIGHT 11

#define BUZZ_PIN 10

#define LCD_PIN_SCE   7
#define LCD_PIN_RESET 8 //13
#define LCD_PIN_DC    6
#define LCD_PIN_SDIN  5
#define LCD_PIN_SCLK  4
#define LCD_C     LOW
#define LCD_D     HIGH
#define LCD_X     84
#define LCD_Y     48

#include <Rtc_Pcf8563.h>
extern Rtc_Pcf8563 rtc;

#include <DHT.h>
#define DHTPIN 2 
#define DHTTYPE DHT11
extern DHT dht;

#define SNOOZE_TIME 1//9

#endif
