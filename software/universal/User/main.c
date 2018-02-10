#include "stm32f10x.h"
#include "bsp_led.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "motor/motor.h"
#include "../common/common.h"
#include "../uart/hal_uart.h"
#include "stdio.h"
#include "../can/can.h"

void task_led( void * pvParameters )
{
	led_init();
	while(1)
	{
		LED_GREEN_ON();
		LED_RED_ON();
		vTaskDelay( 1000 );
		LED_GREEN_OFF();
		LED_RED_OFF();
		vTaskDelay( 1000 );
	}
}


void task_deamon_bldc( void * pvParameters )
{
	bldc_motor_init();
	while(1)
	{
		if (g_flags.bldc_motor_status == 1 &&
			g_global.bldc_motor_duty != 0)
		{
			bldc_motor_start(g_global.bldc_motor_duty);
		}
		else
		{
			bldc_motor_stop();
		}
		
		taskYIELD();
	}	
}


void task_bldc_motor_speed_test( void * pvParameters )
{
	unsigned char flag = 0;
	unsigned int circle = 0;
	unsigned int tick_start;
	unsigned int tick_end;
	unsigned int period;
	unsigned int i = 0;
	unsigned int speed;

	while(1)
	{
		circle = 0;
		tick_start = g_tick_count;
		for (i = 0; i < 1000; i++)
		{
			if (flag == 0)
			{
				if (HALL_TRIGGERED == READ_HALL_WHIRL)
				{
					flag = 1;
					circle++;
					//printf("bldc run circle %d\r\n", circle);
				}
			}
			else
			{
				if (HALL_TRIGGERED != READ_HALL_WHIRL)
				{
					flag = 0;
				}
			}
			vTaskDelay( 1 );
		}
		period = g_tick_count - tick_start;
		//printf("period = %d\r\n", period);
		speed = 60 * circle * 1000 / period;
		printf("speed = %ld RMS\r\n", speed);		
	}
}

void task_bldc_motor_control( void * pvParameters )
{
	while(1)
	{
		g_global.bldc_motor_duty = 99;
		g_flags.bldc_motor_status = 1;
		vTaskDelay( 5000 );
		g_global.bldc_motor_duty = 0;
		g_flags.bldc_motor_status = 0;	
		vTaskDelay( 10000 );
	}
}
/*
void task_step_motor( void * pvParameters )
{	
	step_motor_init();

	while(1)
	{
		step_motor_start(3, STEP_MOTOR_DOWN);
		vTaskDelay(5000);
		step_motor_stop(10);
		vTaskDelay(5000);
		
		step_motor_start(3, STEP_MOTOR_UP);
		vTaskDelay(5000);
		step_motor_stop(10);
		vTaskDelay(5000);
	}
	
}
*/
void task_step_motor( void * pvParameters )
{	
	unsigned int hall_read;
	static unsigned char step_motor_status = 0;
	
	step_motor_init();
	step_motor_start(30, STEP_MOTOR_UP);

	while(1)
	{
		if (step_motor_status == 0)
		{
			if (HALL_TRIGGERED == READ_HALL_UP)
			{
				step_motor_status = 1;
				step_motor_stop(10);
				vTaskDelay(5000);
				step_motor_start(30, STEP_MOTOR_DOWN);
			}
		}
		else
		{
			if (HALL_TRIGGERED == READ_HALL_DOWN)
			{
				step_motor_status = 0;
				step_motor_stop(10);
				vTaskDelay(5000);
				step_motor_start(30, STEP_MOTOR_UP);
			}
		}
		
		vTaskDelay(100);
	}
	
}

void task_serial_debug_test( void * pvParameters )
{	
	unsigned int i;
	USART_Config();
	
	while(1)
	{
		//Usart_SendString( DEBUG_USARTx,"test\r\n");
		//USART_SendData(DEBUG_USARTx, 0x41);
		//USART_SendData(DEBUG_USARTx,'A');
		//printf("%s %s test %d\r\n", __DATE__, __TIME__, i++);
		vTaskDelay(1000);
	}
	
}

void task_hall_sensor_test( void * pvParameters )
{	
	while(1)
	{
		if (HALL_TRIGGERED == READ_HALL_UP)
		{
			printf("up state 00000000\r\n");
		}


		if (HALL_TRIGGERED == READ_HALL_DOWN)
		{
			printf("down state 0000000000000000000000\r\n");
		}


		if (HALL_TRIGGERED == READ_HALL_WHIRL)
		{
			printf("whirl state 000000000000000000000000000000000000\r\n");
		}

		vTaskDelay(10000);
	}
	
}

void task_can_send_test( void * pvParameters )
{	
	unsigned char can_send_buf[8] = {0,1,2,3,4,5,6,7};
	unsigned int extended_id = 0;
	printf("%s %d\r\n", __func__, __LINE__);
	printf("%s %s\r\n", __DATE__, __TIME__); 

	while(1)
	{	
		can_send_msg_standard(0x7FF,extended_id | 0x1000000,can_send_buf,8);
/* 		printf("%s %d\r\n", __func__, __LINE__); */
		extended_id++;
		vTaskDelay(10);
	}
	
}

void task_can_send_multi_test( void * pvParameters )
{	
	s_hal_can_frame hal_can_frame;
	unsigned char length = 64;
	unsigned char i;

	printf("%s %d\r\n", __func__, __LINE__);
	printf("%s %s\r\n", __DATE__, __TIME__);
	
	hal_can_frame.p_data = (unsigned char *)malloc(length);
	if (hal_can_frame.p_data == 0)
	{
		printf("malloc fail\r\n");
	}

	
	for (i = 0; i < length; i++)
	{
		hal_can_frame.p_data[i] = i;
	}

	hal_can_frame.externed_id.length = length;

	while(1)
	{
		can_send_multi_frame(&hal_can_frame);

		vTaskDelay(1000);
	}
}

void vTaskStart( void * pvParameters )
{	
	step_motor_init();
	USART_Config();
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);
	xTaskCreate( task_led, "Task Led", 512, NULL, 1, NULL );
	xTaskCreate( task_deamon_bldc, "Task bldc start", 512, NULL, 1, NULL );
/* 	xTaskCreate( task_bldc_motor_control, "Task bldc stop", 512, NULL, 1, NULL ); */
	//xTaskCreate( task_bldc_motor_speed_test, "task bldc motor speed test", 512, NULL, 1, NULL );
/* 	xTaskCreate( task_step_motor, "Task step motor", 512, NULL, 1, NULL ); */
	xTaskCreate( task_serial_debug_test, "Task serial debug test", 512, NULL, 1, NULL );
	//xTaskCreate( task_hall_sensor_test, "task hall sensor test", 512, NULL, 1, NULL );
/* 	xTaskCreate( task_can_send_test, "Task can send test", 512, NULL, 1, NULL ); */
	xTaskCreate( task_can_send_multi_test, "task can send_multi_test", 512, NULL, 1, NULL );
	
	vTaskDelete( NULL );
}

int main ( void )
{	
	xTaskCreate( vTaskStart, "Task Start", 512, NULL, 1, NULL );
	vTaskStartScheduler();
}



/*********************************************END OF FILE**********************/


