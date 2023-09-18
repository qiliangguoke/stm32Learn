#ifndef __BSP_RELAY_H
#define __BSP_RELAY_H

///////////////////////////////////////
/* 头文件包含区 */
#include "sys.h"
///////////////////////////////////////
/* 宏定义区域 */

#ifdef WSNEP_V01
#define RCC_ALL_RELAY 					( RELAY1_GPIO_CLK | RELAY2_GPIO_CLK | RELAY3_GPIO_CLK | RELAY4_GPIO_CLK ) //所有时钟
#define RELAY1_GPIO_PIN 				GPIO_Pin_0 //RELAY1 引脚号
#define RELAY1_PIN_ID 					0 //RELAY1 引脚序号
#define RELAY1_GPIO_PORT 				GPIOC //RELAY1 端口号
#define RELAY1_GPIO_CLK 				RCC_APB2Periph_GPIOC //RELAY1 时钟
#define RELAY1_FUN_OUT 					PCout //RELAY1 输出端口配置函数
//#define RELAY1_FUN_IN 				PCin //RELAY1 输入端口配置函数

#define RELAY2_GPIO_PIN 				GPIO_Pin_1 //RELAY2 引脚号
#define RELAY2_PIN_ID 					1 //RELAY2 引脚序号
#define RELAY2_GPIO_PORT 				GPIOC //RELAY2 端口号
#define RELAY2_GPIO_CLK 				RCC_APB2Periph_GPIOC //RELAY2 时钟
#define RELAY2_FUN_OUT 					PCout //RELAY2 输出端口配置函数

#define RELAY3_GPIO_PIN 				GPIO_Pin_2 //RELAY3 引脚号
#define RELAY3_PIN_ID 					2 //RELAY3 引脚序号
#define RELAY3_GPIO_PORT 				GPIOC //RELAY3 端口号
#define RELAY3_GPIO_CLK 				RCC_APB2Periph_GPIOC //RELAY3 时钟
#define RELAY3_FUN_OUT 					PCout //RELAY3 输出端口配置函数
//#define RELAY3_FUN_IN 				PCin //RELAY3 输入端口配置函数
//#define RELAY2_FUN_IN 				PCin //RELAY2 输入端口配置函数



#define RELAY4_GPIO_PIN 				GPIO_Pin_3 //RELAY4 引脚号
#define RELAY4_PIN_ID 					3 //RELAY4 引脚序号
#define RELAY4_GPIO_PORT 				GPIOC //RELAY4 端口号
#define RELAY4_GPIO_CLK 				RCC_APB2Periph_GPIOC //RELAY4 时钟
#define RELAY4_FUN_OUT 					PCout //RELAY4 输出端口配置函数
//#define RELAY4_FUN_IN 				PCin //RELAY4 输入端口配置函数


#endif



//IO 操作函数
#define RELAY1 			RELAY1_FUN_OUT(RELAY1_PIN_ID) //REALY1
#define RELAY2 			RELAY2_FUN_OUT(RELAY2_PIN_ID) //REALY2
#define RELAY3 			RELAY3_FUN_OUT(RELAY3_PIN_ID) //REALY3
#define RELAY4 			RELAY4_FUN_OUT(RELAY4_PIN_ID) //REALY4


///////////////////////////////////////
/* 外部变量申明区 */

///////////////////////////////////////
/* 函数申明区 */

void bsp_InitRelay(void);
void bsp_RelayOn(uint8_t _no);
void bsp_RelayOff(uint8_t _no);
void bsp_RelayToggle(uint8_t _no);
uint8_t bsp_IsRelayOn(uint8_t _no);


///////////////////////////////////////
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
