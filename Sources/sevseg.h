#include "avr/io.h"
#include "std_global.h"
#include "timers.h"

#ifndef SEVSEG_H_
#define SEVSEG_H_

// *************** ��������������!!! ***************
#define SEG_A_ON sbi(PORTD, PD3)
#define SEG_B_ON sbi(PORTD, PD5)
#define SEG_C_ON sbi(PORTC, PC1)
#define SEG_D_ON sbi(PORTC, PC3)
#define SEG_E_ON sbi(PORTC, PC4)
#define SEG_F_ON sbi(PORTD, PD7)
#define SEG_G_ON sbi(PORTD, PD6)

#define SEG_A_OFF cbi(PORTD, PD3)
#define SEG_B_OFF cbi(PORTD, PD5)
#define SEG_C_OFF cbi(PORTC, PC1)
#define SEG_D_OFF cbi(PORTC, PC3)
#define SEG_E_OFF cbi(PORTC, PC4)
#define SEG_F_OFF cbi(PORTD, PD7)
#define SEG_G_OFF cbi(PORTD, PD6)

#define KAT_3_ON sbi(PORTB, PB5)
#define KAT_4_ON sbi(PORTD, PD1)
#define KAT_1_ON sbi(PORTD, PD0)
#define KAT_2_ON sbi(PORTC, PC5)

#define KAT_3_OFF cbi(PORTB, PB5)
#define KAT_4_OFF cbi(PORTD, PD1)
#define KAT_1_OFF cbi(PORTD, PD0)
#define KAT_2_OFF cbi(PORTC, PC5)

// *************** ��������������!!! ***************

#define ERROR 0xEE
#define UP 0xFA
#define DOWN 0xFB

// ���� ������������ ���� ���� ��� ����������� �� ����������������
// ��� ����� �����������:
u08 temp_low;
u08 temp_high;

// � ��� ����� �������:
volatile u08 time_low;
volatile u08 time_high;

// ������������� ��� ������� ����������� � ������� (����/�� ����)
volatile u08 timeFlashIsOn;
volatile u08 tempFlashIsOn;

// ��������� ���������� ��� ������� ����������� � �������
u08 flashing;
u08 flash_counter;

void outDigit(u08 digit);

//���������� �� ���������� ������� 400 ��
void sevSegService(void);

#endif /* 7SEG_H_ */
