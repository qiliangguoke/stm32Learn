/*
*********************************************************************************************************
*
*	ģ������ : LEDָʾ������ģ��
*	�ļ����� : bsp_led_h.h
*	˵    �� : ͷ�ļ�������½�����ʹ�ã��������ļ�
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023-04-12	����ʤ
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/
#ifndef __BSP_LED_H
#define __BSP_LED_H

///////////////////////////////////////
/* ͷ�ļ������� */
#include "sys.h"
///////////////////////////////////////
/* �궨������ */
#ifdef WSNEP_V01

#define RCC_ALL_LED 	( LED0_GPIO_CLK | LED1_GPIO_CLK)

#define LED0_GPIO_PIN		GPIO_Pin_5				//LED0���ź�
#define LED0_PIN_ID			5						//LED0�������
#define LED0_GPIO_PORT		GPIOB					//LED0�˿ں�
#define LED0_GPIO_CLK		RCC_APB2Periph_GPIOB	//LED0ʱ��
#define LED0_FUN_OUT		PBout					//LED0����˿����ú���
//#define LED0_FUN_IN			PBin					//LED0�����

#define LED1_GPIO_PIN		GPIO_Pin_5				//LED1���ź�
#define LED1_PIN_ID			5						//LED1�������
#define LED1_GPIO_PORT		GPIOE					//LED1�˿ں�
#define LED1_GPIO_CLK		RCC_APB2Periph_GPIOE	//LED1ʱ��
#define LED1_FUN_OUT		PEout					//LED1����˿����ú���
//#define LED1_FUN_IN			PEin					//LED1�����

#endif
///////////////////////////////////////
/* �ⲿ���������� */
#define LED0    LED0_FUN_OUT(LED0_PIN_ID) //LED0
#define LED1    LED1_FUN_OUT(LED1_PIN_ID) //LED1
///////////////////////////////////////
/* ���������� */
void bsp_InitLed(void);
void bsp_LedOn(uint8_t _no);
void bsp_LedOff(uint8_t _no);
void bsp_LedToggle(uint8_t _no);
uint8_t bsp_IsLedOn(uint8_t _no);

///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
