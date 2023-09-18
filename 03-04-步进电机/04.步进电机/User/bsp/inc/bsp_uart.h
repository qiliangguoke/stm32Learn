#ifndef __BSP_UART_H
#define __BSP_UART_H
///////////////////////////////////////
/* ͷ�ļ������� */
#include"sys.h"
///////////////////////////////////////
/* �궨������ */
#define USART_REC_LEN               1024   //�����������ֽ���  1024
#define EN_USART1_RX                1      //ʹ�ܣ�1��/��ֹ��0������1����
///////////////////////////////////////
/* �ⲿ���������� */
extern uint8_t  USART_RX_BUF[USART_REC_LEN];       //���ջ��������USART_REC_LEN���ֽڣ�ĩ�ֽ�λ���з�
extern uint8_t  ReceiveState;
extern uint16_t RxCounter;	
///////////////////////////////////////
/* ���������� */
void bsp_InitUart(uint32_t baud);

#if EN_USART1_RX   //���ʹ���˽���
void Uart0_STA_Clr(void);
#endif
///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
