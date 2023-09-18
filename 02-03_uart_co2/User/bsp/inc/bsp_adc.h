#ifndef __BSP_ADC_H
#define __BSP_ADC_H
///////////////////////////////////////
/* 头文件包含区 */

#include "sys.h"

///////////////////////////////////////
/* 宏定义区域 */

#define RES_POT_GPIO_PIN 			GPIO_Pin_7 //RES_POT 引脚号
#define RES_POT_PIN_ID 				7 //RES_POT 引脚序号
#define RES_POT_GPIO_PORT 			GPIOF //RES_POT 端口号
#define RES_POT_GPIO_CLK 			RCC_APB2Periph_GPIOF //RES_POT 时钟
#define RES_POT_ADC_X 				ADC3 //RES_POT 的 ADCx
#define RES_POT_ADC_CHANNEL 		ADC_Channel_5 //RES_POT 的 ADC 输入通道
#define RES_POT_ADC_SAMPLETIME 		ADC_SampleTime_55Cycles5 //RES_POT 的 ADC 采样时间
#define SAMP_COUNT 					20 //样本个数，表示采样数据求平均值


#define LSENS_GPIO_PIN GPIO_Pin_8 //LSENS 引脚号
#define LSENS_PIN_ID 8 //LSENS 引脚序号
#define LSENS_GPIO_PORT GPIOF //LSENS 端口号
#define LSENS_GPIO_CLK RCC_APB2Periph_GPIOF //LSENS 时钟
#define LSENS_ADC_X ADC3 //LSENS 的 ADCx
#define LSENS_ADC_CHANNEL ADC_Channel_6 //LSENS 的 ADC 输入通道
#define LSENS_ADC_SAMPLETIME ADC_SampleTime_55Cycles5 //LSENS 的 ADC 采样时间
#define LSENS_READ_TIMES 10



#define VOL_METER_GPIO_PIN GPIO_Pin_1 //VOL_METER 引脚号
#define VOL_METER_PIN_ID 1 //VOL_METER 脚序号
#define VOL_METER_GPIO_PORT GPIOA //VOL_METER 端口号
#define VOL_METER_GPIO_CLK RCC_APB2Periph_GPIOA //VOL_METER 时钟
#define VOL_METER_ADC_X 		ADC1 //VOL_METER 的 ADCx
#define VOL_METER_ADC_CHANNEL ADC_Channel_1 //VOL_METER 的 ADC 输入通道
#define VOL_METER_ADC_SAMPLETIME ADC_SampleTime_239Cycles5 //VOL_METER 的 ADC 采样时间



///////////////////////////////////////
/* 外部变量申明区 */

///////////////////////////////////////
/* 函数申明区 */

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




/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
