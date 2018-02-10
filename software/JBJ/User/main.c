
// 搅拌机
#include "stm32f10x.h"
#include "led.h"
#include "motor.h"  
#include "key.h"
#include "sys.h"
#include <stdbool.h>
extern uint16_t Turn_Big;
extern uint16_t Turn_Small;
extern uint16_t Turn;
extern bool Turn_Big_Flag;
extern bool Turn_Small_Flag;
extern bool Swich_Flag;
extern bool Swich_Stop_Flag;
uint16_t Lift_Motor_Swich = 1; 
uint16_t Swich_Old_State = 0;
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{
	delay_init();	    	 //延时函数初始化		
	GENERAL_TIM_Init();  //定时器初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Extix_Init();		 	//外部中断初始化
	LIFT_MOTOR = 0;
//	TIM3_Mode_Config(10,72);
//	TIM3_Mode_Config(10,71,50);
//	GPIO_SetBits(GPIOB, GPIO_Pin_1);
//	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
//	GPIO_SetBits(GPIOE, GPIO_Pin_14);
    while(1)
   { 
        // if(Turn_Big_Flag||Turn_Small_Flag)
	    // {	
            // if(Turn<=98)
	    	// {
	    		// TIM3_Mode_Config(10,72);
	    	// }
	    	// if(Turn=99)
	    	// {
	    		// TIM3_Mode_Config(50,72);
	    	// }
	    	// if(Turn=100)
	    	// {
	    		// TIM3_Mode_Config(100,72);
	    	// }
            // if(Turn>=101)
	    	// {
	    		// TIM3_Mode_Config(200,72);
	    	// }
			// Turn_Big_Flag = FALSE;
			// Turn_Small_Flag = FALSE;
	    // }
		
	    
		
		
        if(Turn_Big_Flag||Turn_Small_Flag||Swich_Flag||Swich_Stop_Flag)
	    {	
            if(Swich_Flag)
		    {
		    	if(Lift_Motor_Swich==1)
		    	{
		    		Lift_Motor_Swich = 2;
					Swich_Old_State = 2;
		    	}
		    	else if(Lift_Motor_Swich==2)
		    	{
		    		Lift_Motor_Swich = 1;
					Swich_Old_State = 1;
		    	}	
		    }
		    if((Swich_Stop_Flag)&&(Lift_Motor_Swich!=0))
			{
				Lift_Motor_Swich=0;
			}
			else if((Swich_Stop_Flag)&&(Lift_Motor_Swich==0))
			{
				// if(Swich_Old_State==1)
				// {
					// Lift_Motor_Swich = 1;
				// }
                // else if(Swich_Old_State==2)
				// {
					Lift_Motor_Swich = 2;
				// }					
			}	
            if((Turn<=95)&&(Turn>=93))
	    	{
	    		Lift_Motor_Config(Lift_Motor_Swich,10);
				Mix_Motor_Config(Lift_Motor_Swich,10);
	    	}
	    	if((Turn>=96)&&(Turn<=98))
	    	{
	    		Lift_Motor_Config(Lift_Motor_Swich,50);
				Mix_Motor_Config(Lift_Motor_Swich,50);
	    	}
	    	if((Turn>=99)&&(Turn<=101))
	    	{
	    		Lift_Motor_Config(Lift_Motor_Swich,100);
				Mix_Motor_Config(Lift_Motor_Swich,100);
	    	}
            if((Turn>=102)&&(Turn<=104))
	    	{
	    		Lift_Motor_Config(Lift_Motor_Swich,200);
				Mix_Motor_Config(Lift_Motor_Swich,200);
	    	}
			Turn_Big_Flag = FALSE;
			Turn_Small_Flag = FALSE;
			Swich_Flag = FALSE;
			Swich_Stop_Flag = FALSE;
	    }	
   }
}
/*********************************************END OF FILE**********************/
