#include "bsp.h"

/*
***************************************************************************
*          �� �� ����bsp_InitIwdg
*          ����˵�����������Ź�ʱ�����ú���
*          ��   �Σ�uIWDGRlr:0 ----0x0FFF
					  _uIWDGPrer:     IWDG_Prescaler_4
											IWDG_Prescaler_8
											IWDG_Prescaler_16
											IWDG_Prescaler_32
											IWDG_Prescaler_64
											IWDG_Prescaler_128
											IWDG_Prescaler_256
*          �� �� ֵ���� 
***************************************************************************
*/

void bsp_InitIwdg(uint8_t _uIWDGPrer,uint32_t _u1IWDGR1r)
{
	/*���ϵͳ�Ƿ�Ӷ������Ź���λ�лظ�*/
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST)!=RESET)
	{
		/*������ı�־*/
		RCC_ClearFlag();
		printf("**�������Ź���λ***************\r\n");
		
	}
	else 
	{
		/* ��־û������*/
		printf("****���Ƕ������Ź���λ���������ϵ縴λ�����ֶ���λ*******\r\n");
	}
	
	/*ʹ��LSI*/
	RCC_LSICmd(ENABLE);
	
	/*�ȴ�ֱ��LSI����*/
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET)
	{}
		
	/*д��0x5555��ʾ�������IWDG_PR��IWDG_RLR�Ĵ���*/
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	/*LSIԤ��Ƶ*/
	IWDG_SetPrescaler(_uIWDGPrer);
	
	/*������װ��ֵ*/
	IWDG_SetReload(_u1IWDGR1r);
		
	/*����IWDG����*/
	IWDG_ReloadCounter();
		
	/*ʹ��IWDG(LSI oscillator ��Ӳ��ʹ��)*/
	IWDG_Enable();
}

/*
***************************************************************************
*          �� �� ����IWDG_Feed
*          ����˵����ι������
*          ��   �Σ���
*          �� �� ֵ���� 
***************************************************************************
*/
void IWDG_Feed(void)
{
	IWDG_ReloadCounter();
}
