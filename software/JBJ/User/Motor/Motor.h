#ifndef __MOTOR_H
#define __MOTOR_H


#include "stm32f10x.h"
#include "sys.h"

/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������Ĭ��ʹ��TIM3
#define LIFT_MOTOR PDout(1)// PB1


#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM_Period            99
#define            GENERAL_TIM_Prescaler         71

// TIM3 ����Ƚ�ͨ��3
#define            GENERAL_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH3_PORT          GPIOB
#define            GENERAL_TIM_CH3_PIN           GPIO_Pin_0

// TIM3 ����Ƚ�ͨ��4
#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH4_PORT          GPIOB
#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_1

/**************************��������********************************/

void GENERAL_TIM_Init(void);
void Motor_Init(void);
/*****************************************************************************
 ������    :Lift_Motor_Config
 ��������  :�����������
 �������  :mode		 ת��ģʽ�������õ�ֵΪ0��1��2�ֱ��ʾֹͣ���������½�
            
            speed        ת���ٶȣ������õ�ֵ��0��1��2�ֱ��ʾ���е���
           
 ����ֵ    :��
------------------------------------------------------------------------------
 ��	  ��   : 2018��01��10��
 ��	  ��   : zcg
*****************************************************************************/
void Lift_Motor_Config(uint16_t mode,uint16_t speed);

/*****************************************************************************
 ������    :Mix_Motor_Config
 ��������  :����������
 �������  :mode		 ת��ģʽ�������õ�ֵΪ0��1��2�ֱ��ʾֹͣ����ת����ת
            
            speed        ת���ٶȣ���ʱ�����õ�ֵ��0��1��2�ֱ��ʾ���е���
           
 ����ֵ    :��
------------------------------------------------------------------------------
 ��	  ��   : 2018��01��10��
 ��	  ��   : zcg
*****************************************************************************/
void Mix_Motor_Config(uint16_t mode,uint16_t speed);

#endif	/* __MOTOR_H */


