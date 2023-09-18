///////////////////////////////////////
/* ͷ�ļ������� */
#include "bsp.h"

//////////////////////////////////////
/* �궨������ */

#define STM32F10X_SN_ADDR 0x1FFFF7E8
#define EXAMPLE_NAME   "������_2��_WSNEP_V01-201_IO ʵ�飨��ӡʵ�飩"
#define EXAMPLE_DATE	"2023.-5-22"
#define DEMO_VER		"1.0"



/* ���� LCD ��ʾ��ع�����Ϣ */
#define DEV_NAME 			"WSNEP_V01"
#define LCD_EXAMPLE_NAME 	"Relay TEST"


///////////////////////////////////////
/* �ⲿ���������� */

uint8_t ReceiveState;				//����״̬��־
uint16_t RxCounter;	
uint8_t USART_RX_BUF[USART_REC_LEN];	//���ջ��壬���USART_rec_LEN���ֽڣ�ĩ�ֽ�Ϊ���з�

///////////////////////////////////////
/* ���������� */

static void PrintfHelp(void);

static void PrintLogo(void);


///////////////////////////////////////


/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
				/* �ײ�Ӳ������ */
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
	/* �������� */
	uint8_t ucKeyCode;
	
	
	

	
	/*
		ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f10x.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ��
	*/
	bsp_Init();		/* Ӳ����ʼ�� */
	PrintLogo();	/* ��ӡ������Ϣ */
	PrintfHelp();	/* ��ӡ��ʾ��Ϣ */
	
	bsp_InitRelay();

	bsp_StartAutoTimer(0, 300); /* ��ʱ�� 0 ���� 300 ���� */
		
	while(1)
	{
		bsp_Idle();		
	
		if (bsp_CheckTimer(0)) /* �ж϶�ʱ����ʱʱ�� */
		{
			/* ÿ�� 500ms ����һ�� */
			bsp_LedToggle(1); /* ��ת DS0 ��״̬ */
		}
	
		/* ���������¼� */
		ucKeyCode = bsp_GetKey();
		if (ucKeyCode > 0)
		{
			
			/* �м����� */
			switch(ucKeyCode)
			{
				case WKUP_DOWN:
				{
					bsp_RelayToggle(1);				
				}break;
				case KEY0_DOWN:
				{
					bsp_RelayToggle(2);
				}break;
				case KEY1_DOWN://KEY1
				{
					bsp_RelayToggle(3);
				}break;
				case KEY2_DOWN://KEY2
				{
					bsp_RelayToggle(4);
				}break;
			}
		}
			
	}
}
/*
*********************************************************************************************************
*	�� �� ��:PrintfHelp
*	����˵��: ��ӡ��ʾ��Ϣ
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
static void PrintfHelp(void)
{
	printf("������ʾ:\r\n");
	printf("1.�������У�ÿ 300ms DS0 ��Ʒ�תһ��\r\n");
	printf("2.WKUP��KEY0��KEY1��KEY2���ֱ�ת Relay1~4 ��״̬\r\n");
	printf("\r\n\r\n");
}

static void PrintLogo(void)
{
	{
		uint32_t CPU_Sn0,CPU_Sn1,CPU_Sn2;
		
		CPU_Sn0=*(__IO uint32_t*)(STM32F10X_SN_ADDR);
		CPU_Sn1=*(__IO uint32_t*)(STM32F10X_SN_ADDR+4);
		CPU_Sn2=*(__IO uint32_t*)(STM32F10X_SN_ADDR+8);		
		printf("\r\nCPU:STM32F103ZET6,LQFP144,UID=%08X %08X %08X\n\r",CPU_Sn2,CPU_Sn1,CPU_Sn0);	
	}
	printf("\r\n");
	printf("***************************************************************************************************\r\n");
	printf("�������ƣ�%s\r\n",EXAMPLE_NAME);
	printf("���̰汾��%s\r\n",DEMO_VER);
	printf("�������ڣ�%s\r\n",EXAMPLE_DATE);
	
	printf("*��   ��   ��    ��    ����V%d.%d.%d  (STM32F10x_sTdPeriph_Driver)\r\n",__STM32F10X_STDPERIPH_VERSION_MAIN,__STM32F10X_STDPERIPH_VERSION_SUB1,__STM32F10X_STDPERIPH_VERSION_SUB2);
	printf("*\r\n");
	printf("***************************************************************************************************\r\n");
}

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/