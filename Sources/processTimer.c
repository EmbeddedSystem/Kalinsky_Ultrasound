#include "processTimer.h"

void ProcessTimer(void)
{
	static u08 state;
	static u08 minutes; // бПЕЛЪ Б ЛХМСРЮУ

	switch (state)
	{
	case 0: // хяундмне
		minutes = EEPROM_read(EEADDRESS_TIME);
		time_high = minutes / 10;
		time_low = minutes % 10;
		timeFlashIsOn = 1;
		RELAY_UZ_OFF;
		if (GetMessage(MSG_KEY_PRESSED))
		{
			if (keyCode == KEY_TIME_OK)
			{
				state = 2; //рюилеп бйкчвем
				StartTimer(TIMER_1); // реоепэ рюилеп нрявхршбюер йюфдсч яейсмдс
			}
			if ((keyCode == KEY_TIME_UP) || (keyCode == KEY_TIME_DOWN))
			{
				state = 1; //мюярпнийю рюилепю
				StartTimer(TIMER_1);
			}
		}
		break;
	case 1: // мюярпнийю рюилепю
		timeFlashIsOn = 0;
		if (GetMessage(MSG_KEY_PRESSED))
		{
			if (keyCode == KEY_TIME_OK)
			{
				state = 2; //рюилеп бйкчвем
				EEPROM_write(EEADDRESS_TIME, minutes);
			}
			if (keyCode == KEY_TIME_UP)
			{
				if (minutes < EEPROM_read(EEADDRESS_TIME_LIMIT))
				{
					minutes++;
				}
			}
			if (keyCode == KEY_TIME_DOWN)
			{
				if (minutes > 1)
				{
					minutes--;
				}
			}
			time_high = minutes / 10;
			time_low = minutes % 10;
			StartTimer(TIMER_1);
		}
		if (GetTimer(TIMER_1) >= 3 * SEC)
		{
			state = 0;
			EEPROM_write(EEADDRESS_TIME, minutes);
		}
		break;
	case 2: // рюилеп бйкчвем
		RELAY_UZ_ON;
		timeFlashIsOn = 0;
		if (GetMessage(MSG_KEY_PRESSED))
		{
			if (keyCode == KEY_TIME_OK)
			{
				state = 0;
				RELAY_UZ_OFF;
			}
		}
		if (GetTimer(TIMER_1) >= 60 * SEC)// ДКЪ НРКЮДЙХ ЛНФМН ОНЯРЮБХРЭ ЛЕМЭЬЕ 60!
		{
			StartTimer(TIMER_1);
			minutes--;
			if (minutes == 0)
			{
				state = 3;
				RELAY_UZ_OFF;
				StartTimer(TIMER_1);
			}
			else
			{
				time_high = minutes / 10;
				time_low = minutes % 10;
			}
		}
		break;
	case 3: // бпелъ бшькн
		time_high = 0;
		time_low = 0;
		SendMessage(MSG_BEEP_ERROR);
		if (GetTimer(TIMER_1) >= 2 * SEC)
		{
			state = 0;
		}
		if (GetMessage(MSG_KEY_PRESSED))
		{
			state = 0;
		}
		break;
	default:
		break;
	}
}
