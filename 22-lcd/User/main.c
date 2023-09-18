///////////////////////////////////////
/* ͷ�ļ������� */
#include "bsp.h"

//////////////////////////////////////
/* �궨������ */

#define STM32F10X_SN_ADDR 0x1FFFF7E8
#define EXAMPLE_NAME   "������_2��_�¶ȴ�����ʵ�飨��ӡʵ�飩"
#define EXAMPLE_DATE	"2023.-5-22"
#define DEMO_VER		"1.0"

/* ���� LCD ��ʾ��ع�����Ϣ */
#define DEV_NAME "WSNEP_V01"
#define LCD_EXAMPLE_NAME "TFTLCD TEST"

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
	uint8_t ucKeyCode;
	uint8_t x=1;
	uint8_t lcd_id[12]; /* ��� LCD ID �ַ��� */
	/* �������� */
	
	
	
	

	
	/*
		ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f10x.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ��
	*/
	bsp_Init();		/* Ӳ����ʼ�� */
	PrintLogo();	/* ��ӡ������Ϣ */
	PrintfHelp();	/* ��ӡ��ʾ��Ϣ */
	
	TFTLCD_Init(); /* TFTLCD ��ʼ��*/

	POINT_COLOR=RED; 
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//�� LCD ID ��ӡ�� lcd_id ���顣
	POINT_COLOR=RED; 
	
	
	bsp_StartAutoTimer(0,300); /* ��ʱ�� 0 ���� 300 ���� */
	bsp_StartTimer(1,100); /* ��ʱ�� 1 ���� 100 ���� */
	
	while(1)
	{
		ucKeyCode=bsp_GetKey();
	
		if (bsp_CheckTimer(0)) /* �ж϶�ʱ����ʱʱ�� */
		{
			/* ÿ�� 500ms ����һ�� */
			bsp_LedToggle(1); /* ��ת DS0 ��״̬ */
		}
	
		if(bsp_CheckTimer(1))
		{
//			//LCD_ShowNum(90,130,x,2,16);
//			switch(x)
//			{
//				case 1:LCD_Fill(150,70,230,230,BLACK);break;
//				case 2:LCD_Fill(150,70,230,230,BLUE);break;
//				case 3:LCD_Fill(150,70,230,230,RED);break;
//				case 4:LCD_Fill(150,70,230,230,MAGENTA);break;
//				case 5:LCD_Fill(150,70,230,230,GREEN);break;
//				case 6:LCD_Fill(150,70,230,230,CYAN);break;
//				case 7:LCD_Fill(150,70,230,230,YELLOW);break;
//				case 8:LCD_Fill(150,70,230,230,BRRED);break;
//				case 9:LCD_Fill(150,70,230,230,GRAY);break;
//				case 10:LCD_Fill(150,70,230,230,LGRAY);break;
//				case 11:LCD_Fill(150,70,230,230,BROWN);break;
//			}
//			x++;
//			if(x==12)
//			{
//				x=1;
//			}
			
					
			bsp_StartTimer(1,1000); /* ��ʱ�� 1 ���� 1000 ���� */
			
			
			
		}
		if(ucKeyCode>0)
		
		{
			switch(ucKeyCode)
			{
				case WKUP_DOWN://WKUP ����
				{	
					LCD_Clear(0xFFFF);					
					LCD_ShowString(30,40,200,16,16,(uint8_t*)"     ");
					LCD_ShowString(30,70,200,16,16,(uint8_t*)"  *  ");	
					LCD_ShowString(30,90,200,16,16,(uint8_t*)"  **  ");
					LCD_ShowString(30,130,200,16,16,(uint8_t*)" *** ");
					LCD_ShowString(30,170,200,16,16,(uint8_t*)"*****");
				}break;
				case WKUP_UP:		/*WUKP������*/
				{
				
				}
					break;			
				case KEY0_LONG:	//key0����
				{					
					
					
				}break;
				case KEY0_DOWN:
				{																																				
					LCD_Clear(0xFFFF);	
					LCD_ShowString(30,40,200,16,16,(uint8_t*)"*****");
					LCD_ShowString(30,70,200,16,16,(uint8_t*)" *** ");
					LCD_ShowString(30,90,200,16,16,(uint8_t*)"  **  ");
					LCD_ShowString(30,130,200,16,16,(uint8_t*)"  *  ");
					LCD_ShowString(30,170,200,16,16,(uint8_t*)"     ");									
				}break;
				case KEY0_UP:		/*KEY0������*/		
				{
					
				}						
					break;				
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
	printf("1.�������У�ÿ 300 ���� DS0 ��Ʒ�תһ��\r\n");
	printf("2.������в�����ÿ 1 ���Զ�ˢ����ʾ����ɫ����Ӧ�����\r\n");
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
