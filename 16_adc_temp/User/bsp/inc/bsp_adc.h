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


///////////////////////////////////////
#endif




/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
