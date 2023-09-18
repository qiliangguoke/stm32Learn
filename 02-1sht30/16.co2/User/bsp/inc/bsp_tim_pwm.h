/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : bsp_tim_pwm.h
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/
#ifndef __BSP_TIM_PWM_H
#define __BSP_TIM_PWM_H

#include "sys.h"

void bsp_SetTIMOutPWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, TIM_TypeDef* TIMx, uint8_t _ucChannel,uint32_t _ulFreq, uint32_t _ulDutyCycle);

void bsp_SetTIMforInt(TIM_TypeDef* TIMx, uint32_t _ulFreq, uint8_t _PreemptionPriority, uint8_t _SubPriority);

#endif
