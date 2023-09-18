///////////////////////////////////////
/* 头文件包含区 */
#include "bsp.h"

//////////////////////////////////////
/* 宏定义区域 */

#define STM32F10X_SN_ADDR 0x1FFFF7E8
#define EXAMPLE_NAME   "郭文龙_2班_温度传感器实验（打印实验）"
#define EXAMPLE_DATE	"2023.-5-22"
#define DEMO_VER		"1.0"

/* 定义 LCD 显示相关公共信息 */
#define DEV_NAME "WSNEP_V01"
#define LCD_EXAMPLE_NAME "TFTLCD TEST"

///////////////////////////////////////
/* 外部变量申明区 */

uint8_t ReceiveState;				//接收状态标志
uint16_t RxCounter;	
uint8_t USART_RX_BUF[USART_REC_LEN];	//接收缓冲，最大USART_rec_LEN个字节，末字节为换行符

///////////////////////////////////////
/* 函数申明区 */

static void PrintfHelp(void);

static void PrintLogo(void);

const uint8_t TEXT_Buffer[]={"WSNEP_V01 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)
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
	uint8_t ucKeyCode;
	uint8_t x=1;
	uint8_t lcd_id[12]; /* 存放 LCD ID 字符串 */
	/* 按键代码 */
	
	
	
	

	
	/*
		ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f10x.c 文件，主要功能是
	配置CPU系统的时钟
	*/
	bsp_Init();		/* 硬件初始化 */
	PrintLogo();	/* 打印例程信息 */
	PrintfHelp();	/* 打印提示信息 */
	
	TFTLCD_Init(); /* TFTLCD 初始化*/

	POINT_COLOR=RED; 
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将 LCD ID 打印到 lcd_id 数组。
	POINT_COLOR=RED; 
	
	
	bsp_StartAutoTimer(0,300); /* 定时器 0 周期 300 毫秒 */
	bsp_StartTimer(1,100); /* 定时器 1 单次 100 毫秒 */
	
	while(1)
	{
		ucKeyCode=bsp_GetKey();
	
		if (bsp_CheckTimer(0)) /* 判断定时器超时时间 */
		{
			/* 每隔 500ms 进来一次 */
			bsp_LedToggle(1); /* 翻转 DS0 的状态 */
		}
	
		if(bsp_CheckTimer(1))
		{
//			//LCD_ShowNum(90,130,x,2,16);
//			switch(x)
//			{
//				case 1:LCD_Fill(150,70,230,230,BLACK);break;
//				case 2:LCD_Fill(150,70,230,230,BLUE);break;
//				case 3:LCD_Fill(150,70,230,230,RED);break;
//				case 4:LCD_Fill(150,70,230,230,MAGENTA);break;
//				case 5:LCD_Fill(150,70,230,230,GREEN);break;
//				case 6:LCD_Fill(150,70,230,230,CYAN);break;
//				case 7:LCD_Fill(150,70,230,230,YELLOW);break;
//				case 8:LCD_Fill(150,70,230,230,BRRED);break;
//				case 9:LCD_Fill(150,70,230,230,GRAY);break;
//				case 10:LCD_Fill(150,70,230,230,LGRAY);break;
//				case 11:LCD_Fill(150,70,230,230,BROWN);break;
//			}
//			x++;
//			if(x==12)
//			{
//				x=1;
//			}
			
					
			bsp_StartTimer(1,1000); /* 定时器 1 单次 1000 毫秒 */
			
			
			
		}
		if(ucKeyCode>0)
		
		{
			switch(ucKeyCode)
			{
				case WKUP_DOWN://WKUP 按下
				{	
					LCD_Clear(0xFFFF);					
					LCD_ShowString(30,40,200,16,16,(uint8_t*)"     ");
					LCD_ShowString(30,70,200,16,16,(uint8_t*)"  *  ");	
					LCD_ShowString(30,90,200,16,16,(uint8_t*)"  **  ");
					LCD_ShowString(30,130,200,16,16,(uint8_t*)" *** ");
					LCD_ShowString(30,170,200,16,16,(uint8_t*)"*****");
				}break;
				case WKUP_UP:		/*WUKP键弹起*/
				{
				
				}
					break;			
				case KEY0_LONG:	//key0长按
				{					
					
					
				}break;
				case KEY0_DOWN:
				{																																				
					LCD_Clear(0xFFFF);	
					LCD_ShowString(30,40,200,16,16,(uint8_t*)"*****");
					LCD_ShowString(30,70,200,16,16,(uint8_t*)" *** ");
					LCD_ShowString(30,90,200,16,16,(uint8_t*)"  **  ");
					LCD_ShowString(30,130,200,16,16,(uint8_t*)"  *  ");
					LCD_ShowString(30,170,200,16,16,(uint8_t*)"     ");									
				}break;
				case KEY0_UP:		/*KEY0键弹起*/		
				{
					
				}						
					break;				
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
	printf("2.无需进行操作，每 1 秒自动刷新显示，颜色及对应的序号\r\n");
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
