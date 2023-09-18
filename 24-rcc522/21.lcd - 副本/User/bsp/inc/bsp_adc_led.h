/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : bsp_adc_temp.h
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/
#ifndef _BSP_ADC_LED_H
#define _BSP_ADC_LED_H

#include "sys.h"

/*---------------------------------------------*/

#define 	RES_POT_GPIO_PIN 			GPIO_Pin_7 					//RES_POT ���ź�
#define 	RES_POT_PIN_ID 				7 							//RES_POT �������
#define 	RES_POT_GPIO_PORT 			GPIOF 						//RES_POT �˿ں�
#define 	RES_POT_GPIO_CLK 			RCC_APB2Periph_GPIOF 		//RES_POT ʱ��
#define 	RES_POT_ADC_X 				ADC3 						//RES_POT �� ADCx
#define 	RES_POT_ADC_CHANNEL 		ADC_Channel_5 				//RES_POT �� ADC ����ͨ��
#define 	RES_POT_ADC_SAMPLETIME 		ADC_SampleTime_55Cycles5 	//RES_POT �� ADC ����ʱ��

#define 	SAMP_COUNT 					20 							//������������ʾ����������ƽ��ֵ

/*---------------------------------------------*/


/* -------------------------------------------------------------- */

#define 	LSENS_GPIO_PIN 				GPIO_Pin_8 					//LSENS ���ź�
#define 	LSENS_PIN_ID 				8 							//LSENS �������
#define 	LSENS_GPIO_PORT 			GPIOF 						//LSENS �˿ں�
#define 	LSENS_GPIO_CLK 				RCC_APB2Periph_GPIOF 		//LSENS ʱ��
#define 	LSENS_ADC_X 				ADC3 						//LSENS �� ADCx
#define 	LSENS_ADC_CHANNEL 			ADC_Channel_6 				//LSENS �� ADC ����ͨ��
#define 	LSENS_ADC_SAMPLETIME 		ADC_SampleTime_55Cycles5 	//LSENS �� ADC ����ʱ��

#define 	LSENS_READ_TIMES 			10 							//���������������ȡ����,����ô���,Ȼ��ȡƽ��ֵ

/* -------------------------------------------------------------- */

/*��������*/
void bsp_InitAdcPotentiometer2(void);
uint16_t Get_Adc_Potentiometer2(void);

void bsp_InitAdcTemp1(void);
short Get_Temprate1(void);

void bsp_InitAdcLsens(void);
uint8_t Lsens_Get_Val(void);
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
