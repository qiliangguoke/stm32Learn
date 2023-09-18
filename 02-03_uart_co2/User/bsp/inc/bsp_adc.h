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


#define LSENS_GPIO_PIN GPIO_Pin_8 //LSENS ���ź�
#define LSENS_PIN_ID 8 //LSENS �������
#define LSENS_GPIO_PORT GPIOF //LSENS �˿ں�
#define LSENS_GPIO_CLK RCC_APB2Periph_GPIOF //LSENS ʱ��
#define LSENS_ADC_X ADC3 //LSENS �� ADCx
#define LSENS_ADC_CHANNEL ADC_Channel_6 //LSENS �� ADC ����ͨ��
#define LSENS_ADC_SAMPLETIME ADC_SampleTime_55Cycles5 //LSENS �� ADC ����ʱ��
#define LSENS_READ_TIMES 10



#define VOL_METER_GPIO_PIN GPIO_Pin_1 //VOL_METER ���ź�
#define VOL_METER_PIN_ID 1 //VOL_METER �����
#define VOL_METER_GPIO_PORT GPIOA //VOL_METER �˿ں�
#define VOL_METER_GPIO_CLK RCC_APB2Periph_GPIOA //VOL_METER ʱ��
#define VOL_METER_ADC_X 		ADC1 //VOL_METER �� ADCx
#define VOL_METER_ADC_CHANNEL ADC_Channel_1 //VOL_METER �� ADC ����ͨ��
#define VOL_METER_ADC_SAMPLETIME ADC_SampleTime_239Cycles5 //VOL_METER �� ADC ����ʱ��



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
void bsp_InitAdcLsens(void);
uint8_t Lsens_Get_Val(void);
void bsp_InitAdcVolMeter(void);
uint16_t Get_Adc_Volmeter(void);

///////////////////////////////////////
#endif




/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
