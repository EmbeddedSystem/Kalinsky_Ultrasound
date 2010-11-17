#include "DS1821.h"

// переключить режим датчика на противоположный
void toggleMode(void)
{
	sbi(W1_OUT, W1_PIN);
	sbi(W1_DDR, W1_PIN);
	DS_VCC_ON;
	_delay_ms(1);
	DS_VCC_OFF;
	_delay_ms(1);

	int i;
	for (i = 0; i < 16; i++)
	{
		cbi(W1_OUT, W1_PIN);
		_delay_us(10);
		sbi(W1_OUT, W1_PIN);
		_delay_us(10);
	}
	_delay_ms(1);
	DS_VCC_ON;
	_delay_ms(1);
}
u08 checkDS(void)
{
	cli();
	DS_VCC_ON;
	_delay_ms(10);
	if (w1_reset()) // если нет ответа от датчика...
	{
		toggleMode(); //  пытаемся переключить его из режима термостата

		w1_reset();
		w1_byte_wr(0x01); // +125 TH
		w1_byte_wr(0x7D); //

		w1_reset();
		w1_byte_wr(0x02); // TL
		w1_byte_wr(0xE7); //-55

		w1_reset();
		w1_byte_wr(0x0C); // команда записи регистра статуса
		w1_byte_wr(0b00000000); // очищаем бит режима термостата
		_delay_ms(15);
	}
	DS_VCC_OFF;
	_delay_ms(10);
	DS_VCC_ON;
	_delay_ms(10);
	if (w1_reset())
	{
		sei();
		return 1;
	}
	else
	{
		sei();
		return 0; // ОК, датчик ответил
	}
}
u08 w1_reset(void)
{
	cli();
	W1_OUT &= ~(1 << W1_PIN); // One-wire LOW
	W1_DDR |= 1 << W1_PIN;

	_delay_us(480); // 480 us

	W1_DDR &= ~(1 << W1_PIN);
	_delay_us(65); // Wait 15 + 50 us
	u08 err = W1_IN & (1 << W1_PIN); // Sample bus

	_delay_us(480 - 65); // wait until cycle is gone

	if ((W1_IN & (1 << W1_PIN)) == 0) // check bus for HIGH, othwise we have a short circuit
		err = 1;
	sei();
	return err;
}
u08 w1_bit_read(void)
{
	W1_OUT &= ~(1 << W1_PIN); // One-wire LOW
	W1_DDR |= 1 << W1_PIN;

	_delay_us(1); // 1 us time
	W1_DDR &= ~(1 << W1_PIN); // One-wire HIGH and use as input

	_delay_us(14); // 14 us
	u08 value = W1_IN & (1 << W1_PIN); // sample bus
	_delay_us(45); // 45 us

	return value;
}
void w1_bit_write(u08 b)
{
	W1_OUT &= ~(1 << W1_PIN); // One-wire LOW
	W1_DDR |= 1 << W1_PIN;
	_delay_us(10); // 10 us

	if (b)
	{
		W1_DDR &= ~(1 << W1_PIN); // One-wire input
		_delay_us(5 + 45); // in total 60 us
	}
	else
	{
		_delay_us(5 + 45); // 60 us in total
		W1_DDR &= ~(1 << W1_PIN); // One-wire HIGH and use as input
	}
}
int w1_read(u08 bits)
{
	cli();
	u08 i = bits;
	int value = 1 << (bits - 1);
	int b = 0;

	do
	{
		b >>= 1;
		if (w1_bit_read())
			b |= value;

	} while (--i);
	sei();
	return b;
}
u08 w1_byte_rd(void)
{
	return (u08) w1_read(8);
}

void w1_byte_wr(u08 b)
{
	cli();
	u08 i = 8;
	do
	{
		w1_bit_write(b & 1);
		b >>= 1;

	} while (--i);
	sei();
}

u08 readTemp(u08* seg_low, u08* seg_high)
{
	u08 temp;
	if (w1_reset())
	{
		*seg_high = ERROR;
		*seg_low = ERROR;
		return ERROR;
	}
	else
	{
		w1_byte_wr(0xAA);
		temp = w1_byte_rd();
		if ((temp & 0x80) || (temp == 0) || (temp >= 100))
		{
			*seg_high = ERROR;
			*seg_low = ERROR;
			return ERROR;
		}
		else
		{
			*seg_high = temp / 10;
			*seg_low = temp % 10;
			return temp;
		}
	}
}
