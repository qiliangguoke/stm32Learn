#include "bsp.h"


/*
*********************************************************************************************************
*	函 数 名:
*	功能说明: 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_InitKey(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_ALL_KEY,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	
	
	GPIO_InitStructure.GPIO_Pin=KEY0_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode=KEY0_GPIO_MODE;
	GPIO_Init(KEY0_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=KEY1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode=KEY1_GPIO_MODE;
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=KEY2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode=KEY2_GPIO_MODE;
	GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=WKUP_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode=WKUP_GPIO_MODE;
	GPIO_Init(WKUP_GPIO_PORT,&GPIO_InitStructure);
}

/*
*********************************************************************************************************
*	函 数 名:
*	功能说明: 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/

uint8_t bsp_KeyScan(void){
	
	if(WKUP==WKUP_ACTIVE_LEVEL)
		{
		delay_ms(10);
		if(WKUP==WKUP_ACTIVE_LEVEL){
			while(WKUP==WKUP_ACTIVE_LEVEL);
			return WKUP_NUM;
		}
		else	
		{
			return NOKEY_NUM;
		}
	}
		
	else if(KEY0==KEY0_ACTIVE_LEVEL)
		{
	
		delay_ms(10);
		if(KEY0==KEY0_ACTIVE_LEVEL)
		{
			while(KEY0==KEY0_ACTIVE_LEVEL);
			return KEY0_NUM;
		}
		else
		{
			return NOKEY_NUM;
		}
	}
	else if(KEY1==KEY1_ACTIVE_LEVEL)
	{
		delay_ms(10);
		if(KEY1==KEY1_ACTIVE_LEVEL)
		{
			while(KEY1==KEY1_ACTIVE_LEVEL);
			return KEY1_NUM;
		}
		else
		{
			return NOKEY_NUM;
		}
	}
	else if(KEY2==KEY2_ACTIVE_LEVEL)
	{
		delay_ms(10);
		if(KEY2==KEY2_ACTIVE_LEVEL)
		{
			while(KEY2==KEY2_ACTIVE_LEVEL);
			return KEY2_NUM;
		}
		else
		{
			return NOKEY_NUM;
		}
	}
	
	return NOKEY_NUM;
}
