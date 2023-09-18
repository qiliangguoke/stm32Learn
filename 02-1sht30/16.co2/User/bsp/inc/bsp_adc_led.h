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
#ifndef _BSP_ADC_LED_H
#define _BSP_ADC_LED_H

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


/* -------------------------------------------------------------- */

#define 	LSENS_GPIO_PIN 				GPIO_Pin_8 					//LSENS 引脚号
#define 	LSENS_PIN_ID 				8 							//LSENS 引脚序号
#define 	LSENS_GPIO_PORT 			GPIOF 						//LSENS 端口号
#define 	LSENS_GPIO_CLK 				RCC_APB2Periph_GPIOF 		//LSENS 时钟
#define 	LSENS_ADC_X 				ADC3 						//LSENS 的 ADCx
#define 	LSENS_ADC_CHANNEL 			ADC_Channel_6 				//LSENS 的 ADC 输入通道
#define 	LSENS_ADC_SAMPLETIME 		ADC_SampleTime_55Cycles5 	//LSENS 的 ADC 采样时间

#define 	LSENS_READ_TIMES 			10 							//定义光敏传感器读取次数,读这么多次,然后取平均值

/* -------------------------------------------------------------- */

/*函数申明*/
void bsp_InitAdcPotentiometer2(void);
uint16_t Get_Adc_Potentiometer2(void);

void bsp_InitAdcTemp1(void);
short Get_Temprate1(void);

void bsp_InitAdcLsens(void);
uint8_t Lsens_Get_Val(void);
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
