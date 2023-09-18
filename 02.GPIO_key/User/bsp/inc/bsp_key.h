#ifndef __BSP_KEY_H
#define __BSP_KEY_H

///////////////////////////////////////
/* 头文件包含区 */
#include "sys.h"

///////////////////////////////////////
/* 宏定义区域 */
#define RCC_ALL_KEY	(WKUP_GPIO_CLK|KEY0_GPIO_CLK|KEY1_GPIO_CLK|KEY2_GPIO_CLK)

#define WKUP_GPIO_PIN			GPIO_Pin_0
#define WKUP_PIN_ID				0
#define WKUP_GPIO_PORT			GPIOA
#define WKUP_GPIO_CLK			RCC_APB2Periph_GPIOA
//#define WKUP_FUN_OUT			PAout
#define WKUP_FUN_IN				PAin
#define WKUP_GPIO_MODE			GPIO_Mode_IPD
#define WKUP_ACTIVE_LEVEL		1
///////////////////////////////////////
/* 外部变量申明区 */
#define KEY0_GPIO_PIN			GPIO_Pin_4
#define KEY0_PIN_ID				4
#define KEY0_GPIO_PORT			GPIOE
#define KEY0_GPIO_CLK			RCC_APB2Periph_GPIOE
//#define KEY0_FUN_OUT			PEout
#define KEY0_FUN_IN				PEin
#define KEY0_GPIO_MODE			GPIO_Mode_IPU
#define KEY0_ACTIVE_LEVEL		0

#define KEY1_GPIO_PIN			GPIO_Pin_3
#define KEY1_PIN_ID				3
#define KEY1_GPIO_PORT			GPIOE
#define KEY1_GPIO_CLK			RCC_APB2Periph_GPIOE
//#define KEY0_FUN_OUT			PEout
#define KEY1_FUN_IN				PEin
#define KEY1_GPIO_MODE			GPIO_Mode_IPU
#define KEY1_ACTIVE_LEVEL		0

#define KEY2_GPIO_PIN			GPIO_Pin_2
#define KEY2_PIN_ID				2
#define KEY2_GPIO_PORT			GPIOE
#define KEY2_GPIO_CLK			RCC_APB2Periph_GPIOE
//#define KEY0_FUN_OUT			PEout
#define KEY2_FUN_IN				PEin
#define KEY2_GPIO_MODE			GPIO_Mode_IPU
#define KEY2_ACTIVE_LEVEL		0


#define WKUP					WKUP_FUN_IN(WKUP_PIN_ID)
#define KEY0					KEY0_FUN_IN(KEY0_PIN_ID)
#define KEY1					KEY1_FUN_IN(KEY1_PIN_ID)
#define KEY2					KEY2_FUN_IN(KEY2_PIN_ID)


#define NOKEY_NUM	0
#define WKUP_NUM	1
#define KEY0_NUM	2
#define KEY1_NUM	3
#define KEY2_NUM	4
///////////////////////////////////////
/* 函数申明区 */
void bsp_InitKey(void);
uint8_t bsp_KeyScan(void);
///////////////////////////////////////
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/

