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

/* 定义 LCD 显示相关公共信息 */
#define DEV_NAME "WSNEP_V01"
#define LCD_EXAMPLE_NAME "RC522 TEST"

/*仅允许本文件内调用的函数声明*/
static void PrintfLogo(void);
static void PrintfHelp(void);
//static void DAC_Dsiap(void);

void IC_test ( void )
{
char cStr [ 30 ];
char EptStr[30];
uint8_t ucArray_ID [ 4 ]; /*先后存放 IC 卡的类型和 UID(IC 卡序列号)*/ 
uint8_t ucStatusReturn; /*返回状态 */ 
static u16 ucLineCount = 170; /* LCD 起始行为 170 */
sprintf ( EptStr, " "); /* LCD 显示空白，为清空 LCD 显示做准备 */
 /*寻卡*/
if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK ) 
{
/*若失败再次寻卡*/
ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );
}
if ( ucStatusReturn == MI_OK )
{
printf("----------------------------\r\n");
printf("CardType is:0x%02X%02X\r\n",ucArray_ID [ 0 ],ucArray_ID [ 1 ]);
/*防冲撞（当有多张卡进入读写器操作范围时，防冲突机制会从其中选择一张进行操作）*/
if ( PcdAnticoll ( ucArray_ID ) == MI_OK ) 
{
sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",
 ucArray_ID [ 0 ],
 ucArray_ID [ 1 ],
 ucArray_ID [ 2 ],
 ucArray_ID [ 3 ] );
printf ( "%s\r\n",cStr );
printf("----------------------------\r\n\r\n");
if ( ucLineCount == 290 ) /* 最多同时显示 6 行 */
{
for(ucLineCount=170;ucLineCount<=290;ucLineCount+=20)
{
LCD_ShowString(30,ucLineCount,200,16,16,(u8*)EptStr); //循环清空 6 行 LCD 显示
}
ucLineCount=170; /* 设置 LCD 起始行为 170 */
}
LCD_ShowString(30,ucLineCount,200,16,16,(u8*)cStr); //显示读取到的卡号
ucLineCount += 20; /* 设置下一次 LCD 显示行，自增 20 */
}
}
}

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
uint8_t ucKeyCode;
	
	//uint16_t co2_value=0;
	
	
bsp_Init(); /* 硬件初始化 */
PrintfLogo(); /* 打印例程信息到串口 1 */
PrintfHelp(); /* 打印操作提示 */
TFTLCD_Init(); /* TFTLCD 初始化*/
POINT_COLOR=BLUE; 
sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将 LCD ID 打印到 lcd_id 数组。
LCD_ShowString(30,40,200,24,24,(uint8_t*)DEV_NAME);
LCD_ShowString(30,70,200,16,16,(uint8_t*)LCD_EXAMPLE_NAME);
LCD_ShowString(30,90,200,16,16,(uint8_t*)DEMO_VER);
LCD_ShowString(30,110,200,16,16,lcd_id); //显示 LCD ID 
LCD_ShowString(30,130,200,12,12,(uint8_t*)EXAMPLE_DATE);
bsp_InitRc522(); /* 初始化 RC522 的 SPI 端口 */
PcdReset(); /* 复位 RC522 */
M500PcdConfigISOType('A'); /* 设置工作方式 */
bsp_StartAutoTimer(0, 300); /* 定时器 0 周期 300 毫秒 */
bsp_StartAutoTimer(1, 500); /* 定时器 1 周期 500 毫秒 */
/* 进入主程序循环体 */
while(1) 
{
bsp_Idle(); /* CPU 空闲时执行的函数，在 bsp.c */
if (bsp_CheckTimer(0)) /* 定时到 */
{
bsp_LedToggle(1);
}
if (bsp_CheckTimer(1)) /* 定时到 */
{
IC_test();
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
*	函 数 名: PrintfHelp
*	功能说明: 打印操作提示
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void PrintfHelp(void)
{
	printf("操作提示:\r\n");
	printf("1.本程序中，每300msDS0红灯翻转一次\r\n");
	printf("2.无需进行操作，每 1 秒自动刷新显示，颜色及对应的序号\r\n");
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
