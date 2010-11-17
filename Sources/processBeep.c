#include "processBeep.h"

void ProcessBeep(void)
{
	static u08 state;
	switch (state)
	{
	case 0:
		if (GetMessage(MSG_KEY_PRESSED))
		{
			StartTimer(TIMER_3);
			SPEAKER_ON = 1;
			state = 1;
		}
		if (GetMessage(MSG_BEEP_ERROR))
		{
			StartTimer(TIMER_3);
			SPEAKER_ON = 1;
			state = 2;
		}

		break;
	case 1:
		if (GetTimer(TIMER_3) >= 2)
		{
			SPEAKER_ON = 0;
			state = 0;
		}
		break;
	case 2:
		if (GetTimer(TIMER_3) >= 30)
		{
			SPEAKER_ON = 0;
			state = 10;
		}
		break;

	case 10:
		if (GetTimer(TIMER_3) >= 50)
		{
			state = 0;
		}
		break;

	default:
		break;
	}

}
