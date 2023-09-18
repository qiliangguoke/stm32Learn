#include "bsp.h"

/*
*********************************************************************************************************
*
*	模块名称 : 模块
*	文件名称 : bsp_iwdg.c
*	说    明 : 这是看门狗的配置文件
*	修改记录 :
*		版本号  日期   2023-5-10     作者 郭文龙    说明
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*	函 数 名:bsp_InitIwdg
*	功能说明: 独立看门狗配置函数
*	形    参：	_uIWDGPrer：IWDG_Prescaler_8
							IWDG_Prescaler_4
							IWDG_Prescaler_16
							IWDG_Prescaler_32
							IWDG_Prescaler_64
							IWDG_Prescaler_128
							IWDG_Prescaler_256
							_ulIWDGRlr:0---0xfff
				
				
*	返 回 值: 
********************************************************************************************************
*/
void bsp_InitIwdg(uint8_t _uIWDGPrer,uint32_t _ulIWDGRlr)
{
/*检测系统是否从独立看门狗复位中恢复*/
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
		/*清除复位标志*/
		RCC_ClearFlag();
		printf("**独立看门狗复位************************\r\n");
	}
	else
	{	
		/*标志没有设置*/
		printf("**不是独立看门狗复位，可能是上电复位或者手动按键复位********\r\n");
	}
	
	
	/*使能 LSI*/
	RCC_LSICmd(ENABLE);
	
	
	/* 等待直到 LSI 就绪 */
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{}
		
	/*写入 0x5555 表示允许访问 IWDG_PR 和 IWDG_RLR 寄存器 */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	//IWDG_WriteAccess_Enable为0x5555	
	/*LSI 预分频*/
	IWDG_SetPrescaler(_uIWDGPrer);		
		/*设置重装载值*/
	IWDG_SetReload(_ulIWDGRlr);
		
	/*重载 IWDG 计数*/
	IWDG_ReloadCounter();
	/*使能 IWDG (LSI oscillator 由硬件使能)*/
	IWDG_Enable();
}
/*
*********************************************************************************************************
*	函 数 名:WDG_Feed
*	功能说明: 喂狗
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void IWDG_Feed(void)
{
	IWDG_ReloadCounter();
}
