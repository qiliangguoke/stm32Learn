#include "bsp_exti.h"



void KEY_IO_Init(void);
void EXIT_KEY_Init(void);


/*
*********************************************************************************************************
*	函 数 名:
*	功能说明: 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/

void bsp_InitKeyExit(void)
{
	KEY_IO_Init();
	EXTI_KEY_Init();
}
/*
*********************************************************************************************************
*	函 数 名:
*	功能说明: 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void KEY_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_ALL_KEY,ENABLE);
	GPIO_InitStructure.GPIO_Pin=WKUP_GPIO_PIN;
	GPIO_InitStructure.GPIO_MODE;
	GPIO_Init(WKUP_GPIO_PORT,&GPIO_InitStructure0);
	
	
	GPIO_InitStructure.GPIO_Pin=KEY0_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode=KEY0_GPIO_MODE;
	GPIO_Init(KEY0_GPIO_PORT,&GPIO_InitStructure0);
	
	GPIO_InitStructure.GPIO_Pin=KEY1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode=KEY1_GPIO_MODE;
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStructure0);
	
	
	GPIO_InitStructure.GPIO_Pin=KEY2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode=KEY2_GPIO_MODE;
	GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStructure0);

}

void EXTI_KEY_Init(void)
{
	EXTI_InitTypeDef EXTL_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
	
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0X03;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}