#include "delay.h"
#include "keyboard.h"
#include "tm1637.h"
#include "number_converter.h"

#include "stdlib.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"


//keyboard
//C3 GPIOB9
//C2 GPIOB10
//C1 GPIOB11
//R4 GPIOB12
//R3 GPIOB13
//R2 GPIOB14
//R1 GPIOB15

//display
//CLK GPIOB6
//DIO GPIOB7
//UCC 5V
//GND G

int state = 0;
unsigned int keypad_columns[3] = 
{
	GPIO_Pin_9,
	GPIO_Pin_10,
	GPIO_Pin_11
};
unsigned int keypad_rows[4] = 
{
	GPIO_Pin_12,
	GPIO_Pin_13,
	GPIO_Pin_14,
	GPIO_Pin_15
};

int main()
{
	TM1637_init();	
  TM1637_brightness(BRIGHT_TYPICAL);
	keypad_init(keypad_columns, keypad_rows);
  delay_ms(10);
	while (1)
	{
		char key=keypadGetKey();
		int number = -1;;
		
		switch(key) {
			case '*':
				number = state * 10;
				break;
			case '#':
				number = state / 10;
				break;
			default:
				number = convert_char(key);
		}
		
		if (number != -1) {
			state = number;
			TM1637_display_all(state);
		}
		delay_ms(1);
	}
}
