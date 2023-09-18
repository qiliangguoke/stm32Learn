/*
*********************************************************************************************************
*
*	ģ������ : �ж�ģ��
*	�ļ����� : bsp_exti.c
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/
#include "bsp_exti.h"

void KEY_IO_Init(void);//IO��ʼ��
void EXTI_KEY_Init(void);//�жϳ�ʼ��
/*
*********************************************************************************************************
*	�� �� ��: bsp_InitKeyEXTI
*	����˵��: �����жϰ���
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitKeyEXTI(void)
{
	KEY_IO_Init();
	EXTI_KEY_Init();

}

/*
*********************************************************************************************************
*	�� �� ��: KEY_IO_Init
*	����˵��: ���ð�����Ӧ��GPIO
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void KEY_IO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*��һ������GPIOʱ��*/
	RCC_APB2PeriphClockCmd(RCC_ALL_KEY,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);/*�ر�JTAG��ʹ��*/
	
	/*�ڶ������������еİ���GPIO*/
	GPIO_InitStructure.GPIO_Pin = WKUP_GPIO_PIN;/*WKUP�˿�*/
	GPIO_InitStructure.GPIO_Mode = WKUP_GPIO_MODE;/*WKUP�˿�ģʽ*/
	GPIO_Init(WKUP_GPIO_PORT,&GPIO_InitStructure);/*��ʼ��WKUP*/
	
	GPIO_InitStructure.GPIO_Pin = KEY0_GPIO_PIN;/*KEY0�˿�*/
	GPIO_InitStructure.GPIO_Mode = KEY0_GPIO_MODE;/*KEY0�˿�ģʽ*/
	GPIO_Init(KEY0_GPIO_PORT,&GPIO_InitStructure);/*��ʼ��KEY0*/
	
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;/*KEY1�˿�*/
	GPIO_InitStructure.GPIO_Mode = KEY1_GPIO_MODE;/*KEY1�˿�ģʽ*/
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStructure);/*��ʼ��KEY1*/
	
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;/*KEY2�˿�*/
	GPIO_InitStructure.GPIO_Mode = KEY2_GPIO_MODE;/*KEY2�˿�ģʽ*/
	GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStructure);/*��ʼ��KEY2*/
	
}
/*
*********************************************************************************************************
*	�� �� ��: EXTI_KEY_Init(void)
*	����˵��: �����еİ������ó��ⲿ�жϴ�����ʽ
*	��    �Σ���
*	�� �� ֵ: ��
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
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;/*�����ش���*/
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;/**/
	EXTI_Init(&EXTI_InitStructure);/*���� EXTI_InitStruct ��ָ���Ĳ�����ʼ������ EXTI �Ĵ���*/
	
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
	
/*/* �ж����ȼ����� ������ȼ� ����һ��Ҫ�ֿ��������жϣ����ܹ��ϲ���һ����������*/
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
*	�� �� ��: EXTI0_IRQHandler
*	����˵��: �ⲿ�жϷ������
*	��    �Σ���
*	�� �� ֵ: ��
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
*	�� �� ��: EXTI4_IRQHandler
*	����˵��: �ⲿ�жϷ������
*	��    �Σ���
*	�� �� ֵ: ��
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
*	�� �� ��: EXTI3_IRQHandler
*	����˵��: �ⲿ�жϷ������
*	��    �Σ���
*	�� �� ֵ: ��
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
*	�� �� ��: EXTI2_IRQHandler
*	����˵��: �ⲿ�жϷ������
*	��    �Σ���
*	�� �� ֵ: ��
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
