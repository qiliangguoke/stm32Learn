#include "bsp.h"

#ifdef EN_UART4_RX //���ʹ���˽���
//���ջ�����
uint8_t UART4_RX_BUF[UART4_BUF_LEN]; //���ջ���,��� UART4_BUF_LEN ���ֽ�.
//���յ������ݳ���
uint8_t UART4_RX_CNT=0;

void USART4_IRQHandler(void)	//����1�жϷ������
{
	uint8_t Res;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) 	//�����ж�(���յ�һ���ֽ�����)
	{
		Res =USART_ReceiveData(UART4); //��ȡ���յ�������
		if(UART4_RX_CNT<UART4_BUF_LEN)
		{
			UART4_RX_BUF[UART4_RX_CNT]=Res; //��¼���յ���ֵ
			UART4_RX_CNT++; //������������ 1 
		}	
		
		
	}
}
#endif
	void bsp_InitUart4(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//���ʹ���˽���
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/*����1 TX = PC10		RX = Pc11*/
	
	/*��1��������GPIO*/

	/*��GPIOʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	/*��UARTʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	
	/*����USARTTx Ϊ���ù���*/ //USART1_TX	GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			//PC10
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//�����������
	GPIO_Init(GPIOC,&GPIO_InitStructure);				//��ʼ��GPIOA.9
	
	/*����USARTRx Ϊ���ù���*/ //USART1_RX	GPIOA.10��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;					//PC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
	GPIO_Init(GPIOC,&GPIO_InitStructure);				//��ʼ��GPIOA.10
	
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4,ENABLE);//��λ���� 4
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4,DISABLE);//ֹͣ��λ

	

#ifdef EN_UART4_RX		//���ʹ���˽���


/*��2�������ô���Ӳ������*/
	USART_InitStructure.USART_BaudRate = baud;			/*������*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; /*�ֳ�Ϊ8λ���ݸ�ʽ*/
	USART_InitStructure.USART_StopBits =USART_StopBits_1 ;		/*һ��ֹͣλ*/
	USART_InitStructure.USART_Parity = USART_Parity_No;			/*����żУ��λ*/
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /*��Ӳ������������*/
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx; /*�շ�ģʽ*/
	 
	USART_Init(UART4,&USART_InitStructure);	/*��ʼ������1*/
	/*��3����Usart4 NVIC����*/
	
	NVIC_InitStructure.NVIC_IRQChannel=UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	/*��ռ���ȼ�3*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			/*�����ȼ�3*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				/*IRQͨ��ʹ��\*/
	NVIC_Init(&NVIC_InitStructure);			/*����ָ���Ĳ�����ʼ��VIC�Ĵ���*/
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);/*�������ڽ����ж�*/
	
	/*��4���� ʹ�ܴ���1*/
		USART_Cmd(UART4,ENABLE);	/*ʹ�ܴ���*/
#endif

	
}







void UART4_Send_Data(uint8_t *buf,uint8_t len)
{
	uint8_t t;
	for(t=0;t<len;t++)			//ѭ����������
	{	
		while(USART_GetFlagStatus(UART4, USART_FLAG_TC)== RESET);
		USART_SendData(UART4,buf[t]);
	}//��ʹ��һ��ѭ����ѭ�������������е�ÿ���ֽڣ�Ȼ��ͨ��USART_SendData������ÿ���ֽڷ��͵�USART1ģ��
	
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC)== RESET);
	UART4_RX_CNT=0;
}

void UART4_Receive_Data(uint8_t *buf,uint8_t *len)
{
	uint8_t rxlen = UART4_RX_CNT;
	uint8_t i=0;
	*len=0; //Ĭ��Ϊ 0
	delay_ms(10); //�ȴ� 10ms,�������� 10ms û�н��յ�һ������,����Ϊ���ս���
	if(rxlen==UART4_RX_CNT&&rxlen) //���յ�������,�ҽ��������
	{
		for(i=0;i<rxlen;i++)
		{
			buf[i]=UART4_RX_BUF[i];
		}
		*len=UART4_RX_CNT; //��¼�������ݳ���
		UART4_RX_CNT=0; //����
	}
}
