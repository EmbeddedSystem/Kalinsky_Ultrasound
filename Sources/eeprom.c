#include "eeprom.h"

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
	while (EECR & (1 << EEPE))
	{
	};
	EEAR = uiAddress;
	EEDR = ucData;
	EECR |= (1 << EEMPE);
	EECR |= (1 << EEPE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
	while (EECR & (1 << EEPE))
	{
	};
	EEAR = uiAddress;
	EECR |= (1 << EERE);
	return EEDR;
}

void EEPROM_write32(unsigned int uiAddress, u32 ucData)
{
	EEPROM_write(uiAddress + 3, (ucData & 0x000000FF));
	EEPROM_write(uiAddress + 2, (ucData & 0x0000FF00) >> 8);
	EEPROM_write(uiAddress + 1, (ucData & 0x00FF0000) >> 16);
	EEPROM_write(uiAddress, (ucData & 0xFF000000) >> 24);
}
u32 EEPROM_read32(unsigned int uiAddress)
{
	u32 temp;
	temp = EEPROM_read(uiAddress + 3);
	temp |= (u32) EEPROM_read(uiAddress + 2) << 8;
	temp |= (u32) EEPROM_read(uiAddress + 1) << 16;
	temp |= (u32) EEPROM_read(uiAddress) << 24;
	return temp;
}
