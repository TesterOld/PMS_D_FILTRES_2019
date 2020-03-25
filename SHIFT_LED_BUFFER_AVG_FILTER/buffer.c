#include "buffer.h"
#include "delay.h"
unsigned char rIN=0;// for buffer add
unsigned char rOUT=0;// for  buffer read
unsigned int rBuffer [BUF_SIZE_8];// buf size BUF_SIZE sign 

void buffer_add(unsigned int val)
{
	rBuffer[rIN++] = val;
	// Sense in mask value. Value is 0111111 (VALUE!!)
	// If next rang (razriad) then to 0
    rIN &= BUF_MASK_8;// Set to 0. Ring Buffer 
}


unsigned int buffer_read(void)
{
	unsigned int val;
  val=rBuffer[rOUT++];
  // Sense in mask value. Value is 0111111 (VALUE!!)
  // If next rang (razriad) then to 0
    rOUT &= BUF_MASK_8;// Set to 0. Ring Buffer 
  return val;
}

unsigned int bufferReadFilterAvgOrderN(unsigned int filterOrder) {
	unsigned int val;
	for(int i=0; i<filterOrder; i++){
		val +=rBuffer[rOUT++];
		rOUT &= BUF_MASK_8;
	}	
	val = val/filterOrder;
	return val;
}

unsigned int buffer_avg(void)
{
	long long summ=0;
	for(int i=0;i<BUF_SIZE_8;i++)summ+=rBuffer[i];
	summ=summ/BUF_SIZE_8;
	return summ;
}


///////test buff
void test_buff_load(unsigned int load)
{
	for (int i=0; i<load; i++)
		{
		buffer_add(i);
		}
	}

