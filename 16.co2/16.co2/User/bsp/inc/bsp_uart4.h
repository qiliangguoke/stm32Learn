/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : .h
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/
#ifndef __BSP_UART4_H
#define __BSP_UART4_H

#include "sys.h"

#define UART4_BUF_LEN 64 					//���� UART4 ���峤��Ϊ 64 ���ֽ�

extern uint8_t UART4_RX_BUF[UART4_BUF_LEN]; //���ջ���,��� UART4_BUF_LEN ���ֽ�
extern uint8_t UART4_RX_CNT;				//���յ������ݳ���

//����봮���жϽ��գ��벻Ҫע�����º궨��
#define EN_UART4_RX 1 						//0,������;1,����.

void bsp_InitUart4(uint32_t bound);
void UART4_Send_Data(uint8_t *buf,uint8_t len);
void UART4_Receive_Data(uint8_t *buf,uint8_t *len);


#endif
