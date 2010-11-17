#include "sevseg.h"

u08 segment = 1;

void sevSegService(void)
{
	KAT_1_OFF;
	KAT_2_OFF;
	KAT_3_OFF;
	KAT_4_OFF;

	switch (segment)
	{
	case 1:
		outDigit(time_high);
		segment = 2;
		//		if (time_high_flash)
		if (timeFlashIsOn)
		{
			if (flashing)
				KAT_1_ON;
		}
		else
		{
			KAT_1_ON;
		}
		break;
	case 2:
		outDigit(time_low);
		segment = 3;
		//		if (time_low_flash)
		if (timeFlashIsOn)
		{
			if (flashing)
				KAT_2_ON;
		}
		else
		{
			KAT_2_ON;
		}
		break;
	case 3:
		outDigit(temp_high);
		segment = 4;
		if (tempFlashIsOn)
		{
			if (flashing)
				KAT_3_ON;
		}
		else
		{
			KAT_3_ON;
		}
		break;
	case 4:
		outDigit(temp_low);
		segment = 1;
		if (tempFlashIsOn)
		{
			if (flashing)
				KAT_4_ON;
		}
		else
		{
			KAT_4_ON;
		}
		break;
	default:
		break;
	}
}

void outDigit(u08 digit)
{
	SEG_A_ON;
	SEG_B_ON;
	SEG_C_ON;
	SEG_D_ON;
	SEG_E_ON;
	SEG_F_ON;
	SEG_G_ON;
	switch (digit)
	{
	case 0:
		SEG_G_OFF;
		break;
	case 1:
		SEG_A_OFF;
		SEG_D_OFF;
		SEG_E_OFF;
		SEG_F_OFF;
		SEG_G_OFF;
		break;
	case 2:
		SEG_C_OFF;
		SEG_F_OFF;
		break;
	case 3:
		SEG_E_OFF;
		SEG_F_OFF;
		break;
	case 4:
		SEG_A_OFF;
		SEG_E_OFF;
		SEG_D_OFF;
		break;
	case 5:
		SEG_B_OFF;
		SEG_E_OFF;
		break;
	case 6:
		SEG_B_OFF;
		break;
	case 7:
		SEG_D_OFF;
		SEG_E_OFF;
		SEG_F_OFF;
		SEG_G_OFF;
		break;
	case 8:
		break;
	case 9:
		SEG_E_OFF;
		break;
	case 10: // A
		SEG_D_OFF;
		break;
	case 11: // b
		SEG_A_OFF;
		SEG_B_OFF;
		break;
	case 12: // C
		SEG_B_OFF;
		SEG_C_OFF;
		SEG_G_OFF;
		break;
	case 13: // d
		SEG_A_OFF;
		SEG_F_OFF;
		break;
	case 14: // E
		SEG_B_OFF;
		SEG_C_OFF;
		break;
	case 15: // F
		SEG_B_OFF;
		SEG_C_OFF;
		SEG_D_OFF;
		break;
	case ERROR:
		SEG_A_OFF;
		SEG_B_OFF;
		SEG_C_OFF;
		SEG_D_OFF;
		SEG_E_OFF;
		SEG_F_OFF;
		break;
	default:
		SPEAKER_ON = 1;
		break;
	}
}
