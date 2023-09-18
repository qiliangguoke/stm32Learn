/*
*********************************************************************************************************
*
*	ģ������ : LEDָʾ������ģ��
*	�ļ����� : bsp_led.h
*	��    �� : V1.0
*	˵    �� : ͷ�ļ�������½�����ʹ�ã��������ļ�
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/

#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "sys.h"



///////////////////////////////////////////////////////////
//��ֲ�޸���
//����ʵ�ʶ˿��޸�
//��ǰ�汾����������ֲ(ע�⣬�˿ڽ��������ڷ�JTAG/SWD���ţ������JTAG���ţ���Ҫ��AFIOʱ�ӣ���ʧ��JTAG)



#ifdef WSNEP_V01

#define RCC_ALL_LED 	( LED0_GPIO_CLK )

#define LED0_GPIO_PIN		GPIO_Pin_13				//LED0���ź�
#define LED0_PIN_ID			13						//LED0�������
#define LED0_GPIO_PORT		GPIOC					//LED0�˿ں�
#define LED0_GPIO_CLK		RCC_APB2Periph_GPIOC	//LED0ʱ��
#define LED0_FUN_OUT		PCout					//LED0����˿����ú���
//#define LED0_FUN_IN			PBin					//LED0����˿����ú���

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////


//IO��������	 
#define LED0    LED0_FUN_OUT(LED0_PIN_ID) //LED0



/* ���ⲿ���õĺ������� */
void bsp_InitLed(void);
void bsp_LedToggle(uint8_t _no);

#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/