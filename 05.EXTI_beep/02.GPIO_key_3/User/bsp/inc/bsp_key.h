/*
*********************************************************************************************************
*
*	模块名称 : 模块
*	文件名称 : bsp_key.h
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    xxx-xx-xx
*
*
*********************************************************************************************************
*/
#ifndef __bsp_key_H
#define __bsp_key_H

///////////////////////////////////////
/* 头文件包含区 */
#include "sys.h"
///////////////////////////////////////
/* 宏定义区域 */
#define RCC_ALL_KEY  (WKUP_GPIO_CLK|KEY0_GPIO_CLK|KEY1_GPIO_CLK|KEY2_GPIO_CLK)

#define WKUP_GPIO_PIN       GPIO_Pin_0       		 //
#define WKUP_PIN_ID         0                		 //WKUP引脚序号
#define WKUP_GPIO_PORT      GPIOA            		 //WKUP端口号
#define WKUP_GPIO_CLK       RCC_APB2Periph_GPIOA    //WKUP时钟
//#define WKUP_FUN_OUT        PAout                    //WKUP输出端口配置函数
#define WKUP_FUN_IN         PAin                     //WKUP输入端口配置函数
#define WKUP_GPIO_MODE      GPIO_Mode_IPD            //WKUP端口输入模式
#define WKUP_ACTIVE_LEVEL   1                        //WKUP按键有效电平为高电平

//////
#define KEY0_GPIO_PIN       GPIO_Pin_4                //KEY0引脚号
#define KEY0_PIN_ID         4                         //KEY0引脚序号
#define KEY0_GPIO_PORT      GPIOE                     //KEY0端口号
#define KEY0_GPIO_CLK       RCC_APB2Periph_GPIOE      //KEY0时钟
#define KEY0_FUN_OUT        PEout                     //KEY0输出端口号配置函数
#define KEY0_FUN_IN         PEin                      //KEY0输入端口号配置函数
#define KEY0_GPIO_MODE		GPIO_Mode_IPU             //KEY0端口输入模式
#define KEY0_ACTIVE_LEVEL   0 	                       //KEY0按键有效电平为低电平
//////
#define KEY1_GPIO_PIN       GPIO_Pin_3                //KEY1引脚号
#define KEY1_PIN_ID         3                         //KEY1引脚序号
#define KEY1_GPIO_PORT      GPIOE                     //KEY1端口号
#define KEY1_GPIO_CLK       RCC_APB2Periph_GPIOE      //KEY1时钟
#define KEY1_FUN_OUT        PEout                     //KEY1输出端口号配置函数
#define KEY1_FUN_IN         PEin                      //KEY1输入端口号配置函数
#define KEY1_GPIO_MODE		GPIO_Mode_IPU             //KEY1端口输入模式
#define KEY1_ACTIVE_LEVEL   0 	                       //KEY1按键有效电平为低电平
//////
#define KEY2_GPIO_PIN       GPIO_Pin_2                 //KEY2引脚号
#define KEY2_PIN_ID         2                          //KEY2引脚序号
#define KEY2_GPIO_PORT      GPIOE                      //KEY2端口号
#define KEY2_GPIO_CLK       RCC_APB2Periph_GPIOE       //KEY2时钟
#define KEY2_FUN_OUT        PEout                      //KEY2输出端口号配置函数
#define KEY2_FUN_IN         PEin                       //KEY2输入端口号配置函数
#define KEY2_GPIO_MODE		GPIO_Mode_IPU              //KEY2端口输入模式
#define KEY2_ACTIVE_LEVEL   0 	                       //KEY2按键有效电平为低电平
///////////////////////////
//IO操作函数
#define WKUP               	WKUP_FUN_IN(WKUP_PIN_ID)	//WKUP
#define KEY0                KEY0_FUN_IN(KEY0_PIN_ID)    //KEY0
#define KEY1                KEY1_FUN_IN(KEY1_PIN_ID)    //KEY1
#define KEY2                KEY2_FUN_IN(KEY2_PIN_ID)    //KEY2
//////////////////////////
#define KEY_COUNT			6
/**/
#define WKUP_DOWN			KEY_1_DOWN
#define WKUP_UP				KEY_1_UP
#define WKUP_LONG			KEY_1_LONG

#define KEY0_DOWN			KEY_2_DOWN
#define KEY0_UP				KEY_2_UP
#define KEY0_LONG			KEY_2_LONG

#define KEY1_DOWN			KEY_3_DOWN
#define KEY1_UP				KEY_3_UP
#define KEY1_LONG			KEY_3_LONG

#define KEY2_DOWN			KEY_4_DOWN
#define KEY2_UP				KEY_4_UP
#define KEY2_LONG			KEY_4_LONG

#define SYS_DOWN_WKUP_KEY0			KEY_5_DOWN
#define SYS_UP_WKUP_KEY0			KEY_5_UP
#define SYS_LONG_WKUP_KEY0			KEY_5_LONG

#define SYS_DOWN_KEY0_KEY1			KEY_6_DOWN
#define SYS_UP_KEY0_KEY1			KEY_6_UP
#define SYS_LONG_KEY0_KEY1			KEY_6_LONG

///////////////////////////////////////
/* 外部变量申明区 */
/**/
typedef enum
{
	KID_K1=0,
	KID_K2,
	KID_K3,
	KID_K4,
}KEY_ID_E;
/**/
#define KEY_FILTER_TIME		5
#define KEY_LONG_TIME		100
/**/
typedef struct
{
	/**/
	uint8_t(*IsKeyDownFunc)(void);
	uint8_t		Count;
	uint16_t	LongCount;
	uint16_t	LongTime;
	uint8_t		State;
	uint8_t		RepeatSpeed;
	uint8_t		RepeatCount;
}KEY_T;
/**/

typedef enum
{
	KEY_NONE =0,
	KEY_1_DOWN,
	KEY_1_UP,
	KEY_1_LONG,
	
	KEY_2_DOWN,
	KEY_2_UP,
	KEY_2_LONG,
	
	KEY_3_DOWN,
	KEY_3_UP,
	KEY_3_LONG,
	
	KEY_4_DOWN,
	KEY_4_UP,
	KEY_4_LONG,
	
	KEY_5_DOWN,
	KEY_5_UP,
	KEY_5_LONG,
	
	KEY_6_DOWN,
	KEY_6_UP,
	KEY_6_LONG,
	
}KEY_ENUM;
/**/
#define KEY_FIFO_SIZE    10
typedef struct
{
	uint8_t Buf[KEY_FIFO_SIZE];
	uint8_t Read;
	uint8_t Write;
	uint8_t Read2;
}KEY_FIFO_T;
///////////////////////////////////////
/* 供外部调用的函数声明 */
void bsp_InitKey(void);
void bsp_KeyScan(void);
void bsp_PutKey(uint8_t _KeyCode);
uint8_t bsp_GetKey(void);
uint8_t bsp_GetKey2(void);
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID);
void bsp_SetKeyParam(uint8_t _ucKeyID,uint16_t _LongTime,uint8_t _RepeatSpeed);
void bsp_ClearKey(void);

///////////////////////////////////////
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/


