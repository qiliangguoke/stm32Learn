#include "bsp.h"

void bsp_InitBeep(void)

{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_ALL_BEEP,ENABLE);
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	
	GPIO_InitStructure.GPIO_Pin=BEEP_GPIO_PIN;
	GPIO_Init(BEEP_GPIO_PORT,&GPIO_InitStructure);
}

void bsp_BeepOn(void)
{
	BEEP=1;
}

void bsp_BeepOff(void){
	BEEP=0;
}
void bsp_BeepToggle(void){
	BEEP_GPIO_PORT->ODR^=BEEP_GPIO_PIN;
}
uint8_t bsp_IsBeepOn(void)

{
		if((BEEP_GPIO_PORT->ODR & BEEP_GPIO_PIN)==BEEP_GPIO_PIN)
		{
			return 1;
		}
		return 0;
}
