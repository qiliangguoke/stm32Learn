#ifndef _BSP_28BYJ48_H_
#define _BSP_28BYJ48_H_

///////////////////////////////////////
/* 头文件包含区 */
#include "sys.h"
///////////////////////////////////////
/* 宏定义区域 */

//IO 操作函数
#define SM28BYJ48_A         SM28BYJ48_A_FUN_OUT(SM28BYJ48_A_PIN_ID) //SM28BYJ48_A
#define SM28BYJ48_B         SM28BYJ48_B_FUN_OUT(SM28BYJ48_B_PIN_ID) //SM28BYJ48_B
#define SM28BYJ48_C         SM28BYJ48_C_FUN_OUT(SM28BYJ48_C_PIN_ID) //SM28BYJ48_C
#define SM28BYJ48_D         SM28BYJ48_D_FUN_OUT(SM28BYJ48_D_PIN_ID) //SM28BYJ48_D


typedef struct
{
		uint8_t ucSpeed; /* 电机速度 */
		uint8_t ucDir; /* 电机方向 0 正转， 1 反转 2 停止 */
		uint8_t ucStop; /* 0 运行， 1 停止 */
}MOTOR_T;
/* 步进电机导通控制定义 */
enum
{
		SM_OFF = 0, /* A B C D 相均不导通 */
		SM_A, /* A 相导通 */
		SM_B, /* B 相导通 */
		SM_C,
		SM_D,
		SM_AB, /* AB 相导通 */
		SM_BC,
		SM_CD,
		SM_DA
};

///////////////////////////////////////
/* 外部变量申明区 */

///////////////////////////////////////
/* 函数申明区 */

///////////////////////////////////////
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/