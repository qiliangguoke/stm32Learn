#include "bsp.h" /* �ײ�Ӳ������ */
/*
STM32 ÿ��ϵ�ж�����Ψһ��һ��оƬ���кţ�96 λ bit����
STM32F10X �ĵ�ַ�� 0x1FFFF7E8 
STM32F20X �ĵ�ַ�� 0x1FFF7A10
STM32F30X �ĵ�ַ�� 0x1FFFF7AC
STM32F40X �ĵ�ַ�� 0x1FFF7A10
STM32L1XX �ĵ�ַ�� 0x1FF80050
*/
/* SN ��ʼ��ַ */
#define STM32F10X_SN_ADDR 0x1FFFF7E8
/* ���������������̷������� */
#define EXAMPLE_NAME "WSNEP_V01-105_UART ʵ�飨CO2��"
#define EXAMPLE_DATE "2019-08-02"
#define DEMO_VER "1.0"
/* �������ļ��ڵ��õĺ������� */
static void PrintfLogo(void);
static void PrintfHelp(void);
/*
*********************************************************************************************************
* �� �� ��: main
* ����˵��: c �������
* �� �Σ���
* �� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
int main(void)
{
	uint8_t lcd_id[12]; /* ��� LCD ID �ַ��� */
	uint8_t ucKeyCode;
	uint16_t co2_value=0;
	
	uint8_t SYN6288_Write_CMD[12]={0xFD,0x00,0x09,0x01,0x01,0xB5,0xC2,0xD6,0xC2,0xC2,0xD7,0x82};//���������� ��������
	uint8_t SYN6288_Write_CMD_1[12]={0xFD,0x00,0x09,0x01,0x01,0x73,0x6F,0x75,0x6E,0x64,0x6E,0xF9};//���������� ��������
/*
ST �̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f10x.c �ļ�����Ҫ������
���� CPU ϵͳ��ʱ�ӣ��ڲ� Flash ����ʱ������ FSMC �����ⲿ SRAM
*/
	bsp_Init(); /* Ӳ����ʼ�� */
	PrintfLogo(); /* ��ӡ������Ϣ������ 1 */
	PrintfHelp(); /* ��ӡ������ʾ */
	bsp_Init_28byj48();
	bsp_StartAutoTimer(0, 1000); /* ��ʱ�� 0 ���� 1000 ���� */
/* ����������ѭ���� */
	while(1) 
	{
		dirction();
		bsp_Idle(); /* CPU ����ʱִ�еĺ������� bsp.c */
		if (bsp_CheckTimer(0)) /* ��ʱ�� */
		{
			bsp_LedToggle(1);
		}
		
	/* �������¼� */
		ucKeyCode = bsp_GetKey();
		if (ucKeyCode > 0)
		{
		/* �м����� */
			switch(ucKeyCode)
			{
				case WKUP_DOWN://WKUP
				{
					
				}break;
				case KEY0_DOWN://KEY0
				{
					
				}break;
			}
		}
	}
}
/*
*********************************************************************************************************
* �� �� ��: PrintfHelp
* ����˵��: ��ӡ������ʾ
* �� �Σ���
* �� �� ֵ: ��
*********************************************************************************************************
*/
static void PrintfHelp(void)
{
	printf("������ʾ:\r\n");
	printf("1.�������У�ÿ 1 �� DS0 ��Ʒ�תһ��\r\n");
	printf("2.ÿ 1 ���ȡ����ʾһ�� CO2 ���ݣ�ע�� CO2 �ϵ�Ԥ�� 3 ���Ӻ����ݲ�׼ȷ\r\n");
	printf("\r\n\r\n");
}
/*
*********************************************************************************************************
* �� �� ��: PrintfLogo
* ����˵��: ��ӡ�������ƺ����̷�������, ���ϴ����ߺ󣬴򿪴��ڵ������ֹ۲���
* �� �Σ���
* �� �� ֵ: ��
*********************************************************************************************************
*/
static void PrintfLogo(void)
{
/* ��� CPU ID */
{
	uint32_t CPU_Sn0, CPU_Sn1, CPU_Sn2;
	CPU_Sn0 = *(__IO uint32_t*)(STM32F10X_SN_ADDR);
	CPU_Sn1 = *(__IO uint32_t*)(STM32F10X_SN_ADDR + 4);
	CPU_Sn2 = *(__IO uint32_t*)(STM32F10X_SN_ADDR + 8);
	printf("\r\nCPU : STM32F103ZET6, LQFP144, UID = %08X %08X %08X\n\r"
	, CPU_Sn2, CPU_Sn1, CPU_Sn0);
}
	printf("\r\n");
	printf("*************************************************************\r\n");
	printf("* �������� : %s\r\n", EXAMPLE_NAME);/* ��ӡ�������� */
	printf("* ���̰汾 : %s\r\n", DEMO_VER); /* ��ӡ���̰汾 */
	printf("* �������� : %s\r\n", EXAMPLE_DATE); /* ��ӡ�������� */
	/* ��ӡ ST �̼���汾���� 3 ��������� stm32f10x.h �ļ��� */
	printf("* �� �� �� �� �� : V%d.%d.%d (STM32F10x_StdPeriph_Driver)\r\n", 
	__STM32F10X_STDPERIPH_VERSION_MAIN,
	__STM32F10X_STDPERIPH_VERSION_SUB1,__STM32F10X_STDPERIPH_VERSION_SUB2);
	printf("* \r\n"); /* ��ӡһ�пո� */
	printf("*************************************************************\r\n");
}
/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
