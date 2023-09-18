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
*	����˵��: 
*	��    �Σ�ADCx /RES_POT �� ADCx
*				 ADC_Channel  RES_POT �� ADC ����ͨ��
*				ADC_SampleTime   RES_POT �� ADC ����ʱ��
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
	ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime );//���� ADCx �Ĺ���ͨ��������ͨ���š�����˳��Ͳ���ʱ��Ȳ���
	ADC_Cmd(ADCx, ENABLE); //ʹ��ָ���� ADCx
	ADC_ResetCalibration(ADCx); //ʹ�ܸ�λУ׼ 
	while(ADC_GetResetCalibrationStatus(ADCx)); //�ȴ���λУ׼����
	ADC_StartCalibration(ADCx); //���� AD У׼
	while(ADC_GetCalibrationStatus(ADCx)); //�ȴ�У׼����

}
/*
*********************************************************************************************************
*	�� �� ��:Get_Adc
*	����˵��: 
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
static uint16_t Get_Adc(ADC_TypeDef* ADCx) 
{
	//�ú�������ʹ�ܻ���� STM32 �ϵ� ADC ģ�鿪ʼ�������ת�����������ת����ָ�������������ת���������ͨ��������� ADC ת�����̡�
	ADC_SoftwareStartConvCmd(ADCx, ENABLE); //ʹ��ָ���� ADCx �����ת����������
	//ADC_GetFlagStatus  �ú������ڻ�ȡ ADC �Ƿ񴥷���ָ���ı�־λ����������Ĳ������� ADCx �� ADC_FLAG�����У�ADCx Ϊ ADC ģ�飬ADC_FLAG Ϊ ADC �����ı�־λ
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC ));//�ȴ�ת������
	//�ú������ڻ�ȡ STM32 �� ADC ת����ɺ��ת�����ݡ���������Ĳ���Ϊ ADCx������ʾҪ��ȡת�����ݵ� ADC ģ��
	return ADC_GetConversionValue(ADCx); //�������һ�� ADCx �������ת�����
}
/*
*********************************************************************************************************
*	�� �� ��:Get_Adc_Average
*	����˵��: ��ȡƽ��ֵ
*	��    �Σ�
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
*	����˵��: 
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
void bsp_InitAdcPotentiometer(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RES_POT_GPIO_CLK, ENABLE);//��ʱ��
	/* ���� RES_POT Ϊģ������ */
	GPIO_InitStructure.GPIO_Pin = RES_POT_GPIO_PIN;	//����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	//
	GPIO_Init(RES_POT_GPIO_PORT, &GPIO_InitStructure);//�˿ں�
	/* ���� RES_POT �� ADC ���� */
	bsp_InitAdc(RES_POT_ADC_X,RES_POT_ADC_CHANNEL,RES_POT_ADC_SAMPLETIME);
}
/*
*********************************************************************************************************
*	�� �� ��:Get_Adc_Potentiometer
*	����˵��: �����Žӣ���ֹ
*	��    �Σ�
*	�� �� ֵ: ��ѹֵƽ��ֵ
********************************************************************************************************
*/
uint16_t Get_Adc_Potentiometer(void)
{
	uint16_t adcx;
	adcx = Get_Adc_Average(RES_POT_ADC_X,SAMP_COUNT); /* SAMP_COUNT ��ȡƽ�� */
	return adcx;
}
/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
