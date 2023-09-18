/*
*********************************************************************************************************
*
*	ģ������ : ���������
*	�ļ����� : main.c
*	��    �� : V1.0
*	˵    �� : ��������ӡ�ʹ����systick�ж�ʵ�־�ȷ��ʱ������LEDָʾ����˸Ƶ�ʡ�
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2019-08-02 waroyal  �׷�
*
*	Copyright (C), 2014-2019, �������׵���
*
*********************************************************************************************************
*/

#include "bsp.h"				/* �ײ�Ӳ������ */

/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: c�������
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
int main(void)
{
	uint8_t ucKeyCode;
	/*
		ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f10x.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ��
	*/
	bsp_Init();		/* Ӳ����ʼ�� */

	while(1)
	{
		bsp_Idle();
		
		ucKeyCode=bsp_GetKey();
		if(ucKeyCode>0)
		
		{
			switch(ucKeyCode)
			{
				case WKUP_DOWN:
				{
					bsp_BeepToggle();
				}break;
				
				case KEY0_DOWN:
				{
					bsp_LedToggle(2);
				}break;
				case KEY1_DOWN:
				{
					bsp_LedToggle(2);
				}break;
				case KEY2_DOWN:
				{
					bsp_LedToggle(1);
					bsp_LedToggle(2);
				}break;
				case SYS_DOWN_WKUP_KEY0:
				{
					uint8_t i;
					bsp_LedOff(1);
					bsp_LedOff(2);
					
					for(i=0;i<3;i++)
					{
						bsp_LedOn(1);
						bsp_DelayMS(250);
						bsp_LedOff(1);
						bsp_DelayMS(250);
					}
				}break;
				case SYS_DOWN_KEY0_KEY1:
				{
					uint8_t i;
					bsp_LedOff(1);
					bsp_LedOff(2);
					
					for(i=0;i<3;i++)
					{
						bsp_LedOn(2);
						bsp_DelayMS(250);
						bsp_LedOff(2);
						bsp_DelayMS(250);
					}
				}break;
				default: break;
			}
			
		}
		delay_ms(10);
	}
}

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
