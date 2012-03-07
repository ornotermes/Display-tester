/*
	Copyright (c) 2012 Rikard Lindstrom <ornotermes@gmail.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcdlibrary/lcd.c"
#include "custchars.c"

#define LED_R		(1<<PC6)
#define LED_R_PORT	PORTC
#define LED_R_DDR	DDRC

#define LED_G		(1<<PC5)
#define LED_G_PORT	PORTC
#define LED_G_DDR	DDRC

#define LED_B		(1<<PB7)
#define LED_B_PORT	PORTB
#define LED_B_DDR	DDRB

#define BTN			(1<<PD7)
#define BTN_PORT	PORTD
#define BTN_PIN		PIND
#define BTN_DDR		DDRD
#define BTN_VAL		(PIND & (1<<PD7))? 1 : 0

#define LCD_DELAY	_delay_ms(500); while (BTN_VAL)

char lcd_page = 0;

int main(void)
{
	//setup LEDs
	LED_R_DDR |= LED_R;
	LED_R_PORT |= LED_R;
	LED_G_DDR |= LED_G;
	LED_G_PORT |= LED_G;

	//Set full speed (disables CKDIV8 by registers)
	CLKPR = (1<<CLKPCE);
	CLKPR = 0;

	//Init button
	//Has external pullup due to HWB
	EICRB |= (1<<ISC71);
	EIMSK |= (1<<INT7);
	
	sei();
	
	//negative contrast voltage generator
	DDRB = (1<<PB7);
	TCCR1A = (1<<COM1C0);
	TCCR1B = (1<<WGM12)|(1<<CS11)|(1<<CS10);
	OCR1A = 10;
	
	lcd_init(LCD_DISP_ON);
	custchars();

	while(1)
	{
	
		lcd_clrscr();
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_gotoxy(0,1);
		lcd_putc(1);
		lcd_putc(2);
		lcd_puts("  Displaytest   ");
		lcd_putc(1);
		lcd_putc(2);
		lcd_gotoxy(0,2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_puts("      20x4      ");
		lcd_putc(1);
		lcd_putc(2);
		lcd_gotoxy(0,3);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		lcd_putc(1);
		lcd_putc(2);
		LCD_DELAY;
	
		lcd_clrscr();
		for (char i = 0; i < 80; i++)
		{
			lcd_putc(0);
		}
		LCD_DELAY;
	
		lcd_clrscr();
		for (char i = 0; i < 80; i++)
		{
			lcd_putc(3);
		}
		LCD_DELAY;
	
		lcd_clrscr();
		for (char i = 0; i < 80; i++)
		{
			lcd_putc(4);
		}
		LCD_DELAY;
	
		for (char i = 0; i < 4; i++)
		{
			lcd_clrscr();
			for (char y = 0; y < 4; y++)
			{
				lcd_gotoxy(0,y);
				for (char x = 0; x < 20; x++)
				{
					if (32+i*80+y*20+x < 256) lcd_putc(32+i*80+y*20+x);
				}
			}
			LCD_DELAY;
		}
		
	}
	
}

ISR(INT7_vect)
{
}
