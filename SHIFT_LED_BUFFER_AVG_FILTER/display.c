#include "stm32f10x_gpio.h"
#include "delay.h"

//DO NOT USE US_DELAY MORE THAT 200 (200 microseconds)

unsigned char LED_0F[] = { //array that is used to display one digit
	// 0    1     2      3   4    5     6      7   8    9     A(10)      b(11)   C(12)    d(13)     E(14)  F(15)  - (16) empty(17) dot(18)  L1(19)   l2(20) l3 (21) l4(22)  a1(23), a2 (24)
  0xc0,
  0xF9,
  0xA4,
  0xB0,
  0x99,
  0x92,
  0x82,
  0xF8,
  0x80,
  0x90,
  0x88,
  0x83,
  0xC6,
  0xA1,
  0x86,
  0x8e,
  0xFF,
  0xbf,
  0x7f,
  0xde,
  0xe7,
  0xf3,
  0xfc,
  0xd2,
  0xe4
};
// segments ar described as: hgfedcba

unsigned char LED[4];
int cyklDelay = 150;

int SCLK = GPIO_Pin_4;
int RCLK = GPIO_Pin_3;
int DIO = GPIO_Pin_2;

void SetupDisplay() { // initialization of a driver
  GPIO_InitTypeDef port;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  port.GPIO_Pin = DIO | RCLK | SCLK;
  port.GPIO_Mode = GPIO_Mode_Out_PP;
  port.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, & port);
}

void ClearDisplay() { // clears display and shift registers
  GPIO_ResetBits(GPIOA, SCLK);
  GPIO_ResetBits(GPIOA, DIO);
  delay_us(100);
  for (int i = 0; i < 32; i++) {
    GPIO_SetBits(GPIOA, SCLK);
    delay_us(100);
    GPIO_ResetBits(GPIOA, SCLK);
  }
}

void LedOut(unsigned char X) {
  unsigned char i;
  for (i = 8; i >= 1; i--) {
    if (X & 0x80) {
      GPIO_SetBits(GPIOA, DIO);
    } else {
      GPIO_ResetBits(GPIOA, DIO);
    }
    X <<= 1;
    GPIO_ResetBits(GPIOA, SCLK);
    GPIO_SetBits(GPIOA, SCLK);
  }

}

void DisplayLed(void) {
  unsigned char * led_table;
  unsigned char i;
  //first digit
  led_table = LED_0F + LED[0];
  i = * led_table;
  LedOut(i);
  LedOut(0x01);
  GPIO_ResetBits(GPIOA, RCLK);
  GPIO_SetBits(GPIOA, RCLK);
  //second digit
  led_table = LED_0F + LED[1];
  i = * led_table;
  LedOut(i);
  LedOut(0x02);
  GPIO_ResetBits(GPIOA, RCLK);
  GPIO_SetBits(GPIOA, RCLK);
  //third digit
  led_table = LED_0F + LED[2];
  i = * led_table;
  LedOut(i);
  LedOut(0x04);
  GPIO_ResetBits(GPIOA, RCLK);
  GPIO_SetBits(GPIOA, RCLK);
  //fourth digit
  led_table = LED_0F + LED[3];
  i = * led_table;
  LedOut(i);
  LedOut(0x08);
  GPIO_ResetBits(GPIOA, RCLK);
  GPIO_SetBits(GPIOA, RCLK);
}

char mapDigit(int digit){
	return LED_0F[digit];
}

void WriteDigit(int Digit)//(5 displays 0005, 55 displays 0055, 555 displays 0555)
{
	int SegArray[4];
	if((Digit > 9999)||(Digit < -999)||Digit < 0)return;
		LED[3] = Digit/1000;
		Digit %= 1000;
		LED[2] = Digit/100;
		Digit %= 100;
		LED[1] = Digit / 10;
		LED[0] = Digit % 10;
}
