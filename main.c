#include "filter.h"
#include "delay.h"
#include "ADC.h"
#include "tm1637.h"
#include "stdio.h"
#define BUFFER_SIZE 64
#define FILTER_ARITY 16

unsigned int digit_display0 = 0;
struct Buffer buf;

int main()
{
	ADC_init();
	delay_ms(10);
	TM1637_init();
	TM1637_brightness(BRIGHT_TYPICAL);
	delay_ms(10);
	TM1637_display_all(digit_display0);
	delay_ms(1000);
	buf = cbuf_new(BUFFER_SIZE);
	
	TIM_TimeBaseInitTypeDef TIMER_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	/*seed n initial values into buffer*/
	
	for(int i = 0; i < FILTER_ARITY; i++){
		cbuf_write(&buf, ADC_read());
		cbuf_read(&buf);
		delay_ms(5);
	}
	
	int filter_val = 0;
	while (1)
	{
		cbuf_write(&buf, ADC_read());
		filter_val = n_term_recursive_filter(&buf, FILTER_ARITY, filter_val);
		TM1637_display_all(filter_val);
		cbuf_read(&buf);
		delay_ms(25);
	}
}
