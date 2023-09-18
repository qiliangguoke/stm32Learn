#ifndef _BSP_DMA_H_
#define _BSP_DMA_H_

///////////////////////////////////////
/* 头文件包含区 */
#include "sys.h"
///////////////////////////////////////
/* 宏定义区域 */

#define BUFFER_SIZE 16   //发送数据的大小
#define SEND_SIZE 500
#define USART_DR_ADDR (USART1+0x04)		//串口1的地址+偏移地址
#define DMA_CLOCK RCC_AHBPeriph_DMA1	//定义时钟

#define DMA_CHANNEL DMA1_Channel6	//配置 DMA 通道

// 传输完成标志
#define DMA_FLAG_TC DMA1_FLAG_TC6
///////////////////////////////////////
/* 外部变量申明区 */

///////////////////////////////////////
/* 函数申明区 */

void DMA_Config(void);
void USART_DMA_Init(void);
///////////////////////////////////////
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
