#include "bsp_led.h"   

static void led_config ( void )
{		 
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* 配置 LED1 引脚 */
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA, ENABLE );																
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( GPIOA, & GPIO_InitStructure );  

	/* 配置 LED2 引脚 */
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA, ENABLE );																
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( GPIOA, & GPIO_InitStructure ); 			 
}

 /**
  * @brief  LED 初始化函数
  * @param  无
  * @retval 无
  */
void led_init(void)
{
  led_config();
}
