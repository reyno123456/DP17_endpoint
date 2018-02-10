#ifndef _CAN_H
#define _CAN_H

#include "stm32f10x.h"

#define CAN_ID              0x123
#define CAN_DATA_LEN_MAX    8
#define INIT_DATA_LENGTH	64

#define CAN_RX0_INT_ENABLE	1										    

void CAN_Mode_Init(unsigned char tsjw,
						 unsigned char tbs2,
						 unsigned char tbs1,
						 unsigned short brp,
						 unsigned char mode);

unsigned char can_send_msg_standard(unsigned int StdId,
 			  						   		 unsigned int ExtId,
 			  						   		 unsigned char* msg,
 			  						   		 unsigned char len);

/* here have the same define the server */
/* start */
#define HAL_CAN_SINGLE_FRAME 		0
#define HAL_CAN_MUL_FRAME_START 	0x1
#define HAL_CAN_MUL_FRAME_MIDDLE	0x2
#define HAL_CAN_MUL_FRAME_END		0x3
											 
/********************************************
*with 18 bit externed identification
*0x3FFFF
*0x3 used as type
*after 0xFF used as length
*the last 0xFF used as index
********************************************/
typedef struct can_multi_frame_info
{	 
	unsigned char type;
	unsigned char length;
	unsigned char index;
}s_can_multi_frame_info;

typedef struct hal_can_frame
{
	unsigned short int id;
	s_can_multi_frame_info externed_id;

	unsigned char *p_data;
	unsigned char trans_status;
}s_hal_can_frame;

int can_send_multi_frame(s_hal_can_frame *p_hal_can_frame);
int can_recv_multi_frame(CanRxMsg* RxMessage_single, s_hal_can_frame *p_hal_can_frame);

/* end */

#endif
