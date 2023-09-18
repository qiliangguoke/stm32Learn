/*
*********************************************************************************************************
*
*	模块名称 : 模块
*	文件名称 : .h
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/
#include "bsp.h"


#ifdef EN_UART5_RX 							//如果使能了接收

//接收缓存区
uint8_t UART5_RX_BUF[UART5_BUF_LEN]; 		//接收缓冲,最大 UART4_BUF_LEN 个字节.

//接收到的数据长度
uint8_t UART5_RX_CNT=0;

/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/

void UART5_IRQHandler(void)
{
	uint8_t res; 
	
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) //接收到数据
	{
		res =USART_ReceiveData(UART5); 	//读取接收到的数据
		if(UART5_RX_CNT<UART5_BUF_LEN)
	{
		UART5_RX_BUF[UART5_RX_CNT]=res; //记录接收到的值
		UART5_RX_CNT++; //接收数据增加 1 
	} 
	} 
} 
#endif
/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitUart5(uint32_t bound)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//使能 GPIOC 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);	//使能 UART4 时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 		//PC10 TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			  //PC11 RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5,ENABLE);   //复位串口 4
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5,DISABLE);  //停止复位

#ifdef EN_UART5_RX //如果使能了接收
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8 位数据长度
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;///奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
	 
	USART_Init(UART5, &USART_InitStructure);//初始化串口

	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn; //使能串口 4 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //先占优先级 2 级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //从优先级 2 级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); //根据 NVIC_InitStruct 中指定的参数初始化外设 NVIC 寄存器

	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启中断
	
	USART_Cmd(UART5, ENABLE); //使能串口

#endif

}

/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/

void UART5_Send_Data(uint8_t *buf,uint8_t len)
{
	uint8_t t;
	 
	for(t=0;t<len;t++) //循环发送数据
	{ 
		while(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET); 
		USART_SendData(UART5,buf[t]);
	}
	while(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
		
	UART5_RX_CNT=0; 
}
/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void UART5_Receive_Data(uint8_t *buf,uint8_t *len)
{
	uint8_t rxlen = UART5_RX_CNT;
	uint8_t i=0;
	
	*len=0; //默认为 0
	delay_ms(10); //等待 10ms,连续超过 10ms 没有接收到一个数据,则认为接收结束
	if(rxlen==UART5_RX_CNT&&rxlen) //接收到了数据,且接收完成了
	{
	for(i=0;i<rxlen;i++)
	{
		buf[i]=UART5_RX_BUF[i];
	}
	*len=UART5_RX_CNT;  //记录本次数据长度
	UART5_RX_CNT=0; 	//清零
	}
}
/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
