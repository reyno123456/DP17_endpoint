#ifndef _COMMON_H
#define _COMMON_H

typedef struct
{
	unsigned bldc_motor_status : 1;
}s_flags;

typedef struct
{
	unsigned char bldc_motor_duty;
}s_global;


extern unsigned int g_tick_count;

extern void delay_us(unsigned int us);
extern s_flags g_flags;
extern s_global g_global;


#endif
