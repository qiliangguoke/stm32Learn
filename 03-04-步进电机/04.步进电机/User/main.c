#include "bsp.h" /* 底层硬件驱动 */
/*
STM32 每个系列都会有唯一的一个芯片序列号（96 位 bit）：
STM32F10X 的地址是 0x1FFFF7E8 
STM32F20X 的地址是 0x1FFF7A10
STM32F30X 的地址是 0x1FFFF7AC
STM32F40X 的地址是 0x1FFF7A10
STM32L1XX 的地址是 0x1FF80050
*/
/* SN 起始地址 */
#define STM32F10X_SN_ADDR 0x1FFFF7E8
/* 定义例程名和例程发布日期 */
#define EXAMPLE_NAME "WSNEP_V01-105_UART 实验（CO2）"
#define EXAMPLE_DATE "2019-08-02"
#define DEMO_VER "1.0"
/* 仅允许本文件内调用的函数声明 */
static void PrintfLogo(void);
static void PrintfHelp(void);
/*
*********************************************************************************************************
* 函 数 名: main
* 功能说明: c 程序入口
* 形 参：无
* 返 回 值: 错误代码(无需处理)
*********************************************************************************************************
*/
int main(void)
{
	uint8_t lcd_id[12]; /* 存放 LCD ID 字符串 */
	uint8_t ucKeyCode;
	uint16_t co2_value=0;
	
	uint8_t SYN6288_Write_CMD[12]={0xFD,0x00,0x09,0x01,0x01,0xB5,0xC2,0xD6,0xC2,0xC2,0xD7,0x82};//向语音播报 发送命令
	uint8_t SYN6288_Write_CMD_1[12]={0xFD,0x00,0x09,0x01,0x01,0x73,0x6F,0x75,0x6E,0x64,0x6E,0xF9};//向语音播报 发送命令
/*
ST 固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f10x.c 文件，主要功能是
配置 CPU 系统的时钟，内部 Flash 访问时序，配置 FSMC 用于外部 SRAM
*/
	bsp_Init(); /* 硬件初始化 */
	PrintfLogo(); /* 打印例程信息到串口 1 */
	PrintfHelp(); /* 打印操作提示 */
	bsp_Init_28byj48();
	bsp_StartAutoTimer(0, 1000); /* 定时器 0 周期 1000 毫秒 */
/* 进入主程序循环体 */
	while(1) 
	{
		dirction();
		bsp_Idle(); /* CPU 空闲时执行的函数，在 bsp.c */
		if (bsp_CheckTimer(0)) /* 定时到 */
		{
			bsp_LedToggle(1);
		}
		
	/* 处理按键事件 */
		ucKeyCode = bsp_GetKey();
		if (ucKeyCode > 0)
		{
		/* 有键按下 */
			switch(ucKeyCode)
			{
				case WKUP_DOWN://WKUP
				{
					
				}break;
				case KEY0_DOWN://KEY0
				{
					
				}break;
			}
		}
	}
}
/*
*********************************************************************************************************
* 函 数 名: PrintfHelp
* 功能说明: 打印操作提示
* 形 参：无
* 返 回 值: 无
*********************************************************************************************************
*/
static void PrintfHelp(void)
{
	printf("操作提示:\r\n");
	printf("1.本程序中，每 1 秒 DS0 红灯翻转一次\r\n");
	printf("2.每 1 秒读取并显示一次 CO2 数据，注意 CO2 上电预热 3 分钟后数据才准确\r\n");
	printf("\r\n\r\n");
}
/*
*********************************************************************************************************
* 函 数 名: PrintfLogo
* 功能说明: 打印例程名称和例程发布日期, 接上串口线后，打开串口调试助手观察结果
* 形 参：无
* 返 回 值: 无
*********************************************************************************************************
*/
static void PrintfLogo(void)
{
/* 检测 CPU ID */
{
	uint32_t CPU_Sn0, CPU_Sn1, CPU_Sn2;
	CPU_Sn0 = *(__IO uint32_t*)(STM32F10X_SN_ADDR);
	CPU_Sn1 = *(__IO uint32_t*)(STM32F10X_SN_ADDR + 4);
	CPU_Sn2 = *(__IO uint32_t*)(STM32F10X_SN_ADDR + 8);
	printf("\r\nCPU : STM32F103ZET6, LQFP144, UID = %08X %08X %08X\n\r"
	, CPU_Sn2, CPU_Sn1, CPU_Sn0);
}
	printf("\r\n");
	printf("*************************************************************\r\n");
	printf("* 例程名称 : %s\r\n", EXAMPLE_NAME);/* 打印例程名称 */
	printf("* 例程版本 : %s\r\n", DEMO_VER); /* 打印例程版本 */
	printf("* 发布日期 : %s\r\n", EXAMPLE_DATE); /* 打印例程日期 */
	/* 打印 ST 固件库版本，这 3 个定义宏在 stm32f10x.h 文件中 */
	printf("* 固 件 库 版 本 : V%d.%d.%d (STM32F10x_StdPeriph_Driver)\r\n", 
	__STM32F10X_STDPERIPH_VERSION_MAIN,
	__STM32F10X_STDPERIPH_VERSION_SUB1,__STM32F10X_STDPERIPH_VERSION_SUB2);
	printf("* \r\n"); /* 打印一行空格 */
	printf("*************************************************************\r\n");
}
/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
