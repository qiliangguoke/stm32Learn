#ifndef __BSP_BEEP_H_
#define __BSP_BEEP_H_

///////////////////////////////////////
/* 头文件包含区 */
#include "sys.h"
///////////////////////////////////////
/* 宏定义区域 */
#define RCC_ALL_BEEP (BEEP_GPIO_CLK)

#define BEEP_GPIO_PIN		GPIO_Pin_11
#define BEEP_PIN_ID			11
#define BEEP_GPIO_PORT		GPIOG
#define BEEP_GPIO_CLK		RCC_APB2Periph_GPIOG
#define BEEP_FUN_OUT		PGout
#define BEEP_FUN_IN			PGin
///////////////////////////////////////
/* 外部变量申明区 */
#define BEEP 				BEEP_FUN_OUT(BEEP_PIN_ID)
///////////////////////////////////////
/* 函数申明区 */
void bsp_InitBeep(void);
void bsp_BeepOn(void);
void bsp_BeepOff(void);
void bsp_BeepToggle(void);
uint8_t bsp_IsBeepOn(void);
///////////////////////////////////////
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
