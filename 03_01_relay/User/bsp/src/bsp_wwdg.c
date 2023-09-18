#include "bsp.h"
/*
*********************************************************************************************************
*
*	模块名称 : 模块
*	文件名称 : bsp_wwdg.c
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*	函 数 名:bsp_InitWwdg
*	功能说明: 窗口看门狗配置
*	形    参：
*				_ucTreg : T[6:0],计数器值 范围 0x40 到 0x7F 
*				 _ucWreg : W[6:0],窗口值 必须小于 0x80
*				 WWDG_Prescaler : 窗口看门狗分频 PCLK1 = 36MHz
*				 WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
*				 WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
*				WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
*				WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
**	返 回 值: 
*********************************************************************************************************
*/
void bsp_InitWwdg(uint8_t _ucTreg, uint8_t _ucWreg, uint32_t WWDG_Prescaler)
{
	/* 检测系统是否从窗口看门狗复位中恢复 */
	
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) != RESET)
	{ 
		/* 清除复位标志 */
		RCC_ClearFlag();
		printf("**窗口看门狗复位************************\r\n");
	}
	else	
	{
		/* WWDGRST 标志没有设置 */
		printf("**不是窗口看门狗复位，可能是上电复位或者手动按键复位********\r\n");
	}
	
	/* 使能 WWDG 时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	/* 
	 窗口看门狗分频设置：
	 比如选择 WWDG_Prescaler_8
	 (PCLK1 (36MHz)/4096)/8 = 1099 Hz (~910us) 
	*/
	WWDG_SetPrescaler(WWDG_Prescaler);
	
	/* 
	设置窗口值是_ucWreg，用户必须在小于_ucWreg 且大于 0x40 时
	刷新计数器，要不会造成系统复位。
	 */
	WWDG_SetWindowValue(_ucWreg);
	
	/* 
	使能 WWDG，设置计数器
	比如设置_ucTreg=127 8 分频时，那么溢出时间就是= ~910 us * 64 = 58.24 ms 
	窗口看门狗的刷新时间段是: 
			~910 * (127-80) = 42.7ms < 刷新窗口看门狗 < ~910 * 64 = 58.2ms
	*/
	WWDG_Enable(_ucTreg);
	
	/* 清除 EWI 中断标志 */
	WWDG_ClearFlag();
	
	/* 设置 WWDG 的 NVIC */
	bsp_InitWwdgNVIC(ENABLE);
	
	/* 使能 EW 中断 */
	WWDG_EnableIT();
	 
}
/*
*********************************************************************************************************
*	函 数 名:bsp_InitWwdgNVIC
*	功能说明:窗口看门狗 NVIC 配置
*	形    参：FunctionalState NewState:ENABLE , DISABLE
*	返 回 值: 
********************************************************************************************************
*/
void bsp_InitWwdgNVIC(FunctionalState NewState)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
	NVIC_Init(&NVIC_InitStructure);
}
/*
*********************************************************************************************************
*	函 数 名:WWDG_IRQHandler
*	功能说明:窗口看门狗调用中断服务程序。 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void WWDG_IRQHandler(void)
{
	/*特别注意，下面两句的执行顺序不能反了，反了就出问题了*/
	/* 清除 EWI 标志 */
	if (WWDG_GetFlagStatus() != RESET)
	{ 
		/* 清除复位标志 */
		WWDG_ClearFlag();
		/* 更新窗口看门狗计数器 */
		WWDG_SetCounter(127);
	}
}
