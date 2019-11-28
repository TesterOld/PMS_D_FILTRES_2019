#include "delay.h"

void delay_us( unsigned long Val) 
{
	Val=Val*10;
  for( ; Val != 0; Val--) 
  {
	  __nop();
  }
}
