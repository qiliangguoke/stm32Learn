#include "bsp.h"

/*
***************************************************************************
*          �� �� ���� bsp_InitWwdg
*          ����˵���� ���ڿ��Ź�����
*          ��   �Σ���
*          �� �� ֵ���� 
***************************************************************************
*/
void bsp_InitWwdgNVIC(FunctionalState NewState);

void bsp_InitWwdg(uint8_t _ucTreg,uint8_t _ucWreg,uint32_t WWDG_Prescaler)
{
	/*���ϵͳ�Ƿ�Ӵ��ڿ��Ź���λ�лָ�*/
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST)!=RESET)
	{
		/*�����λ��־*/
		RCC_ClearFlag();
		printf("**���ڿ��Ź���λ******************\r\n");
	}
	else
	{
		/*WWDGRST��־û������*/
		printf("**���Ǵ��ڿ��Ź���λ���������ϵ縴λ�����ֶ�������λ*************\r\n");
	}
	
	/*ʹ��WWDGʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	
	/*
	���ڿ��Ź���Ƶ����
	����ѡ��WWDG_Prescaler_8
	*/
	WWDG_SetPrescaler(WWDG_Prescaler);
	
	/*
	���ô���ֵ��_ucWreg,�û�������С��_ucWreg�Ҵ���0x40ʱˢ�¼�������
	Ҫ�������ϵͳ��λ
	*/
	WWDG_SetWindowValue(_ucWreg);
	
	/*
	ʹ��WWDG�����ü�����
	��������_ucTreg=127 8��Ƶʱ����ô���ʱ�����=~910us*64=58.24ms
	*/
	WWDG_Enable(_ucTreg);
	
	/*���EWI�жϱ�־*/
	WWDG_ClearFlag();
	
	/*����WWDG��NVIC*/
	bsp_InitWwdgNVIC(ENABLE);
	
	/*ʹ��EW�ж�*/
	WWDG_EnableIT();
}

/*
***************************************************************************
*          �� �� ����bsp_InitWwdgNVIC
*          ����˵�������ڿ��Ź�NVIC����
*          ��   �Σ�FunctionalState NewState
*          �� �� ֵ���� 
***************************************************************************
*/
void bsp_InitWwdgNVIC(FunctionalState NewState)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel=WWDG_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=NewState;
	NVIC_Init(&NVIC_InitStructure);

}

/*
***************************************************************************
*          �� �� ����WWDG_IRQHandler
*          ����˵�������ڿ��Ź������жϷ������
*          ��   �Σ���
*          �� �� ֵ���� 
***************************************************************************
*/

void WWDG_IRQHandler(void)
{
	/*�ر�ע�⣬���������ִ��˳���ܷ��ˣ����˾ͳ�������*/
	/*���EWI��־*/
	if(WWDG_GetFlagStatus()!=RESET)
	{
		/*�����λ��־*/
		WWDG_ClearFlag();
		
		/*���´��ڿ��Ź�������*/
		WWDG_SetCounter(127);
	}
}
