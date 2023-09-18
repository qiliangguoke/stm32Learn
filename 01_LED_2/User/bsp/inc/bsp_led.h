/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_led_h.h
*	说    明 : 头文件，配合新建工程使用，非完整文件
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023-04-12	黄求胜
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/
#ifndef __BSP_LED_H
#define __BSP_LED_H

///////////////////////////////////////
/* 头文件包含区 */
#include "sys.h"
///////////////////////////////////////
/* 宏定义区域 */
#ifdef WSNEP_V01

#define RCC_ALL_LED 	( LED0_GPIO_CLK | LED1_GPIO_CLK)

#define LED0_GPIO_PIN		GPIO_Pin_5				//LED0引脚号
#define LED0_PIN_ID			5						//LED0引脚序号
#define LED0_GPIO_PORT		GPIOB					//LED0端口号
#define LED0_GPIO_CLK		RCC_APB2Periph_GPIOB	//LED0时钟
#define LED0_FUN_OUT		PBout					//LED0输出端口配置函数
//#define LED0_FUN_IN			PBin					//LED0输入端

#define LED1_GPIO_PIN		GPIO_Pin_5				//LED1引脚号
#define LED1_PIN_ID			5						//LED1引脚序号
#define LED1_GPIO_PORT		GPIOE					//LED1端口号
#define LED1_GPIO_CLK		RCC_APB2Periph_GPIOE	//LED1时钟
#define LED1_FUN_OUT		PEout					//LED1输出端口配置函数
//#define LED1_FUN_IN			PEin					//LED1输入端

#endif
///////////////////////////////////////
/* 外部变量申明区 */
#define LED0    LED0_FUN_OUT(LED0_PIN_ID) //LED0
#define LED1    LED1_FUN_OUT(LED1_PIN_ID) //LED1
///////////////////////////////////////
/* 函数申明区 */
void bsp_InitLed(void);
void bsp_LedOn(uint8_t _no);
void bsp_LedOff(uint8_t _no);
void bsp_LedToggle(uint8_t _no);
uint8_t bsp_IsLedOn(uint8_t _no);

///////////////////////////////////////
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
