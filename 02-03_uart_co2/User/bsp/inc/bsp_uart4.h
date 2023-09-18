#ifndef __BSP_UART4_H
#define __BSP_UART4_H


///////////////////////////////////////
/* 头文件包含区 */

#include "sys.h"

///////////////////////////////////////
/* 宏定义区域 */

#define UART4_BUF_LEN			64		//定义最大接收字节数1024

///////////////////////////////////////
/* 外部变量申明区 */

extern uint8_t UART4_RX_BUF[UART4_BUF_LEN];
extern uint8_t UART4_RX_CNT; //接收到的数据长度

///////////////////////////////////////
/* 函数申明区 */

#define EN_UART4_RX 1

void bsp_InitUart4(uint32_t baud);
void UART4_Send_Data(uint8_t *buf,uint8_t len);
void UART4_Receive_Data(uint8_t *buf,uint8_t *len);



///////////////////////////////////////
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/