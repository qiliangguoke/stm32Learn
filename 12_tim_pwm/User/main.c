///////////////////////////////////////
/* ͷ�ļ������� */
#include "bsp.h"

//////////////////////////////////////
/* �궨������ */

#define STM32F10X_SN_ADDR 0x1FFFF7E8
#define EXAMPLE_NAME   "������_2��_��ʱ������ӡʵ�飩"
#define EXAMPLE_DATE		"2023.-5-17"
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
	while(1)
	{
		bsp_Idle();		
		ucKeyCode=bsp_GetKey();	/* ��ȡ���� */
		if(ucKeyCode>0)		
		{
			switch(ucKeyCode)
			{
				case WKUP_DOWN://WKUP ����
				{		
					bsp_SetTIMforInt(TIM7, 2, 0, 0); /* ����Ϊ 2Hz Ƶ��, ���� 0.5 �붨ʱ�ж�*/
					printf("-----���� TIM7 ��ʱ����0.5 �룩-----\r\n");
					
				}break;
				case KEY0_DOWN:
				{
					TIM_ITConfig(TIM7, TIM_IT_Update, DISABLE); /* ��ֹ TIM7 �ж� */
					bsp_LedOff(2);
					printf("-----ֹͣ TIM7 ��ʱ����Ϩ�� DS1-----\r\n");
				}break;
				default:
				{

				}break;			
			}			
		}		
	}
}

/*
*********************************************************************************************************
* �� �� ��: TIM7_IRQHandler
* ����˵��: TIM7 ��ʱ�жϷ������
* �� �� ֵ: 
*********************************************************************************************************
*/
void TIM7_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		bsp_LedToggle(2);
	}
}

static void PrintfHelp(void)
{
	printf("������ʾ:\r\n");
	printf("1.ͨ������ WKUP ��������ʱ�� TIM7����������Ϊ 0.5 �룬���ڸö�ʱ���ж��з�ת DS1 �̵ƣ�������ʾ���� TIM7 ��ʱ����0.5 �룩\r\n");
	printf("2.ͨ������ KEY0 ���ر� TIM7 ��ʱ�жϣ���Ϩ�� DS1 �̵ƣ�������ʾ�ر� TIM7 ��ʱ����\r\n");
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
