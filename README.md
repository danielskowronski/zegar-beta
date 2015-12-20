# zegar - beta
personal clock, version beta (not as in alpha-beta-rc-rtm-final but alpha-beta-gamma-... - concept version 2)

more details TBA

## casing
3d model to be printed on Prusa i3 printer

## electronics
arduino nano + rtc + thermometer + buzzer + joystick + nokia lcd

## code
I'm making it for myself so it may be weird for normal people (one of features is streaming temperature to PC via USB)

nice drawing on tiny screen and sound playing via interrupts are one of goals

## ideas - todo
- replace 80x40px LCD with 128x64px OLED screen (via I2C)
- snooze (+alarm) countdown if time remaining <=99min (2 digits) => func to compare timeObj
- more alarms => array of timeObj, somehow display settings (eg. via additional field on alarm adjusting page - alarm num, when changed - save tmp var like pos_setClock) => alarm on/off in settings not in main page => maybe alarm with configurable day of activation? => "1234567" with enabled in negative? => more objects!
