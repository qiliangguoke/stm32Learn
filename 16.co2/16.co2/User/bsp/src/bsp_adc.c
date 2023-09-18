#include "bsp.h"

static void bsp_InitAdc(ADC_TypeDef* ADCx,uint8_t ADC_Channel,uint8_t ADC_SampleTime);
static uint16_t Get_Adc(ADC_TypeDef* ADCx); 
static uint16_t Get_Adc_Average(ADC_TypeDef* ADCx,uint8_t times);

/*
*********************************************************************************************************
*	�� �� ��: bsp_InitAdc
*	����˵��: ����ADC��ع�ͨ���á�������Թ���ͨ��Ϊ��
*	��    �Σ�ADC_TypeDef* ADCx �������ĸ� ADC
				uint8_t ADC_Channel �ĸ�ͨ��
				uint8_t ADC_SampleTime ����ʱ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void bsp_InitAdc(ADC_TypeDef* ADCx,uint8_t ADC_Channel,uint8_t ADC_SampleTime)
{
	ADC_InitTypeDef ADC_InitStructure; 
	if(ADCx == ADC1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE ); 	//ʹ��ADC1ͨ��ʱ��
		
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);		//ADC��λ
		
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ���� 
		
		ADC_DeInit(ADC1); //��λADC1,������ADC1��ȫ���Ĵ�������Ϊȱʡֵ
	}
	else if(ADCx == ADC2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE ); 	//ʹ��ADC2ͨ��ʱ��
		
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,ENABLE);		//ADC��λ
		
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,DISABLE);	//��λ���� 
		
		ADC_DeInit(ADC2); //��λADC2,������ADC2��ȫ���Ĵ�������Ϊȱʡֵ
	}
	else if(ADCx == ADC3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE ); 	//ʹ��ADC3ͨ��ʱ��
		
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);		//ADC��λ
		
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);	//��λ���� 
		
		ADC_DeInit(ADC3); //��λADC3,������ADC3��ȫ���Ĵ�������Ϊȱʡֵ
	}
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 	//ADC����ģʽ: ����ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; 		//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1; //˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADCx, &ADC_InitStructure); //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ��� 
	
	/*���� ADCx ����ͨ�� 1 ADC_Channel configuration*/
	ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime);
	
	ADC_Cmd(ADCx, ENABLE); //ʹ��ָ���� ADCx
	
	ADC_ResetCalibration(ADCx); //ʹ�ܸ�λУ׼ 
	
	while(ADC_GetResetCalibrationStatus(ADCx)); //�ȴ���λУ׼����
	
	ADC_StartCalibration(ADCx); //���� AD У׼
	
	while(ADC_GetCalibrationStatus(ADCx)); //�ȴ�У׼����
}

/*
*********************************************************************************************************
*	�� �� ��: Get_Adc
*	����˵��: ��� ADC ֵ��������Թ���ͨ��Ϊ��,���������ڲ�����
*	��    �Σ�ADC_TypeDef* ADCx �������ĸ� ADC
*	�� �� ֵ: ת�����
*********************************************************************************************************
*/
static uint16_t Get_Adc(ADC_TypeDef* ADCx) 
{
	
	ADC_SoftwareStartConvCmd(ADCx, ENABLE); 		//ʹ��ָ����ADCx�����ת����������
	
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC));	//�ȴ�ת������
	
	return ADC_GetConversionValue(ADCx); //�������һ��ADCx�������ת�����
}

/*
*********************************************************************************************************
*	�� �� ��: Get_Adc_Average
*	����˵��: ��ȡADCֵ��������Թ���ͨ��Ϊ��
*	��    �Σ�ADC_TypeDef* ADCx �������ĸ� ADC
				uint8_t ADC_Channel �ĸ�ͨ��
				uint8_t times,��β�����ƽ��ֵ�Ĵ���
*	�� �� ֵ: ת�����
*********************************************************************************************************
*/
static uint16_t Get_Adc_Average(ADC_TypeDef* ADCx,uint8_t times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val += Get_Adc(ADCx);
	}
	return temp_val/times;
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_InitAdcPotentiometer
*	����˵��: bsp_InitAdcPotentiometer ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitAdcPotentiometer(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RES_POT_GPIO_CLK, ENABLE);
	
	/*����RES_POTΪģ������*/
	GPIO_InitStructure.GPIO_Pin = RES_POT_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(RES_POT_GPIO_PORT, &GPIO_InitStructure);
	
	/*����RES_POT��ADC����*/
	bsp_InitAdc(RES_POT_ADC_X,RES_POT_ADC_CHANNEL,RES_POT_ADC_SAMPLETIME);
}

/*
*********************************************************************************************************
*	�� �� ��: Get_Adc_Potentiometer
*	����˵��: �õ���λ����ѹֵ
*	��    �Σ���
*	�� �� ֵ: ��λ����ѹֵ����ֵ����
*********************************************************************************************************
*/
uint16_t Get_Adc_Potentiometer(void)
{
	uint16_t adcx;
	adcx = Get_Adc_Average(RES_POT_ADC_X,SAMP_COUNT); /*SAMP_COUNT��ȡƽ��*/
	return adcx;
}
/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitAdcVolMeter(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(VOL_METER_GPIO_CLK, ENABLE);
	
	/* ���� VOL_METER Ϊģ������ */
	GPIO_InitStructure.GPIO_Pin = VOL_METER_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(VOL_METER_GPIO_PORT, &GPIO_InitStructure);
	
	/* ���� VOL_METER ��ADC���� */
	bsp_InitAdc(VOL_METER_ADC_X,VOL_METER_ADC_CHANNEL,VOL_METER_ADC_SAMPLETIME);
}
/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
uint16_t Get_Adc_Volmeter(void)
{
	uint16_t adcx;
	adcx = Get_Adc_Average(VOL_METER_ADC_X,SAMP_COUNT); //SAMP_COUNT ��ȡƽ��
	return adcx;
}

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/

