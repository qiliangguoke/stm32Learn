/*
*********************************************************************************************************
*
*	模块名称 : 模块
*	文件名称 : bsp_adc_temp.h
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/
#ifndef _BSP_ADC_TEMP_H
#define _BSP_ADC_TEMP_H

#include "sys.h"

/*---------------------------------------------*/

#define 	RES_POT_GPIO_PIN 			GPIO_Pin_7 					//RES_POT 引脚号
#define 	RES_POT_PIN_ID 				7 							//RES_POT 引脚序号
#define 	RES_POT_GPIO_PORT 			GPIOF 						//RES_POT 端口号
#define 	RES_POT_GPIO_CLK 			RCC_APB2Periph_GPIOF 		//RES_POT 时钟
#define 	RES_POT_ADC_X 				ADC3 						//RES_POT 的 ADCx
#define 	RES_POT_ADC_CHANNEL 		ADC_Channel_5 				//RES_POT 的 ADC 输入通道
#define 	RES_POT_ADC_SAMPLETIME 		ADC_SampleTime_55Cycles5 	//RES_POT 的 ADC 采样时间

#define 	SAMP_COUNT 					20 							//样本个数，表示采样数据求平均值

/*---------------------------------------------*/

/*函数申明*/
void bsp_InitAdcPotentiometer1(void);
uint16_t Get_Adc_Potentiometer1(void);

void bsp_InitAdcTemp(void);
short Get_Temprate(void);

#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
