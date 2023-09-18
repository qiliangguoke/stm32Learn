/*
*********************************************************************************************************
*
*	模块名称 : 主程序入口
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023-5-19	黄求胜
*
*	Copyright (C), 2014-2019, 天津德致伦电子
*
*********************************************************************************************************
*/

#include "bsp.h"		 /* 底层硬件驱动 */

uint8_t ReceiveState;    //接收状态标志
uint16_t RxCounter; 
uint8_t USART_RX_BUF[USART_REC_LEN]; //接收缓冲，最大USART_rec_LEN个字节，末字节为换行符

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
#define	EXAMPLE_NAME	"黄求胜_2班_UART实验(CO2)"
#define EXAMPLE_DATE	"2023-6-12"
#define DEMO_VER		"1.0"

/*仅允许本文件内调用的函数声明*/
static void PrintfLogo(void);
static void PrintfHelp(void);
//static void DAC_Dsiap(void);

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
	
	
	
	uint8_t ucKeyCode;
	
	
	
	/*
		ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f10x.c 文件，主要功能是
	配置CPU系统的时钟
	*/
	bsp_Init();		/* 硬件初始化 */
		
	PrintfLogo();	/* 打印例程信息到串口1 */
	
	PrintfHelp();	/* 打印操作提示 */
	
	
	bsp_InitI2C();
	bsp_InitSht3x();
	bsp_StartAutoTimer(0, 1000); /* 定时器0周期1000毫秒 */

	
	
	
	
	/*进入主程序循环体*/
	while(1)
	{
		bsp_Idle();	/* CPU空闲时执行的函数，在bsp.c */
		
		if (bsp_CheckTimer(0)) /*定时到*/
		{
			/* 每隔500ms进来一次 */
			bsp_LedToggle(1);
			if( SHT3X_GetValue() )
			{
				bsp_InitI2C();
				bsp_InitSht3x();
			}
			else
			{
				printf("温度为%.1f℃，湿度为%.1f%%RH\r\n", Tem_Value, RH_Value);
			}
			
		}
		
		/* 处理按键事件 */
		ucKeyCode = bsp_GetKey();
		if (ucKeyCode>0)
		{
			/* 有键按下 */
			switch(ucKeyCode)
			{
				case WKUP_DOWN://wkup
					{
					
					}break;
				case KEY0_DOWN://key0
					{
					
					}break;
			}
		}
	}
}

/*
*********************************************************************************************************
*	函 数 名: PrintfHelp
*	功能说明: 打印操作提示
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void PrintfHelp(void)
{
	printf("操作提示:\r\n");
	printf("1.本程序中，每 500msDS0 红灯翻转一次\r\n");
	printf("2.每 500ms 读取显示显示温湿度信息\r\n");
	printf("\r\n\r\n");
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
	printf("*例程版本	：%s\r\n",DEMO_VER);		/*打印例程版本*/
	printf("*发布时间	：%s\r\n",EXAMPLE_DATE);	/*打印例程日期*/
	
	/*打印ST固件库版本，这3个定义宏在stm32f10x.h文件中*/
	printf("固件库版本	：V%d.%d.%d		(STM32F10x_StdPeriph_Driver)\r\n",
	__STM32F10X_STDPERIPH_VERSION_MAIN,
		__STM32F10X_STDPERIPH_VERSION_SUB1,__STM32F10X_STDPERIPH_VERSION_SUB2);
	printf("*\r\n");/*打印一行空格*/
	printf("***************************************");
}


/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
