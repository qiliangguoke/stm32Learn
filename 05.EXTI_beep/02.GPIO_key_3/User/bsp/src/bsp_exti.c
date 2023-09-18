/*
*********************************************************************************************************
*
*	模块名称 : 中断模块
*	文件名称 : bsp_exti.c
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/
#include "bsp_exti.h"

void KEY_IO_Init(void);//IO初始化
void EXTI_KEY_Init(void);//中断初始化
/*
*********************************************************************************************************
*	函 数 名: bsp_InitKeyEXTI
*	功能说明: 配置中断按键
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitKeyEXTI(void)
{
	KEY_IO_Init();
	EXTI_KEY_Init();

}

/*
*********************************************************************************************************
*	函 数 名: KEY_IO_Init
*	功能说明: 配置按键对应的GPIO
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void KEY_IO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*第一步：打开GPIO时钟*/
	RCC_APB2PeriphClockCmd(RCC_ALL_KEY,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);/*关闭JTAG，使能*/
	
	/*第二步：配置所有的按键GPIO*/
	GPIO_InitStructure.GPIO_Pin = WKUP_GPIO_PIN;/*WKUP端口*/
	GPIO_InitStructure.GPIO_Mode = WKUP_GPIO_MODE;/*WKUP端口模式*/
	GPIO_Init(WKUP_GPIO_PORT,&GPIO_InitStructure);/*初始化WKUP*/
	
	GPIO_InitStructure.GPIO_Pin = KEY0_GPIO_PIN;/*KEY0端口*/
	GPIO_InitStructure.GPIO_Mode = KEY0_GPIO_MODE;/*KEY0端口模式*/
	GPIO_Init(KEY0_GPIO_PORT,&GPIO_InitStructure);/*初始化KEY0*/
	
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;/*KEY1端口*/
	GPIO_InitStructure.GPIO_Mode = KEY1_GPIO_MODE;/*KEY1端口模式*/
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStructure);/*初始化KEY1*/
	
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;/*KEY2端口*/
	GPIO_InitStructure.GPIO_Mode = KEY2_GPIO_MODE;/*KEY2端口模式*/
	GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStructure);/*初始化KEY2*/
	
}
/*
*********************************************************************************************************
*	函 数 名: EXTI_KEY_Init(void)
*	功能说明: 将所有的按键配置成外部中断触发方式
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void EXTI_KEY_Init(void)
{
	EXTI_InitTypeDef 	EXTI_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	/**/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	/**/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	/**/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
	/**/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	/**/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
	
	/**/
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;/**/
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;/**/
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;/*上升沿触发*/
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;/**/
	EXTI_Init(&EXTI_InitStructure);/*根据 EXTI_InitStruct 中指定的参数初始化外设 EXTI 寄存器*/
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;/**/
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;/**/
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;/**/
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;/**/
	EXTI_Init(&EXTI_InitStructure);/**/
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line3;/**/
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;/**/
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;/**/
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;/**/
	EXTI_Init(&EXTI_InitStructure);/**/
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;/**/
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;/**/
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;/**/
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;/**/
	EXTI_Init(&EXTI_InitStructure);/**/
	
/*/* 中断优先级配置 最低优先级 这里一定要分开的设置中断，不能够合并到一个里面设置*/
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
}
/*
*********************************************************************************************************
*	函 数 名: EXTI0_IRQHandler
*	功能说明: 外部中断服务程序
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{
		if(WKUP==WKUP_ACTIVE_LEVEL)
		{
			bsp_BeepToggle();/**/
		}
		EXTI_ClearITPendingBit(EXTI_Line0);/**/
	}
		
}
/*
*********************************************************************************************************
*	函 数 名: EXTI4_IRQHandler
*	功能说明: 外部中断服务程序
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
	{
		if(KEY0==KEY0_ACTIVE_LEVEL)
		{
			bsp_LedToggle(1);/**/
		}
		EXTI_ClearITPendingBit(EXTI_Line4);/**/
	}
		
}
/*
*********************************************************************************************************
*	函 数 名: EXTI3_IRQHandler
*	功能说明: 外部中断服务程序
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
	{
		if(KEY1==KEY1_ACTIVE_LEVEL)
		{
			bsp_LedToggle(2);/**/
		}
		EXTI_ClearITPendingBit(EXTI_Line3);/**/
	}
		
}
/*
*********************************************************************************************************
*	函 数 名: EXTI2_IRQHandler
*	功能说明: 外部中断服务程序
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
	{
		if(KEY2==KEY2_ACTIVE_LEVEL)
		{
			bsp_LedToggle(1);/**/
			bsp_LedToggle(2);/**/
		}
		EXTI_ClearITPendingBit(EXTI_Line2);/**/
	}
		
}
