#include "bsp.h"

/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : bsp_iwdg.c
*	˵    �� : ���ǿ��Ź��������ļ�
*	�޸ļ�¼ :
*		�汾��  ����   2023-5-10     ���� ������    ˵��
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*	�� �� ��:bsp_InitIwdg
*	����˵��: �������Ź����ú���
*	��    �Σ�	_uIWDGPrer��IWDG_Prescaler_8
							IWDG_Prescaler_4
							IWDG_Prescaler_16
							IWDG_Prescaler_32
							IWDG_Prescaler_64
							IWDG_Prescaler_128
							IWDG_Prescaler_256
							_ulIWDGRlr:0---0xfff
				
				
*	�� �� ֵ: 
********************************************************************************************************
*/
void bsp_InitIwdg(uint8_t _uIWDGPrer,uint32_t _ulIWDGRlr)
{
/*���ϵͳ�Ƿ�Ӷ������Ź���λ�лָ�*/
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
		/*�����λ��־*/
		RCC_ClearFlag();
		printf("**�������Ź���λ************************\r\n");
	}
	else
	{	
		/*��־û������*/
		printf("**���Ƕ������Ź���λ���������ϵ縴λ�����ֶ�������λ********\r\n");
	}
	
	
	/*ʹ�� LSI*/
	RCC_LSICmd(ENABLE);
	
	
	/* �ȴ�ֱ�� LSI ���� */
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{}
		
	/*д�� 0x5555 ��ʾ������� IWDG_PR �� IWDG_RLR �Ĵ��� */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	//IWDG_WriteAccess_EnableΪ0x5555	
	/*LSI Ԥ��Ƶ*/
	IWDG_SetPrescaler(_uIWDGPrer);		
		/*������װ��ֵ*/
	IWDG_SetReload(_ulIWDGRlr);
		
	/*���� IWDG ����*/
	IWDG_ReloadCounter();
	/*ʹ�� IWDG (LSI oscillator ��Ӳ��ʹ��)*/
	IWDG_Enable();
}
/*
*********************************************************************************************************
*	�� �� ��:WDG_Feed
*	����˵��: ι��
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
void IWDG_Feed(void)
{
	IWDG_ReloadCounter();
}
