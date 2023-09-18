/*
*********************************************************************************************************
*
*	模块名称 : 蜂鸣器驱动模块
*	文件名称 : bsp_led.h
*	版    本 : V1.0
*	说    明 : 头文件，配合新建工程使用，非完整文件
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/

#ifndef __BSP_BEEP_H
#define __BSP_BEEP_H

#include "sys.h"



///////////////////////////////////////////////////////////
//移植修改区
//按照实际端口修改
//较前版本更加容易移植(注意，端口仅仅适用于非JTAG/SWD引脚，如果是JTAG引脚，需要打开AFIO时钟，并失能JTAG)


#define RCC_ALL_BEEP (BEEP_GPIO_CLK)
#define BEEP_GPIO_PIN GPIO_Pin_11				//BEEP引脚号
#define BEEP_PIN_ID 11							//BEEP引脚序号
#define BEEP_GPIO_PORT GPIOG					//BEEP端口号
#define BEEP_GPIO_CLK RCC_APB2Periph_GPIOG		//BEEP时钟
#define BEEP_FUN_OUT PGout						//BEEP输出端口配置函数
#define BEEP_FUN_IN PGin						//BEEP输入端口配置函数





//IO操作函数	 
#define BEEP    BEEP_FUN_OUT(BEEP_PIN_ID) //BEEP



/* 供外部调用的函数声明 */
void bsp_InitBeep(void);
void bsp_BeepOn(void);
void bsp_BeepOff(void);
void bsp_BeepToggle(void);
uint8_t bsp_IsBeepOn(void);

#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
