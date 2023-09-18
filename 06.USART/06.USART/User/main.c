/*
*********************************************************************************************************
*
*	模块名称 : 主程序入口
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    
*
*	Copyright (C), 2014-2019, 天津德致伦电子
*
*********************************************************************************************************
*/

#include "bsp.h"				/* 底层硬件驱动 */
uint8_t USART_RX_BUF[USART_REC_LEN];	//接收缓冲，最大USART_rec_LEN个字节，末字节为换行符
uint8_t ReceiveState;				//接收状态标志
uint16_t RxCounter;		
void Uart0_STA_Clr(void);
/*

STM32每个系列都有唯一的一个芯片序列号（96位bit）:
	STM32F10X 的地址是	0xFFFF7E8
	STM32F20X 的地址是	0xFFF7A10
	STM32F30X 的地址是	0xFFFF7AC
	STM32F40X 的地址是	0xFFF7A10
	STM32L1XX 的地址是	0x1FF80050
*/
/*SN起始地址*/
#define STM32F10X_SN_ADDR 0x1FFFF7E8

/*定义例程名和例程发布时间*/
#define	EXAMPLE_NAME	"黄求胜_2班_串口（打印实验）"
#define EXAMPLE_DATE	"2023-4-28"
#define DEMO_VER		"1.0"

/*仅允许本文件内调用的函数声明*/
static void PrintfLogo(void);

/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: c程序入口
*	形    参：无
*	返 回 值: 错误代码(无需处理)
*********************************************************************************************************
*/
int main(void)
{
	uint8_t ucKeyCode;	/*按键代码*/
	uint16_t t;
	uint16_t len;
	/*
		ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f10x.c 文件，主要功能是
	配置CPU系统的时钟
	*/
	bsp_Init();		/* 硬件初始化 */
	PrintfLogo();	/*打印例程信息到串口1*/
	
	printf("DS0正在闪烁（闪烁频率 = 1Hz）\r\n");
	printf("操作按键会打印按键事件\r\n");

	bsp_StartAutoTimer(0,500);		/*启动1个500ms的自动重装的定时器*/
	
	/*进入主程序循环体*/
	while(1)
	{
//		if(bsp_CheckTimer(0))
//		{
//			/*每隔500ms进来一次*/
//			bsp_LedToggle(1);	/*翻转DS0的状态*/
//			
//			//printf("请输入数据，以回车键结束\r\n");
//		}
		/*
		按键检测由后台systick中断服务程序实现，我们只需要调用bsp_GetKey读取键值即可。
		这个函数不会等待按键按下，这样我们可以在while循环内做其他的事情
		*/
		ucKeyCode = bsp_GetKey(); 	/*读取按键，无键按下时返回KEY_NONE=0*/
		if(ucKeyCode!=KEY_NONE)
		{
			switch(ucKeyCode)
			{
				case WKUP_DOWN:		/*WKUP键按下*/
						bsp_BeepOn();
					printf("WUKP键按下蜂鸣器进行报警\r\n");
					break;
				case WKUP_UP:		/*WUKP键弹起*/
					bsp_BeepOff();
					printf("WUKP键弹起蜂鸣器停止报警\r\n");
					break;
				case KEY0_LONG:
					bsp_LedToggle(2);
					printf("key0键长按\r\n");
				break;
				case KEY0_DOWN:		/*KEY0键按下*/
					bsp_LedOn(1);
					printf("KEY0键按下红灯亮\r\n");
					break;
				case KEY0_UP:		/*KEY0键弹起*/
					//bsp_LedToggle(1);
					bsp_LedOff(1);
					printf("KEY0键弹起红灯灭\r\n");
					break;

				
				default:
				/*其他的键值不处理*/
				break;
			}
		}
		if(ReceiveState)
		{
			len = RxCounter;	//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1,USART_RX_BUF[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
			Uart0_STA_Clr();//串口0状态清楚
		}
	}
}
/*
*********************************************************************************************************
*	函 数 名: PrintfLogo
*	功能说明: 打印例程名称和例程发布时间，接上串口线后，打开串口调试助手观察结果
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void PrintfLogo(void)
{
	/*检测CPI ID*/
	{
		uint32_t CPU_Sn0,CPU_Sn1,CPU_Sn2;
		
		CPU_Sn0=*(__IO uint32_t*)(STM32F10X_SN_ADDR);
		CPU_Sn1=*(__IO uint32_t*)(STM32F10X_SN_ADDR+4);
		CPU_Sn2=*(__IO uint32_t*)(STM32F10X_SN_ADDR+8);
		
		printf("\r\nCPU:STM32F103ZET6,LQFP144,UID = %08X%08X%08X\n\r",CPU_Sn2,CPU_Sn1,CPU_Sn0);
	}
	printf("\r\n");
	printf("***************************************\r\n");
	printf("*例程名称   	：%s\r\n",EXAMPLE_NAME);/*打印例程名称*/
	printf("*例程版本	：%s\r\n",DEMO_VER);	/*打印例程版本*/
	printf("*发布时间	：%s\r\n",EXAMPLE_DATE);/*打印例程日期*/
	
	/*打印ST固件库版本，这3个定义宏在stm32f10x.h文件中*/
	printf("固件库版本	：V%d.%d.%d		(STM32F10x_StdPeriph_Driver)\r\n",
	__STM32F10X_STDPERIPH_VERSION_MAIN,
		__STM32F10X_STDPERIPH_VERSION_SUB1,__STM32F10X_STDPERIPH_VERSION_SUB2);
	printf("*\r\n");/*打印一行空格*/
	printf("***************************************");
}


/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
