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
//	//定义源地址
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SRC_Buffer;
//	
//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)DST_Buffer;
//	//数据传输方向
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//	
//	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
//	// 外设（内部的 FLASH）地址递增 
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
//	// 内存地址递增
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	// 外设数据单位
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
//	// 内存数据单位
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
//	
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
//		//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 
//		// 优先级：高
//		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//		// 使能内存到内存的传输
//		DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
//		
//		// 配置 DMA 通道 
//		DMA_Init(DMA_CHANNEL, &DMA_InitStructure);
//		
//		//清除 DMA 数据流传输完成标志位
//		DMA_ClearFlag(DMA_FLAG_TC);
//		// 使能 DMA
//		DMA_Cmd(DMA_CHANNEL,ENABLE);
//}

void USART_DMA_Init(void)//串口初始化
{
		//定义dmc结构体变量
		DMA_InitTypeDef DMA_InitStructure;
	 //开启时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//MemoryBaseAddr 储存器地址
    DMA_InitStructure.DMA_MemoryBaseAddr     =  (uint32_t)SendBuf;
	//PeripheralBaseAddr 外设地址  
	  DMA_InitStructure.DMA_PeripheralBaseAddr =  (uint32_t)USART_DR_ADDR;
	//DIR 传输方向			DMA_DIR_PeripheralDST  外设为目标  DMA_DIR_PeripheralSRC 外设为源头
	  DMA_InitStructure.DMA_DIR                =   DMA_DIR_PeripheralDST;
		//传输的大小
	  DMA_InitStructure.DMA_BufferSize         =   SEND_SIZE;
	//设置DMA的内存递增模式，DMA 访问多个内存参数时，需要使用DMA_MemoryInc_Enable，
	//当DMA只访问一个内存参数时可设置成 ：DMA_MemoryInc_Disable。
	  DMA_InitStructure.DMA_MemoryInc          =   DMA_MemoryInc_Enable;
		//PeripheralInc 外设地址增量   DMA_PeripheralInc_Enable 有多个外设连接 
		//								DMA_PeripheralInc_Disable  只有一外设
	  DMA_InitStructure.DMA_PeripheralInc      =   DMA_PeripheralInc_Disable ;
		//MemoryDataSize   储存器外设数据宽度    DMA_MemoryDataSize_Byte   无宽度
		//                         					DMA_MemoryDataSize_HalfWord  外设数据宽度为32位
		//											DMA_MemoryDataSize_Word   内存数据宽度为16位
	  DMA_InitStructure.DMA_MemoryDataSize     =   DMA_MemoryDataSize_Byte;
		//PeripheralDataSize  外设储存宽度      DMA_PeripheralDataSize_Byte   无宽度
		//                         					DMA_PeripheralDataSize_HalfWord  外设数据宽度为32位
		//											DMA_PeripheralDataSize_Word   内存数据宽度为16位		
	  DMA_InitStructure.DMA_PeripheralDataSize =   DMA_PeripheralDataSize_Byte;
		//DMA_Mode   模式选择        DMA_Mode_Normal  正常
		//							DMA_Mode_Circular 连续不断的循环模式，	
	  DMA_InitStructure.DMA_Mode               =   DMA_Mode_Normal;
	  //Priority  优先级别   	可以分为 4 级：VeryHigh，High,Medium,Low.
	  DMA_InitStructure.DMA_Priority           =   DMA_Priority_High;
	  //DMA 的 2 个 memory 中的变量互相访问的 使能内存到内存的传输    DMA_M2M_Disable  不可以   enable  可以
    DMA_InitStructure.DMA_M2M                =   DMA_M2M_Enable;
	//使用的通道
	  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	  //清除DMA数据流传输完成标志位
	  DMA_ClearFlag(DMA1_FLAG_TC4);
	  //使能DM
	  DMA_Cmd(DMA1_Channel4,ENABLE);
	
	
}