#include "bsp.h"

#ifdef EN_UART4_RX //如果使能了接收
//接收缓存区
uint8_t UART4_RX_BUF[UART4_BUF_LEN]; //接收缓冲,最大 UART4_BUF_LEN 个字节.
//接收到的数据长度
uint8_t UART4_RX_CNT=0;

void USART4_IRQHandler(void)	//串口1中断服务程序
{
	uint8_t Res;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) 	//接收中断(接收到一个字节数据)
	{
		Res =USART_ReceiveData(UART4); //读取接收到的数据
		if(UART4_RX_CNT<UART4_BUF_LEN)
		{
			UART4_RX_BUF[UART4_RX_CNT]=Res; //记录接收到的值
			UART4_RX_CNT++; //接收数据增加 1 
		}	
		
		
	}
}
#endif
	void bsp_InitUart4(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//如果使能了接收
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/*串口1 TX = PC10		RX = Pc11*/
	
	/*第1步：配置GPIO*/

	/*打开GPIO时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	/*打开UART时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	
	/*配置USARTTx 为复用功能*/ //USART1_TX	GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			//PC10
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//复用推挽输出
	GPIO_Init(GPIOC,&GPIO_InitStructure);				//初始化GPIOA.9
	
	/*配置USARTRx 为复用功能*/ //USART1_RX	GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;					//PC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//浮空输入
	GPIO_Init(GPIOC,&GPIO_InitStructure);				//初始化GPIOA.10
	
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4,ENABLE);//复位串口 4
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4,DISABLE);//停止复位

	

#ifdef EN_UART4_RX		//如果使能了接收


/*第2步：配置串口硬件参数*/
	USART_InitStructure.USART_BaudRate = baud;			/*波特率*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; /*字长为8位数据格式*/
	USART_InitStructure.USART_StopBits =USART_StopBits_1 ;		/*一个停止位*/
	USART_InitStructure.USART_Parity = USART_Parity_No;			/*无奇偶校验位*/
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /*无硬件数据流控制*/
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx; /*收发模式*/
	 
	USART_Init(UART4,&USART_InitStructure);	/*初始化串口1*/
	/*第3步：Usart4 NVIC配置*/
	
	NVIC_InitStructure.NVIC_IRQChannel=UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	/*抢占优先级3*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			/*子优先级3*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				/*IRQ通道使能\*/
	NVIC_Init(&NVIC_InitStructure);			/*根据指定的参数初始化VIC寄存器*/
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);/*开启串口接收中断*/
	
	/*第4步： 使能串口1*/
		USART_Cmd(UART4,ENABLE);	/*使能串口*/
#endif

	
}







void UART4_Send_Data(uint8_t *buf,uint8_t len)
{
	uint8_t t;
	for(t=0;t<len;t++)			//循环发送数据
	{	
		while(USART_GetFlagStatus(UART4, USART_FLAG_TC)== RESET);
		USART_SendData(UART4,buf[t]);
	}//它使用一个循环来循环遍历缓冲区中的每个字节，然后通过USART_SendData函数将每个字节发送到USART1模块
	
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC)== RESET);
	UART4_RX_CNT=0;
}

void UART4_Receive_Data(uint8_t *buf,uint8_t *len)
{
	uint8_t rxlen = UART4_RX_CNT;
	uint8_t i=0;
	*len=0; //默认为 0
	delay_ms(10); //等待 10ms,连续超过 10ms 没有接收到一个数据,则认为接收结束
	if(rxlen==UART4_RX_CNT&&rxlen) //接收到了数据,且接收完成了
	{
		for(i=0;i<rxlen;i++)
		{
			buf[i]=UART4_RX_BUF[i];
		}
		*len=UART4_RX_CNT; //记录本次数据长度
		UART4_RX_CNT=0; //清零
	}
}
