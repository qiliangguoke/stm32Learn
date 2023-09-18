#include "bsp.h"

/*
*********************************************************************************************************
*	函 数 名:bsp_InitRelay
*	功能说明: 初始化继电器
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_InitRelay(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* 打开 GPIO 时钟 */
	RCC_APB2PeriphClockCmd(RCC_ALL_RELAY, ENABLE);
	/*
	配置所有的 RELAY GPIO 为推挽输出模式
	由于将 GPIO 设置为输出时，GPIO 输出寄存器的值缺省是 0，因此会驱动 LED 点亮.
	这是我不希望的，因此在改变 GPIO 为输出前，先关闭 RELAY
	*/
	bsp_RelayOff(1);	//关闭所有灯
	bsp_RelayOff(2);
	bsp_RelayOff(3);
	bsp_RelayOff(4);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; /* 推挽输出模式 */
	GPIO_InitStructure.GPIO_Pin = RELAY1_GPIO_PIN; /* RELAY1 端口 */
	
	GPIO_Init(RELAY1_GPIO_PORT, &GPIO_InitStructure); /* 初始化 RELAY1 */
	GPIO_InitStructure.GPIO_Pin = RELAY2_GPIO_PIN; /* RELAY2 端口 */
	
	GPIO_Init(RELAY2_GPIO_PORT, &GPIO_InitStructure); /* 初始化 RELAY2 */
	GPIO_InitStructure.GPIO_Pin = RELAY3_GPIO_PIN; /* RELAY3 端口 */
	
	GPIO_Init(RELAY3_GPIO_PORT, &GPIO_InitStructure); /* 初始化 RELAY3 */
	
	GPIO_InitStructure.GPIO_Pin = RELAY4_GPIO_PIN; /* RELAY4 端口 */
	GPIO_Init(RELAY4_GPIO_PORT, &GPIO_InitStructure); /* 初始化 RELAY4 */
}
/*
*********************************************************************************************************
*	函 数 名:bsp_RelayOn
*	功能说明: 打开继电器
*	形    参：打开所用继电器
*	返 回 值: 
********************************************************************************************************
*/
void bsp_RelayOn(uint8_t _no)
{
	/* 高电平点亮，低电平关闭 */
	if (_no == 1)
	{
		RELAY1 = 1;
	}
	else if (_no == 2)
	{
		RELAY2 = 1;
	}
	else if (_no == 3)
	{
		RELAY3 = 1;
	}
	else if (_no == 4)
	{
		RELAY4 = 1;
	}
}
/*
*********************************************************************************************************
*	函 数 名:bsp_RelayOff
*	功能说明: 关闭继电器
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_RelayOff(uint8_t _no)
{
	if (_no == 1)
	{
		RELAY1 = 0;
	}
	else if (_no == 2)
	{
		RELAY2 = 1;
	}
	else if (_no == 3)
	{
		RELAY3 = 0;
	}
	else if (_no == 4)
	{
		RELAY4 = 0;
	}
}
/*
*********************************************************************************************************
*	函 数 名:bsp_RelayToggle
*	功能说明: 反转继电器
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_RelayToggle(uint8_t _no)
{
	if (_no == 1)
	{
		RELAY1_GPIO_PORT->ODR ^= RELAY1_GPIO_PIN;
	}
	else if (_no == 2)
	{
		RELAY2_GPIO_PORT->ODR ^= RELAY2_GPIO_PIN;
	}
	else if (_no == 3)
	{
		RELAY3_GPIO_PORT->ODR ^= RELAY3_GPIO_PIN;
	}
	else if (_no == 4)
	{
		RELAY4_GPIO_PORT->ODR ^= RELAY4_GPIO_PIN;
	}
}
/*
*********************************************************************************************************
*	函 数 名:bsp_IsRelayOn
*	功能说明: 判断继电器是否打开
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
uint8_t bsp_IsRelayOn(uint8_t _no)
{
	if (_no == 1)
	{
		if ((RELAY1_GPIO_PORT->ODR & RELAY1_GPIO_PIN) == RELAY1_GPIO_PIN)
		{
			return 1;
		}
		return 0;
	}
	else if (_no == 2)
	{
		if ((RELAY2_GPIO_PORT->ODR & RELAY2_GPIO_PIN) == RELAY2_GPIO_PIN)
		{
			return 1;
		}
			return 0;
	}
	else if (_no == 3)
	{
		if ((RELAY3_GPIO_PORT->ODR & RELAY3_GPIO_PIN) == RELAY3_GPIO_PIN)
		{
			return 1;
		}
		return 0;
	}
	else if (_no == 4)
	{
		if ((RELAY4_GPIO_PORT->ODR & RELAY4_GPIO_PIN) == RELAY4_GPIO_PIN)
		{
			return 1;
		}
		return 0;
	}
	return 0;
}
