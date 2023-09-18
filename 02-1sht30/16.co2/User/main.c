/*
*********************************************************************************************************
*
*	ģ������ : ���������
*	�ļ����� : main.c
*	��    �� : V1.0
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023-5-19	����ʤ
*
*	Copyright (C), 2014-2019, �������׵���
*
*********************************************************************************************************
*/

#include "bsp.h"		 /* �ײ�Ӳ������ */

uint8_t ReceiveState;    //����״̬��־
uint16_t RxCounter; 
uint8_t USART_RX_BUF[USART_REC_LEN]; //���ջ��壬���USART_rec_LEN���ֽڣ�ĩ�ֽ�Ϊ���з�

/*

STM32ÿ��ϵ�ж���Ψһ��һ��оƬ���кţ�96λbit��:
	STM32F10X �ĵ�ַ��	0xFFFF7E8
	STM32F20X �ĵ�ַ��	0xFFF7A10
	STM32F30X �ĵ�ַ��	0xFFFF7AC
	STM32F40X �ĵ�ַ��	0xFFF7A10
	STM32L1XX �ĵ�ַ��	0x1FF80050
*/
/*SN��ʼ��ַ*/
#define STM32F10X_SN_ADDR 0x1FFFF7E8

/*���������������̷���ʱ��*/
#define	EXAMPLE_NAME	"����ʤ_2��_UARTʵ��(CO2)"
#define EXAMPLE_DATE	"2023-6-12"
#define DEMO_VER		"1.0"

/*�������ļ��ڵ��õĺ�������*/
static void PrintfLogo(void);
static void PrintfHelp(void);
//static void DAC_Dsiap(void);

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
		
	PrintfLogo();	/* ��ӡ������Ϣ������1 */
	
	PrintfHelp();	/* ��ӡ������ʾ */
	
	
	bsp_InitI2C();
	bsp_InitSht3x();
	bsp_StartAutoTimer(0, 1000); /* ��ʱ��0����1000���� */

	
	
	
	
	/*����������ѭ����*/
	while(1)
	{
		bsp_Idle();	/* CPU����ʱִ�еĺ�������bsp.c */
		
		if (bsp_CheckTimer(0)) /*��ʱ��*/
		{
			/* ÿ��500ms����һ�� */
			bsp_LedToggle(1);
			if( SHT3X_GetValue() )
			{
				bsp_InitI2C();
				bsp_InitSht3x();
			}
			else
			{
				printf("�¶�Ϊ%.1f�棬ʪ��Ϊ%.1f%%RH\r\n", Tem_Value, RH_Value);
			}
			
		}
		
		/* �������¼� */
		ucKeyCode = bsp_GetKey();
		if (ucKeyCode>0)
		{
			/* �м����� */
			switch(ucKeyCode)
			{
				case WKUP_DOWN://wkup
					{
					
					}break;
				case KEY0_DOWN://key0
					{
					
					}break;
			}
		}
	}
}

/*
*********************************************************************************************************
*	�� �� ��: PrintfHelp
*	����˵��: ��ӡ������ʾ
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void PrintfHelp(void)
{
	printf("������ʾ:\r\n");
	printf("1.�������У�ÿ 500msDS0 ��Ʒ�תһ��\r\n");
	printf("2.ÿ 500ms ��ȡ��ʾ��ʾ��ʪ����Ϣ\r\n");
	printf("\r\n\r\n");
}

/*
*********************************************************************************************************
*	�� �� ��: PrintfLogo
*	����˵��: ��ӡ�������ƺ����̷���ʱ�䣬���ϴ����ߺ󣬴򿪴��ڵ������ֹ۲���
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void PrintfLogo(void)
{
	/*���CPI ID*/
	{
		uint32_t CPU_Sn0,CPU_Sn1,CPU_Sn2;
		
		CPU_Sn0=*(__IO uint32_t*)(STM32F10X_SN_ADDR);
		CPU_Sn1=*(__IO uint32_t*)(STM32F10X_SN_ADDR+4);
		CPU_Sn2=*(__IO uint32_t*)(STM32F10X_SN_ADDR+8);
		
		printf("\r\nCPU:STM32F103ZET6,LQFP144,UID = %08X%08X%08X\n\r",CPU_Sn2,CPU_Sn1,CPU_Sn0);
	}
	printf("\r\n");
	printf("***************************************\r\n");
	printf("*��������   	��%s\r\n",EXAMPLE_NAME);/*��ӡ��������*/
	printf("*���̰汾	��%s\r\n",DEMO_VER);		/*��ӡ���̰汾*/
	printf("*����ʱ��	��%s\r\n",EXAMPLE_DATE);	/*��ӡ��������*/
	
	/*��ӡST�̼���汾����3���������stm32f10x.h�ļ���*/
	printf("�̼���汾	��V%d.%d.%d		(STM32F10x_StdPeriph_Driver)\r\n",
	__STM32F10X_STDPERIPH_VERSION_MAIN,
		__STM32F10X_STDPERIPH_VERSION_SUB1,__STM32F10X_STDPERIPH_VERSION_SUB2);
	printf("*\r\n");/*��ӡһ�пո�*/
	printf("***************************************");
}


/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
