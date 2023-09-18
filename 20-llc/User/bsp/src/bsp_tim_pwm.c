
/*
*********************************************************************************************************
*
*	模块名称 : pwm模块
*	文件名称 : bsp_tim_pwm.c
*	说    明 : 定时器
*	修改记录 :
*		版本号  日期  2023-5-17      作者  郭文龙   说明
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/
#include "bsp.h"
/*
*********************************************************************************************************
* 函 数 名: bsp_GetRCCofGPIO
* 功能说明: 根据 GPIO 得到 RCC 寄存器
* 形 参：
* 返 回 值: GPIO 外设时钟名
*********************************************************************************************************
*/
uint32_t bsp_GetRCCofGPIO(GPIO_TypeDef* GPIOx)
{
	uint32_t rcc = 0;
	if (GPIOx == GPIOA)
	{
		rcc = RCC_APB2Periph_GPIOA;
	}
	else if (GPIOx == GPIOB)
	{
		rcc = RCC_APB2Periph_GPIOB;
	}
	else if (GPIOx == GPIOC)
	{
		rcc = RCC_APB2Periph_GPIOC;
	}
	else if (GPIOx == GPIOD)
	{
		rcc = RCC_APB2Periph_GPIOD;
	}
	else if (GPIOx == GPIOE)
	{
		rcc = RCC_APB2Periph_GPIOE;
	}
	else if (GPIOx == GPIOF)
	{
		rcc = RCC_APB2Periph_GPIOF;
	}
	else if (GPIOx == GPIOG)
	{
		rcc = RCC_APB2Periph_GPIOG;
	}
		return rcc;
}
/*
*********************************************************************************************************
* 函 数 名: bsp_GetRCCofTIM
* 功能说明: 根据 TIM 得到 RCC 寄存器
* 形 参：
* 返 回 值: TIM 外设时钟名
*********************************************************************************************************
*/
uint32_t bsp_GetRCCofTIM(TIM_TypeDef* TIMx)
{
	uint32_t rcc = 0;
	/*
		APB1 定时器有 TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7
		APB2 定时器有 TIM1, TIM8
	*/
	if (TIMx == TIM1)
	{
		rcc = RCC_APB2Periph_TIM1;
	}
	else if (TIMx == TIM8)
	{
		rcc = RCC_APB2Periph_TIM8;
	}
		/* 下面是APB1时钟 */
	else if (TIMx == TIM2)
	{
		rcc = RCC_APB1Periph_TIM2;
	}
	else if (TIMx == TIM3)
	{
		rcc = RCC_APB1Periph_TIM3;
	}
	else if (TIMx == TIM4)
	{
		rcc = RCC_APB1Periph_TIM4;
	}
	else if (TIMx == TIM5)
	{
		rcc = RCC_APB1Periph_TIM5;
	}
	else if (TIMx == TIM6)
	{
		rcc = RCC_APB1Periph_TIM6;
	}
	else if (TIMx == TIM7)
	{
		rcc = RCC_APB1Periph_TIM7;
	}
	return rcc;
}
/*
*********************************************************************************************************
* 函 数 名: bsp_SetTIMforInt
* 功能说明: 配置 TIM 和 NVIC，用于简单的定时中断. 开启定时中断。 中断服务程序由应用程序实现。
* 形 参: TIMx : 定时器
* 		_ulFreq : 定时频率（Hz）。0表示关闭。
* 		_PreemptionPriority : 中断优先级分组
* 		_SubPriority : 子优先级
* 返 回 值: 
*********************************************************************************************************
*/
void bsp_SetTIMforInt(TIM_TypeDef* TIMx, uint32_t _ulFreq, uint8_t _PreemptionPriority, uint8_t _SubPriority)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //时基结构体 
	uint16_t usPeriod; //暂存的自动重装载寄存器的值 
	uint16_t usPrescaler; // 暂存的时钟预分频寄存器的值
	uint32_t uiTIMxCLK; //暂存的时钟频率
	 /* 使能 TIM 时钟 */
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		RCC_APB2PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
	}
	else
	{
		RCC_APB1PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
	}
	if (_ulFreq == 0) //定时频率为 0
	{
		TIM_Cmd(TIMx, DISABLE); //关闭定时输出 
		/* 关闭 TIM 定时更新中断 (Update) */
		{
			NVIC_InitTypeDef NVIC_InitStructure; //中断结构体在 misc.h 中定义
			uint8_t irq = 0; //中断号, 定义在 stm32f1xx.h
			if (TIMx == TIM1)
				irq = TIM1_UP_IRQn;
			else if (TIMx == TIM2)
				irq = TIM2_IRQn;
			else if (TIMx == TIM3)
				irq = TIM3_IRQn;
			else if (TIMx == TIM4)
				irq = TIM4_IRQn;
			else if (TIMx == TIM5)
				irq = TIM5_IRQn;
			else if (TIMx == TIM6)
				irq = TIM6_IRQn;
			else if (TIMx == TIM7)
				irq = TIM7_IRQn;
			else if (TIMx == TIM8)
				irq = TIM8_UP_IRQn;
			/* 中断优先级 NVIC 设置 */
			NVIC_InitStructure.NVIC_IRQChannel = irq; //TIMx 中断 IRQn
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _PreemptionPriority; //TIMx 抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = _SubPriority; //TIMx 从优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE; //TIMx IRQ 通道失能
			NVIC_Init(&NVIC_InitStructure);//初始化 NVIC 寄存器 
		}
		return;
}
	/*-----------------------------------------------------------------------
		system_stm32f1xx.c 文件中 static void SetSysClockTo72(void) 函数对时钟的配置如下：
			HCLK = SYSCLK 
			RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;//设置 AHB 时钟(HCLK)为系统时钟
			 
			PCLK2 = HCLK
			RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;//设置高速 AHB 时钟(APB2)为 HCLK 时钟
			
			PCLK1 = HCLK
			RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;//设置低速 AHB 时钟(APB1)为 HCLK 的 2 分频
（TIM2-TIM7 输入 TIMxCLK 频率将为 72MHZ/2x2=72MHZ 输入）
			APB1 定时器有 TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7
			APB2 定时器有 TIM1, TIM8 
	----------------------------------------------------------------------- */
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		/* APB2 定时器 */
		uiTIMxCLK = SystemCoreClock;
	}
	else /* APB1 定时器 . */
	{
		uiTIMxCLK = SystemCoreClock; // APB1 clock = SystemCoreClock / 2
	}
	if (_ulFreq < 100) //频率小于 100Hz
	{
		usPrescaler = 10000 - 1; //分频比 = 10000 
		usPeriod = (uiTIMxCLK / 10000) / _ulFreq - 1; //自动重装的值 
	}
	else if (_ulFreq < 3000) //频率大于等于 100Hz 小于 3KHz 
	{
		usPrescaler = 100 - 1; // 分频比 = 100 
		usPeriod = (uiTIMxCLK / 100) / _ulFreq - 1; //自动重装的值 
	}
	else /* 大于等于 3KHz 的频率，无需分频 */
	{
		usPrescaler = 0; //分频比 = 1
		usPeriod = uiTIMxCLK / _ulFreq - 1; //自动重装的值
	}
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = usPeriod; //设置自动重装载寄存器
	TIM_TimeBaseStructure.TIM_Prescaler = usPrescaler; //设置时钟预分频寄存
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割，TDTS=Tck_tim 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //重复计数器的值，没用到，不用设置
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); // 初始化 TIMx 
	TIM_ARRPreloadConfig(TIMx, ENABLE); //使能 ARR 预装载寄存器 
	/* TIM Interrupts enable */
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE); //允许 TIMx 更新中断 
	/* TIMx enable counter */
	TIM_Cmd(TIMx, ENABLE); //使能定时器 TIMx 
	/* 配置 TIM 定时更新中断 (Update) */
	{
		NVIC_InitTypeDef NVIC_InitStructure; //中断结构体在 misc.h 中定义 
		uint8_t irq = 0; // 中断号, 定义在 stm32f1xx.h 
		if (TIMx == TIM1)
			irq = TIM1_UP_IRQn;
		else if (TIMx == TIM2)
			irq = TIM2_IRQn;
		else if (TIMx == TIM3)
			irq = TIM3_IRQn;
		else if (TIMx == TIM4)
			irq = TIM4_IRQn;
		else if (TIMx == TIM5)
			irq = TIM5_IRQn;
		else if (TIMx == TIM6)
			irq = TIM6_IRQn;
		else if (TIMx == TIM7)
			irq = TIM7_IRQn;
		else if (TIMx == TIM8)
			irq = TIM8_UP_IRQn;
		/* 中断优先级 NVIC 设置 */
		NVIC_InitStructure.NVIC_IRQChannel = irq; //TIMx中断IRQn
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _PreemptionPriority; //TIMx 抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = _SubPriority; //TIMx 从优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //TIMx IRQ 通道使能
		NVIC_Init(&NVIC_InitStructure);
	}
}
/*
*********************************************************************************************************
* 函 数 名: bsp_ConfigTimGpio
* 功能说明: 配置 GPIO 和 TIM 时钟， GPIO 连接到 TIM 输出通道
* 形 参:GPIOx
*		GPIO_PinX
*		TIMx
* 		_ucChannel
* 返 回 值: 
*********************************************************************************************************
*/
void bsp_ConfigTimGpio(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinX, TIM_TypeDef* TIMx)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		/* 使能 GPIO 时钟 */
		RCC_APB2PeriphClockCmd(bsp_GetRCCofGPIO(GPIOx), ENABLE);
	 /* 使能 TIM 时钟 */
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		RCC_APB2PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
	}
	else
	{
		RCC_APB1PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
	}
	/* 配置 GPIO */
		GPIO_InitStructure.GPIO_Pin = GPIO_PinX;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOx, &GPIO_InitStructure); 
}
/*
*********************************************************************************************************
* 函 数 名: bsp_SetTIMOutPWM
* 功能说明: 设置引脚输出的 PWM 信号的频率和占空比. 当频率为 0，并且占空为 0 时，关闭定时器，GPIO 输出 0；
* 当频率为 0，占空比为 100%时，GPIO 输出 1.
* 形 参: GPIOx, GPIO_Pin, TIMx 同库函数结构体
*		_ucChannel:通道 1~4
* 		_ulFreq : PWM 信号频率，单位 Hz (实际测试，最大输出频率为 72M / 4 = 18M）. 0 表示禁止输出
* 		_ulDutyCycle : PWM 信号占空比，单位：万分之一。如 5000，表示 50.00%的占空比
* 返 回 值: 
*********************************************************************************************************
*/
void bsp_SetTIMOutPWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, TIM_TypeDef* TIMx, uint8_t _ucChannel,uint32_t _ulFreq, uint32_t _ulDutyCycle)
	{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //时基结构体
		TIM_OCInitTypeDef TIM_OCInitStructure; //输出比较结构体
		uint16_t usPeriod; //暂存的自动重装载寄存器的值
		uint16_t usPrescaler; //暂存的时钟预分频寄存器的值
		uint32_t uiTIMxCLK; //暂存的时钟频率
		bsp_ConfigTimGpio(GPIOx, GPIO_Pin, TIMx);//使能 GPIO 和 TIM 时钟，并连接 TIM 通道到 GPIO
/*-----------------------------------------------------------------------
	system_stm32f10x.c 文件中 static void SetSysClockTo72(void) 函数对时钟的配置如下：
	//HCLK = SYSCLK 
		RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;//设置 AHB 时钟(HCLK)为系统时钟 
	//PCLK2 = HCLK
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;//设置高速 AHB 时钟(APB2)为 HCLK 时钟
	//PCLK1 = HCLK
		RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;//设置低速 AHB 时钟(APB1)为 HCLK 的 2 分频
	（TIM2-TIM7 输入 TIMxCLK 频率将为 72MHZ/2x2=72MHZ 输入）
	APB2 定时器有 TIM1, TIM8
----------------------------------------------------------------------- */	
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		/* APB2 定时器 */
		uiTIMxCLK = SystemCoreClock;
	}
	else /* APB1 定时器 */
	{
		uiTIMxCLK = SystemCoreClock; // SystemCoreClock / 2;
	}
	if (_ulFreq < 100) /* 频率小于 100Hz */
	{
		usPrescaler = 10000 - 1; // 分频比 = 10000 */
		usPeriod = (uiTIMxCLK / 10000) / _ulFreq - 1; // 自动重装的值 
	}
	else if (_ulFreq < 3000) // 频率大于等于 100Hz 小于 3KHz 
	{
		usPrescaler = 100 - 1; // 分频比 = 100 
		usPeriod = (uiTIMxCLK / 100) / _ulFreq - 1; // 自动重装的值 
	}
	else /* 大于等于 3KHz 的频率，无需分频 */
	{
		usPrescaler = 0; // 分频比 = 1 
		usPeriod = uiTIMxCLK / _ulFreq - 1; //自动重装的值 
	}
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = usPeriod; // 设置自动重装载寄存器 
	TIM_TimeBaseStructure.TIM_Prescaler = usPrescaler; // 设置时钟预分频寄存器 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 设置时钟分割，TDTS=Tck_tim 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;// TIM 向上计数模式 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; // 重复计数器的值，没用到，不用设置 
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); // 初始化 TIMx 
	// /* PWM1 Mode configuration: ChannelX */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // 选择 PWM 模式 1 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 比较输出使能 

	TIM_OCInitStructure.TIM_Pulse = (_ulDutyCycle * usPeriod) / 10000; // 比较捕获寄存器的初值 相当于 自动重装载值 乘以 占空比%
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 输出极性高 
	/* 不使能互补输出 只有高级定时器 TIM1 和 TIM8 才有 */
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; // only for TIM1 and TIM8. 
	
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; //only for TIM1 and TIM8.
	
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //only for TIM1 and TIM8.
	
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; //only for TIM1 and TIM8.
	
	if (_ucChannel == 1)
	{
		TIM_OC1Init(TIMx, &TIM_OCInitStructure); // TIMx 通道 1 初始化
		TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable); //通道 1 使能预装载寄存器
	}
	else if (_ucChannel == 2)
	{
		TIM_OC2Init(TIMx, &TIM_OCInitStructure); //TIMx 通道 2 初始化
		TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable); //通道 2 使能预装载寄存器
	}
	else if (_ucChannel == 3)
	{	
		TIM_OC3Init(TIMx, &TIM_OCInitStructure); //TIMx 通道 3 初始化
		TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable); //通道 3 使能预装载寄存器 
	}
	else if (_ucChannel == 4)
	{
		TIM_OC4Init(TIMx, &TIM_OCInitStructure); //IMx 通道 4 初始化
		TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable); //通道 4 使能预装载寄存器
	}
	TIM_ARRPreloadConfig(TIMx, ENABLE); //使能 ARR 预装载寄存器
	/* TIMx enable counter */
	TIM_Cmd(TIMx, ENABLE); //使能定时器 TIMx
	/* 下面这句话对于 TIM1 和 TIM8 是必须的，对于 TIM2-TIM5 则不需要 */
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		TIM_CtrlPWMOutputs(TIMx, ENABLE); //高级定时器主输出使能
	}
}
