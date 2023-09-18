/*
*********************************************************************************************************
*
*	ģ������ : ���������
*	�ļ����� : main.c
*	��    �� : V1.0
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    
*
*	Copyright (C), 2014-2019, �������׵���
*
*********************************************************************************************************
*/

#include "bsp.h"				/* �ײ�Ӳ������ */
uint8_t USART_RX_BUF[USART_REC_LEN];	//���ջ��壬���USART_rec_LEN���ֽڣ�ĩ�ֽ�Ϊ���з�
uint8_t ReceiveState;				//����״̬��־
uint16_t RxCounter;		
void Uart0_STA_Clr(void);
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
#define	EXAMPLE_NAME	"����ʤ_2��_���ڣ���ӡʵ�飩"
#define EXAMPLE_DATE	"2023-4-28"
#define DEMO_VER		"1.0"

/*�������ļ��ڵ��õĺ�������*/
static void PrintfLogo(void);

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
	uint8_t ucKeyCode;	/*��������*/
	uint16_t t;
	uint16_t len;
	/*
		ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f10x.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ��
	*/
	bsp_Init();		/* Ӳ����ʼ�� */
	PrintfLogo();	/*��ӡ������Ϣ������1*/
	
	printf("DS0������˸����˸Ƶ�� = 1Hz��\r\n");
	printf("�����������ӡ�����¼�\r\n");

	bsp_StartAutoTimer(0,500);		/*����1��500ms���Զ���װ�Ķ�ʱ��*/
	
	/*����������ѭ����*/
	while(1)
	{
//		if(bsp_CheckTimer(0))
//		{
//			/*ÿ��500ms����һ��*/
//			bsp_LedToggle(1);	/*��תDS0��״̬*/
//			
//			//printf("���������ݣ��Իس�������\r\n");
//		}
		/*
		��������ɺ�̨systick�жϷ������ʵ�֣�����ֻ��Ҫ����bsp_GetKey��ȡ��ֵ���ɡ�
		�����������ȴ��������£��������ǿ�����whileѭ����������������
		*/
		ucKeyCode = bsp_GetKey(); 	/*��ȡ�������޼�����ʱ����KEY_NONE=0*/
		if(ucKeyCode!=KEY_NONE)
		{
			switch(ucKeyCode)
			{
				case WKUP_DOWN:		/*WKUP������*/
						bsp_BeepOn();
					printf("WUKP�����·��������б���\r\n");
					break;
				case WKUP_UP:		/*WUKP������*/
					bsp_BeepOff();
					printf("WUKP�����������ֹͣ����\r\n");
					break;
				case KEY0_LONG:
					bsp_LedToggle(2);
					printf("key0������\r\n");
				break;
				case KEY0_DOWN:		/*KEY0������*/
					bsp_LedOn(1);
					printf("KEY0�����º����\r\n");
					break;
				case KEY0_UP:		/*KEY0������*/
					//bsp_LedToggle(1);
					bsp_LedOff(1);
					printf("KEY0����������\r\n");
					break;

				
				default:
				/*�����ļ�ֵ������*/
				break;
			}
		}
		if(ReceiveState)
		{
			len = RxCounter;	//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1,USART_RX_BUF[t]);//�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			Uart0_STA_Clr();//����0״̬���
		}
	}
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
	printf("*���̰汾	��%s\r\n",DEMO_VER);	/*��ӡ���̰汾*/
	printf("*����ʱ��	��%s\r\n",EXAMPLE_DATE);/*��ӡ��������*/
	
	/*��ӡST�̼���汾����3���������stm32f10x.h�ļ���*/
	printf("�̼���汾	��V%d.%d.%d		(STM32F10x_StdPeriph_Driver)\r\n",
	__STM32F10X_STDPERIPH_VERSION_MAIN,
		__STM32F10X_STDPERIPH_VERSION_SUB1,__STM32F10X_STDPERIPH_VERSION_SUB2);
	printf("*\r\n");/*��ӡһ�пո�*/
	printf("***************************************");
}


/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
