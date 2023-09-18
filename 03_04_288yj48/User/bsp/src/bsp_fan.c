#include "bsp.h"

/*
*********************************************************************************************************
*	函 数 名:
*	功能说明: 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_FanOff(uint8_t _no){
	
	
	if(_no==1){
		
		FAN0=0;
	}
	else if(_no==2)
	{
		FAN1=0;
	}
}
/*
*********************************************************************************************************
*	函 数 名:
*	功能说明: 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_InitFan(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;//实例化结构体
	
	RCC_APB2PeriphClockCmd(RCC_ALL_FAN,ENABLE);//使能 GPIO 端口时钟 
	
	
	bsp_FanOff(1);
	bsp_FanOff(2);
//关闭FAN1
	
	/* 主要通过操作寄存器 BSRR 和 BRR 两个寄存器来操作 ODR 寄
	存器，这样的好处，是防止使用“读-修改-写”的方式来操作寄存器时发生中断，造成数据错
	误。 */
	//GPIO_SetBits(FAN0_GPIO_PORT,FAN0_GPIO_PIN);  		// 参数：大端口 小端口号
	//GPIO_SetBits(FAN1_GPIO_PORT,FAN1_GPIO_PIN);
	
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;		//GPIO 端口速度为 50MHz
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;		//推挽输出模式
	
	GPIO_InitStructure.GPIO_Pin=FAN0_GPIO_PIN;			/* 设置 FAN0 端口 I/O */
	GPIO_Init(FAN0_GPIO_PORT, &GPIO_InitStructure);		/* 配置 FAN0 */
	
	GPIO_InitStructure.GPIO_Pin=FAN1_GPIO_PIN;			/* 设置 FAN1 端口 I/O */
	GPIO_Init(FAN1_GPIO_PORT, &GPIO_InitStructure);		/* 配置 FAN1 */
}
/*
*********************************************************************************************************
*	函 数 名:
*	功能说明: 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_FanOn(uint8_t _no){
	
	if(_no==1)
	{	
		FAN0=1;
	}
	else if(_no==2)
	{
		FAN1=1;
	}
}
/*
*********************************************************************************************************
*	函 数 名:
*	功能说明: 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_FanToggle(uint8_t _no){
	
	if(_no==1)
	{
		
		FAN0_GPIO_PORT->ODR ^=FAN0_GPIO_PIN;
		
	}
	else if(_no==2)
	{
		FAN1_GPIO_PORT->ODR ^=FAN1_GPIO_PIN;
	}
}

/*
*********************************************************************************************************
*	函 数 名:
*	功能说明: 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
uint8_t bsp_IsFanOn(uint8_t _no)
{
	if(_no ==1)
	{
		if((FAN0_GPIO_PORT->ODR & FAN1_GPIO_PIN)==FAN1_GPIO_PIN)
		{
			return 1;
		}
		return 0;
		
	}
	else if(_no ==2)
	{
		if((FAN1_GPIO_PORT->ODR&FAN1_GPIO_PIN)==FAN0_GPIO_PIN)
		{
			return 1;
		}
			return 0;
	}
	return 0;
}