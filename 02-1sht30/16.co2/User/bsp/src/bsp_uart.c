#include"bsp.h"
/*
*********************************************************************************************************
*	�� �� ��: bsp_InitUart
*	����˵��: ��ʼ��CPU��USART1����Ӳ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/		
void bsp_InitUart1(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
#if EN_USART1_RX	//���ʹ���˽���
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
#endif
	
	/*����1 TX = PA9		RX = PA10*/
	
	/*��1��������GPIO*/

	/*��GPIOʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	/*��UARTʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	/*����USARTTx Ϊ���ù���*/ //USART1_TX	GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			//PA9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//�����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);				//��ʼ��GPIOA.9
	
	/*����USARTRx Ϊ���ù���*/ //USART1_RX	GPIOA.10��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;					//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);				//��ʼ��GPIOA.10
	
	/*��2�������ô���Ӳ������*/
	USART_InitStructure.USART_BaudRate = baud;			/*������*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; /*�ֳ�Ϊ8λ���ݸ�ʽ*/
	USART_InitStructure.USART_StopBits =USART_StopBits_1 ;		/*һ��ֹͣλ*/
	USART_InitStructure.USART_Parity = USART_Parity_No;			/*����żУ��λ*/
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /*��Ӳ������������*/
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx; /*�շ�ģʽ*/
	 
	USART_Init(USART1,&USART_InitStructure);	/*��ʼ������1*/

#if EN_USART1_RX		//���ʹ���˽���

	/*��3����Usart1 NVIC����*/
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	/*��ռ���ȼ�3*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			/*�����ȼ�3*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				/*IRQͨ��ʹ��\*/
	NVIC_Init(&NVIC_InitStructure);			/*����ָ���Ĳ�����ʼ��VIC�Ĵ���*/
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);/*�������ڽ����ж�*/
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);/*�������ڿ����ж�*/
	
#endif

	/*��4���� ʹ�ܴ���1*/
		USART_Cmd(USART1,ENABLE);	/*ʹ�ܴ���*/
}
/*
*********************************************************************************************************
*	�� �� ��: USART1_IRQHandler
*	����˵��: USART1�жϣ���Ҫ�ǽ����жϺͿ����ж�
*	��    �Σ���
*	�� �� ֵ: ��
*   ע    �⣺��ȡUSART1->SR�ܱ���Ī������Ĵ���
*********************************************************************************************************
*/
void USART1_IRQHandler(void)	//����1�жϷ������
{
	uint8_t Res=Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 	//�����ж�(���յ�һ���ֽ�����)
	{
		USART_RX_BUF[RxCounter++] = USART1->DR;		//�ѽ��յ����ֽڱ���
	}
	
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) //�����ж�(���յ� 1֡����)
	{
		Res=USART1->SR;			//��SR�Ĵ���.
		Res=USART1->DR;			//��DR�Ĵ���(�ȶ�SR���ٶ�DR������Ϊ�����IDLE�ж�) .
		ReceiveState = 1;		//��ǽ���״̬��λ
	}
}
/*
*********************************************************************************************************
*	�� �� ��: Uart0_STA_Clr
*	����˵��: ����0״̬�������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Uart0_STA_Clr(void)
{
	RxCounter = 0;		//����BUF��������
    ReceiveState = 0;	//����״̬����
}
/*
*********************************************************************************************************
*/
//�������´���,֧��printf����,������Ҫѡ��use MicoLIB
#if 1
#pragma import(__use_no_semihosting)
/*��׼����Ҫ��֧�ֺ���*/
struct	__FILE
{
	int handle;
};	
FILE 	__stdout;

/*����sys_exit()�Ա���ʹ�ð�����ģʽ*/
void _sys_exit(int x)
{
	x=x;
}
/*
*********************************************************************************************************
*	�� �� ��: fputc
*	����˵��: �ض���putc��������������ʹ��printf�����Ӵ���1��ӡ���
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int fputc(int ch, FILE *f)
{
	while((USART1-> SR&0X40) ==0){};	//ѭ�����ͣ�ֱ���������
	USART1->DR = (u8)ch;
	return ch;
}

#endif
/*
*********************************************************************************************************
*	�� �� ��: USART1_Send_Data
*	����˵��: USART1����len����
*	��    �Σ�buf:�������׵�ַ
			  len�����͵��ֽ���0-255
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void USART1_Send_Data(uint8_t *buf,uint8_t len)
{
	uint8_t t;
	for(t=0;t<len;t++)			//ѭ����������
	{	
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)== RESET);
		USART_SendData(USART1,buf[t]);
	}
	
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)== RESET);
}

