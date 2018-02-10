#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

//#define SWO PEin(4)   	//PE4
//#define SWA PEin(3)	//PE3 
//#define SWB PEin(2)	//PE2
//#define WK_UP PAin(0)	//PA0  WK_UP


#define SWO  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
#define SWA  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1
#define SWB  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键2 
#define STOP   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)//读取按键3(stop) 
 

#define KEY0_PRES 	1	//SWO按下
#define KEY1_PRES	  2	//SWA按下
#define KEY2_PRES 	3	//SWB按下
#define WKUP_PRES   4	//KEY_UP按下(即WK_UP/KEY_UP)

// void EXTIX_Init(void);//外部中断初始化
// void KEY_Init(void);//IO初始化
void Extix_Init(void);//外部中断初始化
void Key_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
