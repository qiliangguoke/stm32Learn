#ifndef __BSP_BEEP_H_
#define __BSP_BEEP_H_

///////////////////////////////////////
/* ͷ�ļ������� */
#include "sys.h"
///////////////////////////////////////
/* �궨������ */
#define RCC_ALL_BEEP (BEEP_GPIO_CLK)

#define BEEP_GPIO_PIN		GPIO_Pin_11
#define BEEP_PIN_ID			11
#define BEEP_GPIO_PORT		GPIOG
#define BEEP_GPIO_CLK		RCC_APB2Periph_GPIOG
#define BEEP_FUN_OUT		PGout
#define BEEP_FUN_IN			PGin
///////////////////////////////////////
/* �ⲿ���������� */
#define BEEP 				BEEP_FUN_OUT(BEEP_PIN_ID)
///////////////////////////////////////
/* ���������� */
void bsp_InitBeep(void);
void bsp_BeepOn(void);
void bsp_BeepOff(void);
void bsp_BeepToggle(void);
uint8_t bsp_IsBeepOn(void);
///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
