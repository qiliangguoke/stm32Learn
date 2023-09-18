/*
*********************************************************************************************************
*
*	ģ������ : BSPģ��(For STM32F103)
*	�ļ����� : bsp.c
*	��    �� : V1.0
*	˵    �� : ����Ӳ���ײ���������ģ������ļ�����Ҫ�ṩ bsp_Init()��������������á��������ÿ��c�ļ������ڿ�
*			  ͷ	���� #include "bsp.h" ���������е���������ģ�顣
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2019-08-02 waroyal  ��ʽ����
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/

#include "bsp.h"


//��bsp_timer�����ʱ�ٰ�װ�����ⲿ����
/*
*********************************************************************************************************
*	�� �� ��: delay_ms
*	����˵��: ��bsp_timer.c�����ʱ����bsp_DelayMS�ٰ�װ�����ⲿ����
*	��    �Σ���bsp_timer.c���bsp_DelayMS
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void delay_ms(uint32_t nms)
{
	bsp_DelayMS(nms);
}
/*
*********************************************************************************************************
*	�� �� ��: delay_us
*	����˵��: ��bsp_timer.c�����ʱ����bsp_DelayUS�ٰ�װ�����ⲿ����
*	��    �Σ���bsp_timer.c���bsp_DelayUS
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void delay_us(uint32_t nus)
{
	bsp_DelayUS(nus);
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_Init
*	����˵��: ��ʼ��Ӳ���豸��ֻ��Ҫ����һ�Ρ��ú�������CPU�Ĵ���������ļĴ�������ʼ��һЩȫ�ֱ�����
*			 ȫ�ֱ�����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Init(void)
{
	/*
		����ST�̼���������ļ��Ѿ�ִ����CPUϵͳʱ�ӵĳ�ʼ�������Բ����ٴ��ظ�����ϵͳʱ�ӡ�
		�����ļ�������CPU��ʱ��Ƶ�ʡ��ڲ�Flash�����ٶȺͿ�ѡ���ⲿSRAM FSMC��ʼ����

		ϵͳʱ��ȱʡ����Ϊ72MHz�������Ҫ���ģ������޸� system_stm32f10x.c �ļ�
	*/

	/* ���ȼ���������Ϊ2 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	bsp_InitLed();		/* ����LED��GPIO�˿� */
	bsp_InitKey();		/*����KEY��GPIO�˿�*/
	bsp_InitBeep();		/*����BEEP��GPIO�˿�*/
	bsp_InitUart1(115200);/*��ʼ������1*/
	bsp_InitTimer();	/* ��ʼ��ϵͳ�δ�ʱ�� (�˺����Ὺ�ж�) */

}

/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer10ms
*	����˵��: �ú���ÿ��10ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ����ʱ��Ҫ���ϸ��
*			������Է��ڴ˺��������磺����ɨ�衢���������п��Ƶȡ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_RunPer10ms(void)
{
	bsp_KeyScan();
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer1ms
*	����˵��: �ú���ÿ��1ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ��Ҫ�����Դ���������
*			 ���Է��ڴ˺�������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
extern void GT811_Timer1ms(void);
void bsp_RunPer1ms(void)
{
	;
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_Idle
*	����˵��: ����ʱִ�еĺ�����һ����������for��whileѭ������������Ҫ���� CPU_IDLE() �������ñ�������
*			 ������ȱʡΪ�ղ������û���������ι��������CPU��������ģʽ�Ĺ��ܡ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
extern void SaveScreenToBmp(uint16_t _index);
void bsp_Idle(void)
{
	/* --- ι�� */

	/* --- ��CPU�������ߣ���Systick��ʱ�жϻ��ѻ��������жϻ��� */

	/* ���� emWin ͼ�ο⣬���Բ���ͼ�ο���Ҫ����ѯ���� */
	//GUI_Exec();

	/* ���� uIP Э�飬���Բ���uip��ѯ���� */


}

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/