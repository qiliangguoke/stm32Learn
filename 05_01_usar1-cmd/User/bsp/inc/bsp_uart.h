#ifndef _BSP_UART_H_
#define _BSP_UART_H_

///////////////////////////////////////
/* ͷ�ļ������� */
#include "sys.h"
///////////////////////////////////////
/* �궨������ */
#define USART_REC_LEN			1024		//�����������ֽ���1024
#define EN_USART1_RX			1			//ʹ�ܣ�1��/��ֹ��0������1����

extern uint8_t USART_RX_BUF[USART_REC_LEN];	//���ջ��壬���USART_rec_LEN���ֽڣ�ĩ�ֽ�Ϊ���з�
extern uint8_t ReceiveState;				//����״̬��־
extern uint16_t RxCounter;					
///////////////////////////////////////
/* �ⲿ���������� */
void bsp_InitUart1(uint32_t baud);
///////////////////////////////////////
/* ���������� */
#if EN_USART1_RX							//���ʹ���˽���

void Uart0_STA_Clr(void);

///////////////////////////////////////
#endif
#endif
/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
