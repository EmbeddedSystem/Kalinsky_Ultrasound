#ifndef EEPROM_H_
#define EEPROM_H_

#include "avr/io.h"
#include "std_global.h"

#define EEADDRESS_TIME 1
#define EEADDRESS_TIME_LIMIT 2
#define EEADDRESS_TEMP 3
#define EEADDRESS_TEMP_LIMIT 4
#define EEADDRESS_DELTA 5
#define EEADDRESS_ANTIBOILER 6

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);
void EEPROM_write32(unsigned int uiAddress, u32 ucData);
u32 EEPROM_read32(unsigned int uiAddress);
#endif /* EEPROM_H_ */

