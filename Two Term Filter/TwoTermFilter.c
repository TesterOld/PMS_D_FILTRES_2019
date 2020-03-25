#include "TwoTermFilter.h"

unsigned int filter(int[] buffer, int index)
{
	int result = 0;
	for (int i = index; i >= index - 2; i--){
		if (i < 0) buffer[i] = 0;
		result += buffer[i];
	}
	return result / 3;
}