#include "bsp.h"
/*
*********************************************************************************************************
*	�� �� ��: bsp_GetRCCofGPIO
*	����˵��: ����GPIO�õ�RCC�Ĵ���
*	��    �Σ���
*	�� �� ֵ: GPIO����ʱ����
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
*	�� �� ��: bsp_GetRCCofTim
*	����˵��: ����TIM�õ�RCC�Ĵ���
*	��    �Σ���
*	�� �� ֵ: TIM����ʱ����
*********************************************************************************************************
*/
uint32_t bsp_GetRCCofTIM(TIM_TypeDef* TIMx)
{
	uint32_t rcc = 0;
	
	/*
		APB1��ʱ����TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7
		APB2��ʱ����TIM1, TIM8
	*/
	if(TIMx == TIM1)
	{
		rcc = RCC_APB2Periph_TIM1;
	}
	else if(TIMx == TIM8)
	{
		rcc = RCC_APB2Periph_TIM8;
	}
	
	/* ������APB1ʱ�� */
	else if(TIMx == TIM2)
	{
		rcc = RCC_APB1Periph_TIM2;
	}
	else if(TIMx == TIM3)
	{
		rcc = RCC_APB1Periph_TIM3;
	}
	else if(TIMx == TIM4)
	{
		rcc = RCC_APB1Periph_TIM4;
	}
	else if(TIMx == TIM5)
	{
		rcc = RCC_APB1Periph_TIM5;
	}
	else if(TIMx == TIM6)
	{
		rcc = RCC_APB1Periph_TIM6;
	}
	else if(TIMx == TIM7)
	{
		rcc = RCC_APB1Periph_TIM7;
	}
	
	return rcc;
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_ConfigTimGpio
*	����˵��: ����GPIO��TIMʱ�ӣ�GPIO���ӵ�TIM���ͨ��
*	��    �Σ�GPIO
				GPIO_PinX
				TIMx
				_ucChannel
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_ConfigTimGpio(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinX, TIM_TypeDef* TIMx)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*ʹ��GPIOʱ��*/
	RCC_APB2PeriphClockCmd(bsp_GetRCCofGPIO(GPIOx), ENABLE);
	
	 /* ʹ��TIMʱ�� */
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		RCC_APB2PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
	}
	else
	{
		RCC_APB1PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
	}
	
	/* ����GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_PinX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		/*���ù���*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure); 
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_SetTIMOutPWM
*	����˵��: �������������PWM�źŵ�Ƶ�ʺ�ռ�ձȡ���Ƶ��Ϊ0������ռ��Ϊ0ʱ���رն�ʱ��,GPIO���0��
			 ������Ϊ0��ռ�ձ�Ϊ100%��GPIO���1.
*	��    �Σ�GPIOx, GPIO_Pin, TIMx ͬ�⺯���ṹ��
				_ucChannel:ͨ��1~4
				_ulFrep:PWM�ź�Ƶ�ʣ���λHZ (ʵ�ʲ��ԣ�������Ƶ��Ϊ72M/4=18M��. 0��ʾ��ֹ���
				_ulDutyCycle: PWM�ź�ռ�ձȵ�λ�����֮һ���� 5000����ʾ50.00%��ռ�ձ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_SetTIMOutPWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, TIM_TypeDef* TIMx, uint8_t _ucChannel,
uint32_t _ulFreq, uint32_t _ulDutyCycle)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 	/* ʱ���ṹ�� */
	TIM_OCInitTypeDef TIM_OCInitStructure; 			/* ����ȽϽṹ�� */
	uint16_t usPeriod; 								/* �ݴ���Զ���װ�ؼĴ�����ֵ */
	uint16_t usPrescaler; 							/* �ݴ��ʱ��Ԥ��Ƶ�Ĵ�����ֵ */
	uint32_t uiTIMxCLK; 							/* �ݴ��ʱ��Ƶ�� */
	bsp_ConfigTimGpio(GPIOx, GPIO_Pin, TIMx);		/* ʹ��GPIO��TIMʱ�ӣ�������TIMͨ����GPIO*/
	
		/*---------------------------------------------------
			system_stm32f10x.c�ļ���static void SetSysClockTo72(void)������ʱ�ӵ��������£�
	
			//HCLK = SYSCLK 
			RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;//����AHBʱ��(HCLK)Ϊϵͳʱ��
			 
			//PCLK2 = HCLK
			RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;//���ø���AHBʱ��(APB2)ΪHCLKʱ��
	
			//PCLK1 = HCLK
			RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;//���õ���AHBʱ��(APB1)ΪHCLK��2��Ƶ
��TIM2-TIM7 ���� TIMxCLK Ƶ�ʽ�Ϊ 72MHZ/2x2=72MHZ ���룩
	
			APB1 ��ʱ���� TIM2, TIM3 ,TIM4, TIM5
			APB2 ��ʱ���� TIM1, TIM8
			
		-------------------------------------------------*/
	
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		/* APB2��ʱ�� */
		uiTIMxCLK = SystemCoreClock;
	}
	else /* APB1��ʱ�� */
	{
		uiTIMxCLK = SystemCoreClock; // SystemCoreClock / 2;
	}
	if (_ulFreq < 100) /* Ƶ��С��100Hz */
	{
		usPrescaler = 10000 - 1; 					  /* ��Ƶ��=10000 */
		usPeriod = (uiTIMxCLK / 10000) / _ulFreq - 1; /* �Զ���װ��ֵ */
	}
	else if (_ulFreq < 3000) /* Ƶ�ʴ��ڵ���100HzС��3KHz */
	{
		usPrescaler = 100 - 1; 						/* ��Ƶ��=100 */
		usPeriod = (uiTIMxCLK / 100) / _ulFreq - 1; /* �Զ���װ��ֵ */
	}
	else /* ���ڵ���3KHz��Ƶ�ʣ������Ƶ */
	{
		usPrescaler = 0; /* ��Ƶ�� = 1 */
		usPeriod = uiTIMxCLK / _ulFreq - 1; /* �Զ���װ��ֵ */
	}
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = usPeriod; 				 /* �����Զ���װ�ؼĴ��� */
	TIM_TimeBaseStructure.TIM_Prescaler = usPrescaler;  		 /* ����ʱ��Ԥ��Ƶ�Ĵ��� */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		 /* ����ʱ�ӷָTDTS=Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  /* TIM ���ϼ���ģʽ */
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;			 /* �ظ���������ֵ��û�õ����������� */
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); 			 /* ��ʼ�� TIMx */
	
// /* PWM1 Mode configuration: ChannelX */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 					/* ѡ�� PWM ģʽ 1 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 		/* �Ƚ����ʹ�� */
	TIM_OCInitStructure.TIM_Pulse = (_ulDutyCycle * usPeriod) / 10000;  /* �Ƚϲ���Ĵ����ĳ�ֵ�൱���Զ���װ��ֵ����ռ�ձ�% */
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			/* ������Ը� */
	
	/* ��ʹ�ܻ������ ֻ�и߼���ʱ�� TIM1 �� TIM8 ���� */
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable; /* only for TIM1 and TIM8. */
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; 	 /* only for TIM1 and TIM8. */
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; 	 /* only for TIM1 and TIM8. */
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; 	 /* only for TIM1 and TIM8. */
	
	if (_ucChannel == 1)
	{
		TIM_OC1Init(TIMx, &TIM_OCInitStructure); 			/* TIMx ͨ�� 1 ��ʼ�� */
		TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);  /* ͨ�� 1 ʹ��Ԥװ�ؼĴ��� */
	}
	else if (_ucChannel == 2)
	{
		TIM_OC2Init(TIMx, &TIM_OCInitStructure);		  /* TIMx ͨ�� 2 ��ʼ�� */
		TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable); /* ͨ�� 2 ʹ��Ԥװ�ؼĴ��� */
	}
	else if (_ucChannel == 3)
	{
		TIM_OC3Init(TIMx, &TIM_OCInitStructure); 			/* TIMx ͨ�� 3 ��ʼ�� */
		TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);   /* ͨ�� 3 ʹ��Ԥװ�ؼĴ��� */
	}
	else if (_ucChannel == 4)
	{
		TIM_OC4Init(TIMx, &TIM_OCInitStructure); 			 /* TIMx ͨ�� 4 ��ʼ�� */
		TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);    /* ͨ�� 4 ʹ��Ԥװ�ؼĴ��� */
	}
		TIM_ARRPreloadConfig(TIMx, ENABLE); 				 /* ʹ�� ARR Ԥװ�ؼĴ��� */
	
	/* TIMx enable counter */
	TIM_Cmd(TIMx, ENABLE); /* ʹ�ܶ�ʱ�� TIMx */
	
	/* ������仰����TIM1��TIM8�Ǳ���ģ�����TIM2-TIM5����Ҫ */
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		TIM_CtrlPWMOutputs(TIMx, ENABLE); /* �߼���ʱ�������ʹ�� */
	}
}
/*
*********************************************************************************************************
*	�� �� ��: bsop_SetTIMforInt
*	����˵��: ����TIM��NVIC,���ڼ򵥵Ķ�ʱ�жϣ�������ʱ�жϣ��жϷ��������Ӧ�ó���ʵ��
*	��    �Σ�TIMx:��ʱ��
			  _ulFreq:��ʱƵ��(Hz)��0 ��ʾ�رա�
*			  _PreemptionPriority:�ж����ȼ�����
* 			  _SubPriority:�����ȼ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void bsp_SetTIMforInt(TIM_TypeDef* TIMx, uint32_t _ulFreq, uint8_t _PreemptionPriority, uint8_t _SubPriority)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; /* ʱ���ṹ�� */
	
	uint16_t usPeriod; 		/* �ݴ���Զ���װ�ؼĴ�����ֵ */
	uint16_t usPrescaler; 	/* �ݴ��ʱ��Ԥ��Ƶ�Ĵ�����ֵ */
	uint32_t uiTIMxCLK; 	/* �ݴ��ʱ��Ƶ�� */
	
	 /* ʹ��TIMʱ�� */
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		RCC_APB2PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
	}
	else
	{
		RCC_APB1PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
	}
	if (_ulFreq == 0) 			/* ��ʱƵ��Ϊ0 */
	{
		TIM_Cmd(TIMx, DISABLE); /* �رն�ʱ��� */
		
		/* �ر�TIM��ʱ�����ж� (Update) */
		{
			NVIC_InitTypeDef NVIC_InitStructure; /* �жϽṹ���� misc.h �ж��� */
			
			uint8_t irq = 0; /* �жϺ�, ������ stm32f1xx.h */
				
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
			
			/* �ж����ȼ� NVIC ���� */
			NVIC_InitStructure.NVIC_IRQChannel = irq; 									/* TIMx�ж� IRQn */
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _PreemptionPriority; /* TIMx��ռ���ȼ� */
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = _SubPriority; 				/* TIMx�����ȼ� */
			NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE; 							/* TIMx IRQ ͨ��ʧ�� */
			NVIC_Init(&NVIC_InitStructure);
		/* ��ʼ�� NVIC �Ĵ��� */
		}
		return;
	}
	
/*---------------------------------------------------
	system_stm32f1xx.c �ļ��� static void SetSysClockTo72(void) ������ʱ�ӵ��������£�
	
	//HCLK = SYSCLK 
	RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;//���� AHB ʱ��(HCLK)Ϊϵͳʱ��
 
	//PCLK2 = HCLK
	RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;//���ø��� AHB ʱ��(APB2)Ϊ HCLK ʱ��
	
	//PCLK1 = HCLK
	RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;//���õ��� AHB ʱ��(APB1)Ϊ HCLK �� 2 ��Ƶ
��TIM2-TIM7 ���� TIMxCLK Ƶ�ʽ�Ϊ 72MHZ/2x2=72MHZ ���룩
	
	APB1 ��ʱ���� TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7
    APB2 ��ʱ���� TIM1, TIM8
	
	-------------------------------------------------*/
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		/* APB2��ʱ�� */
		uiTIMxCLK = SystemCoreClock;
	}
	else /* APB1��ʱ�� */
	{
		uiTIMxCLK = SystemCoreClock; // APB1 clock = SystemCoreClock / 2;
	}
	if (_ulFreq < 100) /* Ƶ��С��100Hz */
	{
		usPrescaler = 10000 - 1; 					  /* ��Ƶ�� = 10000 */
		usPeriod = (uiTIMxCLK / 10000) / _ulFreq - 1; /* �Զ���װ��ֵ */
	}
	else if (_ulFreq < 3000) /* Ƶ�ʴ��ڵ��� 100Hz С�� 3KHz */
	{
		usPrescaler = 100 - 1;						 /* ��Ƶ�� = 100 */
		usPeriod = (uiTIMxCLK / 100) / _ulFreq - 1;  /* �Զ���װ��ֵ */
	}
	else /* ���ڵ��� 3KHz ��Ƶ�ʣ������Ƶ */
	{
		usPrescaler = 0; 					/* ��Ƶ�� = 1 */
		usPeriod = uiTIMxCLK / _ulFreq - 1; /* �Զ���װ��ֵ */
	}
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = usPeriod; 				/* �����Զ���װ�ؼĴ��� */
	TIM_TimeBaseStructure.TIM_Prescaler = usPrescaler;  		/* ����ʱ��Ԥ��Ƶ�Ĵ��� */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		/* ����ʱ�ӷָTDTS=Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* TIM ���ϼ���ģʽ */
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 			/* �ظ���������ֵ��û�õ����������� */
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); 			/* ��ʼ��TIMx */
	TIM_ARRPreloadConfig(TIMx, ENABLE); 						/* ʹ��ARRԤװ�ؼĴ��� */
	
	/* TIM Interrupts enable */
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE); /* ����TIMx�����ж� */
	
	/* TIMx enable counter */
	TIM_Cmd(TIMx, ENABLE); /* ʹ�ܶ�ʱ�� TIMx */
	
	/* ���� TIM ��ʱ�����ж� (Update) */
	{
		NVIC_InitTypeDef NVIC_InitStructure; /* �жϽṹ����misc.h�ж��� */
		uint8_t irq = 0; /* �жϺ�, ������ stm32f1xx.h */
		
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
		
		
	/* �ж����ȼ�NVIC���� */
	NVIC_InitStructure.NVIC_IRQChannel = irq; /* TIMx �ж� IRQn */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _PreemptionPriority; /* TIMx ��ռ���ȼ� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = _SubPriority; /* TIMx �����ȼ� */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; /* TIMx IRQ ͨ��ʹ�� */
	NVIC_Init(&NVIC_InitStructure); /* ��ʼ�� NVIC �Ĵ��� */
	}
}

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/

