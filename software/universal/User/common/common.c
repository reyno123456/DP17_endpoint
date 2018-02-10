#include "common.h"

unsigned int g_tick_count = 0;

void delay_us(unsigned int us)
{
	unsigned int i;
	unsigned int j;
	for (j = 0; j < us; j++)
	{
		for (i = 0; i < 90 ; i++)
		{
		
		}
	}
}

s_flags g_flags;
s_global g_global;
