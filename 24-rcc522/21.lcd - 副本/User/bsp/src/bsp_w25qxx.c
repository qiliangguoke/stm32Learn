#include "bsp.h"
void W25QXX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd( RCC_ALL_W25QXX, ENABLE ); //W25QXX ʱ��ʹ��
GPIO_InitStructure.GPIO_Pin = W25QXX_CS_GPIO_PIN; // W25QXX_CS ����
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(W25QXX_CS_GPIO_PORT, &GPIO_InitStructure);
GPIO_SetBits(W25QXX_CS_GPIO_PORT,W25QXX_CS_GPIO_PIN);
W25QXX_CS = 1; //SPI FLASH ��ѡ��
bsp_InitSPIx(W25QXX_SPIx); //��ʼ�� SPI
SPIx_SetSpeed(W25QXX_SPIx,SPI_BaudRatePrescaler_2); //����Ϊ 18M ʱ��,����ģʽ
SPIx_SetCPOL_CPHA(W25QXX_SPIx,SPI_CPOL_High,SPI_CPHA_2Edge);//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
}

/*
*********************************************************************************************************
*	�� �� ��: 
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static uint8_t W25QXX_SPIx_ReadWriteByte(uint8_t TxData)
{
uint8_t temp;
temp = SPIx_ReadWriteByte(W25QXX_SPIx,TxData);
return temp;
}
/*
*********************************************************************************************************
* �� �� ��: W25QXX_ReadSR
* ����˵��: ��ȡ W25QXX ��״̬�Ĵ���
* �� ��: ��
* �� �� ֵ: ��
* �� ע��
*
* BIT7 6 5 4 3 2 1 0
* SPR RV TB BP2 BP1 BP0 WEL BUSY
* SPR:Ĭ�� 0,״̬�Ĵ�������λ,��� WP ʹ��
* TB,BP2,BP1,BP0:FLASH ����д��������
* WEL:дʹ������
* BUSY:æ���λ(1,æ;0,����)
* Ĭ��:0x00
*********************************************************************************************************
*/
uint8_t W25QXX_ReadSR(void) 
{ 
uint8_t byte = 0;
W25QXX_CS = 0; //ʹ������ 
W25QXX_SPIx_ReadWriteByte(W25X_ReadStatusReg); //���Ͷ�ȡ״̬�Ĵ������� 
byte = W25QXX_SPIx_ReadWriteByte(Dummy_Byte); //��ȡһ���ֽ� 
W25QXX_CS = 1; //ȡ��Ƭѡ 
return byte; 
} 
/*
*********************************************************************************************************
* �� �� ��: W25QXX_Write_SR
* ����˵��: д W25QXX ״̬�Ĵ���
* �� ��: sr ��Ҫд��ļĴ���ֵ
* �� �� ֵ: ��
* �� ע��ֻ�� SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
*********************************************************************************************************
*/
void W25QXX_Write_SR(uint8_t sr) 
{
	W25QXX_CS = 0; //ʹ������ 
W25QXX_SPIx_ReadWriteByte(W25X_WriteStatusReg); //����дȡ״̬�Ĵ������� 
W25QXX_SPIx_ReadWriteByte(sr); //д��һ���ֽ� 
W25QXX_CS = 1; //ȡ��Ƭѡ 
} 
/*
*********************************************************************************************************
* �� �� ��: W25QXX_Write_Enable
* ����˵��: W25QXX дʹ��,�� WEL ��λ
* �� ��: ��
* �� �� ֵ: ��
*********************************************************************************************************
*/
void W25QXX_Write_Enable(void) 
{
W25QXX_CS = 0; //ʹ������ 
 W25QXX_SPIx_ReadWriteByte(W25X_WriteEnable); //����дʹ�� 
W25QXX_CS = 1; //ȡ��Ƭѡ 
} 
 
/*
*********************************************************************************************************
* �� �� ��: W25QXX_Write_Disable
* ����˵��: W25QXX д��ֹ,�� WEL ����
* �� ��: ��
* �� �� ֵ: ��
*********************************************************************************************************
*/
void W25QXX_Write_Disable(void) 
{ 
W25QXX_CS = 0; //ʹ������ 
 W25QXX_SPIx_ReadWriteByte(W25X_WriteDisable); //����д��ָֹ�� 
W25QXX_CS = 1; //ȡ��Ƭѡ 
} 
/*
*********************************************************************************************************
* �� �� ��: W25QXX_ReadID
* ����˵��: ��ȡоƬ ID
* �� ��: ��
* �� �� ֵ: ����
* 0XEF13,��ʾоƬ�ͺ�Ϊ W25Q80 
* 0XEF14,��ʾоƬ�ͺ�Ϊ W25Q16 
* 0XEF15,��ʾоƬ�ͺ�Ϊ W25Q32 
* 0XEF16,��ʾоƬ�ͺ�Ϊ W25Q64 
* 0XEF17,��ʾоƬ�ͺ�Ϊ W25Q128 
*********************************************************************************************************
*/
uint16_t W25QXX_ReadID(void)
{
uint16_t Temp = 0;
W25QXX_CS = 0; 
W25QXX_SPIx_ReadWriteByte(W25X_ManufactDeviceID); //���Ͷ�ȡ ID ����
W25QXX_SPIx_ReadWriteByte(0x00); //���� 24bits ��ַ 0x000000���� 3 ���ֽ� 0x00
W25QXX_SPIx_ReadWriteByte(0x00); 
W25QXX_SPIx_ReadWriteByte(0x00); 
Temp |= W25QXX_SPIx_ReadWriteByte(Dummy_Byte)<<8; 
Temp |= W25QXX_SPIx_ReadWriteByte(Dummy_Byte);
W25QXX_CS = 1;
return Temp;
} 
/*
*********************************************************************************************************
* �� �� ��: W25QXX_Write_Disable
* ����˵��: ��ȡ SPI FLASH,��ָ����ַ��ʼ��ȡָ�����ȵ�����
* �� ��: pBuffer:���ݴ洢��
* ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
* NumByteToRead:Ҫ��ȡ���ֽ���(��� 65535)
* �� �� ֵ: ��
*********************************************************************************************************
*/
void W25QXX_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead) 
{ 
uint16_t i;
W25QXX_CS = 0; //ʹ������ 
 W25QXX_SPIx_ReadWriteByte(W25X_ReadData); //���Ͷ�ȡ���� 
 W25QXX_SPIx_ReadWriteByte((uint8_t)((ReadAddr)>>16)); //���� 24bit ��ַ 
 W25QXX_SPIx_ReadWriteByte((uint8_t)((ReadAddr)>>8)); 
 W25QXX_SPIx_ReadWriteByte((uint8_t)ReadAddr); 
 for(i=0;i<NumByteToRead;i++)
{ 
 pBuffer[i]=W25QXX_SPIx_ReadWriteByte(0XFF); //ѭ������ 
 }
W25QXX_CS = 1; 
} 
/*
*********************************************************************************************************
* �� �� ��: W25QXX_Write_Disable
* ����˵��: SPI ��һҳ(0~65535)��д������ 256 ���ֽڵ����� ��ָ����ַ��ʼд����� 256 �ֽڵ�����
* �� ��: pBuffer:���ݴ洢��
* WriteAddr:��ʼд��ĵ�ַ(24bit)
* NumByteToWrite:Ҫд����ֽ���(��� 256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!
* �� �� ֵ: ��
*********************************************************************************************************
*/
void W25QXX_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{
uint16_t i;
 W25QXX_Write_Enable(); //SET WEL 
W25QXX_CS = 0; //ʹ������ 
 W25QXX_SPIx_ReadWriteByte(W25X_PageProgram); //����дҳ���� 
 W25QXX_SPIx_ReadWriteByte((uint8_t)((WriteAddr)>>16)); //���� 24bit ��ַ 
 W25QXX_SPIx_ReadWriteByte((uint8_t)((WriteAddr)>>8)); 
 W25QXX_SPIx_ReadWriteByte((uint8_t)WriteAddr); 
 for(i=0;i<NumByteToWrite;i++)
{
W25QXX_SPIx_ReadWriteByte(pBuffer[i]);//ѭ��д��
}
W25QXX_CS = 1; //ȡ��Ƭѡ
W25QXX_Wait_Busy(); //�ȴ�д�����
}
/*
*********************************************************************************************************
* �� �� ��: W25QXX_Write_NoCheck
* ����˵��: �޼���д SPI FLASH
* �� ��: pBuffer:���ݴ洢��
* WriteAddr:��ʼд��ĵ�ַ(24bit)
* NumByteToWrite:Ҫд����ֽ���(��� 65535) 
* �� �� ֵ: ��
* ע ��:
* ����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ 0XFF,�����ڷ� 0XFF ��д������ݽ�ʧ��!
* �����Զ���ҳ����
* ��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
*********************************************************************************************************
*/
void W25QXX_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite) 
{ 
uint16_t pageremain;
pageremain = 256 - WriteAddr%256; //��ҳʣ����ֽ��� 
if(NumByteToWrite<=pageremain)
{
pageremain=NumByteToWrite;//������ 256 ���ֽ�
}
while(1)
{ 
W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
if(NumByteToWrite == pageremain)
{
break;//д�������
}
else //NumByteToWrite>pageremain
{
	pBuffer+=pageremain;
WriteAddr+=pageremain;
NumByteToWrite-=pageremain; //��ȥ�Ѿ�д���˵��ֽ���
if(NumByteToWrite>256)
{
pageremain=256; //һ�ο���д�� 256 ���ֽ�
}
else 
{
pageremain=NumByteToWrite; //���� 256 ���ֽ���
}
}
}; 
} 
/*
*********************************************************************************************************
* �� �� ��: W25QXX_Write
* ����˵��: д SPI FLASH,��ָ����ַ��ʼд��ָ�����ȵ�����
* �� ��: pBuffer:���ݴ洢��
* WriteAddr:��ʼд��ĵ�ַ(24bit)
* NumByteToWrite:Ҫд����ֽ���(��� 65535) 
* �� �� ֵ: ��
* ע ��: �ú�������������!
*********************************************************************************************************
*/
uint8_t W25QXX_BUFFER[4096];
void W25QXX_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite) 
{ 
uint32_t secpos;
uint16_t secoff;
uint16_t secremain; 
uint16_t i; 
uint8_t * W25QXX_BUF;
 W25QXX_BUF = W25QXX_BUFFER; 
secpos = WriteAddr/4096;//������ַ 
secoff = WriteAddr%4096;//�������ڵ�ƫ��
secremain = 4096 - secoff;//����ʣ��ռ��С 
BSP_Printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//������
if(NumByteToWrite<=secremain)
{
secremain=NumByteToWrite;//������ 4096 ���ֽ�
}
while(1) 
{
W25QXX_Read(W25QXX_BUF,secpos*4096,4096);//������������������
for(i=0;i<secremain;i++)//У������
{
if(W25QXX_BUF[secoff+i]!=0XFF)break;//��Ҫ���� 
}
if(i<secremain)//��Ҫ����
{
W25QXX_Erase_Sector(secpos); //�����������
for(i=0;i<secremain;i++) //����
{
W25QXX_BUF[i+secoff]=pBuffer[i]; 
}
W25QXX_Write_NoCheck(W25QXX_BUF,secpos*4096,4096);//д���������� 
}else 
{
W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 
}
if(NumByteToWrite == secremain)
{
break;//д�������
}
else//д��δ����
{
secpos++;//������ַ�� 1
	secoff = 0;//ƫ��λ��Ϊ 0 
 pBuffer+=secremain; //ָ��ƫ��
WriteAddr+=secremain; //д��ַƫ�� 
 NumByteToWrite-=secremain; //�ֽ����ݼ�
if(NumByteToWrite>4096)
{
secremain=4096;//��һ����������д����
}
else 
{
secremain=NumByteToWrite; //��һ����������д����
}
}
};
}
/*
*********************************************************************************************************
* �� �� ��: W25QXX_Erase_Chip
* ����˵��: ��������оƬ
* �� ��: ��
* �� �� ֵ: ��
* ע ��: �ȴ�ʱ�䳬��...
*********************************************************************************************************
*/
void W25QXX_Erase_Chip(void) 
{ 
 W25QXX_Write_Enable(); //SET WEL 
 W25QXX_Wait_Busy(); 
 W25QXX_CS = 0; //ʹ������ 
 W25QXX_SPIx_ReadWriteByte(W25X_ChipErase); //����Ƭ�������� 
W25QXX_CS = 1; //ȡ��Ƭѡ 
W25QXX_Wait_Busy(); //�ȴ�оƬ��������
} 
/*
*********************************************************************************************************
* �� �� ��: W25QXX_Erase_Sector
* ����˵��: ����һ������
* �� ��: Dst_Addr:������ַ ����ʵ����������
* �� �� ֵ: ��
* ע ��: ����һ������������ʱ��:150ms
*********************************************************************************************************
*/
void W25QXX_Erase_Sector(uint32_t Dst_Addr) 
{ 
//���� falsh �������,������ 
BSP_Printf("fe:%x\r\n",Dst_Addr);
Dst_Addr*=4096;
 W25QXX_Write_Enable(); //SET WEL 
 W25QXX_Wait_Busy(); 
 W25QXX_CS = 0; //ʹ������ 
 W25QXX_SPIx_ReadWriteByte(W25X_SectorErase); //������������ָ��
 W25QXX_SPIx_ReadWriteByte((uint8_t)((Dst_Addr)>>16)); //���� 24bit ��ַ 
 W25QXX_SPIx_ReadWriteByte((uint8_t)((Dst_Addr)>>8)); 
 W25QXX_SPIx_ReadWriteByte((uint8_t)Dst_Addr); 
W25QXX_CS = 1; //ȡ��Ƭѡ 
 W25QXX_Wait_Busy(); //�ȴ��������
} 
/*
*********************************************************************************************************
* �� �� ��: W25QXX_Wait_Busy
* ����˵��: �ȴ�����
* �� ��: ��
* �� �� ֵ: ��
*********************************************************************************************************
*/
void W25QXX_Wait_Busy(void) 
{ 
while((W25QXX_ReadSR()&0x01) == 0x01); // �ȴ� BUSY λ���
}
/*
*********************************************************************************************************
* �� �� ��: W25QXX_PowerDown
* ����˵��: �������ģʽ
* �� ��: ��
* �� �� ֵ: ��
*********************************************************************************************************
*/
void W25QXX_PowerDown(void) 
{ 
 W25QXX_CS = 0; //ʹ������ 
 W25QXX_SPIx_ReadWriteByte(W25X_PowerDown); //���͵������� 
W25QXX_CS = 1; //ȡ��Ƭѡ 
 delay_us(3); //�ȴ� TPD 
} 
/*
*********************************************************************************************************
* �� �� ��: W25QXX_WAKEUP
* ����˵��: ����
* �� ��: ��
* �� �� ֵ: ��
*********************************************************************************************************
*/
void W25QXX_WAKEUP(void) 
{ 
 W25QXX_CS = 0; //ʹ������ 
 W25QXX_SPIx_ReadWriteByte(W25X_ReleasePowerDown); // send W25X_PowerDown command 0xAB 
W25QXX_CS = 1; //ȡ��Ƭѡ 
 delay_us(3); //�ȴ� TRES1
} 
/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
