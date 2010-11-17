#include "timers.h"

// TIMER0 - таймер только для индикатора
void timer0_init(void)// 400 Hz indicator
{
	sbi(TCCR0B, CS02); // fosc/256
	sbi(TIFR0, TOV0);
	TCNT0 = 0x64;
	sbi(TIMSK0, TOIE0);
}
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 0x64; // Перезарядка таймера
	sevSegService(); //Обслуживание индикатора
	flash_counter++;
	if (90 == flash_counter)
	{
		flash_counter = 0;
		flashing = ~flashing;
	}
}

// TIMER1 - таймер только для софтовых таймеров программы, 10 мс
void timer1_init(void)
{
	sbi(TCCR1B, CS10); // fosc/64
	sbi(TCCR1B, CS11); // fosc/64
	sbi(TIFR1, TOV1);
	TCNT1 = 0xFB1E; // 10 мс
	sbi(TIMSK1, TOIE1);
}
ISR(TIMER1_OVF_vect)
{
	TCNT1 = 0xFB1E;

	// Обслуживание софтовых таймеров одним аппаратным таймером
	int i;
	for (i = 0; i <= LAST_TIMER; i++)
	{
		if (TStates[i] == TIMER_RUNNING)
		{
			Timers[i]++; //Инкремент счетчиков программных таймеров
		}
	}
}

// TIMER2 - таймер только для спикера
void timer2_init(void)// 2KHz speaker
{
	sbi(TCCR2B, CS21); // fosc/32
	sbi(TCCR2B, CS20); // fosc/32
	sbi(TIFR2, TOV2);
	TCNT2 = 0x83; // 2KHz
	sbi(TIMSK2, TOIE2);
}
ISR(TIMER2_OVF_vect)
{
	//TCNT2 = 0xC2; // Перезарядка таймера
	TCNT2 = 0xC7; // Перезарядка таймера
	if (SPEAKER_ON) // Если надо, дергаем ногой спикера и пищим 2 КГц
	{
		PORTB = PORTB ^ (1 << PB0);
	}
	else
	{
		cbi(PORTB, PB0); // Когда не надо не пищим, а нога всегда в 0
	}
}

// Инициализация программных и аппаратных таймеров, делается один раз в начале программы
void InitTimers(void)
{
	timer0_init(); //Инициализация аппаратного таймера
	timer1_init(); //Инициализация аппаратного таймера
	timer2_init(); //Инициализация аппаратного таймера

	int i;
	for (i = 0; i <= LAST_TIMER; i++)
	{
		TStates[i] = TIMER_STOPPED; // Инициализация программных таймеров
		// счетчики обнулять необязательно, во время старта обнуляются все равно
	}
}

// Подпрограммы софтовых таймеров
void StartTimer(int TimerID) // Запуск софтового таймера
{
	Timers[TimerID] = 0; // Сброс счетчика таймера
	TStates[TimerID] = TIMER_RUNNING;
}

void PauseTimer(int TimerID)
{
	if (TStates[TimerID] == TIMER_RUNNING)
	{
		TStates[TimerID] = TIMER_PAUSED;
	}
}

void ReleaseTimer(int TimerID)
{
	if (TStates[TimerID] == TIMER_PAUSED)
	{
		TStates[TimerID] = TIMER_RUNNING;
	}
}

u32 GetTimer(int TimerID)
{
	return Timers[TimerID];
}

void SetTimer(int TimerID, u32 value)
{
	Timers[TimerID] = value;
}
