#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

//#define SWO PEin(4)   	//PE4
//#define SWA PEin(3)	//PE3 
//#define SWB PEin(2)	//PE2
//#define WK_UP PAin(0)	//PA0  WK_UP


#define SWO  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����0
#define SWA  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����1
#define SWB  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//��ȡ����2 
#define STOP   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)//��ȡ����3(stop) 
 

#define KEY0_PRES 	1	//SWO����
#define KEY1_PRES	  2	//SWA����
#define KEY2_PRES 	3	//SWB����
#define WKUP_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)

// void EXTIX_Init(void);//�ⲿ�жϳ�ʼ��
// void KEY_Init(void);//IO��ʼ��
void Extix_Init(void);//�ⲿ�жϳ�ʼ��
void Key_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
