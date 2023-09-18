#ifndef __BSP_UART_H
#define __BSP_UART_H
#include "sys.h"
#define USART_REC_LEN		1024		//定义最大接收字节数1024
#define EN_USART1_RX		1			//使能（1）/禁止（0）串口1接收
/*声明*/
extern uint8_t USART_RX_BUF[USART_REC_LEN];//接收缓冲，最大USART_REC_LEN个字节  末字节为换行符
extern uint8_t ReceiveState;				//接收状态标记
extern uint16_t RxCounter;

void bsp_InitUart1(uint32_t baud);

#if EN_USART1_RX	//如果使能了接收

void Uart0_STA_Clr(void);

#endif

#endif

