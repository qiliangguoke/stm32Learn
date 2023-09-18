#include "bsp.h"

uint8_t  USART_RX_BUF[USART_REC_LEN];       //���ջ��������USART_REC_LEN���ֽڣ�ĩ�ֽ�λ���з�
uint8_t  ReceiveState;
uint16_t RxCounter;
/*
***************************************************************************
*          �� �� ����
*          ����˵����
*          ��   �Σ���
*          �� �� ֵ���� 
***************************************************************************
*/

void bsp_InitUart(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
#if EN_USARTI_RX
	NVIC_InitTypeDef NVIC_InitStructure;
#endif
	
	//����1 TX=PA9  RX=PA10
	//��һ������GPIO
	//��GPIOʱ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//��UARTʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//����USART Tx Ϊ���ù��� USART1_TX GPIOA.9
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;					//PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  			//�����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);					//��ʼ��GPIOA9
	
	//����USART Rx Ϊ���ù��� USART1_RX GPIOA.10
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;				//PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		//��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);					//��ʼ��GPIOA.10
	
	//��2�������ô���Ӳ������
	USART_InitStructure.USART_BaudRate=baud;									  //������
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;					  // �ֳ�Ϊ8Ϊ���ݸ�ʽ
	USART_InitStructure.USART_StopBits=USART_StopBits_1;						  //һ��ֹͣλ
	USART_InitStructure.USART_Parity=USART_Parity_No;						      //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //��Ӳ������������
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;                  //�շ�ģʽ
	
	USART_Init(USART1,&USART_InitStructure);    			//��ʼ������1
	
#if EN_USARTI_RX
	
	//
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);	//�������ڽ����ж�
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);	//�������ڿ����ж�
	
#endif

	//
	USART_Cmd(USART1,ENABLE);	
}

/*
***************************************************************************
*          �� �� ����
*          ����˵����
*          ��   �Σ���
*          �� �� ֵ���� 
***************************************************************************
*/

void USART1_IRQHandler(void)		//����1�жϷ������
{
	uint8_t Res=Res;
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)   //�����жϣ����յ�һ���ֽ����ݣ�
	{
		USART_RX_BUF[RxCounter++]=USART1->DR;
	}
	if(USART_GetFlagStatus(USART1,USART_IT_IDLE)!=RESET)
	{
		Res=USART1->SR; //��SR�Ĵ���
		Res=USART1->DR; //��DR�Ĵ���
		ReceiveState = 1;   //��ǽ���״̬��Ϊ
	}
}

/*
***************************************************************************
*          �� �� ����
*          ����˵����
*          ��   �Σ���
*          �� �� ֵ���� 
***************************************************************************
*/

void Uart0_STA_Clr(void)
{
	RxCounter = 0;
	ReceiveState = 0;
}


#if 1
#pragma import(__use_no_semihosting)

//��׼�⺯����Ҫ��֧�ֺ���
struct __FILE
{
	int handle;
};

FILE __stdout;

void _sys_exit(int x)
{
	x = x;
}

/*
***************************************************************************
*          �� �� ����
*          ����˵����
*          ��   �Σ���
*          �� �� ֵ���� 
***************************************************************************
*/

int fputc(int ch,FILE *f)
{
	while((USART1->SR&0x40)==0){};
	USART1->DR = (u8)ch;
	return ch;
	
}

#endif

/*
***************************************************************************
*          �� �� ����
*          ����˵����
*          ��   �Σ���
*          �� �� ֵ���� 
***************************************************************************
*/
void USART1_Send_Data(uint8_t *buf,uint8_t len)
{
	uint8_t t;
	for(t=0;t<len;t++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
		USART_SendData(USART1,buf[t]);
	}
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
}
