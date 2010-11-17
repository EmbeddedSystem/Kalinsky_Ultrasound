#ifndef DS1821_H_
#define DS1821_H_

#include "std_global.h"
#include "avr/io.h"
#include "util/delay.h"
#include "sevseg.h"

#define DS_VCC_ON sbi(PORTB, PB7)
#define DS_VCC_OFF cbi(PORTB, PB7)

#define W1_PIN	PB6
#define W1_IN	PINB
#define W1_OUT	PORTB
#define W1_DDR	DDRB

void toggleMode(void);
u08 w1_reset(void);
u08 w1_byte_rd(void);
void w1_byte_wr(u08 b);
u08 checkDS(void);
u08 readTemp(u08* seg_low, u08* seg_high);
#endif /* DS1821_H_ */
