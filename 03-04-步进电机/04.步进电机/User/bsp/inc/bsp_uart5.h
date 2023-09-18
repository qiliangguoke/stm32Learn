#ifndef __BSP_UART5_H
#define __BSP_UART5_H
#include "sys.h"

#define UART5_BUF_LEN 64 //���� UART5 ���峤��Ϊ 64 ���ֽ�

extern uint8_t UART5_RX_BUF[UART5_BUF_LEN]; //���ջ���,��� UART4_BUF_LEN ���ֽ�
extern uint8_t UART5_RX_CNT; //���յ������ݳ���

//����봮���жϽ��գ��벻Ҫע�����º궨��
#define EN_UART5_RX 1 //0,������;1,����.

void bsp_InitUart5(uint32_t bound);
void UART5_Send_Data(uint8_t *buf,uint8_t len);
void UART5_Receive_Data(uint8_t *buf,uint8_t *len);
#endif