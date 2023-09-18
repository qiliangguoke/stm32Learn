#ifndef _BSP_28BYJ48_H_
#define _BSP_28BYJ48_H_

///////////////////////////////////////
/* 头文件包含区 */
#include "sys.h"
///////////////////////////////////////
/* 宏定义区域 */

#define RCC_ALL_SM28BYJ48 				( SM28BYJ48_A_GPIO_CLK | SM28BYJ48_B_GPIO_CLK | SM28BYJ48_C_GPIO_CLK | SM28BYJ48_D_GPIO_CLK )
#define SM28BYJ48_OUT_GPIO_MODE 		GPIO_Mode_Out_PP 			//SM28BYJ48_A_OUT 输入模式
//橙色A相
#define SM28BYJ48_A_GPIO_PIN			GPIO_Pin_7 //FAN1 引脚号
#define SM28BYJ48_A_PIN_ID 				7 //FAN1 引脚序号
#define SM28BYJ48_A_GPIO_PORT 			GPIOC //FAN1 端口号
#define SM28BYJ48_A_GPIO_CLK 			RCC_APB2Periph_GPIOC //FAN1 时钟
#define SM28BYJ48_A_FUN_OUT 			PCout //FAN1 输出端口配置函数

#define SM28BYJ48_A_OUT_ACTIVE_LEVEL				0 						//SM28BYJ48_A 有效电平为低电平
//黄色B相
#define SM28BYJ48_B_GPIO_PIN			GPIO_Pin_6 //FAN1 引脚号
#define SM28BYJ48_B_PIN_ID 				6 //FAN1 引脚序号
#define SM28BYJ48_B_GPIO_PORT 			GPIOC //FAN1 端口号
#define SM28BYJ48_B_GPIO_CLK 			RCC_APB2Periph_GPIOC //FAN1 时钟
#define SM28BYJ48_B_FUN_OUT 			PCout //FAN1 输出端口配置函数
#define SM28BYJ48_B_OUT_ACTIVE_LEVEL				0 						//SM28BYJ48_B 有效电平为低电平
//粉色C相
#define SM28BYJ48_C_GPIO_PIN			GPIO_Pin_5 //FAN1 引脚号
#define SM28BYJ48_C_PIN_ID 				5 //FAN1 引脚序号
#define SM28BYJ48_C_GPIO_PORT 			GPIOC //FAN1 端口号
#define SM28BYJ48_C_GPIO_CLK 			RCC_APB2Periph_GPIOC //FAN1 时钟
#define SM28BYJ48_C_FUN_OUT 			PCout //FAN1 输出端口配置函数
#define SM28BYJ48_C_OUT_ACTIVE_LEVEL				0 						//SM28BYJ48_c 有效电平为低电平
//蓝色D相
#define SM28BYJ48_D_GPIO_PIN			GPIO_Pin_4 //FAN1 引脚号
#define SM28BYJ48_D_PIN_ID 				4 //FAN1 引脚序号
#define SM28BYJ48_D_GPIO_PORT 			GPIOC //FAN1 端口号
#define SM28BYJ48_D_GPIO_CLK 			RCC_APB2Periph_GPIOC //FAN1 时钟
#define SM28BYJ48_D_FUN_OUT 			PCout //FAN1 输出端口配置函数
#define SM28BYJ48_D_OUT_ACTIVE_LEVEL				0 						//SM28BYJ48_D  有效电平为低电平
//IO 操作函数
#define SM28BYJ48_A SM28BYJ48_A_FUN_OUT(SM28BYJ48_A_PIN_ID) //SM28BYJ48_A
#define SM28BYJ48_B SM28BYJ48_B_FUN_OUT(SM28BYJ48_B_PIN_ID) //SM28BYJ48_B
#define SM28BYJ48_C SM28BYJ48_C_FUN_OUT(SM28BYJ48_C_PIN_ID) //SM28BYJ48_C
#define SM28BYJ48_D SM28BYJ48_D_FUN_OUT(SM28BYJ48_D_PIN_ID) //SM28BYJ48_D

///////////////////////////////////////
/* 外部变量申明区 */



/* 定义结构体便于全局变量操作
*/
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
	SM_A=1, /* A 相导通 */
	SM_B=2, /* B 相导通 */
	SM_C=3,
	SM_D=4,
	SM_AB=5, /* AB 相导通 */
	SM_BC=6,
	SM_CD=7,
	SM_DA=8
};

extern MOTOR_T g_tMot; /* 定义全局变量 */
///////////////////////////////////////
/* 函数申明区 */
void bsp_Init_28byj48(void);
void dirction(void);
static void motPowerOn(uint8_t _ucMode);
///////////////////////////////////////
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
