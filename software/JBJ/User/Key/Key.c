#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "motor.h" 
#include <stdbool.h>
uint16_t Turn_Big = 10;
uint16_t Turn_Small = 10;
uint16_t Turn = 98;
bool Turn_Big_Flag = FALSE;
bool Turn_Small_Flag = FALSE;
bool Swich_Flag = FALSE;
bool Swich_Stop_Flag = FALSE;
//按键初始化函数
void Key_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//SWO-SWB
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE1,2,3,4
}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，SWO按下
//2，SWA按下
//3，SWB按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,SWO>SWA>SWB>KEY3!!
// u8 KEY_Scan(u8 mode)
// {	 
	// static u8 key_up=1;//按键按松开标志
	// if(mode)key_up=1;  //支持连按		  
	// if(key_up&&(SWO==0||SWA==0||SWB==0||WK_UP==1))
	// {
		// delay_ms(10);//去抖动 
		// key_up=0;
		// if(SWO==0)return KEY0_PRES;
		// else if(SWA==0)return KEY1_PRES;
		// else if(SWB==0)return KEY2_PRES;
		// else if(WK_UP==1)return WKUP_PRES;
	// }else if(SWO==1&&SWA==1&&SWB==1&&WK_UP==0)key_up=1; 	    
 	// return 0;// 无按键按下
// }

//外部中断0服务程序
void Extix_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    Key_Init();	 //	按键端口初始化

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

    //GPIOE.2 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//SWB
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	//GPIOE.1	  中断线以及中断初始化配置 下降沿触发 //S3
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOE.3	  中断线以及中断初始化配置 下降沿触发 //SWA
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOE.4	  中断线以及中断初始化配置  下降沿触发	//SWO
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器



  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}

//外部中断1服务程序 
void EXTI1_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(STOP==0)	 	 //WK_UP按键
	{				 
		Swich_Stop_Flag = TRUE;
	}
	EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE1上的中断标志位  
}
 
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
//	delay_ms(10);//消抖
	if(SWB==0)	  //按键SWB
	{
		// delay_ms(10);//消抖
		if(SWA==1)
		{
		   // Turn_Big++;
		   Turn_Big_Flag = TRUE;
            // if(Turn_Big > 60000)
            // {
			    // Turn_Big = 10;
			// }
            Turn++;
			if(Turn>104)
			{
				Turn = 104;
			}
		}	
	} 
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
//	delay_ms(10);//消抖
	if(SWA==0)	 //按键SWA
	{	
	    // delay_ms(10);//消抖
		if(SWB==1)
		{
			// Turn_Small++;
			Turn_Small_Flag = TRUE;
			// if(Turn_Small > 60000)
            // {
			    // Turn_Small = 10;
			// }
		    Turn--;
			if(Turn<93)
			{
				Turn = 93;
			}	
		}
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(SWO==0)	 //按键SWO
	{
        Swich_Flag =TRUE;		//GPIO_SetBits(GPIOB, GPIO_Pin_1);
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位  
}
