#ifndef __BSP_UART4_H
#define __BSP_UART4_H


///////////////////////////////////////
/* ͷ�ļ������� */

#include "sys.h"

///////////////////////////////////////
/* �궨������ */

#define UART4_BUF_LEN			64		//�����������ֽ���1024

///////////////////////////////////////
/* �ⲿ���������� */

extern uint8_t UART4_RX_BUF[UART4_BUF_LEN];
extern uint8_t UART4_RX_CNT; //���յ������ݳ���

///////////////////////////////////////
/* ���������� */

#define EN_UART4_RX 1

void bsp_InitUart4(uint32_t baud);
void UART4_Send_Data(uint8_t *buf,uint8_t len);
void UART4_Receive_Data(uint8_t *buf,uint8_t *len);



///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/