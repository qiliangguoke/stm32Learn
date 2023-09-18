#include "bsp.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/*
*********************************************************************************************************
*	�� �� ��bsp_LedOff
*	����˵��: �жϹ��Ǹ���
*	��    �Σ���һ���Ƶڶ�����
*	�� �� ֵ: ��
********************************************************************************************************
*/
void bsp_LedOff(uint8_t _no){
	
	
	if(_no==1){
		
		LED0=1;
	}
	else if(_no==2)
	{
		LED1=1;
	}
}



/*
*********************************************************************************************************
*	�� �� ��: bsp_InitLed(void)
*	����˵��: ��ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
********************************************************************************************************
*/
void bsp_InitLed(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;//ʵ�����ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_ALL_LED,ENABLE);
	
	
	bsp_LedToggle(1);
	bsp_LedToggle(2);
//�ر�led1
	
	
	GPIO_SetBits(LED0_GPIO_PORT,LED0_GPIO_PIN);  // ��������˿� С�˿ں�
	GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);
	
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//�������ģʽ
	
	GPIO_InitStructure.GPIO_Pin=LED0_GPIO_PIN;
	GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=LED1_GPIO_PIN;
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
}


/*
*********************************************************************************************************
*	�� �� ��:bsp_LEdOn
*	����˵��: ����
*	��    �Σ�uint8_t
*	�� �� ֵ: ��
********************************************************************************************************
*/
void bsp_LedOn(uint8_t _no){
	
	if(_no==1)
	{	
		LED0=0;
	}
	else if(_no==2)
	{
		LED1=0;
	}
}
/*
*********************************************************************************************************
*	�� �� ��:bsp_LedToggle
*	����˵��: ��ת
*	��    �Σ�uint8_t
*	�� �� ֵ: ��
********************************************************************************************************
*/
void bsp_LedToggle(uint8_t _no){
	
	if(_no==1)
	{
		
		LED0_GPIO_PORT->ODR ^=LED0_GPIO_PIN;
		
	}
	else if(_no==2)
	{
		LED1_GPIO_PORT->ODR ^=LED1_GPIO_PIN;
	}
}
/*
*********************************************************************************************************
*	�� �� ��:bsp_IsLedOn
*	����˵��: ��ѯ���״̬
*	��    �Σ�uint8_t
*	�� �� ֵ: uint8_t
********************************************************************************************************
*/
uint8_t bsp_IsLedOn(uint8_t _no)
{
	if(_no ==1)
	{
		if((LED0_GPIO_PORT->ODR & LED1_GPIO_PIN)==LED1_GPIO_PIN)
		{
			return 1;
		}
		return 0;
		
	}
	else if(_no ==2)
	{
		if((LED1_GPIO_PORT->ODR&LED1_GPIO_PIN)==LED0_GPIO_PIN)
		{
			return 1;
		}
			return 0;
	}
	return 0;
}
