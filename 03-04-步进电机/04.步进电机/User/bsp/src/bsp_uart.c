#include "bsp.h"

uint8_t  USART_RX_BUF[USART_REC_LEN];       //接收换船，最大USART_REC_LEN个字节，末字节位换行符
uint8_t  ReceiveState;
uint16_t RxCounter;
/*
***************************************************************************
*          函 数 名：
*          功能说明：
*          形   参：无
*          返 回 值：无 
***************************************************************************
*/

void bsp_InitUart(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
#if EN_USARTI_RX
	NVIC_InitTypeDef NVIC_InitStructure;
#endif
	
	//串口1 TX=PA9  RX=PA10
	//第一步配置GPIO
	//打开GPIO时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//打开UART时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//配置USART Tx 为复用功能 USART1_TX GPIOA.9
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;					//PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  			//复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);					//初始化GPIOA9
	
	//配置USART Rx 为复用功能 USART1_RX GPIOA.10
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;				//PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		//浮空输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);					//初始化GPIOA.10
	
	//第2步：配置串口硬件参数
	USART_InitStructure.USART_BaudRate=baud;									  //波特率
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;					  // 字长为8为数据格式
	USART_InitStructure.USART_StopBits=USART_StopBits_1;						  //一个停止位
	USART_InitStructure.USART_Parity=USART_Parity_No;						      //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //无硬件数据流控制
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;                  //收发模式
	
	USART_Init(USART1,&USART_InitStructure);    			//初始化串口1
	
#if EN_USARTI_RX
	
	//
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);	//开启串口接收中断
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);	//开启串口空闲中断
	
#endif

	//
	USART_Cmd(USART1,ENABLE);	
}

/*
***************************************************************************
*          函 数 名：
*          功能说明：
*          形   参：无
*          返 回 值：无 
***************************************************************************
*/

void USART1_IRQHandler(void)		//串口1中断服务程序
{
	uint8_t Res=Res;
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)   //接收中断（接收到一个字节数据）
	{
		USART_RX_BUF[RxCounter++]=USART1->DR;
	}
	if(USART_GetFlagStatus(USART1,USART_IT_IDLE)!=RESET)
	{
		Res=USART1->SR; //读SR寄存器
		Res=USART1->DR; //读DR寄存器
		ReceiveState = 1;   //标记接收状态置为
	}
}

/*
***************************************************************************
*          函 数 名：
*          功能说明：
*          形   参：无
*          返 回 值：无 
***************************************************************************
*/

void Uart0_STA_Clr(void)
{
	RxCounter = 0;
	ReceiveState = 0;
}


#if 1
#pragma import(__use_no_semihosting)

//标准库函数需要的支持函数
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
*          函 数 名：
*          功能说明：
*          形   参：无
*          返 回 值：无 
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
*          函 数 名：
*          功能说明：
*          形   参：无
*          返 回 值：无 
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
