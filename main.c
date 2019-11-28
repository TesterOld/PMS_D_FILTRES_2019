#include "buffer.h"
#include "delay.h"
#include "buffer.h"
#include "ADC.h"
#include "tm1637.h"
// Display Tm 1637 shuld be:GNG-GND, VCC-5v, DIO - B6, CLC - B7

//#define BUF_SIZE_128 128
//#define BUF_SIZE_64  64
//#define BUF_SIZE_16  16
//#define BUF_SIZE_8   8
//#define BUF_SIZE_4   4
//// Two GPIO for SPI emul //GPIO_Pin_6|GPIO_Pin_7;//GPIOB
//#define SYSTICK_MAX_VALUE 16777215

//A1 - ADC
void init_encoder(void);
uint16_t getEncoderValue(void);
void init_leds(void);

unsigned int digit_display0 = 0;
unsigned int digit_display2 = 2222;
unsigned int digit_ads = 0007;


int main()
{
 	//ADC_init();
	init_encoder();
  //delay_ms(10);
	init_leds();
	//GPIOC_init_13_o ();
	TM1637_init();	
  TM1637_brightness(BRIGHT_TYPICAL); 
	delay_ms(10);
	TM1637_display_all(getEncoderValue() * 10000);
	delay_ms(1000);
	
	//test_buff_load(5);
 
	
	while (1)
	{
		//buffer_add(ADC_read());
		//delay_ms(10);
		
		//TM1637_display_all(getEncoderValue() * 10000);
    TM1637_display_all(getEncoderValue());
		//delay_ms(1000);
		//delay_ms(10);
		//TM1637_display_all(ADC_read());
		//
		delay_ms(100);
		//delay_ms(getEncoderValue() * 10000);
		//delay_ms(100);
		
	}
}


void init_encoder(void) {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef encoder;
  encoder.GPIO_Mode = GPIO_Mode_IPU;
  encoder.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOA, &encoder);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseInitTypeDef timer;
  TIM_TimeBaseStructInit(&timer);
  timer.TIM_Prescaler = 0;
  timer.TIM_Period = 256;
  timer.TIM_CounterMode = TIM_CounterMode_Down | TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &timer);

  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI1,
  TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

  TIM_Cmd(TIM2, ENABLE);
}

uint16_t getEncoderValue(void) {
  return TIM_GetCounter(TIM2);
}

void init_leds() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef LED;
	LED.GPIO_Pin = GPIO_Pin_0;
	LED.GPIO_Speed = GPIO_Speed_2MHz;
	LED.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOB, &LED);
}