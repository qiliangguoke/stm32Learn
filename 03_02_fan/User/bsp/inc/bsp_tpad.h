#ifndef __BSP_TPAD_H
#define __BSP_TPAD_H

///////////////////////////////////////
/* 头文件包含区 */
#include "sys.h"

///////////////////////////////////////
/* 宏定义区域 */

////*******通用定时器 TIM 参数定义，只限 TIM2、3、4、5***********/
//// 当使用不同的定时器的时候，对应的 GPIO 是不一样的，这点要注意
//// 我们这里默认使用 TIM5

#define TIMx_CAP_TIM TIM5
#define TIMx_CAP_TIM_APBxClock_FUN RCC_APB1PeriphClockCmd
#define TIMx_CAP_TIM_CLK RCC_APB1Periph_TIM5
#define TPAD_ARR_MAX_VAL 0XFFFF
#define TIMx_CAP_TIM_PSC (6-1) //以 12M 的频率计数

// TIM 输入捕获通道 GPIO 相关宏定义

#define TIMx_CAP_TIM_CH_GPIO_CLK RCC_APB2Periph_GPIOA
#define TIMx_CAP_TIM_CH_PORT GPIOA
#define TIMx_CAP_TIM_CH_PIN GPIO_Pin_1
#define TIMx_CAP_TIM_CHANNEL_x TIM_Channel_2

// 中断相关宏定义

#define TIMx_CAP_TIM_IT_CCx TIM_IT_CC2
#define TIMx_CAP_TIM_IT_UPDATE TIM_IT_Update
#define TIMx_CAP_TIM_IRQ TIM5_IRQn
#define TIMx_CAP_TIM_INT_FUN TIM5_IRQHandler

// 获取捕获寄存器值函数宏定义
#define TIMx_CAP_TIM_GetCapturex_FUN TIM_GetCapture2

// 捕获信号极性函数宏定义
#define TIMx_CAP_TIM_OCxPolarityConfig_FUN TIM_OC2PolarityConfig

//触摸的门限值,也就是必须大于 tpad_default_val+TPAD_GATE_VAL,才认为是有效触摸.
#define TPAD_GATE_VAL 100

///////////////////////////////////////
/* 外部变量申明区 */

///////////////////////////////////////
/* 函数申明区 */

uint8_t bsp_TpadInit(void); /* 触摸按键初始化 */
uint8_t bsp_TpadScan(void); /* 触摸按键扫描 */

///////////////////////////////////////
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
