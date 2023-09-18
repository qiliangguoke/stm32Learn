#ifndef __BSP_FAN_H
#define __BSP_FAN_H

///////////////////////////////////////
/* 头文件包含区 */

#include "sys.h"

///////////////////////////////////////
/* 宏定义区域 */

#ifdef WSNEP_V01

#define RCC_ALL_FAN		( FAN0_GPIO_CLK | FAN1_GPIO_CLK )


///FAN0配置
#define FAN0_GPIO_PIN			GPIO_Pin_8						//FAN0引脚号
#define FAN0_PIN_ID				8								//FAN引脚序号
#define FAN0_GPIO_PORT			GPIOB							//FAN端口号 peb
#define FAN0_GPIO_CLK			RCC_APB2Periph_GPIOB			//FAN0时钟
#define FAN0_FUN_OUT			PBout							//FAN 配置函数

///FAN1配置
#define FAN1_GPIO_PIN			GPIO_Pin_9						//FAN1引脚号
#define FAN1_PIN_ID				9								//FAN引脚序号
#define FAN1_GPIO_PORT			GPIOB					//FAN端口号 peb
#define FAN1_GPIO_CLK			RCC_APB2Periph_GPIOB			//FAN1时钟
#define FAN1_FUN_OUT			PBout							//FAN 配置函数


#define FAN0					FAN0_FUN_OUT(FAN0_PIN_ID)		//FAN0
#define FAN1					FAN1_FUN_OUT(FAN1_PIN_ID)		//FAN1


#endif
///////////////////////////////////////
/* 外部变量申明区 */

///////////////////////////////////////
/* 函数申明区 */

void bsp_FanOff(uint8_t _no);
void bsp_InitFan(void);
void bsp_FanToggle(uint8_t _no);
void bsp_FanOn(uint8_t _no);
uint8_t bsp_IsFanOn(uint8_t _no);

///////////////////////////////////////
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/