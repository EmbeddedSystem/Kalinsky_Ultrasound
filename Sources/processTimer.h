#ifndef PROCESSTIMER_H_
#define PROCESSTIMER_H_

#include "std_global.h"
#include "eeprom.h"
#include "sevseg.h"
#include "processMessages.h"
#include "processKeyboard.h"

#define RELAY_UZ_ON sbi(PORTC, PC2)
#define RELAY_UZ_OFF cbi(PORTC, PC2)
#define RELAY_UZ (PORTC & (1 << 2))

void ProcessTimer(void);

#endif /* PROCESSTIMER_H_ */
