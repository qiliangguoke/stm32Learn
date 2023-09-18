/*
*********************************************************************************************************
*
*	ģ������ : ���������
*	�ļ����� : main.c
*	��    �� : V1.0
*	˵    �� : ����
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0   2023-04-28  ����ٻ   �׷�
*
*	Copyright (C), 2014-2019, �������׵���
*
*********************************************************************************************************
*/

#include "bsp.h"				/* �ײ�Ӳ������ */

/*SN��ʼ��ַ*/
#define STM32F10X_SN_ADDR 0x1FFFF7E8
/*���������������̷�������*/
#define EXAMPLE_NAME  "����ٻ-2��-uart����ӡʵ�飩"
#define	EXAMPLE_DATE "2023-4-29"
#define DEMO_VER	"1.0"
#define UID "UID=570966413137484205D8FF39"
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
	uint8_t ucKeyCode;		/*��������*/
	uint16_t t;
	uint16_t len;
	uint8_t flag=0,flag1=0;
	uint8_t i;
	/*
		ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f10x.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ�ӣ��ڲ�Flash����ʱ������FSMC�����ⲿSRAM
	*/
	bsp_Init();		/* Ӳ����ʼ�� */
	PrintfLogo();	/*��ӡ������Ϣ������1*/
	
	//printf("DS0 ������˸(��˸Ƶ��=1Hz)\r\n");
	printf("�����������ӡ�����¼�\r\n");
	
	bsp_StartAutoTimer(0,500);		/*����1��500ms���Զ���װ�Ķ�ʱ��*/
	
	while(1)
	{
			if(bsp_CheckTimer(0))	/*�ж϶�ʱ����ʱʱ��*/
			{
				/*ÿ��500ms����һ��*/
				//bsp_LedToggle(1);/*��תDS0��״̬*/
				
				//printf("���������ݣ��Իس�������\r\n");
			}
			/*��������ɺ�̨systick�жϷ������ʵ������ֻ��Ҫ����bsp_GetKey��ȡ��ֵ���ɡ������������
			�ȴ��������£��������ǿ�����whileѭ����������������*/
			ucKeyCode = bsp_GetKey();		/*��ȡ��ֵ���޼�����ʱ����KEY_NONE=0*/
			if(ucKeyCode!=KEY_NONE)
			{
				/*�м�����*/
				switch(ucKeyCode)
				{
					case WKUP_LONG://WKUP����       
					{	
						flag=1;
						bsp_LedOn(1);
						printf("WKUP������������,(����һ���)DS0����\r\n");
						break;
					}
					case WKUP_UP://WKUP����       
					{	
						if(flag==1)
						{
							bsp_LedOff(1);
							bsp_LedOff(2);
							printf("WKUP���������DS0��DS1Ϩ��\r\n");
						}else
						{
							bsp_LedOn(2);
							printf("WKUP�̰������DS1����\r\n");
						}
						flag=0;
						break;
					}
					case KEY0_LONG://KEY0������       
					{	
						flag1=1;
						bsp_BeepToggle();
						printf("KEY0������ʱ����������\r\n");
						break;
					}
					case KEY0_UP://KEY0������       
					{	
						if(flag1==1)
						{
							bsp_BeepOff();
							printf("KEY0�����𣬷���������\r\n");
						}else
						{
							printf("KEY0�̰������������DS1��˸����\r\n");
							
							bsp_LedOff(1);
							bsp_LedOff(2);
							for(i=0;i<3;i++)
							{
								bsp_LedOn(2);
								bsp_DelayMS(250);
								bsp_LedOff(2);
								bsp_DelayMS(250);
							}
						}
						flag1=0;
						break;
					}
					default:/*�����ļ�ֵ������*/
						break;
			}
		}
		if( ReceiveState )
		{
			len = RxCounter;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ��\r\n\r\n");
			for(t=0;t<len;t++)
      {
				USART_SendData(USART1,USART_RX_BUF[t]);//�򴮿�1��������
				while( USART_GetFlagStatus( USART1,USART_FLAG_TC )!=SET);//�ȴ����ͽ���
      }
			printf("\r\n\r\n");	//���뻻��
			Uart0_STA_Clr();//����0״̬���
		}		
	
}
}


/*
*********************************************************************************************************
*	�� �� ��: PrintfLogo
*	����˵��: ��ӡ�������ƺ����̷������ڣ����ϴ����ߺ󣬴򿪴��ڵ������ֹ۲���
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void PrintfLogo(void)
{
	/*���CPU ID*/
	{
		uint32_t CPU_Sn0,CPU_Sn1,CPU_Sn2;
		CPU_Sn0=*(__IO uint32_t*)(STM32F10X_SN_ADDR);
		CPU_Sn1=*(__IO uint32_t*)(STM32F10X_SN_ADDR+4);
		CPU_Sn2=*(__IO uint32_t*)(STM32F10X_SN_ADDR+8);
		
		printf("\r\nCPU:STM32F103ZET6,LQFP144,UID=%08X%08X%08X\n\r",CPU_Sn2,CPU_Sn1,CPU_Sn0);
	}
	printf("\r\n");
	printf("**********************************************************\r\n");
	printf("* ��������	��%s\r\n",EXAMPLE_NAME);/*��ӡ��������*/
	printf("* ���̰汾	��%s\r\n",DEMO_VER);/*��ӡ���̰汾*/
	printf("* ��������	��%s\r\n",EXAMPLE_DATE);/*��ӡ��������*/
	printf("* UID	��%s\r\n",UID);/*��ӡUID*/
	
	/*��ӡST�����汾����3���������stm32f10x.h�ļ���*/
	printf("* �̼���汾��V5%d.%d.%d(STM32F10x_StdPeriph_Driver)\r\n",__STM32F10X_STDPERIPH_VERSION_MAIN,__STM32F10X_STDPERIPH_VERSION_SUB1,__STM32F10X_STDPERIPH_VERSION_SUB2);
	printf("\r\n");/*��ӡһ�пո�*/
	printf("**********************************************************\r\n");
}


/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
