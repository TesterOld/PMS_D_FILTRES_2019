#include "stm32f10x_gpio.h"
#include "delay.h"

void WriteDigit(int Digit);
char mapDigit(int digit);
void DisplayLed(void);
void LedOut(unsigned char X);
void ClearDisplay();
void SetupDisplay();