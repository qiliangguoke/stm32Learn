#ifndef __BSP_TIM_PWM_H
#define __BSP_TIM_PWM_H
#include "sys.h"

void bsp_SetTIMforInt(TIM_TypeDef* TIMx, uint32_t _ulFreq, uint8_t _PreemptionPriority, uint8_t _SubPriority);
#endif
