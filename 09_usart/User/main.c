

#include "bsp.h"				/* 底层硬件驱动 */

uint8_t USART_RX_BUF[USART_REC_LEN];	//接收缓冲，最大USART_rec_LEN个字节，末字节为换行符
uint8_t ReceiveState;				//接收状态标志
uint16_t RxCounter;		


#define STM32F10X_SN_ADDR 0x1FFFF7E8


#define EXAMPLE_NAME   "郭文龙_2班_串口1（打印实验）"
#define EXAMPLE_DATE		"2023.-5-1"
#define DEMO_VER		"1.0"

static void PrintLogo(void);
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
	uint16_t t;
	uint16_t len;
	uint8_t  n;
	/*
		ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f10x.c 文件，主要功能是
	配置CPU系统的时钟
	*/
	bsp_Init();		/* 硬件初始化 */
	PrintLogo();
	printf("DS0正在闪烁（闪烁频率=1Mz）\r\n");
	printf("操作案件会打印按键事件\r\n");
	
	bsp_StartAutoTimer(0,500);
	while(1)
	{
		
		//if(bsp_CheckTimer(0))
		//{
		//	bsp_LedToggle(1);
			
		//}
		
		
		ucKeyCode=bsp_GetKey();
		if(ucKeyCode>0)
		
		{
			switch(ucKeyCode)
			{
				case WKUP_DOWN://WKUP 按下
				{		
					bsp_BeepToggle();
					printf("WKUP键按下,蜂鸣器报警\r\n");
				}break;
				case WKUP_UP:		/*WUKP键弹起*/
					bsp_BeepOff();				
					printf("WUKP键弹起蜂鸣器停止报警\r\n");
					break;			
				case KEY0_LONG:	//key0长按
				{					
					n=3;
					bsp_LedOn(2);
					printf("KEY0_UP长按，绿灯亮起\r\n");
					
				}break;
				case KEY0_DOWN:
				{																																				
					n=1;									
				}break;
				case KEY0_UP:		/*KEY0键弹起*/		
					if(n==1){
						bsp_LedToggle(1);
						n=0;
						printf("KEY0_UP键短按,控制红灯亮灭\r\n");
					}
					if(n==3){
						printf("KEY0_UP键弹起，绿灯熄灭\r\n");
						n=0;
						bsp_LedOff(2);
					}						
					break;				
			}
			
		}
		
		if(ReceiveState)
		{
			
			len=RxCounter;
			printf("\r\n你发送的消息为：\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1,USART_RX_BUF[t]);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
			}
			printf("\r\n\r\n");
			Uart0_STA_Clr();
		}
	}
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
