#ifndef __BSP_FAN_H
#define __BSP_FAN_H

///////////////////////////////////////
/* ͷ�ļ������� */

#include "sys.h"

///////////////////////////////////////
/* �궨������ */

#ifdef WSNEP_V01

#define RCC_ALL_FAN		( FAN0_GPIO_CLK | FAN1_GPIO_CLK )


///FAN0����
#define FAN0_GPIO_PIN			GPIO_Pin_8						//FAN0���ź�
#define FAN0_PIN_ID				8								//FAN�������
#define FAN0_GPIO_PORT			GPIOB							//FAN�˿ں� peb
#define FAN0_GPIO_CLK			RCC_APB2Periph_GPIOB			//FAN0ʱ��
#define FAN0_FUN_OUT			PBout							//FAN ���ú���

///FAN1����
#define FAN1_GPIO_PIN			GPIO_Pin_9						//FAN1���ź�
#define FAN1_PIN_ID				9								//FAN�������
#define FAN1_GPIO_PORT			GPIOB					//FAN�˿ں� peb
#define FAN1_GPIO_CLK			RCC_APB2Periph_GPIOB			//FAN1ʱ��
#define FAN1_FUN_OUT			PBout							//FAN ���ú���


#define FAN0					FAN0_FUN_OUT(FAN0_PIN_ID)		//FAN0
#define FAN1					FAN1_FUN_OUT(FAN1_PIN_ID)		//FAN1


#endif
///////////////////////////////////////
/* �ⲿ���������� */

///////////////////////////////////////
/* ���������� */

void bsp_FanOff(uint8_t _no);
void bsp_InitFan(void);
void bsp_FanToggle(uint8_t _no);
void bsp_FanOn(uint8_t _no);
uint8_t bsp_IsFanOn(uint8_t _no);

///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/