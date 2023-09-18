#ifndef __BSP_ADC_H
#define __BSP_ADC_H
///////////////////////////////////////
/* ͷ�ļ������� */

#include "sys.h"

///////////////////////////////////////
/* �궨������ */

#define RES_POT_GPIO_PIN 			GPIO_Pin_7 //RES_POT ���ź�
#define RES_POT_PIN_ID 				7 //RES_POT �������
#define RES_POT_GPIO_PORT 			GPIOF //RES_POT �˿ں�
#define RES_POT_GPIO_CLK 			RCC_APB2Periph_GPIOF //RES_POT ʱ��
#define RES_POT_ADC_X 				ADC3 //RES_POT �� ADCx
#define RES_POT_ADC_CHANNEL 		ADC_Channel_5 //RES_POT �� ADC ����ͨ��
#define RES_POT_ADC_SAMPLETIME 		ADC_SampleTime_55Cycles5 //RES_POT �� ADC ����ʱ��
#define SAMP_COUNT 					20 //������������ʾ����������ƽ��ֵ

///////////////////////////////////////
/* �ⲿ���������� */

///////////////////////////////////////
/* ���������� */

//void bsp_InitAdc(ADC_TypeDef* ADCx,uint8_t ADC_Channel,uint8_t ADC_SampleTime);

//uint16_t Get_Adc_Average(ADC_TypeDef* ADCx,uint8_t times);
//void bsp_InitAdcPotentiometer(void);
//uint16_t Get_Adc_Potentiometer(void);

void bsp_InitAdcPotentiometer(void);
uint16_t Get_Adc_Potentiometer(void);
void bsp_InitAdcTemp(void);
short Get_Temprate(void);


///////////////////////////////////////
#endif




/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
