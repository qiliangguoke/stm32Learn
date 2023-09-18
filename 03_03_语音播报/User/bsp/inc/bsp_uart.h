#ifndef _BSP_UART_H_
#define _BSP_UART_H_

///////////////////////////////////////
/* 头文件包含区 */
#include "sys.h"
///////////////////////////////////////
/* 宏定义区域 */
#define USART_REC_LEN			1024		//定义最大接收字节数1024
#define EN_USART1_RX			1			//使能（1）/禁止（0）串口1接收

extern uint8_t USART_RX_BUF[USART_REC_LEN];	//接收缓冲，最大USART_rec_LEN个字节，末字节为换行符
extern uint8_t ReceiveState;				//接收状态标志
extern uint16_t RxCounter;					
///////////////////////////////////////
/* 外部变量申明区 */
void bsp_InitUart1(uint32_t baud);
///////////////////////////////////////
/* 函数申明区 */
#if EN_USART1_RX							//如果使能了接收

void Uart0_STA_Clr(void);

///////////////////////////////////////
#endif
#endif
/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
