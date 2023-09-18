#include "bsp.h"
#include "bsp_uart.h"
//定义
uint8_t USART_RX_BUF[USART_REC_LEN];//接收缓冲，最大USART_REC_LEN个字节  末字节为换行符
uint8_t ReceiveState;				//接收状态标记
uint16_t RxCounter;
/*
*********************************************************************************************************
*	函 数 名: bsp_InitUart
*	功能说明: 初始化CPU的USART1串口硬件设备
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitUart1(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
#if EN_USART1_RX   //如果使能了接收
	NVIC_InitTypeDef NVIC_InitStructure;
#endif
	/*串口1 TX=PA9    RX=PA10*/
	/*第1步：配置GPIO*/
	/*打开GPIO时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	/*打开UART时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	/*配置USART Tx为复用功能*/   //USART1_TX		GPIOA.9
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;			//PA.9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);			//初始化GPIOA.10
	/*配置USART Rx为复用功能*/   //USART1_RX		GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);			//初始化GPIOA.10
	
	/*第2步：配置串口硬件参数*/
	USART_InitStructure.USART_BaudRate=baud;			/*波特率*/
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;			/*字长为8位数据格式*/
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			/*一个停止位*/
	USART_InitStructure.USART_Parity=USART_Parity_No;				/*无奇偶校验位*/
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;			/*无硬件数据流控制*/
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;			/*收发模式*/
	
	USART_Init(USART1,&USART_InitStructure);		/*初始化串口1*/
#if EN_USART1_RX	//如果使能了接收
	/*第3步：Usart1 NVIC配置*/
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;		//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;		//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);				//根据指定的参数初始化VIC寄存器
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);		/*开启串口接收中断*/
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);		/*开启串口空闲中断*/
#endif
	/*第4步：使能串口1*/
	USART_Cmd(USART1,ENABLE);/*使能串口*/
}

/*
*********************************************************************************************************
*	函 数 名: USART1_IRQHandler
*	功能说明: USART1中断，主要是接收中断和空闲中断
*	形    参：无
*	返 回 值: 无
	注	  意：读取USARTx->SR能避免莫名其妙的错误
*********************************************************************************************************
*/
void USART1_IRQHandler(void)		//串口1中断服务程序
{
	uint8_t Res=Res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)//接收中断（接收到一个字节数据）
	{
		USART_RX_BUF[RxCounter++]=USART1->DR;//把接收到的字节保存
	}
	if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET)	//接收中断（接收到1帧数据）
	{
		Res=USART1->SR;//读取SR寄存器
		Res=USART1->DR;//读取DR寄存器（先读SR,再读DR,就是为了清除IDLE中断）
		ReceiveState=1;//标记接收状态置位
	}
}

/*
*********************************************************************************************************
*	函 数 名:Uart0_STA_Clr 
*	功能说明: 串口0状态清除函数
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void Uart0_STA_Clr(void)
{
	RxCounter = 0;//串口BUF计数清零
	ReceiveState = 0;//接收状态清零
}
/*
*******************************************************
*/
//加入以下代码，支持printf函数，而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
/*标准库需要的支持函数*/
struct __FILE
{
	int handle;
};
FILE __stdout;
/*定义_sys_exit()以避免使用半主机模式*/
void _sys_exit(int x)
{
	x=x;
}
/*
*********************************************************************************************************
*	函 数 名:fputc 
*	功能说明: 重定义putc函数，这样可以使用printf函数从串口1打印输出
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
int fputc(int ch,FILE *f)
{
	while((USART1->SR&0x40)==0){};//循环发送，直到发送完毕
	USART1->DR=(u8)ch;
	return ch;
}
#endif

/*
*********************************************************************************************************
*	函 数 名: USART1_Send_Data
*	功能说明: USART1发送len个字
*	形    参：buf：发送区首地址
*			  len：发送的字节数0~255
*	返 回 值: 无
*********************************************************************************************************
*/
void USART1_Send_Data(uint8_t *buf,uint8_t len)
{
	uint8_t t;
	for(t=0;t<len;t++)//循环发送数据
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_SendData(USART1,buf[t]);
	}
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
}











