/*
*********************************************************************************************************
*
*	模块名称 : 主程序入口
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 : 跑马灯例子。使用了systick中断实现精确定时，控制LED指示灯闪烁频率。
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2019-08-02 waroyal  首发
*
*	Copyright (C), 2014-2019, 天津德致伦电子
*
*********************************************************************************************************
*/

#include "bsp.h"				/* 底层硬件驱动 */

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

	while(1)
	{
		bsp_Idle();
		
		ucKeyCode=bsp_GetKey();
		if(ucKeyCode>0)
		
		{
			switch(ucKeyCode)
			{
				case WKUP_DOWN:
				{
					bsp_BeepToggle();
				}break;
				
				case KEY0_DOWN:
				{
					bsp_LedToggle(2);
				}break;
				case KEY1_DOWN:
				{
					bsp_LedToggle(2);
				}break;
				case KEY2_DOWN:
				{
					bsp_LedToggle(1);
					bsp_LedToggle(2);
				}break;
				case SYS_DOWN_WKUP_KEY0:
				{
					uint8_t i;
					bsp_LedOff(1);
					bsp_LedOff(2);
					
					for(i=0;i<3;i++)
					{
						bsp_LedOn(1);
						bsp_DelayMS(250);
						bsp_LedOff(1);
						bsp_DelayMS(250);
					}
				}break;
				case SYS_DOWN_KEY0_KEY1:
				{
					uint8_t i;
					bsp_LedOff(1);
					bsp_LedOff(2);
					
					for(i=0;i<3;i++)
					{
						bsp_LedOn(2);
						bsp_DelayMS(250);
						bsp_LedOff(2);
						bsp_DelayMS(250);
					}
				}break;
				default: break;
			}
			
		}
		delay_ms(10);
	}
}

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
