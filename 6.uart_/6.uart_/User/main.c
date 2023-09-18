/*
*********************************************************************************************************
*
*	模块名称 : 主程序入口
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 : 串口
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0   2023-04-28  范佳倩   首发
*
*	Copyright (C), 2014-2019, 天津德致伦电子
*
*********************************************************************************************************
*/

#include "bsp.h"				/* 底层硬件驱动 */

/*SN起始地址*/
#define STM32F10X_SN_ADDR 0x1FFFF7E8
/*定义例程名和例程发布日期*/
#define EXAMPLE_NAME  "范佳倩-2班-uart（打印实验）"
#define	EXAMPLE_DATE "2023-4-29"
#define DEMO_VER	"1.0"
#define UID "UID=570966413137484205D8FF39"
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
	uint8_t ucKeyCode;		/*按键代码*/
	uint16_t t;
	uint16_t len;
	uint8_t flag=0,flag1=0;
	uint8_t i;
	/*
		ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f10x.c 文件，主要功能是
	配置CPU系统的时钟，内部Flash访问时序，配置FSMC用于外部SRAM
	*/
	bsp_Init();		/* 硬件初始化 */
	PrintfLogo();	/*打印例程信息到串口1*/
	
	//printf("DS0 正在闪烁(闪烁频率=1Hz)\r\n");
	printf("操作按键会打印按键事件\r\n");
	
	bsp_StartAutoTimer(0,500);		/*启动1个500ms的自动重装的定时器*/
	
	while(1)
	{
			if(bsp_CheckTimer(0))	/*判断定时器超时时间*/
			{
				/*每隔500ms进来一次*/
				//bsp_LedToggle(1);/*翻转DS0的状态*/
				
				//printf("请输入数据，以回车键结束\r\n");
			}
			/*按键检测由后台systick中断服务程序实现我们只需要调用bsp_GetKey读取键值即可。这个函数不会
			等待按键按下，这样我们可以在while循环内做其他的事情*/
			ucKeyCode = bsp_GetKey();		/*读取键值，无键按下时返回KEY_NONE=0*/
			if(ucKeyCode!=KEY_NONE)
			{
				/*有键按下*/
				switch(ucKeyCode)
				{
					case WKUP_LONG://WKUP长按       
					{	
						flag=1;
						bsp_LedOn(1);
						printf("WKUP键长按过程中,(按下一秒后)DS0常亮\r\n");
						break;
					}
					case WKUP_UP://WKUP弹起       
					{	
						if(flag==1)
						{
							bsp_LedOff(1);
							bsp_LedOff(2);
							printf("WKUP长按弹起后DS0、DS1熄灭\r\n");
						}else
						{
							bsp_LedOn(2);
							printf("WKUP短按弹起后DS1常亮\r\n");
						}
						flag=0;
						break;
					}
					case KEY0_LONG://KEY0键按下       
					{	
						flag1=1;
						bsp_BeepToggle();
						printf("KEY0键长按时，蜂鸣器响\r\n");
						break;
					}
					case KEY0_UP://KEY0键弹起       
					{	
						if(flag1==1)
						{
							bsp_BeepOff();
							printf("KEY0键弹起，蜂鸣器静音\r\n");
						}else
						{
							printf("KEY0短按结束，弹起后DS1闪烁三次\r\n");
							
							bsp_LedOff(1);
							bsp_LedOff(2);
							for(i=0;i<3;i++)
							{
								bsp_LedOn(2);
								bsp_DelayMS(250);
								bsp_LedOff(2);
								bsp_DelayMS(250);
							}
						}
						flag1=0;
						break;
					}
					default:/*其他的键值不处理*/
						break;
			}
		}
		if( ReceiveState )
		{
			len = RxCounter;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为：\r\n\r\n");
			for(t=0;t<len;t++)
      {
				USART_SendData(USART1,USART_RX_BUF[t]);//向串口1发送数据
				while( USART_GetFlagStatus( USART1,USART_FLAG_TC )!=SET);//等待发送结束
      }
			printf("\r\n\r\n");	//插入换行
			Uart0_STA_Clr();//串口0状态清除
		}		
	
}
}


/*
*********************************************************************************************************
*	函 数 名: PrintfLogo
*	功能说明: 打印例程名称和例程发布日期，接上串口线后，打开串口调试助手观察结果
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void PrintfLogo(void)
{
	/*检测CPU ID*/
	{
		uint32_t CPU_Sn0,CPU_Sn1,CPU_Sn2;
		CPU_Sn0=*(__IO uint32_t*)(STM32F10X_SN_ADDR);
		CPU_Sn1=*(__IO uint32_t*)(STM32F10X_SN_ADDR+4);
		CPU_Sn2=*(__IO uint32_t*)(STM32F10X_SN_ADDR+8);
		
		printf("\r\nCPU:STM32F103ZET6,LQFP144,UID=%08X%08X%08X\n\r",CPU_Sn2,CPU_Sn1,CPU_Sn0);
	}
	printf("\r\n");
	printf("**********************************************************\r\n");
	printf("* 例程名称	：%s\r\n",EXAMPLE_NAME);/*打印例程名称*/
	printf("* 例程版本	：%s\r\n",DEMO_VER);/*打印例程版本*/
	printf("* 发布日期	：%s\r\n",EXAMPLE_DATE);/*打印例程日期*/
	printf("* UID	：%s\r\n",UID);/*打印UID*/
	
	/*打印ST固体库版本，这3个定义宏在stm32f10x.h文件中*/
	printf("* 固件库版本：V5%d.%d.%d(STM32F10x_StdPeriph_Driver)\r\n",__STM32F10X_STDPERIPH_VERSION_MAIN,__STM32F10X_STDPERIPH_VERSION_SUB1,__STM32F10X_STDPERIPH_VERSION_SUB2);
	printf("\r\n");/*打印一行空格*/
	printf("**********************************************************\r\n");
}


/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
