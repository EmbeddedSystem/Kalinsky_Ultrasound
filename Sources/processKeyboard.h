#ifndef PROCESSKEYBOARD_H_
#define PROCESSKEYBOARD_H_

#include "processMessages.h"
#include "avr/io.h"
#include "sevseg.h"
#include "timers.h"

#define KEY_TIME_UP 1
#define KEY_TIME_DOWN 2
#define KEY_TEMP_UP 3
#define KEY_TEMP_DOWN 4
#define KEY_TIME_OK 5
#define KEY_TEMP_OK 6

#define DEBOUNCE 10
#define FIRST_DELAY 100
#define AUTO_REPEAT 15

void ProcessKeyboard();
volatile u08 keyCode;

#endif /* PROCESSKEYBOARD_H_ */
