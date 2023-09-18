#include "bsp.h"


 MOTOR_T  g_tMot; /* ����ȫ�ֱ��� */
/*
***************************************************************************
*          �� �� ���� bsp_Init_28byj48
*          ����˵���� ��ʼ��
*          ��   �Σ���
*          �� �� ֵ���� 
***************************************************************************
*/
void bsp_Init_28byj48(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//ʵ�����ṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = SM28BYJ48_A_GPIO_PIN | SM28BYJ48_B_GPIO_PIN | SM28BYJ48_C_GPIO_PIN |SM28BYJ48_D_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = SM28BYJ48_OUT_GPIO_MODE;
	GPIO_Init(SM28BYJ48_A_GPIO_PORT,&GPIO_InitStructure);
	
}
/*
***************************************************************************
*          �� �� ����ͨ��״̬
*          ����˵����
*          ��   �Σ���
*          �� �� ֵ���� 
***************************************************************************
*/
static void motPowerOn(uint8_t _ucMode)
{
	if (_ucMode == SM_OFF)
	{
	SM28BYJ48_A = 0;
	SM28BYJ48_B = 0;
	SM28BYJ48_C = 0;
	SM28BYJ48_D = 0;
	}
	else if (_ucMode == SM_A)
	{
	SM28BYJ48_A = 1;
	SM28BYJ48_B = 0;
	SM28BYJ48_C = 0;
	SM28BYJ48_D = 0;
	}
	else if (_ucMode == SM_B)
	{
	SM28BYJ48_A = 1;
	SM28BYJ48_B = 1;
	SM28BYJ48_C = 0;
	SM28BYJ48_D = 0;
	}
	else if (_ucMode == SM_C)
	{
	SM28BYJ48_A = 0;
	SM28BYJ48_B = 1;
	SM28BYJ48_C = 0;
	SM28BYJ48_D = 0;
	}else if (_ucMode == SM_D)
	{
	SM28BYJ48_A = 0;
	SM28BYJ48_B = 1;
	SM28BYJ48_C = 1;
	SM28BYJ48_D = 0;
	}
	else if (_ucMode == SM_AB)
	{
	SM28BYJ48_A = 0;
	SM28BYJ48_B = 0;
	SM28BYJ48_C = 1;
	SM28BYJ48_D = 0;
	}
	else if (_ucMode == SM_BC)
	{
	SM28BYJ48_A = 0;
	SM28BYJ48_B = 0;
	SM28BYJ48_C = 1;
	SM28BYJ48_D = 1;
	}	
	else if (_ucMode == SM_CD)
	{
	SM28BYJ48_A = 0;
	SM28BYJ48_B = 0;
	SM28BYJ48_C = 0;
	SM28BYJ48_D = 1;
	}
	else if (_ucMode == SM_DA)
	{
	SM28BYJ48_A = 1;
	SM28BYJ48_B = 0;
	SM28BYJ48_C = 0;
	SM28BYJ48_D = 1;
	}	
}
/*
***************************************************************************
*          �� �� �������ִ�к���
*          ����˵����
*          ��   �Σ���
*          �� �� ֵ���� 
***************************************************************************
*/
void dirction(void)
{
	uint8_t i;
//	
//	for(i=0;i<9;i++)
//	{
//		motPowerOn(i);
//		delay_ms(1);
//	}
	
	for(i=8;i>0;i--)
	{
		motPowerOn(i);
		delay_ms(1);
	}
}