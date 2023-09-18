#include "bsp.h"
#include "bsp_dma.h"
#include "sys.h"


const uint32_t SRC_Buffer[BUFFER_SIZE]= {
												
												0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
												0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
												0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
												0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
												};

uint32_t DST_Buffer[BUFFER_SIZE];
uint32_t SendBuf[SEND_SIZE];

//void DMA_Config(void){
//	
//	DMA_InitTypeDef DMA_InitStructure;
//	RCC_AHBPeriphClockCmd(DMA_CLOCK, ENABLE);
//	//����Դ��ַ
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SRC_Buffer;
//	
//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)DST_Buffer;
//	//���ݴ��䷽��
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//	
//	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
//	// ���裨�ڲ��� FLASH����ַ���� 
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
//	// �ڴ��ַ����
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	// �������ݵ�λ
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
//	// �ڴ����ݵ�λ
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
//	
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
//		//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 
//		// ���ȼ�����
//		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//		// ʹ���ڴ浽�ڴ�Ĵ���
//		DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
//		
//		// ���� DMA ͨ�� 
//		DMA_Init(DMA_CHANNEL, &DMA_InitStructure);
//		
//		//��� DMA ������������ɱ�־λ
//		DMA_ClearFlag(DMA_FLAG_TC);
//		// ʹ�� DMA
//		DMA_Cmd(DMA_CHANNEL,ENABLE);
//}

void USART_DMA_Init(void)//���ڳ�ʼ��
{
		//����dmc�ṹ�����
		DMA_InitTypeDef DMA_InitStructure;
	 //����ʱ��
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//MemoryBaseAddr ��������ַ
    DMA_InitStructure.DMA_MemoryBaseAddr     =  (uint32_t)SendBuf;
	//PeripheralBaseAddr �����ַ  
	  DMA_InitStructure.DMA_PeripheralBaseAddr =  (uint32_t)USART_DR_ADDR;
	//DIR ���䷽��			DMA_DIR_PeripheralDST  ����ΪĿ��  DMA_DIR_PeripheralSRC ����ΪԴͷ
	  DMA_InitStructure.DMA_DIR                =   DMA_DIR_PeripheralDST;
		//����Ĵ�С
	  DMA_InitStructure.DMA_BufferSize         =   SEND_SIZE;
	//����DMA���ڴ����ģʽ��DMA ���ʶ���ڴ����ʱ����Ҫʹ��DMA_MemoryInc_Enable��
	//��DMAֻ����һ���ڴ����ʱ�����ó� ��DMA_MemoryInc_Disable��
	  DMA_InitStructure.DMA_MemoryInc          =   DMA_MemoryInc_Enable;
		//PeripheralInc �����ַ����   DMA_PeripheralInc_Enable �ж���������� 
		//								DMA_PeripheralInc_Disable  ֻ��һ����
	  DMA_InitStructure.DMA_PeripheralInc      =   DMA_PeripheralInc_Disable ;
		//MemoryDataSize   �������������ݿ��    DMA_MemoryDataSize_Byte   �޿��
		//                         					DMA_MemoryDataSize_HalfWord  �������ݿ��Ϊ32λ
		//											DMA_MemoryDataSize_Word   �ڴ����ݿ��Ϊ16λ
	  DMA_InitStructure.DMA_MemoryDataSize     =   DMA_MemoryDataSize_Byte;
		//PeripheralDataSize  ���财����      DMA_PeripheralDataSize_Byte   �޿��
		//                         					DMA_PeripheralDataSize_HalfWord  �������ݿ��Ϊ32λ
		//											DMA_PeripheralDataSize_Word   �ڴ����ݿ��Ϊ16λ		
	  DMA_InitStructure.DMA_PeripheralDataSize =   DMA_PeripheralDataSize_Byte;
		//DMA_Mode   ģʽѡ��        DMA_Mode_Normal  ����
		//							DMA_Mode_Circular �������ϵ�ѭ��ģʽ��	
	  DMA_InitStructure.DMA_Mode               =   DMA_Mode_Normal;
	  //Priority  ���ȼ���   	���Է�Ϊ 4 ����VeryHigh��High,Medium,Low.
	  DMA_InitStructure.DMA_Priority           =   DMA_Priority_High;
	  //DMA �� 2 �� memory �еı���������ʵ� ʹ���ڴ浽�ڴ�Ĵ���    DMA_M2M_Disable  ������   enable  ����
    DMA_InitStructure.DMA_M2M                =   DMA_M2M_Enable;
	//ʹ�õ�ͨ��
	  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	  //���DMA������������ɱ�־λ
	  DMA_ClearFlag(DMA1_FLAG_TC4);
	  //ʹ��DM
	  DMA_Cmd(DMA1_Channel4,ENABLE);
	
	
}