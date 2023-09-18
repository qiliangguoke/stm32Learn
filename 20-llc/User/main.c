///////////////////////////////////////
/* ͷ�ļ������� */
#include "bsp.h"

//////////////////////////////////////
/* �궨������ */

#define STM32F10X_SN_ADDR 0x1FFFF7E8
#define EXAMPLE_NAME   "������_2��_�¶ȴ�����ʵ�飨��ӡʵ�飩"
#define EXAMPLE_DATE	"2023.-5-22"
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

const uint8_t TEXT_Buffer[]={"WSNEP_V01 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)
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
	
	uint8_t datatemp[SIZE];
	

	
	/*
		ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f10x.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ��
	*/
	bsp_Init();		/* Ӳ����ʼ�� */
	PrintLogo();	/* ��ӡ������Ϣ */
	PrintfHelp();	/* ��ӡ��ʾ��Ϣ */
	
	AT24CXX_Init(); /* IIC ��ʼ�� */

	bsp_InitAdcVolMeter(); /* ��ʼ�� ADC ��ѹ�� */
	while(AT24CXX_Check())//��ⲻ�� 24c02
	{
		delay_ms(500);
		LED1=!LED1;//DS1 ��˸
	}
	bsp_StartAutoTimer(0, 300); /* ��ʱ�� 0 ���� 300 ���� */
	
	
	
	while(1)
	{
		bsp_Idle();		
	
		if (bsp_CheckTimer(0)) /* �ж϶�ʱ����ʱʱ�� */
		{
			/* ÿ�� 500ms ����һ�� */
			bsp_LedToggle(1); /* ��ת DS0 ��״̬ */
		}
	
		/* �������¼� */
		ucKeyCode = bsp_GetKey();
		if (ucKeyCode > 0)
		{
			
			/* �м����� */
			switch(ucKeyCode)
			{
				case WKUP_DOWN:
				{
					printf("24C02 Write Finished!\r\n");
					AT24CXX_Write(0,(uint8_t*)TEXT_Buffer,SIZE);
					
				}break;
				case KEY0_DOWN:
				{
					printf("Start Read 24C02.... \r\n");
					AT24CXX_Read(0,datatemp,SIZE);
					printf("The Data Readed Is: %s\r\n",datatemp);
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
	printf("1.�������У�ÿ 300msDS0 ��Ʒ�תһ��\r\n");
	printf("2.WKUP д�� EEPORM��KEY0 ��ȡ����ʾ������ EEPROM ��Ϣ\r\n");
	printf("3.ͨ�����ڴ�ӡ��ȡ������\r\n");
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
