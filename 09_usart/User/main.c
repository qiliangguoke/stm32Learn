

#include "bsp.h"				/* �ײ�Ӳ������ */

uint8_t USART_RX_BUF[USART_REC_LEN];	//���ջ��壬���USART_rec_LEN���ֽڣ�ĩ�ֽ�Ϊ���з�
uint8_t ReceiveState;				//����״̬��־
uint16_t RxCounter;		


#define STM32F10X_SN_ADDR 0x1FFFF7E8


#define EXAMPLE_NAME   "������_2��_����1����ӡʵ�飩"
#define EXAMPLE_DATE		"2023.-5-1"
#define DEMO_VER		"1.0"

static void PrintLogo(void);
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
	uint16_t t;
	uint16_t len;
	uint8_t  n;
	/*
		ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f10x.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ��
	*/
	bsp_Init();		/* Ӳ����ʼ�� */
	PrintLogo();
	printf("DS0������˸����˸Ƶ��=1Mz��\r\n");
	printf("�����������ӡ�����¼�\r\n");
	
	bsp_StartAutoTimer(0,500);
	while(1)
	{
		
		//if(bsp_CheckTimer(0))
		//{
		//	bsp_LedToggle(1);
			
		//}
		
		
		ucKeyCode=bsp_GetKey();
		if(ucKeyCode>0)
		
		{
			switch(ucKeyCode)
			{
				case WKUP_DOWN://WKUP ����
				{		
					bsp_BeepToggle();
					printf("WKUP������,����������\r\n");
				}break;
				case WKUP_UP:		/*WUKP������*/
					bsp_BeepOff();				
					printf("WUKP�����������ֹͣ����\r\n");
					break;			
				case KEY0_LONG:	//key0����
				{					
					n=3;
					bsp_LedOn(2);
					printf("KEY0_UP�������̵�����\r\n");
					
				}break;
				case KEY0_DOWN:
				{																																				
					n=1;									
				}break;
				case KEY0_UP:		/*KEY0������*/		
					if(n==1){
						bsp_LedToggle(1);
						n=0;
						printf("KEY0_UP���̰�,���ƺ������\r\n");
					}
					if(n==3){
						printf("KEY0_UP�������̵�Ϩ��\r\n");
						n=0;
						bsp_LedOff(2);
					}						
					break;				
			}
			
		}
		
		if(ReceiveState)
		{
			
			len=RxCounter;
			printf("\r\n�㷢�͵���ϢΪ��\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1,USART_RX_BUF[t]);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
			}
			printf("\r\n\r\n");
			Uart0_STA_Clr();
		}
	}
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
