
/*
*********************************************************************************************************
*
*	模块名称 : 模块
*	文件名称 : bsp_tpad.h
*	说    明 : 电容按键
*	修改记录 :
*		版本号  日期  2023-5-18  作者 郭文龙   说明
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/
#include "bsp.h"
/* 本函数内部调用的函数 申明*/

static void TPAD_TIM_GPIO_Config(void);
static void TPAD_TIM_Config(void);
static void bsp_TpadTimInit(void);
static void bsp_TpadReset(void);
static uint16_t TPAD_Get_Val(void);
static uint16_t TPAD_Get_MaxVal( uint8_t n );

/* tpad 空载值 */
vu16 tpad_default_val = 0; /* 空载的时候(没有手按下),计数器需要的时间 */
/*
*********************************************************************************************************
*	函 数 名:TPAD_Get_Val
*	功能说明: 电容触摸按键获取充电时间,如果超时，则直接返回定时器的计数值形
*	形    参：
*	返 回 值: 电容按键充电捕获到高电平的计数器值
********************************************************************************************************
*/
static uint16_t TPAD_Get_Val ( void )
{
	bsp_TpadReset(); /* 每次捕获的时候，必须先复位放电 */
				/* 等待捕获上升沿 */
	 while ( TIM_GetFlagStatus ( TIMx_CAP_TIM, TIMx_CAP_TIM_IT_CCx ) == RESET ) 
	 {
		/* 一般充电时间都是在 ms 级别以内，很少会超过定时器的最大定时值 */
		if ( TIM_GetCounter ( TIMx_CAP_TIM ) > TPAD_ARR_MAX_VAL - 500 )
		{
			/* 超时了,直接返回 CNT 的值 */
			return TIM_GetCounter ( TIMx_CAP_TIM ); 
		}
	 };
	return TIMx_CAP_TIM_GetCapturex_FUN ( TIMx_CAP_TIM );
}
/*
*********************************************************************************************************
*	函 数 名:TPAD_Get_MaxVal
*	功能说明: 电容触摸按键获取充电时间,采样多次，获取最大值 
*	形    参：连续采样次数
*	返 回 值: n 次采样的最大值
********************************************************************************************************
*/
static uint16_t TPAD_Get_MaxVal( uint8_t n )
{
	 uint16_t temp = 0;
	 uint16_t res = 0;
	 while ( n-- )
	 {
		temp = TPAD_Get_Val(); //得到一次值
		if ( temp > res )
		{
			res = temp;
		}
	 };
	 return res;
}
/*
*********************************************************************************************************
*	函 数 名:bsp_TpadScan
*	功能说明: 扫描触摸按键
*	形    参：连续采样次数
*	返 回 值:  0,没有按下;1,有按下;
********************************************************************************************************
*/
uint8_t bsp_TpadScan(void)
{
	static uint8_t keyen = 0; //0,可以开始检测;>0,还不能开始检测
	uint8_t res = 0;
	uint8_t sample = 3; //默认采样次数为 3 次
	uint16_t rval;
	rval = TPAD_Get_MaxVal ( sample );
	/* 大于 tpad_default_val+TPAD_GATE_VAL,有效 */
	if ( rval > ( tpad_default_val + TPAD_GATE_VAL ) ) 
	{
		if ( keyen == 0 )
		{
			res = 1; //keyen==0,有效
		}
		//printf("r:%d\r\n",rval);
	keyen = 3; /* 至少要再过 3 次之后才能按键有效 */
	}
	if ( keyen )
	{
		keyen--;
	}
	return res;
}
/*
*********************************************************************************************************
*	函 数 名:TPAD_TIM_GPIO_Config
*	功能说明:电容触摸按键 GPIO 初始化函数
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
static void TPAD_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIMx_CAP_TIM_APBxClock_FUN( TIMx_CAP_TIM_CLK, ENABLE ); /* 使能 TIMx 时钟 */
	RCC_APB2PeriphClockCmd( TIMx_CAP_TIM_CH_GPIO_CLK, ENABLE ); /* 使能对应电容触摸输入端口时钟 */
	GPIO_InitStructure.GPIO_Pin = TIMx_CAP_TIM_CH_PIN; /* 电容触摸端口配置 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; /* 端口速度 50MHz */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; /* 浮空输入 */
	GPIO_Init ( TIMx_CAP_TIM_CH_PORT, &GPIO_InitStructure ); /* 初始化触摸端口 */
}
/*
*********************************************************************************************************
*	函 数 名: TPAD_TIM_Config
*	功能说明: 电容触摸按键 定时器 初始化函数
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
static void TPAD_TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIMx_CAP_TIM_APBxClock_FUN( TIMx_CAP_TIM_CLK, ENABLE ); //使能 TIMx 时钟
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = TPAD_ARR_MAX_VAL; /* 设置自动重装载寄存器 */
	TIM_TimeBaseStructure.TIM_Prescaler = TIMx_CAP_TIM_PSC; /* 设置时钟预分频寄存器 */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; /* 设置时钟分割，TDTS=Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* TIM 向上计数模式 */
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; /* 重复计数器的值，没用到，不用设置 */
	TIM_TimeBaseInit(TIMx_CAP_TIM, &TIM_TimeBaseStructure); /* 初始化 TIMx */
	TIM_ICInitStructure.TIM_Channel = TIMx_CAP_TIM_CHANNEL_x; /* 配置输入捕获的通道，需要根据具体的GPIO 来配置 */
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;/* 上升沿捕获 */
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; /* 输入通道和捕获通道的映射关系，这里选择直连*/
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; /* 配置输入分频,不分频 */
	TIM_ICInitStructure.TIM_ICFilter = 0x03; /* IC2F=0011b 配置输入滤波器 8 个定时器时钟周期滤波 */
	TIM_ICInit( TIMx_CAP_TIM, &TIM_ICInitStructure ); /* 定时器输入捕获初始化 */
	/* 使能计数器 */
	TIM_Cmd( TIMx_CAP_TIM,ENABLE);
}
/*
*********************************************************************************************************
*	函 数 名:bsp_TpadTimInit
*	功能说明:电容触摸按键 定时器 引脚初始化函数 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
static void bsp_TpadTimInit(void)
{
	TPAD_TIM_GPIO_Config();//电容触摸按键 GPIO 初始化函数
	TPAD_TIM_Config();//电容触摸按键 定时器 初始化函数
}
/*
*********************************************************************************************************
*	函 数 名:bsp_TpadReset
*	功能说明:根据 TIM 得到 RCC 寄存器 
*	形    参：
*	返 回 值: TIM 外设时钟名
********************************************************************************************************
*/
static void bsp_TpadReset ( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd ( TIMx_CAP_TIM_CH_GPIO_CLK, ENABLE ); //使能电容触摸端口时钟
	//设置 GPIOA.1 为推挽使出
	GPIO_InitStructure.GPIO_Pin = TIMx_CAP_TIM_CH_PIN; /* 电容触摸端口配置 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; /* 推挽输出 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; /* 端口速度为 50MHz */
	GPIO_Init ( TIMx_CAP_TIM_CH_PORT, &GPIO_InitStructure );
	GPIO_ResetBits ( TIMx_CAP_TIM_CH_PORT, TIMx_CAP_TIM_CH_PIN ); /* 触摸端口输出低电平,放电 */
	delay_ms ( 5 ); /* 放电等待，放电时间很快，一般是 us 级别的 */
	TIM_SetCounter ( TIMx_CAP_TIM, 0 ); /* 设置计数器归零 */
	TIM_ClearITPendingBit ( TIMx_CAP_TIM, TIMx_CAP_TIM_IT_CCx | TIMx_CAP_TIM_IT_UPDATE ); //清除中断标志
	/* 设置触摸端口为浮空输入 ,用于输入捕获*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; /* 浮空输入 */
	GPIO_Init ( TIMx_CAP_TIM_CH_PORT, &GPIO_InitStructure ); /* 初始化端口 */
}
/*
*********************************************************************************************************
*	函 数 名:bsp_TpadInit
*	功能说明: 获得空载的时候触摸按键的取值.
*	形    参：
*	返 回 值: : 0,初始化成功;1,初始化失败
********************************************************************************************************
*/
uint8_t bsp_TpadInit(void)
{
	uint16_t buf[10];
	uint16_t temp;
	uint8_t j, i;
	bsp_TpadTimInit();
	for ( i = 0; i < 10; i++ ) /* 连续读取 10 次 */
	{
		buf[i] = TPAD_Get_Val();
		delay_ms ( 10 );
	}
	for ( i = 0; i < 9; i++ ) /* 排序 */
	{
		for ( j = i + 1; j < 10; j++ )
		{
			if ( buf[i] > buf[j] ) /* 升序排列 */
			{
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}
	
	temp = 0;
	
	for ( i = 2; i < 8; i++ )
	{
		temp += buf[i]; /* 取中间的 6 个数据进行平均 */
	}
	tpad_default_val = temp / 6;
	 
	printf ( "tpad_default_val:%d\r\n", tpad_default_val );
	
	printf("\r\n\r\n");
	if ( tpad_default_val > TPAD_ARR_MAX_VAL / 2 )
	{
		return 1; /* 初始化遇到超过 TPAD_ARR_MAX_VAL/2 的数值,不正常! */
	}
	return 0;
}
/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
