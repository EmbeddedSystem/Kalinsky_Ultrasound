#include "processWorkTime.h"

void ProcessWorktime(void)
{
	if (GetTimer(TIMER_9) >= 60 * SEC) // ��� � ������

	{
		StartTimer(TIMER_9);
		EEPROM_write32(0x10, EEPROM_read32(0x10) + 1); // ��������� �����������

		if (EEPROM_read32(0x50))// ���� ������� ����-�����,
		{
			if (EEPROM_read32(0x10) >= EEPROM_read32(0x50)) // ���� ��������� ����������� ������ ����-�����������:
				SendMessage(MSG_ANTIBOILER); // ������� ������
		}

		if (ThermostatIsOn)
		{
			EEPROM_write32(0x20, EEPROM_read32(0x20) + 1); // ��������� ����������
		}
		if (RELAY_TEN)
		{
			EEPROM_write32(0x30, EEPROM_read32(0x30) + 1); // ��������� ���
		}
		if (RELAY_UZ)
		{
			EEPROM_write32(0x40, EEPROM_read32(0x40) + 1); // ��������� ��
		}
	}
}
