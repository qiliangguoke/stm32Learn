#include "bsp.h"
/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : bsp_wwdg.c
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*	�� �� ��:bsp_InitWwdg
*	����˵��: ���ڿ��Ź�����
*	��    �Σ�
*				_ucTreg : T[6:0],������ֵ ��Χ 0x40 �� 0x7F 
*				 _ucWreg : W[6:0],����ֵ ����С�� 0x80
*				 WWDG_Prescaler : ���ڿ��Ź���Ƶ PCLK1 = 36MHz
*				 WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
*				 WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
*				WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
*				WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
**	�� �� ֵ: 
*********************************************************************************************************
*/
void bsp_InitWwdg(uint8_t _ucTreg, uint8_t _ucWreg, uint32_t WWDG_Prescaler)
{
	/* ���ϵͳ�Ƿ�Ӵ��ڿ��Ź���λ�лָ� */
	
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) != RESET)
	{ 
		/* �����λ��־ */
		RCC_ClearFlag();
		printf("**���ڿ��Ź���λ************************\r\n");
	}
	else	
	{
		/* WWDGRST ��־û������ */
		printf("**���Ǵ��ڿ��Ź���λ���������ϵ縴λ�����ֶ�������λ********\r\n");
	}
	
	/* ʹ�� WWDG ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	/* 
	 ���ڿ��Ź���Ƶ���ã�
	 ����ѡ�� WWDG_Prescaler_8
	 (PCLK1 (36MHz)/4096)/8 = 1099 Hz (~910us) 
	*/
	WWDG_SetPrescaler(WWDG_Prescaler);
	
	/* 
	���ô���ֵ��_ucWreg���û�������С��_ucWreg �Ҵ��� 0x40 ʱ
	ˢ�¼�������Ҫ�������ϵͳ��λ��
	 */
	WWDG_SetWindowValue(_ucWreg);
	
	/* 
	ʹ�� WWDG�����ü�����
	��������_ucTreg=127 8 ��Ƶʱ����ô���ʱ�����= ~910 us * 64 = 58.24 ms 
	���ڿ��Ź���ˢ��ʱ�����: 
			~910 * (127-80) = 42.7ms < ˢ�´��ڿ��Ź� < ~910 * 64 = 58.2ms
	*/
	WWDG_Enable(_ucTreg);
	
	/* ��� EWI �жϱ�־ */
	WWDG_ClearFlag();
	
	/* ���� WWDG �� NVIC */
	bsp_InitWwdgNVIC(ENABLE);
	
	/* ʹ�� EW �ж� */
	WWDG_EnableIT();
	 
}
/*
*********************************************************************************************************
*	�� �� ��:bsp_InitWwdgNVIC
*	����˵��:���ڿ��Ź� NVIC ����
*	��    �Σ�FunctionalState NewState:ENABLE , DISABLE
*	�� �� ֵ: 
********************************************************************************************************
*/
void bsp_InitWwdgNVIC(FunctionalState NewState)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
	NVIC_Init(&NVIC_InitStructure);
}
/*
*********************************************************************************************************
*	�� �� ��:WWDG_IRQHandler
*	����˵��:���ڿ��Ź������жϷ������ 
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
void WWDG_IRQHandler(void)
{
	/*�ر�ע�⣬���������ִ��˳���ܷ��ˣ����˾ͳ�������*/
	/* ��� EWI ��־ */
	if (WWDG_GetFlagStatus() != RESET)
	{ 
		/* �����λ��־ */
		WWDG_ClearFlag();
		/* ���´��ڿ��Ź������� */
		WWDG_SetCounter(127);
	}
}
