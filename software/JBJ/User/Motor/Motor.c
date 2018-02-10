
#include "motor.h" 

void Lift_Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
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
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
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
 ������    :Lift_Motor_Config
 ��������  :�����������
 �������  :mode		 ת��ģʽ�������õ�ֵΪ0��1��2�ֱ��ʾֹͣ���������½�
            
            speed        ת���ٶȣ������õ�ֵ��0��1��2�ֱ��ʾ���е���
           
 ����ֵ    :��
------------------------------------------------------------------------------
 ��	  ��   : 2018��01��10��
 ��	  ��   :zcg
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
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//�����ʼ���ṹ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ�ܶ�ʱ��4ʱ��
    //��ʼ��TIM4
	if(speed==10)
	{
		TIM_TimeBaseStructure.TIM_Period = /*GENERAL_TIM_Period*/(speed*10-1); //�Զ���װ�ؼĴ�����ֵ
	}	
    else if(speed==50)
	{
		TIM_TimeBaseStructure.TIM_Period = 19; //�Զ���װ�ؼĴ�����ֵ
	}
    else if(speed==100)
	{
		TIM_TimeBaseStructure.TIM_Period = /*GENERAL_TIM_Period*/(speed/10-1); //�Զ���װ�ؼĴ�����ֵ
	}
    else if(speed==200)
	{
		TIM_TimeBaseStructure.TIM_Period = 4; //�Զ���װ�ؼĴ�����ֵ
	}
    else if(speed==500)
	{
		TIM_TimeBaseStructure.TIM_Period = 1; //�Զ���װ�ؼĴ�����ֵ
	}    	
    TIM_TimeBaseStructure.TIM_Prescaler = 71; //TIMXԤ��Ƶ��ֵ;
	// TIM3_PWM_Init(9999,143);//Ƶ��Ϊ��72*10^6/(9999+1)/(143+1)=50Hz
// ����TIM_SetCompare2(TIM3,4999);//�õ�ռ�ձ�Ϊ50%��pwm����
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ʱ�ӷָ�;ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //����������ģʽ�����ϼ���
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //�������Ϲ��ܶԶ�ʱ�����г�ʼ��
/******************************************************************************/	
	
	// ռ�ձ�����
	// uint16_t CCR3_Val = 50;	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 1
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
	
	// ʹ�ܼ�����
	TIM_Cmd(TIM4, ENABLE);
}
/*****************************************************************************
 ������    :Mix_Motor_Config
 ��������  :����������
 �������  :mode		 ת��ģʽ�������õ�ֵΪ0��1��2�ֱ��ʾֹͣ����ת����ת
            
            speed        ת���ٶȣ���ʱ�����õ�ֵ��0��1��2�ֱ��ʾ���е���
           
 ����ֵ    :��
------------------------------------------------------------------------------
 ��	  ��   : 2018��01��10��
 ��	  ��   :zcg
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
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//�����ʼ���ṹ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ�ܶ�ʱ��4ʱ��
    //��ʼ��TIM4
	if(speed==10)
	{
		TIM_TimeBaseStructure.TIM_Period = /*GENERAL_TIM_Period*/(speed*10-1); //�Զ���װ�ؼĴ�����ֵ
	}	
    else if(speed==50)
	{
		TIM_TimeBaseStructure.TIM_Period = 19; //�Զ���װ�ؼĴ�����ֵ
	}
    else if(speed==100)
	{
		TIM_TimeBaseStructure.TIM_Period = /*GENERAL_TIM_Period*/(speed/10-1); //�Զ���װ�ؼĴ�����ֵ
	}
    else if(speed==200)
	{
		TIM_TimeBaseStructure.TIM_Period = 4; //�Զ���װ�ؼĴ�����ֵ
	}
    else if(speed==500)
	{
		TIM_TimeBaseStructure.TIM_Period = 1; //�Զ���װ�ؼĴ�����ֵ
	}    	
    TIM_TimeBaseStructure.TIM_Prescaler = 71; //TIMXԤ��Ƶ��ֵ;
	// TIM3_PWM_Init(9999,143);//Ƶ��Ϊ��72*10^6/(9999+1)/(143+1)=50Hz
// ����TIM_SetCompare2(TIM3,4999);//�õ�ռ�ձ�Ϊ50%��pwm����
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ʱ�ӷָ�;ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //����������ģʽ�����ϼ���
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //�������Ϲ��ܶԶ�ʱ�����г�ʼ��
/******************************************************************************/	
	
	// ռ�ձ�����
	// uint16_t CCR3_Val = 50;	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 3
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
	
	// ʹ�ܼ�����
	TIM_Cmd(TIM4, ENABLE);
}

void GENERAL_TIM_Init(void)
{
	Motor_Init();
	Lift_Motor_Config(1,10);
	Mix_Motor_Config(1,10);
}

/*********************************************END OF FILE**********************/
