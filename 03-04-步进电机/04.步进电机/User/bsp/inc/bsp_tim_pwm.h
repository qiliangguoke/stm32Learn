#ifndef _BSP_TIM_PWM_H
#define _BSP_TIM_PWM_H

///////////////////////////////////////
/* ͷ�ļ������� */
#include "sys.h"
///////////////////////////////////////
/* �궨������ */

///////////////////////////////////////
/* �ⲿ���������� */

///////////////////////////////////////
/* ���������� */
void bsp_SetTIMforInt(TIM_TypeDef* TIMx,uint32_t _ulFreq,uint8_t _PreemptionPriority,uint8_t _SubPriority);
void bsp_SetTIMOutPWM(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,TIM_TypeDef* TIMx,uint8_t _ucChannel,
	uint32_t _ulFreq,uint32_t _ulDutyCycle);
///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
