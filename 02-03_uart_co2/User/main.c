///////////////////////////////////////
/* 头文件包含区 */
#include "bsp.h"
#include "bsp_uart4.c"
//////////////////////////////////////
/* 宏定义区域 */

#define STM32F10X_SN_ADDR 0x1FFFF7E8
#define EXAMPLE_NAME   "郭文龙_2班_温度传感器实验（打印实验）"
#define EXAMPLE_DATE	"2023.-5-22"
#define DEMO_VER		"1.0"

///////////////////////////////////////
/* 外部变量申明区 */

//uint8_t ReceiveState;				//接收状态标志
//uint16_t RxCounter;	
//uint8_t USART_RX_BUF[USART_REC_LEN];
///////////////////////////////////////
/* 函数申明区 */

static void PrintfHelp(void);

static void PrintLogo(void);
//static void DAC_Dsiap(void);

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
	uint8_t lcd_id[12]; /* 存放 LCD ID 字符串 */
	/* 按键代码 */
	uint8_t ucKeyCode;
	
	uint16_t  co2_value= 0;
	/*
		ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f10x.c 文件，主要功能是
	配置CPU系统的时钟
	*/
	bsp_Init();		/* 硬件初始化 */
	
	PrintLogo();	/* 打印例程信息 */
	PrintfHelp();	/* 打印提示信息 */
	bsp_InitUart4(9600);/*注意，串口 4 初始化放在 LCD 之前*/
	bsp_StartAutoTimer(0, 1000); /* 定时器 0 周期 300 毫秒 */
	
	while(1)
	{
		bsp_Idle();		
	
		if (bsp_CheckTimer(0)) /* 判断定时器超时时间 */
		{
			
			/* 每隔 500ms 进来一次 */
			bsp_LedToggle(1); /* 翻转 DS0 的状态 */
			
			//co2_value=CO2_READ();
			co2_value = CO2_READ();//读取二氧化碳值
			if( co2_value != 65535 )
			{
				printf("二氧化碳浓度%d \r\n",co2_value);
			}
		}
	
		/* 处理按键事件 */
		ucKeyCode = bsp_GetKey();
		if (ucKeyCode > 0)
		{
			
			/* 有键按下 */
			switch(ucKeyCode)
			{
				case WKUP_DOWN:
				{
					
					
					
				}break;
				case KEY0_DOWN:
				{
					
				}break;
			}
		}
			
	}
}
/*
*********************************************************************************************************
*	函 数 名:PrintfHelp
*	功能说明: 打印提示信息
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
static void PrintfHelp(void)
{
	printf("操作提示:\r\n");
	printf("1.本程序中，每 300 毫秒 DS0 红灯翻转一次\r\n");
	printf("2.改变 DAC1 输出电压值的方法：WKUP 增大，KEY0 减小\r\n");
	printf("3.按键 WKUP 和 KEY0 均会触发 ADC 采样，采样结果通过串口打印\r\n");
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
