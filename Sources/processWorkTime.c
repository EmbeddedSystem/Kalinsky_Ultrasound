#include "processWorkTime.h"

void ProcessWorktime(void)
{
	if (GetTimer(TIMER_9) >= 60 * SEC) // раз в минуту

	{
		StartTimer(TIMER_9);
		EEPROM_write32(0x10, EEPROM_read32(0x10) + 1); // НАРАБОТКА КОНТРОЛЛЕРА

		if (EEPROM_read32(0x50))// Если включен демо-режим,
		{
			if (EEPROM_read32(0x10) >= EEPROM_read32(0x50)) // Если наработка контроллера больше демо-ограничения:
				SendMessage(MSG_ANTIBOILER); // Портить малину
		}

		if (ThermostatIsOn)
		{
			EEPROM_write32(0x20, EEPROM_read32(0x20) + 1); // НАРАБОТКА ТЕРМОСТАТА
		}
		if (RELAY_TEN)
		{
			EEPROM_write32(0x30, EEPROM_read32(0x30) + 1); // НАРАБОТКА ТЭН
		}
		if (RELAY_UZ)
		{
			EEPROM_write32(0x40, EEPROM_read32(0x40) + 1); // НАРАБОТКА УЗ
		}
	}
}
