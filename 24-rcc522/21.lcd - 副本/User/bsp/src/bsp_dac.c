#include "bsp.h"

/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitDac1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE ); 	/* 使能PORTA通道时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE ); 	/* 使能DAC通道时钟 */
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 				/* 端口配置 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 			/* 模拟输入 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4); 						/* PA.4输出高 */
	
	DAC_InitType.DAC_Trigger = DAC_Trigger_None; 							/* 不使用触发功能 TEN1=0 */
	DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None; 				/* 不使用波形发生 */
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0; 	/* 屏蔽、幅值设置 */
	DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Disable; 				/* DAC1 输出缓存关闭 BOFF1=1 */
	DAC_Init(DAC_Channel_1,&DAC_InitType); 									/* 初始化 DAC 通道 1 */
	
	DAC_Cmd(DAC_Channel_1, ENABLE);			 /* 使能 DAC1 */
	DAC_SetChannel1Data(DAC_Align_12b_R, 0); /* 12 位右对齐数据格式设置 DAC 值,初始值设定为 0 */
}
/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void Dac1_Set_Vol(uint16_t vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4095/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp); 	/* 12位右对齐数据格式设置DAC值 */
}

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
