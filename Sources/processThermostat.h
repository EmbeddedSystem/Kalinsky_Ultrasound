#ifndef PROCESSTHERMOSTAT_H_
#define PROCESSTHERMOSTAT_H_

#include "processMessages.h"
#include "avr/io.h"
#include "timers.h"
#include "DS1821.h"
#include "sevseg.h"
#include "processKeyboard.h"
#include "eeprom.h"

#define RELAY_TEN_ON sbi(PORTD, PD2)
#define RELAY_TEN_OFF cbi(PORTD, PD2)
#define RELAY_TEN (PORTD & (1 << 2))

volatile u08 ThermostatIsOn;
void ProcessThermostat(void);

#endif /* PROCESSTHERMOSTAT_H_ */
