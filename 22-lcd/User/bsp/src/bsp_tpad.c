
/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : bsp_tpad.h
*	˵    �� : ���ݰ���
*	�޸ļ�¼ :
*		�汾��  ����  2023-5-18  ���� ������   ˵��
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/
#include "bsp.h"
/* �������ڲ����õĺ��� ����*/

static void TPAD_TIM_GPIO_Config(void);
static void TPAD_TIM_Config(void);
static void bsp_TpadTimInit(void);
static void bsp_TpadReset(void);
static uint16_t TPAD_Get_Val(void);
static uint16_t TPAD_Get_MaxVal( uint8_t n );

/* tpad ����ֵ */
vu16 tpad_default_val = 0; /* ���ص�ʱ��(û���ְ���),��������Ҫ��ʱ�� */
/*
*********************************************************************************************************
*	�� �� ��:TPAD_Get_Val
*	����˵��: ���ݴ���������ȡ���ʱ��,�����ʱ����ֱ�ӷ��ض�ʱ���ļ���ֵ��
*	��    �Σ�
*	�� �� ֵ: ���ݰ�����粶�񵽸ߵ�ƽ�ļ�����ֵ
********************************************************************************************************
*/
static uint16_t TPAD_Get_Val ( void )
{
	bsp_TpadReset(); /* ÿ�β����ʱ�򣬱����ȸ�λ�ŵ� */
				/* �ȴ����������� */
	 while ( TIM_GetFlagStatus ( TIMx_CAP_TIM, TIMx_CAP_TIM_IT_CCx ) == RESET ) 
	 {
		/* һ����ʱ�䶼���� ms �������ڣ����ٻᳬ����ʱ�������ʱֵ */
		if ( TIM_GetCounter ( TIMx_CAP_TIM ) > TPAD_ARR_MAX_VAL - 500 )
		{
			/* ��ʱ��,ֱ�ӷ��� CNT ��ֵ */
			return TIM_GetCounter ( TIMx_CAP_TIM ); 
		}
	 };
	return TIMx_CAP_TIM_GetCapturex_FUN ( TIMx_CAP_TIM );
}
/*
*********************************************************************************************************
*	�� �� ��:TPAD_Get_MaxVal
*	����˵��: ���ݴ���������ȡ���ʱ��,������Σ���ȡ���ֵ 
*	��    �Σ�������������
*	�� �� ֵ: n �β��������ֵ
********************************************************************************************************
*/
static uint16_t TPAD_Get_MaxVal( uint8_t n )
{
	 uint16_t temp = 0;
	 uint16_t res = 0;
	 while ( n-- )
	 {
		temp = TPAD_Get_Val(); //�õ�һ��ֵ
		if ( temp > res )
		{
			res = temp;
		}
	 };
	 return res;
}
/*
*********************************************************************************************************
*	�� �� ��:bsp_TpadScan
*	����˵��: ɨ�败������
*	��    �Σ�������������
*	�� �� ֵ:  0,û�а���;1,�а���;
********************************************************************************************************
*/
uint8_t bsp_TpadScan(void)
{
	static uint8_t keyen = 0; //0,���Կ�ʼ���;>0,�����ܿ�ʼ���
	uint8_t res = 0;
	uint8_t sample = 3; //Ĭ�ϲ�������Ϊ 3 ��
	uint16_t rval;
	rval = TPAD_Get_MaxVal ( sample );
	/* ���� tpad_default_val+TPAD_GATE_VAL,��Ч */
	if ( rval > ( tpad_default_val + TPAD_GATE_VAL ) ) 
	{
		if ( keyen == 0 )
		{
			res = 1; //keyen==0,��Ч
		}
		//printf("r:%d\r\n",rval);
	keyen = 3; /* ����Ҫ�ٹ� 3 ��֮����ܰ�����Ч */
	}
	if ( keyen )
	{
		keyen--;
	}
	return res;
}
/*
*********************************************************************************************************
*	�� �� ��:TPAD_TIM_GPIO_Config
*	����˵��:���ݴ������� GPIO ��ʼ������
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
static void TPAD_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIMx_CAP_TIM_APBxClock_FUN( TIMx_CAP_TIM_CLK, ENABLE ); /* ʹ�� TIMx ʱ�� */
	RCC_APB2PeriphClockCmd( TIMx_CAP_TIM_CH_GPIO_CLK, ENABLE ); /* ʹ�ܶ�Ӧ���ݴ�������˿�ʱ�� */
	GPIO_InitStructure.GPIO_Pin = TIMx_CAP_TIM_CH_PIN; /* ���ݴ����˿����� */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; /* �˿��ٶ� 50MHz */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; /* �������� */
	GPIO_Init ( TIMx_CAP_TIM_CH_PORT, &GPIO_InitStructure ); /* ��ʼ�������˿� */
}
/*
*********************************************************************************************************
*	�� �� ��: TPAD_TIM_Config
*	����˵��: ���ݴ������� ��ʱ�� ��ʼ������
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
static void TPAD_TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIMx_CAP_TIM_APBxClock_FUN( TIMx_CAP_TIM_CLK, ENABLE ); //ʹ�� TIMx ʱ��
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = TPAD_ARR_MAX_VAL; /* �����Զ���װ�ؼĴ��� */
	TIM_TimeBaseStructure.TIM_Prescaler = TIMx_CAP_TIM_PSC; /* ����ʱ��Ԥ��Ƶ�Ĵ��� */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; /* ����ʱ�ӷָTDTS=Tck_tim */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* TIM ���ϼ���ģʽ */
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; /* �ظ���������ֵ��û�õ����������� */
	TIM_TimeBaseInit(TIMx_CAP_TIM, &TIM_TimeBaseStructure); /* ��ʼ�� TIMx */
	TIM_ICInitStructure.TIM_Channel = TIMx_CAP_TIM_CHANNEL_x; /* �������벶���ͨ������Ҫ���ݾ����GPIO ������ */
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;/* �����ز��� */
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; /* ����ͨ���Ͳ���ͨ����ӳ���ϵ������ѡ��ֱ��*/
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; /* ���������Ƶ,����Ƶ */
	TIM_ICInitStructure.TIM_ICFilter = 0x03; /* IC2F=0011b ���������˲��� 8 ����ʱ��ʱ�������˲� */
	TIM_ICInit( TIMx_CAP_TIM, &TIM_ICInitStructure ); /* ��ʱ�����벶���ʼ�� */
	/* ʹ�ܼ����� */
	TIM_Cmd( TIMx_CAP_TIM,ENABLE);
}
/*
*********************************************************************************************************
*	�� �� ��:bsp_TpadTimInit
*	����˵��:���ݴ������� ��ʱ�� ���ų�ʼ������ 
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
static void bsp_TpadTimInit(void)
{
	TPAD_TIM_GPIO_Config();//���ݴ������� GPIO ��ʼ������
	TPAD_TIM_Config();//���ݴ������� ��ʱ�� ��ʼ������
}
/*
*********************************************************************************************************
*	�� �� ��:bsp_TpadReset
*	����˵��:���� TIM �õ� RCC �Ĵ��� 
*	��    �Σ�
*	�� �� ֵ: TIM ����ʱ����
********************************************************************************************************
*/
static void bsp_TpadReset ( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd ( TIMx_CAP_TIM_CH_GPIO_CLK, ENABLE ); //ʹ�ܵ��ݴ����˿�ʱ��
	//���� GPIOA.1 Ϊ����ʹ��
	GPIO_InitStructure.GPIO_Pin = TIMx_CAP_TIM_CH_PIN; /* ���ݴ����˿����� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; /* ������� */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; /* �˿��ٶ�Ϊ 50MHz */
	GPIO_Init ( TIMx_CAP_TIM_CH_PORT, &GPIO_InitStructure );
	GPIO_ResetBits ( TIMx_CAP_TIM_CH_PORT, TIMx_CAP_TIM_CH_PIN ); /* �����˿�����͵�ƽ,�ŵ� */
	delay_ms ( 5 ); /* �ŵ�ȴ����ŵ�ʱ��ܿ죬һ���� us ����� */
	TIM_SetCounter ( TIMx_CAP_TIM, 0 ); /* ���ü��������� */
	TIM_ClearITPendingBit ( TIMx_CAP_TIM, TIMx_CAP_TIM_IT_CCx | TIMx_CAP_TIM_IT_UPDATE ); //����жϱ�־
	/* ���ô����˿�Ϊ�������� ,�������벶��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; /* �������� */
	GPIO_Init ( TIMx_CAP_TIM_CH_PORT, &GPIO_InitStructure ); /* ��ʼ���˿� */
}
/*
*********************************************************************************************************
*	�� �� ��:bsp_TpadInit
*	����˵��: ��ÿ��ص�ʱ����������ȡֵ.
*	��    �Σ�
*	�� �� ֵ: : 0,��ʼ���ɹ�;1,��ʼ��ʧ��
********************************************************************************************************
*/
uint8_t bsp_TpadInit(void)
{
	uint16_t buf[10];
	uint16_t temp;
	uint8_t j, i;
	bsp_TpadTimInit();
	for ( i = 0; i < 10; i++ ) /* ������ȡ 10 �� */
	{
		buf[i] = TPAD_Get_Val();
		delay_ms ( 10 );
	}
	for ( i = 0; i < 9; i++ ) /* ���� */
	{
		for ( j = i + 1; j < 10; j++ )
		{
			if ( buf[i] > buf[j] ) /* �������� */
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
		temp += buf[i]; /* ȡ�м�� 6 �����ݽ���ƽ�� */
	}
	tpad_default_val = temp / 6;
	 
	printf ( "tpad_default_val:%d\r\n", tpad_default_val );
	
	printf("\r\n\r\n");
	if ( tpad_default_val > TPAD_ARR_MAX_VAL / 2 )
	{
		return 1; /* ��ʼ���������� TPAD_ARR_MAX_VAL/2 ����ֵ,������! */
	}
	return 0;
}
/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
