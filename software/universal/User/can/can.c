#include "can.h"
#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

s_hal_can_frame g_hal_can_frame;
s_hal_can_frame g_hal_can_frame_send;


static int frame_to_multi_frame(CanRxMsg* p_can_recv_single, s_hal_can_frame *p_hal_can_frame);

void CAN_Mode_Init(unsigned char tsjw,
						 unsigned char tbs2,
						 unsigned char tbs1,
						 unsigned short brp,
						 unsigned char mode)
{ 
	GPIO_InitTypeDef 		GPIO_InitStructure; 
	CAN_InitTypeDef        	CAN_InitStructure;
	CAN_FilterInitTypeDef  	CAN_FilterInitStructure;
#if CAN_RX0_INT_ENABLE 
 	NVIC_InitTypeDef  		NVIC_InitStructure;	
#endif

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);//使能PORTA时钟	                   											 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    
	GPIO_PinRemapConfig(GPIO_Remap2_CAN1,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);			

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_Init(GPIOD, &GPIO_InitStructure);			
    // CAN_GPIO_Config();
	//CAN单元设置
	CAN_InitStructure.CAN_TTCM=DISABLE;			 
	CAN_InitStructure.CAN_ABOM=DISABLE;			 
	CAN_InitStructure.CAN_AWUM=DISABLE;			
	CAN_InitStructure.CAN_NART=ENABLE;			
	CAN_InitStructure.CAN_RFLM=DISABLE;		 	 
	CAN_InitStructure.CAN_TXFP=DISABLE;			 
	CAN_InitStructure.CAN_Mode= mode;	        

	CAN_InitStructure.CAN_SJW=tsjw;				
	CAN_InitStructure.CAN_BS1=tbs1; 			
	CAN_InitStructure.CAN_BS2=tbs2;				
	CAN_InitStructure.CAN_Prescaler=brp;        
	CAN_Init(CAN1, &CAN_InitStructure);        	

	CAN_FilterInitStructure.CAN_FilterNumber=0;	
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 	
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; 	
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;	
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;

	CAN_FilterInit(&CAN_FilterInitStructure);			
	
#if CAN_RX0_INT_ENABLE 
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);						    

	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

	hal_can_buffer_init();
}   

unsigned char can_send_msg_standard(unsigned int StdId,
								 unsigned int ExtId,
								 unsigned char* msg,
								 unsigned char len)
{	
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	TxMessage.StdId=StdId;		
	TxMessage.ExtId=ExtId;		
/* 	TxMessage.IDE=CAN_Id_Standard; 	 */
	TxMessage.IDE = CAN_Id_Extended;
	// TxMessage.IDE=IDE; 	
	TxMessage.RTR=CAN_RTR_Data;		
	TxMessage.DLC=len;				
	for(i=0;i<len;i++)
	TxMessage.Data[i]=msg[i];			          
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	
	if(i>=0XFFF)return 1;
	return 0;	 
}

#if CAN_RX0_INT_ENABLE													 
 void USB_LP_CAN1_RX0_IRQHandler(void)
 {
	//CanRxFlag = TRUE;
	CanRxMsg RxMessage;
//	int i=0;
	CAN_Receive(CAN1, 0, &RxMessage);
/*
	for(i=0;i<8;i++)
	{
		printf("rxbuf[%d]:%d\r\n",i,RxMessage.Data[i]);
	}
	printf("RxMessage.ExtId = 0x%08x\r\n", RxMessage.ExtId);
*/

	frame_to_multi_frame(&RxMessage, &g_hal_can_frame);
 }
#endif

static int frame_to_multi_frame(CanRxMsg* p_can_recv_single, s_hal_can_frame *p_hal_can_frame)
{
	unsigned char frame_type;
	static unsigned int i;
	unsigned char length;
	unsigned char frame_index;

	frame_type = (p_can_recv_single->ExtId >> 17) & 0x3;
	length = p_can_recv_single->ExtId >> 9;
	frame_index = p_can_recv_single->ExtId >> 1;
	p_hal_can_frame->trans_status = frame_type;

	//printf("frame_type = 0x%x, length = 0x%x, frame_index = 0x%x\r\n", frame_type, length, frame_index);

	switch (frame_type)
	{
		case HAL_CAN_MUL_FRAME_START:
			memcpy(p_hal_can_frame->p_data, &p_can_recv_single->Data, CAN_DATA_LEN_MAX);
		break;

		case HAL_CAN_MUL_FRAME_MIDDLE:
			memcpy(p_hal_can_frame->p_data + frame_index*CAN_DATA_LEN_MAX, &p_can_recv_single->Data, CAN_DATA_LEN_MAX);
		break;

		case HAL_CAN_MUL_FRAME_END:
			memcpy(p_hal_can_frame->p_data + frame_index*CAN_DATA_LEN_MAX,&p_can_recv_single->Data, CAN_DATA_LEN_MAX);

			for (i = 0; i < INIT_DATA_LENGTH; i++)
			{
				printf("p_hal_can_frame->p_data[%d] = %d\r\n", i, p_hal_can_frame->p_data[i]);
			}
		break;

		default:break;
	}

	return 0;
}

static int hal_can_buffer_init(void)
{
	g_hal_can_frame.p_data = calloc(sizeof(unsigned char), INIT_DATA_LENGTH*sizeof(unsigned char));

	if (g_hal_can_frame.p_data == 0)
	{
		printf("malloc error\r\n");
	}
	return 0;
}


int can_send_multi_frame(s_hal_can_frame *p_hal_can_frame)
{
	unsigned int i;
	unsigned int length;
	unsigned int frame_index;
	CanTxMsg frame;
	int ret;
	unsigned char mbox;
	unsigned char const_length;

	if (p_hal_can_frame->externed_id.length < 8)
	{
		printf("send buffer fail\r\n");
	}

	frame.ExtId = ((CAN_ID << 20) | (1 << 31));
	frame.ExtId &= ~(0x3FFFF << 1);
	length = p_hal_can_frame->externed_id.length;
	const_length = p_hal_can_frame->externed_id.length;
	frame.ExtId |= length << 9;
	
	frame_index = 0;
	while(1)
	{
		if (frame_index * CAN_DATA_LEN_MAX >= const_length)
		{
			break;
		}
		
		for (i = 0; i < 8; i++)
		{
			frame.Data[i] = p_hal_can_frame->p_data[i + frame_index * CAN_DATA_LEN_MAX];
		}

		if (frame_index == 0)
		{
			frame.ExtId &= ~(0x3 << 17);							// type clear
			frame.ExtId |= (HAL_CAN_MUL_FRAME_START << 17);			// type set start
		}
		else if ((frame_index+1) * CAN_DATA_LEN_MAX < p_hal_can_frame->externed_id.length)
		{
			frame.ExtId &= ~(0x3 << 17);							// type clear
			frame.ExtId |= (HAL_CAN_MUL_FRAME_MIDDLE << 17);		// type set start
		}
		else
		{
			frame.ExtId &= ~(0x3 << 17);							// type clear
			frame.ExtId |= (HAL_CAN_MUL_FRAME_END << 17);			// type set start			
		}
		
		frame.ExtId &= ~(0xFF << 1);								// index clear
		frame.ExtId |= frame_index << 1;							// index set

		//DEBUG_INFO("canid = 0x%x\n", pframe->can_id);	

		frame.IDE = CAN_Id_Extended;
		// TxMessage.IDE=IDE;	
		frame.RTR=CAN_RTR_Data; 	
		frame.DLC=CAN_DATA_LEN_MAX;				
				  
		mbox = CAN_Transmit(CAN1, &frame);	
		i = 0;
		while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))
		{
			printf("can trans error\r\n");
			
			if(++i>=0XFFF)
				return -1;
		}

		frame_index++;
		vTaskDelay(1);
	}

	return 0;
}

