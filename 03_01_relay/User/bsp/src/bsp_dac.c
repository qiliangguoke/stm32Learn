#include "bsp.h"




void bsp_InitDac1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE ); /* ʹ�� PORTA ͨ��ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE ); /* ʹ�� DAC ͨ��ʱ�� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; /* �˿����� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; /* ģ������ */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4); /* PA.4 ����� */
	DAC_InitType.DAC_Trigger = DAC_Trigger_None; /* ��ʹ�ô������� TEN1=0 */
	DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None; /* ��ʹ�ò��η��� */
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0; /* ���Ρ���ֵ���� */
	DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Disable; /* DAC1 �������ر� BOFF1=1 */
	DAC_Init(DAC_Channel_1,&DAC_InitType); /* ��ʼ�� DAC ͨ�� 1 */
	DAC_Cmd(DAC_Channel_1, ENABLE); /* ʹ�� DAC1 */
	DAC_SetChannel1Data(DAC_Align_12b_R, 0); /* 12 λ�Ҷ������ݸ�ʽ���� DAC ֵ,��ʼֵ�趨Ϊ 0 */
	
}

void Dac1_Set_Vol(uint16_t vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4095/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp); /* 12 λ�Ҷ������ݸ�ʽ���� DAC ֵ */
	
}