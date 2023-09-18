
#include "bsp_uart.h"
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "sys.h"
#include "bsp.h"

uint8_t usart3_recieve_data[usart3_data_max] = {0};
uint32_t usart3_recieve_len = 0;
bool usart3_recieve_all = false;

int fputc(int ch, FILE *p) {
  USART_SendData(USART3, (u8)ch);
  while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
    ;
  return ch;
}

void usart3_write(uint8_t *buf, uint16_t cnt) {
  DMA_InitTypeDef DMA_InitStruct;

  USART_ITConfig(USART3, USART_IT_TC, DISABLE);

  DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);

  DMA_Cmd(DMA1_Channel2, DISABLE);

  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);
  DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)buf;
  DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStruct.DMA_BufferSize = cnt;
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel2, &DMA_InitStruct);

  DMA_Cmd(DMA1_Channel2, ENABLE);
  delay_ms(20); //�ӳ�һ�£��ȴ��������
}

void DMA1_Channel2_IRQHandler(void) {
  if (DMA_GetITStatus(DMA1_IT_TC2) != RESET) {
    DMA_Cmd(DMA1_Channel2, DISABLE);
  }

  DMA_ClearFlag(DMA1_IT_TC2);
}

/**
 * USART1_IRQHandler
 *
 * @method USART1_IRQHandler
 */
void USART3_IRQHandler(void) {
  // if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
  //   printf("%c", USART_ReceiveData(USART3));
  //   // USART_SendData(USART3, USART_ReceiveData(USART3));
  //   // while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
  //   //   ;
  // }
  if (USART_GetITStatus(USART3, USART_IT_IDLE) != RESET) {
    USART3->SR;
    USART3->DR; //��USART_IT_IDLE��־

    DMA_Cmd(DMA1_Channel3, DISABLE);
    usart3_recieve_len =
        usart3_data_max - DMA_GetCurrDataCounter(DMA1_Channel3);
    usart3_recieve_all = true;
    DMA_SetCurrDataCounter(DMA1_Channel3, usart3_data_max);
    DMA_Cmd(DMA1_Channel3, ENABLE);
  }
}

/**
 * USART1_Init
 *
 * @method USART1_Init
 *
 * txd:pb10   rxd:pb11
 *
 *DMA��ʽ��DMA1_Channel2---USART3 TX;DMA1_Channel3---USART3 RX Ӳ��������
 *
 * @param  baud       ������
 */
void USART3_Init(uint32_t baud) {

  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  USART_DeInit(USART3);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // TX:PB10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; // RX:PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // DMA1ͨ��2���� USART3---TX
  DMA_DeInit(DMA1_Channel2);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR); //�����ַ
  // DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)NULL;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel2, &DMA_InitStructure);
  DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);
  // DMA�����ж�����
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // DMA1ͨ��3���� USART3-RX
  DMA_DeInit(DMA1_Channel3);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)usart3_recieve_data;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = usart3_data_max;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel3, &DMA_InitStructure);

  DMA_Cmd(DMA1_Channel3, ENABLE);

  // Usart3 NVIC
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //�ж������ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  USART_InitStructure.USART_BaudRate = baud;                  //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;      // 1ֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No;         //�޼���
  USART_InitStructure.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None; //��Ӳ��������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�˫��
  USART_Init(USART3, &USART_InitStructure);

  // USART_Cmd(USART3, ENABLE); //ʹ��USART3

  // USART_ClearFlag(USART3, USART_FLAG_TC);

  // USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //ʹ�ܽ����ж�

  //�ж�����
  USART_ITConfig(USART3, USART_IT_TC, DISABLE);
  USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
  USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);

  USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE); //����DMA��ʽ����
  USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE); //����DMA��ʽ����
  USART_Cmd(USART3, ENABLE);                     //ʹ��USART3
}

static char *itoa(int value, char *string, int radix) {
  int i, d;
  int flag = 0;
  char *ptr = string;

  /* This implementation only works for decimal numbers. */
  if (radix != 10) {
    *ptr = 0;
    return string;
  }

  if (!value) {
    *ptr++ = 0x30;
    *ptr = 0;
    return string;
  }

  /* if this is a negative value insert the minus sign. */
  if (value < 0) {
    *ptr++ = '-';

    /* Make the value positive. */
    value *= -1;
  }

  for (i = 10000; i > 0; i /= 10) {
    d = value / i;

    if (d || flag) {
      *ptr++ = (char)(d + 0x30);
      value -= (d * i);
      flag = 1;
    }
  }

  /* Null terminate the string. */
  *ptr = 0;

  return string;

} /* NCL_Itoa */

void USART_printf(USART_TypeDef *USARTx, char *Data, ...) {
  const char *s;
  int d;
  char buf[16];

  va_list ap;
  va_start(ap, Data);

  while (*Data != 0) // �ж��Ƿ񵽴��ַ���������
  {
    if (*Data == 0x5c) //'\'
    {
      switch (*++Data) {
      case 'r': //�س���
        USART_SendData(USARTx, 0x0d);
        Data++;
        break;

      case 'n': //���з�
        USART_SendData(USARTx, 0x0a);
        Data++;
        break;

      default:
        Data++;
        break;
      }
    }

    else if (*Data == '%') { //
      switch (*++Data) {
      case 's': //�ַ���
        s = va_arg(ap, const char *);

        for (; *s; s++) {
          USART_SendData(USARTx, *s);
          while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
            ;
        }

        Data++;

        break;

      case 'd':
        //ʮ����
        d = va_arg(ap, int);

        itoa(d, buf, 10);

        for (s = buf; *s; s++) {
          USART_SendData(USARTx, *s);
          while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
            ;
        }

        Data++;

        break;

      default:
        Data++;

        break;
      }
    }

    else
      USART_SendData(USARTx, *Data++);

    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
      ;
  }
}
#if 1
#pragma import(__use_no_semihosting)
/*��׼����Ҫ��֧�ֺ���*/
struct	__FILE
{
	int handle;
};	
FILE 	__stdout;

/*����sys_exit()�Ա���ʹ�ð�����ģʽ*/
void _sys_exit(int x)
{
	x=x;
}
#endif
