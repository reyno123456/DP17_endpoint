#ifndef _MOTOR_H
#define _MOTOR_H

#define step_motor_dir_clockwise()                     GPIO_ResetBits ( GPIOB, GPIO_Pin_9 )
#define step_motor_dir_anticlocksize()                 GPIO_SetBits ( GPIOB, GPIO_Pin_9 )

#define step_motor_clk_ON()                            GPIO_ResetBits ( GPIOB, GPIO_Pin_8 )
#define step_motor_clk_OFF()                           GPIO_SetBits ( GPIOB, GPIO_Pin_8 )

#define READ_HALL_UP 									GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)
#define READ_HALL_DOWN									GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)
#define READ_HALL_WHIRL									GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)

#define STEP_MOTOR_UP			0
#define STEP_MOTOR_DOWN			1

#define HALL_TRIGGERED			0
#define HALL_NOT_TRIGGERED		1

void step_motor_init(void);
void step_motor_start(unsigned short int us, unsigned char direction);
void step_motor_stop(unsigned short int us);
void bldc_motor_init(void);
void bldc_motor_start(unsigned char duty);
void bldc_motor_stop(void);


#endif
