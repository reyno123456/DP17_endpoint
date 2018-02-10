
#include "motor.h" 

void Lift_Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
//    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void Mix_Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
//    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void Motor_Init(void)
{
	Lift_Motor_Init();
	Mix_Motor_Init();
}
/*****************************************************************************
 函数名    :Lift_Motor_Config
 功能描述  :升降电机控制
 输入参数  :mode		 转动模式：可设置的值为0、1、2分别表示停止、上升、下降
            
            speed        转动速度：可设置的值有0、1、2分别表示高中低速
           
 返回值    :无
------------------------------------------------------------------------------
 日	  期   : 2018年01月10日
 作	  者   :zcg
*****************************************************************************/
void Lift_Motor_Config(uint16_t mode,uint16_t speed)
{
	if(mode==1)
	{
		LIFT_MOTOR = 0;
		GPIO_SetBits(GPIOB, GPIO_Pin_7);
	}
	else if(mode==2)
	{
		LIFT_MOTOR = 1;
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	}	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//定义初始化结构体
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //使能定时器4时钟
    //初始化TIM4
	if(speed==10)
	{
		TIM_TimeBaseStructure.TIM_Period = /*GENERAL_TIM_Period*/(speed*10-1); //自动重装载寄存器的值
	}	
    else if(speed==50)
	{
		TIM_TimeBaseStructure.TIM_Period = 19; //自动重装载寄存器的值
	}
    else if(speed==100)
	{
		TIM_TimeBaseStructure.TIM_Period = /*GENERAL_TIM_Period*/(speed/10-1); //自动重装载寄存器的值
	}
    else if(speed==200)
	{
		TIM_TimeBaseStructure.TIM_Period = 4; //自动重装载寄存器的值
	}
    else if(speed==500)
	{
		TIM_TimeBaseStructure.TIM_Period = 1; //自动重装载寄存器的值
	}    	
    TIM_TimeBaseStructure.TIM_Prescaler = 71; //TIMX预分频的值;
	// TIM3_PWM_Init(9999,143);//频率为：72*10^6/(9999+1)/(143+1)=50Hz
// 　　TIM_SetCompare2(TIM3,4999);//得到占空比为50%的pwm波形
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //时钟分割;时钟分频因子 ，配置死区时间时需要用到
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数器计数模式，向上计数
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据以上功能对定时器进行初始化
/******************************************************************************/	
	
	// 占空比配置
	// uint16_t CCR3_Val = 50;	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 1
	if(mode==0)
	{
		TIM_OCInitStructure.TIM_Pulse = 0;
	}
    else
	{	
	    if(speed==10)
	    {
	    	TIM_OCInitStructure.TIM_Pulse = 50;
	    }
        else if(speed==50)
	    {
	    	TIM_OCInitStructure.TIM_Pulse = 10;
	    }
	    else if(speed==100)
	    {
	    	TIM_OCInitStructure.TIM_Pulse = 5;
	    }
	    else if(speed==200)
	    {
	    	TIM_OCInitStructure.TIM_Pulse = 3;
	    }
	    else if(speed==500)
	    {
	    	TIM_OCInitStructure.TIM_Pulse = 1;
	    }
	}	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	// 使能计数器
	TIM_Cmd(TIM4, ENABLE);
}
/*****************************************************************************
 函数名    :Mix_Motor_Config
 功能描述  :搅拌电机控制
 输入参数  :mode		 转动模式：可设置的值为0、1、2分别表示停止、正转、反转
            
            speed        转动速度：暂时可设置的值有0、1、2分别表示高中低速
           
 返回值    :无
------------------------------------------------------------------------------
 日	  期   : 2018年01月10日
 作	  者   :zcg
*****************************************************************************/
void Mix_Motor_Config(uint16_t mode,uint16_t speed)
{
	if(mode==1)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_9);
	}
	else if(mode==2)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	}	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//定义初始化结构体
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //使能定时器4时钟
    //初始化TIM4
	if(speed==10)
	{
		TIM_TimeBaseStructure.TIM_Period = /*GENERAL_TIM_Period*/(speed*10-1); //自动重装载寄存器的值
	}	
    else if(speed==50)
	{
		TIM_TimeBaseStructure.TIM_Period = 19; //自动重装载寄存器的值
	}
    else if(speed==100)
	{
		TIM_TimeBaseStructure.TIM_Period = /*GENERAL_TIM_Period*/(speed/10-1); //自动重装载寄存器的值
	}
    else if(speed==200)
	{
		TIM_TimeBaseStructure.TIM_Period = 4; //自动重装载寄存器的值
	}
    else if(speed==500)
	{
		TIM_TimeBaseStructure.TIM_Period = 1; //自动重装载寄存器的值
	}    	
    TIM_TimeBaseStructure.TIM_Prescaler = 71; //TIMX预分频的值;
	// TIM3_PWM_Init(9999,143);//频率为：72*10^6/(9999+1)/(143+1)=50Hz
// 　　TIM_SetCompare2(TIM3,4999);//得到占空比为50%的pwm波形
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //时钟分割;时钟分频因子 ，配置死区时间时需要用到
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数器计数模式，向上计数
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据以上功能对定时器进行初始化
/******************************************************************************/	
	
	// 占空比配置
	// uint16_t CCR3_Val = 50;	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 3
	if(mode==0)
	{
		TIM_OCInitStructure.TIM_Pulse = 0;
	}
    else
	{	
	    if(speed==10)
	    {
	    	TIM_OCInitStructure.TIM_Pulse = 50;
	    }
        else if(speed==50)
	    {
	    	TIM_OCInitStructure.TIM_Pulse = 10;
	    }
	    else if(speed==100)
	    {
	    	TIM_OCInitStructure.TIM_Pulse = 5;
	    }
	    else if(speed==200)
	    {
	    	TIM_OCInitStructure.TIM_Pulse = 3;
	    }
	    else if(speed==500)
	    {
	    	TIM_OCInitStructure.TIM_Pulse = 1;
	    }
	}	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	// 使能计数器
	TIM_Cmd(TIM4, ENABLE);
}

void GENERAL_TIM_Init(void)
{
	Motor_Init();
	Lift_Motor_Config(1,10);
	Mix_Motor_Config(1,10);
}

/*********************************************END OF FILE**********************/
