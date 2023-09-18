///////////////////////////////////////
/* ͷ�ļ������� */
#include "bsp.h"

//////////////////////////////////////
/* �궨������ */

#define STM32F10X_SN_ADDR 0x1FFFF7E8
#define EXAMPLE_NAME   "������_2��_pwm����ӡʵ�飩"
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
static void SetRpValue(uint8_t DutyCycle);
static void RgbLedRpInit(uint16_t DutyCycle);

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
	uint16_t ucRedDucyCycle = 50;
	
	/*
		ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f10x.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ��
	*/
	bsp_Init();		/* Ӳ����ʼ�� */
	PrintLogo();	/* ��ӡ������Ϣ */
	PrintfHelp();	/* ��ӡ��ʾ��Ϣ */
	RgbLedRpInit(ucRedDucyCycle); /* ��ʼ�� RGB*/
	
	printf("---ucRedDucyCycle �ĳ�ʼֵΪ %d---\r\n",ucRedDucyCycle);
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
					{
						ucRedDucyCycle+=10;
						SetRpValue(ucRedDucyCycle); // RGB G �Ƶ����  �𽥱䰵
						
						printf("---ucRedDucyCycle ֵΪ %d,�𽥱䰵---\r\n",ucRedDucyCycle);
					}
					
				}break;
				case KEY0_DOWN:
				{
					if(ucRedDucyCycle >= 10)
					{
						ucRedDucyCycle-=10;
						SetRpValue(ucRedDucyCycle); //RGB G �Ƶ���� /�𽥱���
						printf("---ucRedDucyCycle ֵΪ %d,�𽥱���---\r\n",ucRedDucyCycle);
					}
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
*	�� �� ��:RgbLedRpInit
*	����˵��: RGB �ĺ�Ƴ�ʼ��
*	��    �Σ�DutyCycle Ϊռ�ձȣ�ȡֵ��ΧΪ 0~100
*	�� �� ֵ: 
********************************************************************************************************
*/
static void RgbLedRpInit(uint16_t DutyCycle)
{
	DutyCycle *= 100; 
	/*
	void bsp_SetTIMOutPWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, TIM_TypeDef* TIMx, uint8_t _ucChannel,
	uint32_t _ulFreq, uint32_t _ulDutyCycle);
	*/
	bsp_SetTIMOutPWM(GPIOB,GPIO_Pin_9,TIM4,4,90000,DutyCycle);/* PB9 ��Ӧ�� TIM4 �� CH4��90KHZ */
}
/*
*********************************************************************************************************
*	�� �� ��:SetRpValue
*	����˵��: ���� RGB ������ռ�ձ�
*	��    �Σ�uint8_t DutyCycle:ռ�ձȣ�ȡֵ��Χ 0~100
*	�� �� ֵ: 
********************************************************************************************************
*/
static void SetRpValue(uint8_t DutyCycle)
{
	uint16_t temp = 0;
	if(DutyCycle==100)
	{
		TIM_SetCompare4(TIM4,799);//800-1 90KHz ʱ
	}
	temp = DutyCycle * 9; //ע����� 90KHz ��Ƶ�ʣ�ARR ��������Ϊ 900,ռ�ձ�λ 0~100��������ֵΪ 9
	TIM_SetCompare4(TIM4,temp);
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
	printf("1. ���� RGB ������ PWM Ƶ���� 90KHz����ʼռ�ձ��� 50%%\r\n");
	printf("2. WKUP �� - RGB R �𽥱䰵\r\n");
	printf("3. KEY0 �� - RGB R �𽥱���\r\n");
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
