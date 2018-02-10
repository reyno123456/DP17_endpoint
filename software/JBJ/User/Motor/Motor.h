#ifndef __MOTOR_H
#define __MOTOR_H


#include "stm32f10x.h"
#include "sys.h"

/************通用定时器TIM参数定义，只限TIM2、3、4、5************/
// 当使用不同的定时器的时候，对应的GPIO是不一样的，这点要注意
// 我们这里默认使用TIM3
#define LIFT_MOTOR PDout(1)// PB1


#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM_Period            99
#define            GENERAL_TIM_Prescaler         71

// TIM3 输出比较通道3
#define            GENERAL_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH3_PORT          GPIOB
#define            GENERAL_TIM_CH3_PIN           GPIO_Pin_0

// TIM3 输出比较通道4
#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM_CH4_PORT          GPIOB
#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_1

/**************************函数声明********************************/

void GENERAL_TIM_Init(void);
void Motor_Init(void);
/*****************************************************************************
 函数名    :Lift_Motor_Config
 功能描述  :升降电机控制
 输入参数  :mode		 转动模式：可设置的值为0、1、2分别表示停止、上升、下降
            
            speed        转动速度：可设置的值有0、1、2分别表示高中低速
           
 返回值    :无
------------------------------------------------------------------------------
 日	  期   : 2018年01月10日
 作	  者   : zcg
*****************************************************************************/
void Lift_Motor_Config(uint16_t mode,uint16_t speed);

/*****************************************************************************
 函数名    :Mix_Motor_Config
 功能描述  :搅拌电机控制
 输入参数  :mode		 转动模式：可设置的值为0、1、2分别表示停止、正转、反转
            
            speed        转动速度：暂时可设置的值有0、1、2分别表示高中低速
           
 返回值    :无
------------------------------------------------------------------------------
 日	  期   : 2018年01月10日
 作	  者   : zcg
*****************************************************************************/
void Mix_Motor_Config(uint16_t mode,uint16_t speed);

#endif	/* __MOTOR_H */


