///////////////////////////////////////
/* 头文件包含区 */
#include "bsp.h"

//////////////////////////////////////
/* 宏定义区域 */

#define STM32F10X_SN_ADDR 0x1FFFF7E8
#define EXAMPLE_NAME   "郭文龙_2班_独立看门狗（打印实验）"
#define EXAMPLE_DATE		"2023.-5-10"
#define DEMO_VER		"1.0"

///////////////////////////////////////
/* 外部变量申明区 */

uint8_t ReceiveState;				//接收状态标志
uint16_t RxCounter;	
uint8_t USART_RX_BUF[USART_REC_LEN];	//接收缓冲，最大USART_rec_LEN个字节，末字节为换行符

///////////////////////////////////////
/* 函数申明区 */

static void PrintfHelp(void);
static void PrintLogo(void);

///////////////////////////////////////


/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
				/* 底层硬件驱动 */
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
	/* 按键代码 */
	uint8_t ucKeyCode;
	
	/*
		ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f10x.c 文件，主要功能是
	配置CPU系统的时钟
	*/
	bsp_Init();		/* 硬件初始化 */
	PrintLogo();	/* 打印例程信息 */
	PrintfHelp();	/* 打印提示信息 */
	
	bsp_InitIwdg(IWDG_Prescaler_64,625); /* 初始化独立看门狗 */
	
	/* 启动300ms的定时器 */
	bsp_StartAutoTimer(0,300);
	
	/* 启动 1 个 20ms 的自动重装的定时器 */
	bsp_StartAutoTimer(1,20); 
	
	while(1)
	{
		if (bsp_CheckTimer(0)) /* 判断定时器超时时间 */
		{
			bsp_LedToggle(2);	/* 反转绿灯 */
		}
		if (bsp_CheckTimer(1)) /* 判断定时器超时时间 */
		{
			//bsp_LedToggle(0);
			IWDG_Feed();		/* 喂狗 */
		}
				
		ucKeyCode=bsp_GetKey();	/* 读取按键 */
		if(ucKeyCode>0)		
		{
			switch(ucKeyCode)
			{
				case WKUP_DOWN://WKUP 按下
				{		
					bsp_StopTimer(1); /* 停止软件定时器 1 */
					
					
					printf("停止软件定时器 1");
					
				}break;
				default:
				{

				}break;			
			}			
		}		
	}
}
static void PrintfHelp(void)
{
	printf("操作提示:\r\n");
	printf("1.本程序中，每 300msDS0 绿灯翻转一次\r\n");
	printf("2.启动 1 个周期大约为 1 秒的 IWDG 看门狗\r\n");
	printf("3.每 20ms 喂狗一次，使用软件定时器\r\n");
	printf("4.WKUP 停止每 20ms 一次的喂狗行为，使 IWDG 复位\r\n");
	printf("5.通过串口打印状态信息\r\n");
	printf("\r\n\r\n");
}

static void PrintLogo(void)
{
	{
		uint32_t CPU_Sn0,CPU_Sn1,CPU_Sn2;
		
		CPU_Sn0=*(__IO uint32_t*)(STM32F10X_SN_ADDR);
		CPU_Sn1=*(__IO uint32_t*)(STM32F10X_SN_ADDR+4);
		CPU_Sn2=*(__IO uint32_t*)(STM32F10X_SN_ADDR+8);		
		printf("\r\nCPU:STM32F103ZET6,LQFP144,UID=%08X %08X %08X\n\r",CPU_Sn2,CPU_Sn1,CPU_Sn0);	
	}
	printf("\r\n");
	printf("***************************************************************************************************\r\n");
	printf("例程名称：%s\r\n",EXAMPLE_NAME);
	printf("历程版本：%s\r\n",DEMO_VER);
	printf("发布日期：%s\r\n",EXAMPLE_DATE);
	
	printf("*固   件   库    版    本：V%d.%d.%d  (STM32F10x_sTdPeriph_Driver)\r\n",__STM32F10X_STDPERIPH_VERSION_MAIN,__STM32F10X_STDPERIPH_VERSION_SUB1,__STM32F10X_STDPERIPH_VERSION_SUB2);
	printf("*\r\n");
	printf("***************************************************************************************************\r\n");
}

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
