#include "bsp.h"

void bsp_InitBeep(void)

{
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体
	
	RCC_APB2PeriphClockCmd(RCC_ALL_BEEP,ENABLE);//打开某些外设对应的时钟
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//设置为推挽输出模式
	
	GPIO_InitStructure.GPIO_Pin=BEEP_GPIO_PIN;//初始化gpio口
	GPIO_Init(BEEP_GPIO_PORT,&GPIO_InitStructure);
}
/*
*********************************************************************************************************
*	函 数 名:bsp_BeepOn
*	功能说明: 打开蜂鸣器
*	形    参：无
*	返 回 值: 无
********************************************************************************************************
*/
void bsp_BeepOn(void)
{
	BEEP=1;//
}
/*
*********************************************************************************************************
*	函 数 名:bsp_BeepOff
*	功能说明: 关闭蜂鸣器
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_BeepOff(void){
	BEEP=0;
}

/*
*********************************************************************************************************
*	函 数 名:bsp_BeepToggle
*	功能说明: 反转蜂鸣器电压
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_BeepToggle(void){
	BEEP_GPIO_PORT->ODR^=BEEP_GPIO_PIN;
}
/*
*********************************************************************************************************
*	函 数 名:bsp_IsBeepOn
*	功能说明: 判断蜂鸣器是否开启
*	形    参：无
*	返 回 值: 1代表开启，0代表关闭
********************************************************************************************************
*/
uint8_t bsp_IsBeepOn(void)

{
		if((BEEP_GPIO_PORT->ODR & BEEP_GPIO_PIN)==BEEP_GPIO_PIN)
		{
			return 1;
		}
		return 0;
}
