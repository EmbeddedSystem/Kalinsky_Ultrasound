#include "processThermostat.h"

void ProcessThermostat(void)
{
	static u08 state;
	static u08 temperature;

	switch (state)
	{
	case 0: // »—’ŒƒÕŒ≈
		ThermostatIsOn = 0;
		RELAY_TEN_OFF;
		tempFlashIsOn = 1;
		// ‡Á ‚ ÒÂÍÛÌ‰Û Ò˜ËÚ˚‚‡ÂÏ ÚÂÏÔÂ‡ÚÛÛ
		if (GetTimer(TIMER_2) >= SEC)
		{
			temperature = readTemp(&temp_low, &temp_high);
			StartTimer(TIMER_2);
			if (temperature == ERROR)
			{
				SendMessage(MSG_BEEP_ERROR);
				checkDS();
				w1_reset();
				w1_byte_wr(0xEE);
			}
		}
		if (GetMessage(MSG_KEY_PRESSED))
		{
			if (keyCode == KEY_TEMP_OK)
			{
				state = 1;
			}
			if (keyCode == KEY_TEMP_UP)
			{
				state = 2;
				StartTimer(TIMER_2);
				temperature = EEPROM_read(EEADDRESS_TEMP);
			}
			if (keyCode == KEY_TEMP_DOWN)
			{
				state = 2;
				StartTimer(TIMER_2);
				temperature = EEPROM_read(EEADDRESS_TEMP);
			}
		}
		break;
	case 1: //“≈–ÃŒ—“¿“ ¬ Àﬁ◊≈Õ
		ThermostatIsOn = 1;
		tempFlashIsOn = 0;
		// ‡Á ‚ ÒÂÍÛÌ‰Û Ò˜ËÚ˚‚‡ÂÏ ÚÂÏÔÂ‡ÚÛÛ
		if (GetTimer(TIMER_2) >= SEC)
		{
			temperature = readTemp(&temp_low, &temp_high);
			StartTimer(TIMER_2);
			if (temperature == ERROR)
			{
				RELAY_TEN_OFF;
				SendMessage(MSG_BEEP_ERROR);
				checkDS();
				w1_reset();
				w1_byte_wr(0xEE);
			}
			else
			{
				if (temperature >= EEPROM_read(EEADDRESS_TEMP))
				{
					RELAY_TEN_OFF;
				}
				else if (temperature < (EEPROM_read(EEADDRESS_TEMP)
						- EEPROM_read(EEADDRESS_DELTA)))
				{
					RELAY_TEN_ON;
				}
			}
		}
		if (GetMessage(MSG_KEY_PRESSED))
		{
			if (keyCode == KEY_TEMP_OK)
			{
				RELAY_TEN_OFF;
				state = 0;
			}
		}
		if (GetMessage(MSG_ANTIBOILER))
		{
			RELAY_TEN_OFF;
			state = 3;
		}
		break;
	case 2: // Õ¿—“–Œ… ¿
		ThermostatIsOn = 0;
		temp_high = temperature / 10;
		temp_low = temperature % 10;
		tempFlashIsOn = 0;

		if (GetMessage(MSG_KEY_PRESSED))
		{
			StartTimer(TIMER_2);
			if (keyCode == KEY_TEMP_OK)
			{
				state = 1;
				EEPROM_write(EEADDRESS_TEMP, temperature);
			}
			if (keyCode == KEY_TEMP_UP)
			{
				if (temperature < EEPROM_read(EEADDRESS_TEMP_LIMIT))
				{
					temperature++;
				}
			}
			if (keyCode == KEY_TEMP_DOWN)
			{
				if (temperature >= 2)
				{
					temperature--;
				}
			}
		}
		if (GetTimer(TIMER_2) >= 3 * SEC)
		{
			state = 0;
			EEPROM_write(EEADDRESS_TEMP, temperature);
		}
		break;
	case 3: //¡ÀŒ »–Œ¬ ¿ ¿Õ»“» »œﬂ“»À‹Õ» ¿
		ThermostatIsOn = 0;
		RELAY_TEN_OFF;
		SendMessage(MSG_BEEP_ERROR);
		if (GetMessage(MSG_KEY_PRESSED))
		{
			keyCode = 0;
			state = 0;
		}
		break;
	default:
		break;
	}
}
