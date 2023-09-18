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

/* ���� LCD ��ʾ��ع�����Ϣ */
#define DEV_NAME "WSNEP_V01"
#define LCD_EXAMPLE_NAME "RC522 TEST"

/*�������ļ��ڵ��õĺ�������*/
static void PrintfLogo(void);
static void PrintfHelp(void);
//static void DAC_Dsiap(void);

void IC_test ( void )
{
char cStr [ 30 ];
char EptStr[30];
uint8_t ucArray_ID [ 4 ]; /*�Ⱥ��� IC �������ͺ� UID(IC �����к�)*/ 
uint8_t ucStatusReturn; /*����״̬ */ 
static u16 ucLineCount = 170; /* LCD ��ʼ��Ϊ 170 */
sprintf ( EptStr, " "); /* LCD ��ʾ�հף�Ϊ��� LCD ��ʾ��׼�� */
 /*Ѱ��*/
if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK ) 
{
/*��ʧ���ٴ�Ѱ��*/
ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );
}
if ( ucStatusReturn == MI_OK )
{
printf("----------------------------\r\n");
printf("CardType is:0x%02X%02X\r\n",ucArray_ID [ 0 ],ucArray_ID [ 1 ]);
/*����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����*/
if ( PcdAnticoll ( ucArray_ID ) == MI_OK ) 
{
sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",
 ucArray_ID [ 0 ],
 ucArray_ID [ 1 ],
 ucArray_ID [ 2 ],
 ucArray_ID [ 3 ] );
printf ( "%s\r\n",cStr );
printf("----------------------------\r\n\r\n");
if ( ucLineCount == 290 ) /* ���ͬʱ��ʾ 6 �� */
{
for(ucLineCount=170;ucLineCount<=290;ucLineCount+=20)
{
LCD_ShowString(30,ucLineCount,200,16,16,(u8*)EptStr); //ѭ����� 6 �� LCD ��ʾ
}
ucLineCount=170; /* ���� LCD ��ʼ��Ϊ 170 */
}
LCD_ShowString(30,ucLineCount,200,16,16,(u8*)cStr); //��ʾ��ȡ���Ŀ���
ucLineCount += 20; /* ������һ�� LCD ��ʾ�У����� 20 */
}
}
}

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
	
uint8_t lcd_id[12]; /* ��� LCD ID �ַ��� */
uint8_t ucKeyCode;
	
	//uint16_t co2_value=0;
	
	
bsp_Init(); /* Ӳ����ʼ�� */
PrintfLogo(); /* ��ӡ������Ϣ������ 1 */
PrintfHelp(); /* ��ӡ������ʾ */
TFTLCD_Init(); /* TFTLCD ��ʼ��*/
POINT_COLOR=BLUE; 
sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//�� LCD ID ��ӡ�� lcd_id ���顣
LCD_ShowString(30,40,200,24,24,(uint8_t*)DEV_NAME);
LCD_ShowString(30,70,200,16,16,(uint8_t*)LCD_EXAMPLE_NAME);
LCD_ShowString(30,90,200,16,16,(uint8_t*)DEMO_VER);
LCD_ShowString(30,110,200,16,16,lcd_id); //��ʾ LCD ID 
LCD_ShowString(30,130,200,12,12,(uint8_t*)EXAMPLE_DATE);
bsp_InitRc522(); /* ��ʼ�� RC522 �� SPI �˿� */
PcdReset(); /* ��λ RC522 */
M500PcdConfigISOType('A'); /* ���ù�����ʽ */
bsp_StartAutoTimer(0, 300); /* ��ʱ�� 0 ���� 300 ���� */
bsp_StartAutoTimer(1, 500); /* ��ʱ�� 1 ���� 500 ���� */
/* ����������ѭ���� */
while(1) 
{
bsp_Idle(); /* CPU ����ʱִ�еĺ������� bsp.c */
if (bsp_CheckTimer(0)) /* ��ʱ�� */
{
bsp_LedToggle(1);
}
if (bsp_CheckTimer(1)) /* ��ʱ�� */
{
IC_test();
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
*	�� �� ��: PrintfHelp
*	����˵��: ��ӡ������ʾ
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void PrintfHelp(void)
{
	printf("������ʾ:\r\n");
	printf("1.�������У�ÿ300msDS0��Ʒ�תһ��\r\n");
	printf("2.������в�����ÿ 1 ���Զ�ˢ����ʾ����ɫ����Ӧ�����\r\n");
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
