#include "motor.h"
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "../common/common.h"

static void step_motor_gpio_config ( void )
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* ���� dir ���� */
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOB, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( GPIOB, & GPIO_InitStructure );	

	/* ���� pwm ���� */
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOB, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( GPIOB, & GPIO_InitStructure );
	
	/* ����   speed ���� */
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOE, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( GPIOE, & GPIO_InitStructure );

	/* ����   up ���� */
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOE, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( GPIOE, & GPIO_InitStructure );

	/* ����   down ���� */
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOE, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( GPIOE, & GPIO_InitStructure );

}

void step_motor_init(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//�����ʼ���ṹ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ�ܶ�ʱ��4ʱ��

	TIM_TimeBaseStructure.TIM_Period = 6;
	
    TIM_TimeBaseStructure.TIM_Prescaler = 71; //TIMXԤ��Ƶ��ֵ;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ʱ�ӷָ�;ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //����������ģʽ�����ϼ���
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //�������Ϲ��ܶԶ�ʱ�����г�ʼ��
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OCInitStructure.TIM_Pulse = 5;

	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	step_motor_gpio_config();
	// TIM_Cmd(TIM4, ENABLE);
}

void step_motor_one_step(unsigned short int us)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//�����ʼ���ṹ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ�ܶ�ʱ��4ʱ��

	TIM_TimeBaseStructure.TIM_Period = us;
    TIM_TimeBaseStructure.TIM_Prescaler = 71; //TIMXԤ��Ƶ��ֵ;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ʱ�ӷָ�;ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //����������ģʽ�����ϼ���
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //�������Ϲ��ܶԶ�ʱ�����г�ʼ��

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = us>>2;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4, ENABLE);
}

void step_motor_start(unsigned short int us, unsigned char direction)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//�����ʼ���ṹ��
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	unsigned int phase_delay_us = us;

	if (direction == 0)
	{
		step_motor_dir_clockwise();
	}
	else
	{
		step_motor_dir_anticlocksize();
	}
	
	for (phase_delay_us = 100;  phase_delay_us > us; phase_delay_us--)
	{
		step_motor_one_step(phase_delay_us);
		vTaskDelay(20);
	}
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ�ܶ�ʱ��4ʱ��

	TIM_TimeBaseStructure.TIM_Period = us;
    TIM_TimeBaseStructure.TIM_Prescaler = 71; //TIMXԤ��Ƶ��ֵ;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ʱ�ӷָ�;ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //����������ģʽ�����ϼ���
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //�������Ϲ��ܶԶ�ʱ�����г�ʼ��

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = us>>1;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM4, ENABLE);
}

void step_motor_stop(unsigned short int us)
{
	unsigned int phase_delay_us;
	for (phase_delay_us = us;  phase_delay_us < 50; phase_delay_us++)
	{
		step_motor_one_step(phase_delay_us);
		vTaskDelay(1);
	}
	TIM_Cmd(TIM4, DISABLE);
}

void bldc_motor_init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOB, ENABLE );																
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( GPIOB, & GPIO_InitStructure );  

	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOB, ENABLE );																
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( GPIOB, & GPIO_InitStructure ); 	  		

}

void bldc_motor_one_step(unsigned       char duty)
{
	GPIO_SetBits ( GPIOB, GPIO_Pin_6 );
	vTaskDelay(duty);	
	GPIO_ResetBits ( GPIOB, GPIO_Pin_6 );
	vTaskDelay(100 - duty);
}

void bldc_motor_start(unsigned       char duty)
{
	unsigned char current_duty;

	if (duty > 100)
	{
		duty = 100;
	}
	
	for (current_duty = 0; current_duty < duty; current_duty++)
	{
		GPIO_SetBits ( GPIOB, GPIO_Pin_6 );
		vTaskDelay(duty);	
		GPIO_ResetBits ( GPIOB, GPIO_Pin_6 );
		vTaskDelay(100 - duty);		
	}
}

void bldc_motor_stop(void)
{
	GPIO_ResetBits ( GPIOB, GPIO_Pin_6 );
}
