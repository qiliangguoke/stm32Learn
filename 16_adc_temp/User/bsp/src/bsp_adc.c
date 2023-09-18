/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : bsp_adc.c
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/

#include "bsp.h"


static void bsp_InitAdc(ADC_TypeDef* ADCx,uint8_t ADC_Channel,uint8_t ADC_SampleTime);
static uint16_t Get_Adc(ADC_TypeDef* ADCx); 
static uint16_t Get_Adc_Average(ADC_TypeDef* ADCx,uint8_t times);
/*
*********************************************************************************************************
*	�� �� ��:bsp_InitAdc
*	����˵��: ���� ADC ��ع�ͨ���á�������Թ���ͨ��Ϊ��
*	��    �Σ� ADC_TypeDef* ADCx �������ĸ� ADC
*				uint8_t ADC_Channel �ĸ�ͨ��
*				uint8_t ADC_SampleTime ����ʱ��
*	�� �� ֵ: 
********************************************************************************************************
*/
static void bsp_InitAdc(ADC_TypeDef* ADCx,uint8_t ADC_Channel,uint8_t ADC_SampleTime)
{ 
	ADC_InitTypeDef ADC_InitStructure; 
	if(ADCx == ADC1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE ); //ʹ�� ADC1 ͨ��ʱ��
		
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);//ADC ��λ
		
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);//��λ���� 
		
		ADC_DeInit(ADC1); //��λ ADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	}
	else if(ADCx == ADC2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE ); //ʹ�� ADC2 ͨ��ʱ��
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,ENABLE);//ADC ��λ
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,DISABLE);//��λ���� 
		ADC_DeInit(ADC2); //��λ ADC2,������ ADC2 ��ȫ���Ĵ�������Ϊȱʡֵ
	}
	else if(ADCx == ADC3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE ); //ʹ�� ADC3 ͨ��ʱ��
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);//ADC ��λ
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);//��λ���� 
		ADC_DeInit(ADC3); //��λ ADC3,������ ADC3 ��ȫ���Ĵ�������Ϊȱʡֵ
	}	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC ����ģʽ: ����ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; //ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC �����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1; //˳����й���ת���� ADC ͨ������Ŀ
	ADC_Init(ADCx, &ADC_InitStructure); //���� ADC_InitStruct ��ָ���Ĳ�����ʼ������ ADCx �ļĴ��� 
	/* ���� ADCx ����ͨ�� 1 ADC_Channel configuration */
	ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime );
	ADC_Cmd(ADCx, ENABLE); //ʹ��ָ���� ADCx
	ADC_ResetCalibration(ADCx); //ʹ�ܸ�λУ׼ 
	while(ADC_GetResetCalibrationStatus(ADCx)); //�ȴ���λУ׼����
	ADC_StartCalibration(ADCx); //���� AD У׼
	while(ADC_GetCalibrationStatus(ADCx)); //�ȴ�У׼����

}
/*
*********************************************************************************************************
*	�� �� ��:Get_Adc
*	����˵��: 	��� ADC ֵ��������Թ���ͨ��Ϊ��,���������ڲ�����
*	��    �Σ�	ADC_TypeDef* ADCx �������ĸ� ADC
*	�� �� ֵ: 	ת�����
********************************************************************************************************
*/
static uint16_t Get_Adc(ADC_TypeDef* ADCx) 
{
	ADC_SoftwareStartConvCmd(ADCx, ENABLE); //ʹ��ָ���� ADCx �����ת����������
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADCx); //�������һ�� ADCx �������ת�����
}
/*
*********************************************************************************************************
*	�� �� ��:Get_Adc_Average
*	����˵��: 	��� ADC ֵ��������Թ���ͨ��Ϊ��
*	��    �Σ�	ADC_TypeDef* ADCx �������ĸ� ADC
*				uint8_t ADC_Channel �ĸ�ͨ��
*				uint8_t times,��β�����ƽ��ֵ�Ĵ���
*	�� �� ֵ: 
********************************************************************************************************
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
*	�� �� ��:bsp_InitAdcPotentiometer
*	����˵��: bsp_InitAdcPotentiometer ����
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
	/*  */
//void bsp_InitAdcPotentiometer(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
	//RCC_APB2PeriphClockCmd(RES_POT_GPIO_CLK, ENABLE);
	///* ���� RES_POT Ϊģ������ */
//	GPIO_InitStructure.GPIO_Pin = RES_POT_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//	GPIO_Init(RES_POT_GPIO_PORT, &GPIO_InitStructure);
	/* ���� RES_POT �� ADC ���� */
//	bsp_InitAdc(RES_POT_ADC_X,RES_POT_ADC_CHANNEL,RES_POT_ADC_SAMPLETIME);
//}
/*
*********************************************************************************************************
*	�� �� ��:Get_Adc_Potentiometer
*	����˵��: 	�õ���λ����ѹֵ
*	��    �Σ�
*	�� �� ֵ: 	��λ����ѹֵ����ֵ����
********************************************************************************************************
*/
uint16_t Get_Adc_Potentiometer(void)
{
	uint16_t adcx;
	adcx = Get_Adc_Average(RES_POT_ADC_X,SAMP_COUNT); /* SAMP_COUNT ��ȡƽ�� */
	return adcx;
}
/*
*********************************************************************************************************
*	�� �� ��:bsp_InitAdcTemp
*	����˵��: ���� AdcTemp ����
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
void bsp_InitAdcTemp(void)
{
	/* �����ڲ��¶ȴ������� ADC ���� */
	bsp_InitAdc(ADC1,ADC_Channel_TempSensor,ADC_SampleTime_55Cycles5);
	/* ʹ���ڲ��¶ȴ�������ͨ�� */
	ADC_TempSensorVrefintCmd(ENABLE);
}
/*
*********************************************************************************************************
*	�� �� ��:Get_Temprate
*	����˵��: �õ��¶�ֵ��
*	��    �Σ�
*	�� �� ֵ: �¶�ֵ(������ 100 ��,��λ:��.)
********************************************************************************************************
*/
short Get_Temprate(void)//��ȡ�ڲ��¶ȴ������¶�ֵ
{
	uint32_t adcx;
	short result;
	double temperate;
	adcx=Get_Adc_Average(ADC1,SAMP_COUNT); //SAMP_COUNT ��ȡƽ��
	temperate=(float)adcx*(3.3/4096); //��ѹֵ
	temperate=(1.43-temperate)/0.0043+25; //ת��Ϊ�¶�ֵ
	result=temperate*=100; //���� 100 ��.
	return result;
}
/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
