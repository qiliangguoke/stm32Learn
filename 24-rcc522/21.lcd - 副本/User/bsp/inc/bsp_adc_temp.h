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
#ifndef _BSP_ADC_TEMP_H
#define _BSP_ADC_TEMP_H

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

/*��������*/
void bsp_InitAdcPotentiometer1(void);
uint16_t Get_Adc_Potentiometer1(void);

void bsp_InitAdcTemp(void);
short Get_Temprate(void);

#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
