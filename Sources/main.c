#include "main.h"

void initPorts()
{
	PORTB = 0b00011110;
	DDRB = 0b10100001;

	PORTC = 0b11000001;
	DDRC = 0b00111110;

	PORTD = 0b00010000;
	DDRD = 0b11101111;
}

void initEEPROM(void)
{
	// ������ ��������������� ����� � ������ ��� ����� 0XFF
	if (EEPROM_read(0) == 0xFF)
	{
		EEPROM_write(EEADDRESS_TEMP, 28); // 20 ��������
		EEPROM_write(EEADDRESS_TEMP_LIMIT, 60); // 60 �������� ��������
		EEPROM_write(EEADDRESS_TIME, 5); // 15 �����
		EEPROM_write(EEADDRESS_TIME_LIMIT, 30); // 30 ����� ��������
		EEPROM_write(EEADDRESS_DELTA, 0); // ������ ����������� ����������� ������������
		EEPROM_write(EEADDRESS_ANTIBOILER, 2); // ��������������� ��������

		EEPROM_write32(0x10, 0);
		EEPROM_write32(0x20, 0);
		EEPROM_write32(0x30, 0);
		EEPROM_write32(0x40, 0);
		EEPROM_write32(0x50, 0); // ����-�����, � �������, 0 ���� ��������

		// TODO �������� ��������� ��� ��������
		// �������� �������� ���� �������� � ������ ��������� �� ������ �� ��������
		// ����� ������� ���� ��� ������ ������ ��� �������� ���������� �� ���������
		EEPROM_write(0, 0);
	}
}

int main()
{
	initPorts();
	InitMessages();
	InitTimers();
	initEEPROM();
	StartTimer(TIMER_2);
	StartTimer(TIMER_9);

	checkDS();
	w1_reset();
	w1_byte_wr(0xEE);
	sei();

	while (1)
	{
		ProcessKeyboard();
		ProcessBeep();
		ProcessThermostat();
		ProcessTimer();
		ProcessWorktime();
		ProcessAntiboiler();

		//*** ����������� � �����! *********
		ProcessMessages();
		//**********************************
	}
	return 0;
}
