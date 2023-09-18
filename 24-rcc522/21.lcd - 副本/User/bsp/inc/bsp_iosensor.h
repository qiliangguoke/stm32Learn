#ifndef __BSP_IOSENSOR_H
#define __BSP_IOSENSOR_H

#include "sys.h"

/////////////////////////////////////
//��ֲ�޸���
//����ʵ�ʶ˿��޸�
//��ǰ�汾����������ֲ(ע�⣬�˿ڽ��������ڷ� JTAG/SWD ���ţ������ JTAG ���ţ���Ҫ�� AFIO ʱ�ӣ���ʧ�� JTAG)

/////////////////////////////////////
//DO101 �𶯴�����
#define VIBRATE_OUT_GPIO_PIN 	GPIO_Pin_11     	  //VIBRATE_OUT ���ź�
#define VIBRATE_OUT_PIN_ID 		11 			 		  //VIBRATE_OUT �������
#define VIBRATE_OUT_GPIO_PORT 	GPIOA 	 		  	  //VIBRATE_OUT �˿ں�
#define VIBRATE_OUT_GPIO_CLK 	RCC_APB2Periph_GPIOA  //VIBRATE_OUT ʱ��
//#define VIBRATE_OUT_FUN_OUT 		PAout 			//VIBRATE_OUT ����˿����ú���
#define VIBRATE_OUT_FUN_IN 			PAin 			//VIBRATE_OUT ����˿����ú���
#define VIBRATE_OUT_GPIO_MODE 		GPIO_Mode_IPU   //VIBRATE_OUT �ⲿ�ж�����ģʽ
#define VIBRATE_OUT_ACTIVE_LEVEL 	0 			    //VIBRATE_OUT ��Ч��ƽΪ�͵�ƽ

#define VIBRATE_OUT_PORT_SRC 		GPIO_PortSourceGPIOA 	//VIBRATE_OUT �ⲿ�ж϶˿ں�
#define VIBRATE_OUT_PIN_SRC 		GPIO_PinSource11 		//VIBRATE_OUT �ⲿ�ж����ź�
#define VIBRATE_OUT_EXTI_LINE 		EXTI_Line11 			//VIBRATE_OUT �ⲿ�жϺ�
#define VIBRATE_OUT_EXTI_TRIG 		EXTI_Trigger_Falling 	//VIBRATE_OUT �ⲿ�жϴ�����ʽ
#define VIBRATE_OUT_EXTI_IRQN 		EXTI15_10_IRQn 			//VIBRATE_OUT �ⲿ�ж� NVIC ��

/////////////////////////////////////
//PIR ������⴫����
#define PIR_OUT_GPIO_PIN 		GPIO_Pin_14 //PIR_OUT ���ź�
#define PIR_OUT_PIN_ID 			14		    //PIR_OUT �������
#define PIR_OUT_GPIO_PORT 		GPIOG 	 //PIR_OUT �˿ں�
#define PIR_OUT_GPIO_CLK 		RCC_APB2Periph_GPIOG //PIR_OUT ʱ��
//#define PIR_OUT_FUN_OUT 		PGout 			//PIR_OUT ����˿����ú���
#define PIR_OUT_FUN_IN 			PGin 			//PIR_OUT ����˿����ú���
#define PIR_OUT_GPIO_MODE 		GPIO_Mode_IPD 	//PIR_OUT �ⲿ�ж�����ģʽ
#define PIR_OUT_ACTIVE_LEVEL 	1 				//PIR_OUT ��Ч��ƽΪ�ߵ�ƽ

#define PIR_OUT_PORT_SRC 	GPIO_PortSourceGPIOG //PIR_OUT �ⲿ�ж϶˿ں�
#define PIR_OUT_PIN_SRC 	GPIO_PinSource14 	 //PIR_OUT �ⲿ�ж����ź�
#define PIR_OUT_EXTI_LINE 	EXTI_Line14 		 //PIR_OUT �ⲿ�жϺ�
#define PIR_OUT_EXTI_TRIG 	EXTI_Trigger_Rising  //PIR_OUT �ⲿ�жϴ�����ʽ
#define PIR_OUT_EXTI_IRQN 	EXTI15_10_IRQn 		 //PIR_OUT �ⲿ�ж� NVIC ��

/////////////////////////////////////

//IO ��������
#define VIBRATE_OUT 	VIBRATE_OUT_FUN_IN(VIBRATE_OUT_PIN_ID)  //��ȡ VIBRATE_OUT �͵�ƽ��Ч
#define PIR_OUT 		PIR_OUT_FUN_IN(PIR_OUT_PIN_ID) 			//��ȡ PIR_OUT �ߵ�ƽ��Ч

extern uint8_t VIBRATE_OUT_flag;
extern uint8_t PIR_OUT_flag;

/* ���ⲿ���õĺ������� */

void bsp_InitIoSensor(void);

#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
