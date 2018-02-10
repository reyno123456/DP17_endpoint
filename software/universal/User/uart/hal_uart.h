#ifndef _HAL_UART_H
#define _HAL_UART_H

#include "stm32f10x.h"


// ����2-USART2
#define  DEBUG_USARTx                   USART2
#define  DEBUG_USART_CLK                RCC_APB1Periph_USART2
#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO ���ź궨��
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT         GPIOD
#define  DEBUG_USART_TX_GPIO_PIN          GPIO_Pin_5
#define  DEBUG_USART_RX_GPIO_PORT       GPIOD
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_6

#define  DEBUG_USART_IRQ                USART2_IRQn
#define  DEBUG_USART_IRQHandler         USART2_IRQHandler

void USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

#endif
