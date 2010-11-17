#include "processKeyboard.h"

static u08 AskKeyPorts(void)
{
	if ((PINC & (1 << 0)) == 0)
	{
		return KEY_TEMP_UP;
	}
	if ((PINB & (1 << 4)) == 0)
	{
		return KEY_TIME_DOWN;
	}
	if ((PINB & (1 << 2)) == 0)
	{
		return KEY_TEMP_OK;
	}
	if ((PIND & (1 << 4)) == 0)
	{
		return KEY_TIME_UP;
	}
	if ((PINB & (1 << 1)) == 0)
	{
		return KEY_TEMP_DOWN;
	}
	if ((PINB & (1 << 3)) == 0)
	{
		return KEY_TIME_OK;
	}
	return 0;
}

void ProcessKeyboard()
{
	static u08 state;
	//temp_low = AskKeyPorts();
	switch (state)
	{
	case 0:
		// Ожидание нажатия на клавишу
		if ((keyCode = AskKeyPorts()) > 0)
		{
			StartTimer(TIMER_0);
			state = 1;
		}
		break;
	case 1:
		// Отработка задержки антидребезга
		if (GetTimer(TIMER_0) >= DEBOUNCE)
		{
			state = 2;
		}
		break;
	case 2:

		if (keyCode == AskKeyPorts())
		{
			StartTimer(TIMER_0);
			SendMessage(MSG_KEY_PRESSED);
			state = 3;
		}
		else
		{
			state = 0;
		}
		break;
	case 3:
		if (keyCode == AskKeyPorts())
		{
			if (GetTimer(TIMER_0) >= FIRST_DELAY)
			{
				StartTimer(TIMER_0);
				if (keyCode <= 4)
				{
					SendMessage(MSG_KEY_PRESSED);
				}
				state = 4;
			}
		}

		else
		{
			state = 0;
		}
		break;
	case 4:
		if (keyCode == AskKeyPorts())
		{
			if (GetTimer(TIMER_0) >= AUTO_REPEAT)
			{
				StartTimer(TIMER_0);
				if (keyCode <= 4)
				{
					SendMessage(MSG_KEY_PRESSED);
				}
				state = 4;
			}
		}
		else
		{
			state = 0;
		}
		break;

	default:
		break;
	}
}
