#ifndef __BSP_LED_H
#define __BSP_LED_H

//����ٷ���
#include "sys.h"

//��ֲ�޸���
//����led�ƵĶ˿�
#ifdef WSNEP_V01

#define RCC_ALL_LED				( LED0_GPIO_CLK | LED1_GPIO_CLK )

///LED0����
#define LED0_GPIO_PIN			GPIO_Pin_5						//LED0���ź�
#define LED0_PIN_ID				5								//led�������
#define LED0_GPIO_PORT			GPIOB							//led�˿ں� peb
#define LED0_GPIO_CLK			RCC_APB2Periph_GPIOB			//led0ʱ��
#define LED0_FUN_OUT			PBout							//led ���ú���


////////

///LED1����
#define LED1_GPIO_PIN			GPIO_Pin_5						//LED1���ź�
#define LED1_PIN_ID				5								//led�������
#define LED1_GPIO_PORT			GPIOE							//led�˿ں� peb
#define LED1_GPIO_CLK			RCC_APB2Periph_GPIOE			//led1ʱ��
#define LED1_FUN_OUT			PEout							//led ���ú���

////////

#endif

//io��������
#define LED0					LED0_FUN_OUT(LED0_PIN_ID)		//LED0
#define LED1					LED1_FUN_OUT(LED1_PIN_ID)		//led1






//��������
void bsp_LedOff(uint8_t _no);
void bsp_InitLed(void);
void bsp_LedToggle(uint8_t _no);
void bsp_LedOn(uint8_t _no);
uint8_t bsp_IsLedOn(uint8_t _no);


#endif

