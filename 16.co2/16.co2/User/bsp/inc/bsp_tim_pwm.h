/*
*********************************************************************************************************
*
*	模块名称 : 模块
*	文件名称 : bsp_tim_pwm.h
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/
#ifndef __BSP_TIM_PWM_H
#define __BSP_TIM_PWM_H

#include "sys.h"

void bsp_SetTIMOutPWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, TIM_TypeDef* TIMx, uint8_t _ucChannel,uint32_t _ulFreq, uint32_t _ulDutyCycle);

void bsp_SetTIMforInt(TIM_TypeDef* TIMx, uint32_t _ulFreq, uint8_t _PreemptionPriority, uint8_t _SubPriority);

#endif
