#ifndef TIMERS_H_
#define TIMERS_H_

#include "std_global.h"
#include <avr/interrupt.h>
#include "processMessages.h"
#include "sevseg.h"

// � ���� �������� ������� (1 ��� �������) ����� 10 ��
// �������������� ��������
#define TIMER_0		0 // ����������
#define TIMER_1		1 // ������ ������� 3 ��� ��� ��������
#define TIMER_2		2 // ���������
#define TIMER_3		3 // �������
#define TIMER_4		4 // ���������������
#define TIMER_5 	5 // ��������� �����������
#define TIMER_6 	6 // ��������� ����������
#define TIMER_7 	7 // ��������� ���
#define TIMER_8 	8 // ��������� ��
#define TIMER_9 	9 // ������ 1 ������
#define LAST_TIMER	10

// ��������� ��������:
#define TIMER_STOPPED 0
#define TIMER_RUNNING 1
#define TIMER_PAUSED 2

#define SEC 100 //������� ����� ������������ ������� � �������
volatile u32 Timers[LAST_TIMER + 1]; // �������� ��������
volatile u08 TStates[LAST_TIMER + 1]; // ��������� ��������

void InitTimers(void);
void StartTimer(int TimerID);
void PauseTimer(int TimerID);
void ReleaseTimer(int TimerID);
u32 GetTimer(int TimerID);
void SetTimer(int TimerID, u32 value);

u08 volatile SPEAKER_ON;

#endif /* TIMERS_H_ */
