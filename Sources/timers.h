#ifndef TIMERS_H_
#define TIMERS_H_

#include "std_global.h"
#include <avr/interrupt.h>
#include "processMessages.h"
#include "sevseg.h"

// У всех таймеров дискрет (1 тик таймера) равен 10 мс
// Идентификаторы таймеров
#define TIMER_0		0 // Клавиатура
#define TIMER_1		1 // Таймер таймаут 3 сек для настроек
#define TIMER_2		2 // Термостат
#define TIMER_3		3 // Динамик
#define TIMER_4		4 // Антикипятильник
#define TIMER_5 	5 // Наработка контроллера
#define TIMER_6 	6 // Наработка термостата
#define TIMER_7 	7 // Наработка ТЭН
#define TIMER_8 	8 // Наработка УЗ
#define TIMER_9 	9 // Таймер 1 минута
#define LAST_TIMER	10

// Состояния таймеров:
#define TIMER_STOPPED 0
#define TIMER_RUNNING 1
#define TIMER_PAUSED 2

#define SEC 100 //сколько тиков программного таймера в секунду
volatile u32 Timers[LAST_TIMER + 1]; // счетчики таймеров
volatile u08 TStates[LAST_TIMER + 1]; // состояния таймеров

void InitTimers(void);
void StartTimer(int TimerID);
void PauseTimer(int TimerID);
void ReleaseTimer(int TimerID);
u32 GetTimer(int TimerID);
void SetTimer(int TimerID, u32 value);

u08 volatile SPEAKER_ON;

#endif /* TIMERS_H_ */
