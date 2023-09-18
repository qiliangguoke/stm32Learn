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
*	功能说明: 
*	形    参：ADCx /RES_POT 的 ADCx
*				 ADC_Channel  RES_POT 的 ADC 输入通道
*				ADC_SampleTime   RES_POT 的 ADC 采样时间
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
	ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime );//配置 ADCx 的规则通道，包括通道号、采样顺序和采样时间等参数
	ADC_Cmd(ADCx, ENABLE); //使能指定的 ADCx
	ADC_ResetCalibration(ADCx); //使能复位校准 
	while(ADC_GetResetCalibrationStatus(ADCx)); //等待复位校准结束
	ADC_StartCalibration(ADCx); //开启 AD 校准
	while(ADC_GetCalibrationStatus(ADCx)); //等待校准结束

}
/*
*********************************************************************************************************
*	函 数 名:Get_Adc
*	功能说明: 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
static uint16_t Get_Adc(ADC_TypeDef* ADCx) 
{
	//该函数用于使能或禁用 STM32 上的 ADC 模块开始软件启动转换。软件启动转换是指由软件发出启动转换的命令，即通过软件触发 ADC 转换过程。
	ADC_SoftwareStartConvCmd(ADCx, ENABLE); //使能指定的 ADCx 的软件转换启动功能
	//ADC_GetFlagStatus  该函数用于获取 ADC 是否触发了指定的标志位。函数传入的参数包括 ADCx 和 ADC_FLAG，其中，ADCx 为 ADC 模块，ADC_FLAG 为 ADC 触发的标志位
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC ));//等待转换结束
	//该函数用于获取 STM32 上 ADC 转换完成后的转换数据。函数传入的参数为 ADCx，即表示要获取转换数据的 ADC 模块
	return ADC_GetConversionValue(ADCx); //返回最近一次 ADCx 规则组的转换结果
}
/*
*********************************************************************************************************
*	函 数 名:Get_Adc_Average
*	功能说明: 读取平均值
*	形    参：
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
*	功能说明: 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_InitAdcPotentiometer(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RES_POT_GPIO_CLK, ENABLE);//打开时钟
	/* 配置 RES_POT 为模拟输入 */
	GPIO_InitStructure.GPIO_Pin = RES_POT_GPIO_PIN;	//引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	//
	GPIO_Init(RES_POT_GPIO_PORT, &GPIO_InitStructure);//端口号
	/* 配置 RES_POT 的 ADC 参数 */
	bsp_InitAdc(RES_POT_ADC_X,RES_POT_ADC_CHANNEL,RES_POT_ADC_SAMPLETIME);
}
/*
*********************************************************************************************************
*	函 数 名:Get_Adc_Potentiometer
*	功能说明: 代码桥接，防止
*	形    参：
*	返 回 值: 电压值平均值
********************************************************************************************************
*/
uint16_t Get_Adc_Potentiometer(void)
{
	uint16_t adcx;
	adcx = Get_Adc_Average(RES_POT_ADC_X,SAMP_COUNT); /* SAMP_COUNT 次取平均 */
	return adcx;
}
/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
