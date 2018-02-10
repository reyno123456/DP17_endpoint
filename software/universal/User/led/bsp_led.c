#include "bsp_led.h"   

static void led_config ( void )
{		 
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* ���� LED1 ���� */
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA, ENABLE );																
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( GPIOA, & GPIO_InitStructure );  

	/* ���� LED2 ���� */
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA, ENABLE );																
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( GPIOA, & GPIO_InitStructure ); 			 
}

 /**
  * @brief  LED ��ʼ������
  * @param  ��
  * @retval ��
  */
void led_init(void)
{
  led_config();
}
