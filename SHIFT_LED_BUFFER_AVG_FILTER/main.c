#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "delay.h"
#include "display.h"
#include "buffer.h"

int main() {
  SetupDisplay();
	ClearDisplay();
	test_buff_load(8);
	int i = 0;
  while (1) {
		
		if(i < 1){
			unsigned int filteredValue = bufferReadFilterAvgOrderN(4);
			WriteDigit(filteredValue);
		}
		if(i > 10000){
			i=0;
		}
    i++;
		DisplayLed();
    delay_us(1);
  }
};