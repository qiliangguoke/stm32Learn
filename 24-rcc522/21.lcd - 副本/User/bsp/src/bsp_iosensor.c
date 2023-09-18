#include "bsp.h"

uint8_t VIBRATE_OUT_flag = 0; //�𶯴�����������־
uint8_t PIR_OUT_flag = 0; 	  //������⴫����������־

void SENSOR_IO_Init(void);  //IO ��ʼ��
void EXTI_Sensor_Init(void);//�жϳ�ʼ��
/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitIoSensor(void)
{
	SENSOR_IO_Init();
	EXTI_Sensor_Init();
}
/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void SENSOR_IO_Init(void) //IO ��ʼ��
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //ʹ�ܸ��ù���ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر� jtag��ʹ�� SWD�������� SWD ģʽ����
	
	RCC_APB2PeriphClockCmd(VIBRATE_OUT_GPIO_CLK,ENABLE); //ʹ�� VIBRATE_OUT ʱ��
	//��ʼ�� VIBRATE_OUT 
	GPIO_InitStructure.GPIO_Pin = VIBRATE_OUT_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = VIBRATE_OUT_GPIO_MODE; //���ó����룬Ĭ������ 
	GPIO_Init(VIBRATE_OUT_GPIO_PORT, &GPIO_InitStructure); //��ʼ�� VIBRATE
	
	RCC_APB2PeriphClockCmd(PIR_OUT_GPIO_CLK,ENABLE); //ʹ�� PIR_OUT ʱ��
	//��ʼ�� PIR_OUT 
	GPIO_InitStructure.GPIO_Pin = PIR_OUT_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = PIR_OUT_GPIO_MODE; //���ó����룬Ĭ������ 
	GPIO_Init(PIR_OUT_GPIO_PORT, &GPIO_InitStructure); //��ʼ�� PIR
}
/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void EXTI_Sensor_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //�ر� jtag��ʹ�� SWD�������� SWD ģʽ����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //ʹ�ܸ��ù���ʱ��
	
	//VIBRATE �ж����Լ��жϳ�ʼ������
	GPIO_EXTILineConfig(VIBRATE_OUT_PORT_SRC,VIBRATE_OUT_PIN_SRC); 
	
	EXTI_InitStructure.EXTI_Line = VIBRATE_OUT_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = VIBRATE_OUT_EXTI_TRIG;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); //���� EXTI_InitStruct ��ָ���Ĳ�����ʼ������ EXTI �Ĵ���
	
	/////////////////////////////////////////////
	
	NVIC_InitStructure.NVIC_IRQChannel = VIBRATE_OUT_EXTI_IRQN; //ʹ�� VIBRATE ���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //��ռ���ȼ� 2 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //�����ȼ� 2 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //���� NVIC_InitStruct ��ָ���Ĳ�����ʼ������ NVIC �Ĵ���
	
	//PIR �ж����Լ��жϳ�ʼ������
	GPIO_EXTILineConfig(PIR_OUT_PORT_SRC,PIR_OUT_PIN_SRC); 
	
	EXTI_InitStructure.EXTI_Line = PIR_OUT_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = PIR_OUT_EXTI_TRIG;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); //���� EXTI_InitStruct ��ָ���Ĳ�����ʼ������ EXTI �Ĵ���
	
	/////////////////////////////////////////////
	
	NVIC_InitStructure.NVIC_IRQChannel = PIR_OUT_EXTI_IRQN; //ʹ�� GAS ���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //��ռ���ȼ� 2 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //�����ȼ� 2 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //���� NVIC_InitStruct ��ָ���Ĳ�����ʼ������ NVIC �Ĵ���
}
/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(VIBRATE_OUT_EXTI_LINE)!=RESET) 
	{
	if(VIBRATE_OUT == VIBRATE_OUT_ACTIVE_LEVEL) //VIBRATE_OUT ����Ϊ�͵�ƽ
		{
			VIBRATE_OUT_flag = 1;//��־��λ��������������ѯ
		}
		//�жϴ����������
		EXTI_ClearITPendingBit(VIBRATE_OUT_EXTI_LINE);
	} 
	
	if(EXTI_GetITStatus(PIR_OUT_EXTI_LINE)!=RESET) 
		{
		if(PIR_OUT == PIR_OUT_ACTIVE_LEVEL) //PIR_OUT ����Ϊ�ߵ�ƽ
		{
			PIR_OUT_flag = 1;//��־��λ��������������ѯ
		}
		//�жϴ����������
		EXTI_ClearITPendingBit(PIR_OUT_EXTI_LINE);
	} 
}
/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
