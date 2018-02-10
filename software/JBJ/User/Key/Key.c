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
//������ʼ������
void Key_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//SWO-SWB
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE1,2,3,4
}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��SWO����
//2��SWA����
//3��SWB���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,SWO>SWA>SWB>KEY3!!
// u8 KEY_Scan(u8 mode)
// {	 
	// static u8 key_up=1;//�������ɿ���־
	// if(mode)key_up=1;  //֧������		  
	// if(key_up&&(SWO==0||SWA==0||SWB==0||WK_UP==1))
	// {
		// delay_ms(10);//ȥ���� 
		// key_up=0;
		// if(SWO==0)return KEY0_PRES;
		// else if(SWA==0)return KEY1_PRES;
		// else if(SWB==0)return KEY2_PRES;
		// else if(WK_UP==1)return WKUP_PRES;
	// }else if(SWO==1&&SWA==1&&SWB==1&&WK_UP==0)key_up=1; 	    
 	// return 0;// �ް�������
// }

//�ⲿ�ж�0�������
void Extix_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    Key_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

    //GPIOE.2 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//SWB
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	//GPIOE.1	  �ж����Լ��жϳ�ʼ������ �½��ش��� //S3
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //SWA
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOE.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	//SWO
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���



  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}

//�ⲿ�ж�1������� 
void EXTI1_IRQHandler(void)
{
	delay_ms(10);//����
	if(STOP==0)	 	 //WK_UP����
	{				 
		Swich_Stop_Flag = TRUE;
	}
	EXTI_ClearITPendingBit(EXTI_Line1); //���LINE1�ϵ��жϱ�־λ  
}
 
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
//	delay_ms(10);//����
	if(SWB==0)	  //����SWB
	{
		// delay_ms(10);//����
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
	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE2�ϵ��жϱ�־λ  
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
//	delay_ms(10);//����
	if(SWA==0)	 //����SWA
	{	
	    // delay_ms(10);//����
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
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);//����
	if(SWO==0)	 //����SWO
	{
        Swich_Flag =TRUE;		//GPIO_SetBits(GPIOB, GPIO_Pin_1);
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
}
