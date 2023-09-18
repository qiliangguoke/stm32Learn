///////////////////////////////////////
/* 头文件包含区 */
#include "bsp.h"

//////////////////////////////////////
/* 宏定义区域 */

#define STM32F10X_SN_ADDR 0x1FFFF7E8
#define EXAMPLE_NAME   "郭文龙_2班_pwm（打印实验）"
#define EXAMPLE_DATE		"2023.-5-17"
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
static void SetRpValue(uint8_t DutyCycle);
static void RgbLedRpInit(uint16_t DutyCycle);

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
	uint16_t ucRedDucyCycle = 50;
	
	/*
		ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f10x.c 文件，主要功能是
	配置CPU系统的时钟
	*/
	bsp_Init();		/* 硬件初始化 */
	PrintLogo();	/* 打印例程信息 */
	PrintfHelp();	/* 打印提示信息 */
	RgbLedRpInit(ucRedDucyCycle); /* 初始化 RGB*/
	
	printf("---ucRedDucyCycle 的初始值为 %d---\r\n",ucRedDucyCycle);
	while(1)
	{
		bsp_Idle();		
		ucKeyCode=bsp_GetKey();	/* 读取按键 */
		if(ucKeyCode>0)		
		{
			switch(ucKeyCode)
			{
				case WKUP_DOWN://WKUP 按下
				{		
					{
						ucRedDucyCycle+=10;
						SetRpValue(ucRedDucyCycle); // RGB G 灯的情况  逐渐变暗
						
						printf("---ucRedDucyCycle 值为 %d,逐渐变暗---\r\n",ucRedDucyCycle);
					}
					
				}break;
				case KEY0_DOWN:
				{
					if(ucRedDucyCycle >= 10)
					{
						ucRedDucyCycle-=10;
						SetRpValue(ucRedDucyCycle); //RGB G 灯的情况 /逐渐变亮
						printf("---ucRedDucyCycle 值为 %d,逐渐变亮---\r\n",ucRedDucyCycle);
					}
				}break;
				default:
				{

				}break;			
			}			
		}		
	}
}
/*
*********************************************************************************************************
*	函 数 名:RgbLedRpInit
*	功能说明: RGB 的红灯初始化
*	形    参：DutyCycle 为占空比，取值范围为 0~100
*	返 回 值: 
********************************************************************************************************
*/
static void RgbLedRpInit(uint16_t DutyCycle)
{
	DutyCycle *= 100; 
	/*
	void bsp_SetTIMOutPWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, TIM_TypeDef* TIMx, uint8_t _ucChannel,
	uint32_t _ulFreq, uint32_t _ulDutyCycle);
	*/
	bsp_SetTIMOutPWM(GPIOB,GPIO_Pin_9,TIM4,4,90000,DutyCycle);/* PB9 对应上 TIM4 的 CH4，90KHZ */
}
/*
*********************************************************************************************************
*	函 数 名:SetRpValue
*	功能说明: 设置 RGB 的蓝灯占空比
*	形    参：uint8_t DutyCycle:占空比，取值范围 0~100
*	返 回 值: 
********************************************************************************************************
*/
static void SetRpValue(uint8_t DutyCycle)
{
	uint16_t temp = 0;
	if(DutyCycle==100)
	{
		TIM_SetCompare4(TIM4,799);//800-1 90KHz 时
	}
	temp = DutyCycle * 9; //注意对于 90KHz 的频率，ARR 的满量程为 900,占空比位 0~100，即步进值为 9
	TIM_SetCompare4(TIM4,temp);
}
/*
*********************************************************************************************************
* 函 数 名: TIM7_IRQHandler
* 功能说明: TIM7 定时中断服务程序
* 返 回 值: 
*********************************************************************************************************
*/
void TIM7_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		bsp_LedToggle(2);
	}
}

static void PrintfHelp(void)
{
	printf("操作提示:\r\n");
	printf("1. 设置 RGB 的蓝灯 PWM 频率是 90KHz，初始占空比是 50%%\r\n");
	printf("2. WKUP 键 - RGB R 逐渐变暗\r\n");
	printf("3. KEY0 键 - RGB R 逐渐变亮\r\n");
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
