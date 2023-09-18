/*
*********************************************************************************************************
*
*	模块名称 : 模块
*	文件名称 : bsp_adc.c
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/

#include "bsp.h"


static void bsp_InitAdc(ADC_TypeDef* ADCx,uint8_t ADC_Channel,uint8_t ADC_SampleTime);
static uint16_t Get_Adc(ADC_TypeDef* ADCx); 
static uint16_t Get_Adc_Average(ADC_TypeDef* ADCx,uint8_t times);
/*
*********************************************************************************************************
*	函 数 名:bsp_InitAdc
*	功能说明: 配置 ADC 相关共通配置。这里仅以规则通道为例
*	形    参： ADC_TypeDef* ADCx 具体是哪个 ADC
*				uint8_t ADC_Channel 哪个通道
*				uint8_t ADC_SampleTime 采样时间
*	返 回 值: 
********************************************************************************************************
*/
static void bsp_InitAdc(ADC_TypeDef* ADCx,uint8_t ADC_Channel,uint8_t ADC_SampleTime)
{ 
	ADC_InitTypeDef ADC_InitStructure; 
	if(ADCx == ADC1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE ); //使能 ADC1 通道时钟
		
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);//ADC 复位
		
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);//复位结束 
		
		ADC_DeInit(ADC1); //复位 ADC1,将外设 ADC1 的全部寄存器重设为缺省值
	}
	else if(ADCx == ADC2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE ); //使能 ADC2 通道时钟
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,ENABLE);//ADC 复位
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,DISABLE);//复位结束 
		ADC_DeInit(ADC2); //复位 ADC2,将外设 ADC2 的全部寄存器重设为缺省值
	}
	else if(ADCx == ADC3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE ); //使能 ADC3 通道时钟
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);//ADC 复位
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);//复位结束 
		ADC_DeInit(ADC3); //复位 ADC3,将外设 ADC3 的全部寄存器重设为缺省值
	}	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC 工作模式: 独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; //模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC 数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1; //顺序进行规则转换的 ADC 通道的数目
	ADC_Init(ADCx, &ADC_InitStructure); //根据 ADC_InitStruct 中指定的参数初始化外设 ADCx 的寄存器 
	/* 配置 ADCx 规则通道 1 ADC_Channel configuration */
	ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime );
	ADC_Cmd(ADCx, ENABLE); //使能指定的 ADCx
	ADC_ResetCalibration(ADCx); //使能复位校准 
	while(ADC_GetResetCalibrationStatus(ADCx)); //等待复位校准结束
	ADC_StartCalibration(ADCx); //开启 AD 校准
	while(ADC_GetCalibrationStatus(ADCx)); //等待校准结束

}
/*
*********************************************************************************************************
*	函 数 名:Get_Adc
*	功能说明: 	获得 ADC 值。这里仅以规则通道为例,仅供函数内部调用
*	形    参：	ADC_TypeDef* ADCx 具体是哪个 ADC
*	返 回 值: 	转换结果
********************************************************************************************************
*/
static uint16_t Get_Adc(ADC_TypeDef* ADCx) 
{
	ADC_SoftwareStartConvCmd(ADCx, ENABLE); //使能指定的 ADCx 的软件转换启动功能
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADCx); //返回最近一次 ADCx 规则组的转换结果
}
/*
*********************************************************************************************************
*	函 数 名:Get_Adc_Average
*	功能说明: 	获得 ADC 值。这里仅以规则通道为例
*	形    参：	ADC_TypeDef* ADCx 具体是哪个 ADC
*				uint8_t ADC_Channel 哪个通道
*				uint8_t times,多次采样求平均值的次数
*	返 回 值: 
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
*	函 数 名:bsp_InitAdcPotentiometer
*	功能说明: bsp_InitAdcPotentiometer 参数
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
	/*  */
//void bsp_InitAdcPotentiometer(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
	//RCC_APB2PeriphClockCmd(RES_POT_GPIO_CLK, ENABLE);
	///* 配置 RES_POT 为模拟输入 */
//	GPIO_InitStructure.GPIO_Pin = RES_POT_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//	GPIO_Init(RES_POT_GPIO_PORT, &GPIO_InitStructure);
	/* 配置 RES_POT 的 ADC 参数 */
//	bsp_InitAdc(RES_POT_ADC_X,RES_POT_ADC_CHANNEL,RES_POT_ADC_SAMPLETIME);
//}
/*
*********************************************************************************************************
*	函 数 名:Get_Adc_Potentiometer
*	功能说明: 	得到电位器电压值
*	形    参：
*	返 回 值: 	电位器电压值，均值采样
********************************************************************************************************
*/
uint16_t Get_Adc_Potentiometer(void)
{
	uint16_t adcx;
	adcx = Get_Adc_Average(RES_POT_ADC_X,SAMP_COUNT); /* SAMP_COUNT 次取平均 */
	return adcx;
}
/*
*********************************************************************************************************
*	函 数 名:bsp_InitAdcTemp
*	功能说明: 配置 AdcTemp 参数
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_InitAdcTemp(void)
{
	/* 配置内部温度传感器的 ADC 参数 */
	bsp_InitAdc(ADC1,ADC_Channel_TempSensor,ADC_SampleTime_55Cycles5);
	/* 使能内部温度传感器的通道 */
	ADC_TempSensorVrefintCmd(ENABLE);
}
/*
*********************************************************************************************************
*	函 数 名:Get_Temprate
*	功能说明: 得到温度值。
*	形    参：
*	返 回 值: 温度值(扩大了 100 倍,单位:℃.)
********************************************************************************************************
*/
short Get_Temprate(void)//获取内部温度传感器温度值
{
	uint32_t adcx;
	short result;
	double temperate;
	adcx=Get_Adc_Average(ADC1,SAMP_COUNT); //SAMP_COUNT 次取平均
	temperate=(float)adcx*(3.3/4096); //电压值
	temperate=(1.43-temperate)/0.0043+25; //转换为温度值
	result=temperate*=100; //扩大 100 倍.
	return result;
}
/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
