#include "processAntiboiler.h"

void ProcessAntiboiler(void)
{
	static u08 state;
	switch (state)
	{
	case 0: // ÂÛÊËÞ×ÅÍÎ
		if ((ThermostatIsOn == 1) && (RELAY_UZ == 0))
		{
			if (EEPROM_read(EEADDRESS_ANTIBOILER))
			{
				state = 1;
				StartTimer(TIMER_4);
			}
		}
		break;
	case 1: // ÎÆÈÄÀÍÈÅ ÑÐÀÁÀÒÛÂÀÍÈß ÀÍÒÈÊÈÏßÒÈËÜÍÈÊÀ
		if (ThermostatIsOn == 0)
		{
			state = 0;
		}
		if (RELAY_UZ == 1)
		{
			state = 0;
		}
		if (GetTimer(TIMER_4) >= (EEPROM_read(EEADDRESS_ANTIBOILER) * 60 * SEC))
		{
			SendMessage(MSG_ANTIBOILER);
			state = 0;
		}
		break;
	default:
		break;
	}
}
