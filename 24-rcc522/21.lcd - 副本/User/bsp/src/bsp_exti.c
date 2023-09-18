/*
*********************************************************************************************************
*
*	模块名称 : 中断模块
*	文件名称 : bsp_exti.C
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
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);/*关闭JTAG，使能SWD，可以用SWD模式调试*/
	
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
	/*使能AFIO时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	/*连接EXTI Line0到PA0引脚*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	/*连接EXTI Line2到PE2引脚*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
	/*连接EXTI Line3到PE3引脚*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	/*连接EXTI Line4到PE4引脚*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
	
	/*配置EXTI LineXXX*/
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;/*WKUP*/
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;/*上升沿触发*/
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);/*根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器*/
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;/*KEY0*/
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;/*下降沿触发*/
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);/*根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器*/
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line3;/*KEY1*/
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;/*下降沿触发*/
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);/*根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器*/
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;/*KEY2*/
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;/*下降沿触发*/
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);/*根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器*/
	
/*中断优先级配置 最低优先级 这里一定要分开的设置中断，不能够合并到一个里面设置*/
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
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)/*判断对应中断线上是否有中断产生*/
	{
		if(WKUP==WKUP_ACTIVE_LEVEL)
		{
			bsp_BeepToggle();/*翻转蜂鸣器状态*/
		}
		EXTI_ClearITPendingBit(EXTI_Line0);/*清楚中断标志位*/
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
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)/*判断对应中断线上是否有中断产生*/
	{
		if(KEY0==KEY0_ACTIVE_LEVEL)
		{
			bsp_LedToggle(1);/*翻转DS0状态*/
		}
		EXTI_ClearITPendingBit(EXTI_Line4);/*清楚中断标志位*/
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
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)/*判断对应中断上是否有中断产生*/
	{
		if(KEY1==KEY1_ACTIVE_LEVEL)
		{
			bsp_LedToggle(2);/*翻转灯DS1状态*/
		}
		EXTI_ClearITPendingBit(EXTI_Line3);/*清楚中断标志位*/
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
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)/*判断对应中断线上是否有中断产生*/
	{
		if(KEY2==KEY2_ACTIVE_LEVEL)
		{
			bsp_LedToggle(1);/*翻转DS0状态*/
			bsp_LedToggle(2);/*翻转DS1状态*/
		}
		EXTI_ClearITPendingBit(EXTI_Line2);/*清楚中断标志位*/
	}
		
}
