///////////////////////////////////////
/* ͷ�ļ������� */
#include "bsp.h"

//////////////////////////////////////
/* �궨������ */

#define STM32F10X_SN_ADDR 0x1FFFF7E8
#define EXAMPLE_NAME   "������_2��_�������Ź�����ӡʵ�飩"
#define EXAMPLE_DATE		"2023.-5-10"
#define DEMO_VER		"1.0"

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
	
	bsp_InitIwdg(IWDG_Prescaler_64,625); /* ��ʼ���������Ź� */
	
	/* ����300ms�Ķ�ʱ�� */
	bsp_StartAutoTimer(0,300);
	
	/* ���� 1 �� 20ms ���Զ���װ�Ķ�ʱ�� */
	bsp_StartAutoTimer(1,20); 
	
	while(1)
	{
		if (bsp_CheckTimer(0)) /* �ж϶�ʱ����ʱʱ�� */
		{
			bsp_LedToggle(2);	/* ��ת�̵� */
		}
		if (bsp_CheckTimer(1)) /* �ж϶�ʱ����ʱʱ�� */
		{
			//bsp_LedToggle(0);
			IWDG_Feed();		/* ι�� */
		}
				
		ucKeyCode=bsp_GetKey();	/* ��ȡ���� */
		if(ucKeyCode>0)		
		{
			switch(ucKeyCode)
			{
				case WKUP_DOWN://WKUP ����
				{		
					bsp_StopTimer(1); /* ֹͣ�����ʱ�� 1 */
					
					
					printf("ֹͣ�����ʱ�� 1");
					
				}break;
				default:
				{

				}break;			
			}			
		}		
	}
}
static void PrintfHelp(void)
{
	printf("������ʾ:\r\n");
	printf("1.�������У�ÿ 300msDS0 �̵Ʒ�תһ��\r\n");
	printf("2.���� 1 �����ڴ�ԼΪ 1 ��� IWDG ���Ź�\r\n");
	printf("3.ÿ 20ms ι��һ�Σ�ʹ�������ʱ��\r\n");
	printf("4.WKUP ֹͣÿ 20ms һ�ε�ι����Ϊ��ʹ IWDG ��λ\r\n");
	printf("5.ͨ�����ڴ�ӡ״̬��Ϣ\r\n");
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
