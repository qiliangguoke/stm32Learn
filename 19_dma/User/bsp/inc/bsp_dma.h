#ifndef _BSP_DMA_H_
#define _BSP_DMA_H_

///////////////////////////////////////
/* ͷ�ļ������� */
#include "sys.h"
///////////////////////////////////////
/* �궨������ */

#define BUFFER_SIZE 16   //�������ݵĴ�С
#define SEND_SIZE 500
#define USART_DR_ADDR (USART1+0x04)		//����1�ĵ�ַ+ƫ�Ƶ�ַ
#define DMA_CLOCK RCC_AHBPeriph_DMA1	//����ʱ��

#define DMA_CHANNEL DMA1_Channel6	//���� DMA ͨ��

// ������ɱ�־
#define DMA_FLAG_TC DMA1_FLAG_TC6
///////////////////////////////////////
/* �ⲿ���������� */

///////////////////////////////////////
/* ���������� */

void DMA_Config(void);
void USART_DMA_Init(void);
///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
