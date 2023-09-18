/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : .h
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/
#include "bsp.h"


#ifdef EN_UART5_RX 							//���ʹ���˽���

//���ջ�����
uint8_t UART5_RX_BUF[UART5_BUF_LEN]; 		//���ջ���,��� UART4_BUF_LEN ���ֽ�.

//���յ������ݳ���
uint8_t UART5_RX_CNT=0;

/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void UART5_IRQHandler(void)
{
	uint8_t res; 
	
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) //���յ�����
	{
		res =USART_ReceiveData(UART5); 	//��ȡ���յ�������
		if(UART5_RX_CNT<UART5_BUF_LEN)
	{
		UART5_RX_BUF[UART5_RX_CNT]=res; //��¼���յ���ֵ
		UART5_RX_CNT++; //������������ 1 
	} 
	} 
} 
#endif
/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitUart5(uint32_t bound)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ�� GPIOC ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);	//ʹ�� UART4 ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 		//PC10 TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			  //PC11 RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5,ENABLE);   //��λ���� 4
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5,DISABLE);  //ֹͣ��λ

#ifdef EN_UART5_RX //���ʹ���˽���
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8 λ���ݳ���
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;///��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ
	 
	USART_Init(UART5, &USART_InitStructure);//��ʼ������

	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn; //ʹ�ܴ��� 4 �ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ� 2 ��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ� 2 ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //���� NVIC_InitStruct ��ָ���Ĳ�����ʼ������ NVIC �Ĵ���

	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�����ж�
	
	USART_Cmd(UART5, ENABLE); //ʹ�ܴ���

#endif

}

/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void UART5_Send_Data(uint8_t *buf,uint8_t len)
{
	uint8_t t;
	 
	for(t=0;t<len;t++) //ѭ����������
	{ 
		while(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET); 
		USART_SendData(UART5,buf[t]);
	}
	while(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
		
	UART5_RX_CNT=0; 
}
/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void UART5_Receive_Data(uint8_t *buf,uint8_t *len)
{
	uint8_t rxlen = UART5_RX_CNT;
	uint8_t i=0;
	
	*len=0; //Ĭ��Ϊ 0
	delay_ms(10); //�ȴ� 10ms,�������� 10ms û�н��յ�һ������,����Ϊ���ս���
	if(rxlen==UART5_RX_CNT&&rxlen) //���յ�������,�ҽ��������
	{
	for(i=0;i<rxlen;i++)
	{
		buf[i]=UART5_RX_BUF[i];
	}
	*len=UART5_RX_CNT;  //��¼�������ݳ���
	UART5_RX_CNT=0; 	//����
	}
}
/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
