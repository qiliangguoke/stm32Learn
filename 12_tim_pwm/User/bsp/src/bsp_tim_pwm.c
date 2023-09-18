
/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : bsp_tim_pwm.c
*	˵    �� : ��ʱ��
*	�޸ļ�¼ :
*		�汾��  ����  2023-5-17      ����  ������   ˵��
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/
#include "bsp.h"
/*
*********************************************************************************************************
* �� �� ��: bsp_GetRCCofTIM
* ����˵��: ���� TIM �õ� RCC �Ĵ���
* �� �Σ�
* �� �� ֵ: TIM ����ʱ����
*********************************************************************************************************
*/
uint32_t bsp_GetRCCofTIM(TIM_TypeDef* TIMx)
{
	uint32_t rcc = 0;
	/*
		APB1 ��ʱ���� TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7
		APB2 ��ʱ���� TIM1, TIM8
	*/
	if (TIMx == TIM1)
	{
		rcc = RCC_APB2Periph_TIM1;
	}
	else if (TIMx == TIM8)
	{
		rcc = RCC_APB2Periph_TIM8;
	}
		/* ������APB1ʱ�� */
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
* �� �� ��: bsp_SetTIMforInt
* ����˵��: ���� TIM �� NVIC�����ڼ򵥵Ķ�ʱ�ж�. ������ʱ�жϡ� �жϷ��������Ӧ�ó���ʵ�֡�
* �� ��: TIMx : ��ʱ��
* 		_ulFreq : ��ʱƵ�� ��Hz���� 0 ��ʾ�رա�
* 			_PreemptionPriority : �ж����ȼ�����
* 			_SubPriority : �����ȼ�
* �� �� ֵ: 
*********************************************************************************************************
*/
void bsp_SetTIMforInt(TIM_TypeDef* TIMx, uint32_t _ulFreq, uint8_t _PreemptionPriority, uint8_t _SubPriority)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //ʱ���ṹ�� 
	uint16_t usPeriod; //�ݴ���Զ���װ�ؼĴ�����ֵ 
	uint16_t usPrescaler; // �ݴ��ʱ��Ԥ��Ƶ�Ĵ�����ֵ
	uint32_t uiTIMxCLK; //�ݴ��ʱ��Ƶ��
	 /* ʹ�� TIM ʱ�� */
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		RCC_APB2PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
	}
	else
	{
		RCC_APB1PeriphClockCmd(bsp_GetRCCofTIM(TIMx), ENABLE);
	}
	if (_ulFreq == 0) //��ʱƵ��Ϊ 0
	{
		TIM_Cmd(TIMx, DISABLE); //�رն�ʱ��� 
		/* �ر� TIM ��ʱ�����ж� (Update) */
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
			NVIC_InitStructure.NVIC_IRQChannel = irq; /* TIMx �ж� IRQn */
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _PreemptionPriority; /* TIMx ��ռ���ȼ� */
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = _SubPriority; /* TIMx �����ȼ� */
			NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE; /* TIMx IRQ ͨ��ʧ�� */
			NVIC_Init(&NVIC_InitStructure);
			/* ��ʼ�� NVIC �Ĵ��� */
		}
		return;
}
	/*-----------------------------------------------------------------------
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
	----------------------------------------------------------------------- */
	if ((TIMx == TIM1) || (TIMx == TIM8))
	{
		/* APB2 ��ʱ�� */
		uiTIMxCLK = SystemCoreClock;
	}
	else /* APB1 ��ʱ�� . */
	{
		uiTIMxCLK = SystemCoreClock; // APB1 clock = SystemCoreClock / 2;
	}
	if (_ulFreq < 100) //Ƶ��С�� 100Hz
	{
		usPrescaler = 10000 - 1; //��Ƶ�� = 10000 
		usPeriod = (uiTIMxCLK / 10000) / _ulFreq - 1; //* �Զ���װ��ֵ 
	}
	else if (_ulFreq < 3000) //Ƶ�ʴ��ڵ��� 100Hz С�� 3KHz 
	{
		usPrescaler = 100 - 1; // ��Ƶ�� = 100 
		usPeriod = (uiTIMxCLK / 100) / _ulFreq - 1; //�Զ���װ��ֵ 
	}
	else /* ���ڵ��� 3KHz ��Ƶ�ʣ������Ƶ */
	{
		usPrescaler = 0; //* ��Ƶ�� = 1 */
		usPeriod = uiTIMxCLK / _ulFreq - 1; //* �Զ���װ��ֵ */
	}
		/* Time base configuration */
		TIM_TimeBaseStructure.TIM_Period = usPeriod; //�����Զ���װ�ؼĴ���
		TIM_TimeBaseStructure.TIM_Prescaler = usPrescaler; //����ʱ��Ԥ��Ƶ�Ĵ�
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָTDTS=Tck_tim 
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM ���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //�ظ���������ֵ��û�õ�����������
		TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); // ��ʼ�� TIMx 
		TIM_ARRPreloadConfig(TIMx, ENABLE); //ʹ�� ARR Ԥװ�ؼĴ��� 
		/* TIM Interrupts enable */
		TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE); //���� TIMx �����ж� 
		/* TIMx enable counter */
		TIM_Cmd(TIMx, ENABLE); //ʹ�ܶ�ʱ�� TIMx 
		/* ���� TIM ��ʱ�����ж� (Update) */
	{
		NVIC_InitTypeDef NVIC_InitStructure; //�жϽṹ���� misc.h �ж��� 
		uint8_t irq = 0; // �жϺ�, ������ stm32f1xx.h 
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
		NVIC_InitStructure.NVIC_IRQChannel = irq; //TIMx�ж�IRQn
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = _PreemptionPriority; //TIMx ��ռ���ȼ�
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = _SubPriority; //TIMx �����ȼ�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //TIMx IRQ ͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);
	}
}
