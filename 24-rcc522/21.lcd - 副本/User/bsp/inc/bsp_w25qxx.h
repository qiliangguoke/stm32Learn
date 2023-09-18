#ifndef __BSP_W25QXX_H
#define __BSP_W25QXX_H
#include "sys.h" 
/****************************************************************************/
#define RCC_ALL_W25QXX ( W25QXX_CS_GPIO_CLK )
#define W25QXX_CS_GPIO_PIN GPIO_Pin_12 //W25QXX_CS ���ź�
#define W25QXX_CS_PIN_ID 12 //W25QXX_CS �������
#define W25QXX_CS_GPIO_PORT GPIOB //W25QXX_CS �˿ں�
#define W25QXX_CS_GPIO_CLK RCC_APB2Periph_GPIOB //W25QXX_CS ʱ��
#define W25QXX_CS_FUN_OUT PBout //W25QXX_CS ����˿����ú���
//#define W25QXX_CS_FUN_IN PBin //W25QXX_CS ����˿����ú���
#define W25QXX_SPIx SPI2 //W25QXX ʹ�� SPI2 �˿�
/****************************************************************************/
//W25X ϵ��/Q ϵ��оƬ�б� 
//W25Q80 ID 0XEF13
//W25Q16 ID 0XEF14
//W25Q32 ID 0XEF15
//W25Q64 ID 0XEF16
//W25Q128 ID 0XEF17
#define W25Q80 0XEF13 
#define W25Q16 0XEF14
#define W25Q32 0XEF15
#define W25Q64 0XEF16
#define W25Q128 0XEF17
//4Kbytes Ϊһ�� Sector
//16 ������Ϊ 1 �� Block
//W25Q128
//����Ϊ 16M �ֽ�,���� 128 �� Block,4096 �� Sector
#define W25QXX_TYPE W25Q128 //���� W25QXX оƬ�ͺ� 
//IO ��������
#define W25QXX_CS W25QXX_CS_FUN_OUT(W25QXX_CS_PIN_ID) //W25QXX_CS W25QXX ��Ƭѡ�ź�
////////////////////////////////////////////////////////////////////////////
/*ָ�����-��ͷ*******************************/
#define W25X_WriteEnable 0x06 
#define W25X_WriteDisable 0x04 
#define W25X_ReadStatusReg 0x05 
#define W25X_WriteStatusReg 0x01 
#define W25X_ReadData 0x03 
#define W25X_FastReadData 0x0B 
#define W25X_FastReadDual 0x3B 
#define W25X_PageProgram 0x02 
#define W25X_BlockErase 0xD8 
#define W25X_SectorErase 0x20 
#define W25X_ChipErase 0xC7 
#define W25X_PowerDown 0xB9 
#define W25X_ReleasePowerDown 0xAB 
#define W25X_DeviceID 0xAB 
#define W25X_ManufactDeviceID 0x90 
#define W25X_JedecDeviceID 0x9F
#define Dummy_Byte 0xFF
/*ָ�����-��β*******************************/
void W25QXX_Init(void);
uint16_t W25QXX_ReadID(void); //��ȡ FLASH ID
uint8_t W25QXX_ReadSR(void); //��ȡ״̬�Ĵ���
void W25QXX_Write_SR(uint8_t sr); //д״̬�Ĵ���
void W25QXX_Write_Enable(void); //дʹ��
void W25QXX_Write_Disable(void); //д����
void W25QXX_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
void W25QXX_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead); //��ȡ flash
void W25QXX_Write(uint8_t* pBuffer,u32 WriteAddr,uint16_t NumByteToWrite); //д�� flash
void W25QXX_Erase_Chip(void); //��Ƭ����
void W25QXX_Erase_Sector(uint32_t Dst_Addr); //��������
void W25QXX_Wait_Busy(void); //�ȴ�����
void W25QXX_PowerDown(void); //�������ģʽ
void W25QXX_WAKEUP(void); //����
#endif
/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
