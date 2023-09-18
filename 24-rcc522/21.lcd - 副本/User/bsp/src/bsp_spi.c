#include "bsp.h"
/*
*********************************************************************************************************
* �� �� ��: SPI_RCC_Configuration
* ����˵��: ʹ�� SPI ʱ��
* �� ��: SPIx ��Ҫʹ�õ� SPI
* �� �� ֵ: ��
*********************************************************************************************************
*/
static void SPI_RCC_Configuration(SPI_TypeDef* SPIx)
{
if(SPIx==SPI1)
{
RCC_SPI1(SPI1_CLK,ENABLE); //ʹ�� SPI1 ʱ��
}
else
{
RCC_SPI2(SPI2_CLK,ENABLE); //ʹ�� SPI2 ʱ��
}
}
/*
*********************************************************************************************************
* �� �� ��: SPI_GPIO_Configuration
* ����˵��: ����ָ�� SPI ������
* �� ��: SPIx ��Ҫʹ�õ� SPI
* �� �� ֵ: ��
*********************************************************************************************************
*/
static void SPI_GPIO_Configuration(SPI_TypeDef* SPIx)
{
GPIO_InitTypeDef SPI_InitStructure;
 if(SPIx==SPI1)
{
RCC_APB2PeriphClockCmd(SPI1_GPIO_ALL_CLK,ENABLE); //ʹ�� SPI1 �˿�ʱ��
SPI_InitStructure.GPIO_Pin = SPI1_SCK_GPIO_PIN;
SPI_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
SPI_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
GPIO_Init(SPI1_SCK_GPIO_PORT, &SPI_InitStructure);
GPIO_SetBits(SPI1_SCK_GPIO_PORT,SPI1_SCK_GPIO_PIN); //����
SPI_InitStructure.GPIO_Pin = SPI1_MISO_GPIO_PIN;
SPI_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
SPI_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
GPIO_Init(SPI1_MISO_GPIO_PORT, &SPI_InitStructure);
GPIO_SetBits(SPI1_MISO_GPIO_PORT,SPI1_MISO_GPIO_PIN); //����
SPI_InitStructure.GPIO_Pin = SPI1_MOSI_GPIO_PIN;
SPI_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
SPI_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
GPIO_Init(SPI1_MOSI_GPIO_PORT, &SPI_InitStructure);
GPIO_SetBits(SPI1_MOSI_GPIO_PORT,SPI1_MOSI_GPIO_PIN); //����
}else
{
RCC_APB2PeriphClockCmd(SPI2_GPIO_ALL_CLK,ENABLE); //ʹ�� SPI2 �˿�ʱ��
	SPI_InitStructure.GPIO_Pin = SPI2_SCK_GPIO_PIN;
SPI_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
SPI_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
GPIO_Init(SPI2_SCK_GPIO_PORT, &SPI_InitStructure);
GPIO_SetBits(SPI2_SCK_GPIO_PORT,SPI2_SCK_GPIO_PIN); //����
SPI_InitStructure.GPIO_Pin = SPI2_MISO_GPIO_PIN;
SPI_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
SPI_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
GPIO_Init(SPI2_MISO_GPIO_PORT, &SPI_InitStructure);
GPIO_SetBits(SPI2_MISO_GPIO_PORT,SPI2_MISO_GPIO_PIN); //����
SPI_InitStructure.GPIO_Pin = SPI2_MOSI_GPIO_PIN;
SPI_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
SPI_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
GPIO_Init(SPI2_MOSI_GPIO_PORT, &SPI_InitStructure);
GPIO_SetBits(SPI2_MOSI_GPIO_PORT,SPI2_MOSI_GPIO_PIN); //����
} 
}
/*
*********************************************************************************************************
* �� �� ��: SPIx_SetCPOL_CPHA
* ����˵��: ����ָ�� SPI CPOL ���� CPHA ����ʱ�ӵ�λ��
* �� ��: SPIx ��Ҫʹ�õ� SPI
* CPOL Set:SPI_CPOL_Low,SPI_CPOL_High
* CPHA Set:SPI_CPHA_1Edge,SPI_CPHA_2Edge
* �� �� ֵ: ��
* ע �⣺������ bsp_InitSPIx ���������
*********************************************************************************************************
*/
void SPIx_SetCPOL_CPHA(SPI_TypeDef* SPIx,uint16_t SPI_CPOL,uint16_t SPI_CPHA)
{
assert_param(IS_SPI_ALL_PERIPH(SPIx));
assert_param(IS_SPI_CPOL(SPI_CPOL));
assert_param(IS_SPI_CPHA(SPI_CPHA));
//���� SPIx ����ͬ��ʱ�ӵĿ���״̬Ϊ?��ƽ
if(SPI_CPOL == SPI_CPOL_High)
{
SPIx->CR1 |= SPI_CPOL_High;
}
else
{
SPIx->CR1 &= (uint16_t)~SPI_CPOL_High;
}
//���� SPIx ����ͬ��ʱ�ӵĵ�?�������أ��������½������ݱ�����
if(SPI_CPHA == SPI_CPHA_2Edge )
{
SPIx->CR1 |= SPI_CPHA_2Edge;
}
else
{
SPIx->CR1 &= (uint16_t)~SPI_CPHA_2Edge;
}
SPI_Cmd(SPIx,ENABLE); 
}
/*
*********************************************************************************************************
* �� �� ��: SPIx_SetSpeed
* ����˵��: SPI �ٶ����ú���
* �� ��: SPIx ��Ҫʹ�õ� SPI
* SpeedSet:
* SPI_BaudRatePrescaler_2 2 ��Ƶ 
* SPI_BaudRatePrescaler_8 8 ��Ƶ 
* SPI_BaudRatePrescaler_16 16 ��Ƶ 
* SPI_BaudRatePrescaler_256 256 ��Ƶ
* �� �� ֵ: ��
* ע �⣺������ bsp_InitSPIx ���������
*********************************************************************************************************
*/
void SPIx_SetSpeed(SPI_TypeDef* SPIx,uint16_t SPI_BaudRatePrescaler)
	{
assert_param(IS_SPI_ALL_PERIPH(SPIx));
assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
SPIx->CR1 &= (uint16_t)~SPI_BaudRatePrescaler_256; //ֻ����ٶ�����λ
SPIx->CR1 |= SPI_BaudRatePrescaler; //���� SPIx �ٶ�
SPI_Cmd(SPIx,ENABLE); 
}
/*
*********************************************************************************************************
* �� �� ��: bsp_InitSPIx
* ����˵��: ���� SPIx ��ص����ݡ�
* �� ��: SPIx ��Ҫʹ�õ� SPI
* �� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitSPIx(SPI_TypeDef* SPIx)
{ 
SPI_InitTypeDef SPI_InitStructure;
SPI_RCC_Configuration(SPIx);
SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //���� SPI �������˫�������ģʽ:SPI ����Ϊ˫��˫��ȫ˫��
SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //���� SPI ����ģʽ:����Ϊ�� SPI
SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //���� SPI �����ݴ�С:SPI ���ͽ��� 8 λ֡�ṹ
SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; //����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //����ͬ��ʱ�ӵĵ�һ�������أ��������½������ݱ�����
// SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //����ͬ��ʱ�ӵ�
// SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS �ź���Ӳ����NSS �ܽţ����������ʹ�� SSI λ������:�ڲ� NSS �ź��� SSI λ����
SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; //���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //ָ�����ݴ���� MSB λ����LSB λ��ʼ:���ݴ���� MSB λ��ʼ
SPI_InitStructure.SPI_CRCPolynomial = 7; //CRC ֵ����Ķ���ʽ
SPI_Init(SPIx, &SPI_InitStructure); //���� SPI_InitStruct ��ָ���Ĳ�����ʼ������ SPIx �Ĵ���
SPI_GPIO_Configuration(SPIx); //�˿�����
SPI_Cmd(SPIx, ENABLE); //ʹ��SPIx
}
/*
*********************************************************************************************************
* �� �� ��: SPI_WriteByte
* ����˵��: д 1 �ֽ����ݵ� SPI ����
* �� ��: TxData д�����ߵ�����
* �� �� ֵ: ���ݷ���״̬:0 ���ݷ��ͳɹ�,-1 ���ݷ���ʧ��
*********************************************************************************************************
*/
int32_t SPI_WriteByte(SPI_TypeDef* SPIx, uint16_t TxData)
{
uint8_t retry=0;
while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) //���ָ���� SPI ��־λ�������:���ͻ���ձ�־λ
{
retry++;
if(retry>200)return -1;
	} 
SPI_I2S_SendData(SPIx, TxData); //ͨ������ SPIx ����һ������
retry=0;
while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET) //���ָ���� SPI ��־λ�������:���ܻ���ǿձ�־λ
{
retry++;
if(retry>200)return -1;
} 
return 0; //������ȷ����
}
/*
*********************************************************************************************************
* �� �� ��: SPI_ReadByte
* ����˵��: �� SPI ���߶�ȡ 1 �ֽ�����
* �� ��: p_RxData ���ݴ����ַ
* �� �� ֵ: ���ݶ�ȡ״̬:0 ���ݷ��ͳɹ�,-1 ���ݷ���ʧ��
*********************************************************************************************************
*/
int32_t SPI_ReadByte(SPI_TypeDef* SPIx, uint16_t *p_RxData)
{
uint8_t retry=0;
//while((SPIx->SR&SPI_I2S_FLAG_TXE)==0) //�ȴ���������
while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) //���ָ���� SPI ��־λ�������:���ͻ���ձ�־λ
{
retry++;
if(retry>200)return -1;
} 
SPI_I2S_SendData(SPIx, 0xFF); //ͨ������ SPIx ����һ�� dumy ����
retry=0;
while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET) //���ָ���� SPI ��־λ�������:���ܻ���ǿձ�־λ
{
retry++;
if(retry>200)return -1;
}
*p_RxData = SPI_I2S_ReceiveData(SPIx); 
return 0; //������ȷ����
}
/*
*********************************************************************************************************
* �� �� ��: SPI_WriteNBytes
* ����˵��: �� SPI ����д���ֽ�����
* �� ��: p_TxData �������ݻ������׵�ַ
* sendDataNum ���������ֽ���
* �� �� ֵ: ���ݷ���״̬:0 ���ݷ��ͳɹ�,-1 ���ݷ���ʧ��
*********************************************************************************************************
*/
int32_t SPI_WriteNBytes(SPI_TypeDef* SPIx, uint8_t *p_TxData,uint32_t sendDataNum)
{
uint16_t retry=0;
while(sendDataNum--)
{
while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) //���ָ���� SPI ��־λ�������:���ͻ���ձ�־λ
{
retry++;
if(retry>20000)return -1;
}
SPI_I2S_SendData(SPIx, *p_TxData++); //ͨ������ SPIx ����һ������
retry=0; 
while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET) //���ָ���� SPI ��־λ�������:���ܻ���ǿձ�־λ
{
retry++;
if(retry>20000)return -1;
}
}
return 0;//������ȷ����
}
/*
*********************************************************************************************************
* �� �� ��: SPI_ReadNBytes
* ����˵��: �� SPI ���߶�ȡ���ֽ�����
* �� ��: p_RxData ���ݴ����ַ
* readDataNum ��ȡ�����ֽ���
* �� �� ֵ: ���ݶ�ȡ״̬:0 ���ݷ��ͳɹ�,-1 ���ݷ���ʧ��
*********************************************************************************************************
*/
int32_t SPI_ReadNBytes(SPI_TypeDef* SPIx, uint8_t *p_RxData,uint32_t readDataNum)
{
uint16_t retry=0;
while(readDataNum--)
{
SPI_I2S_SendData(SPIx, 0xFF); //ͨ������ SPIx ����һ�� dumy ����
while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) //���ָ���� SPI ��־λ�������:���ͻ���ձ�־λ
{
retry++;
if(retry>20000)return -1;
}
retry = 0;
while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET) //���ָ���� SPI ��־λ�������:���ܻ���ǿձ�־λ
{
retry++;
if(retry>20000)return -1;
}
*p_RxData++ = SPI_I2S_ReceiveData(SPIx);
}
return 0;//������ȷ����
}
/*
*********************************************************************************************************
* �� �� ��: SPIx_ReadWriteByte
* ����˵��: �� SPI ���߶�дһ���ֽ�
* �� ��: SPIx ��Ҫʹ�õ� SPI
* TxData:Ҫд����ֽ�
* �� �� ֵ: ��ȡ�����ֽ�
*********************************************************************************************************
*/
uint8_t SPIx_ReadWriteByte(SPI_TypeDef* SPIx,uint8_t TxData)
{
u8 retry=0;
while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) //���ָ���� SPI ��־λ�������:���ͻ���ձ�־λ
{
retry++;
if(retry>200)return 0;
}
SPI_I2S_SendData(SPIx, TxData); //ͨ������ SPIx ����һ������
retry=0;
while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET) //���ָ���� SPI ��־λ�������:���ܻ���ǿձ�־λ
{
retry++;
if(retry>200)return 0;
} 
return SPI_I2S_ReceiveData(SPIx); //����ͨ�� SPIx ������յ����� 
}
/*
*********************************************************************************************************
* �� �� ��: SPI1_ReadWriteByte
* ����˵��: �� SPI ���߶�дһ���ֽ�
* �� ��: TxData:Ҫд����ֽ�
* �� �� ֵ: ��ȡ�����ֽ�
*********************************************************************************************************
*/
uint8_t SPI1_ReadWriteByte(uint8_t TxData)
{
uint8_t temp;
temp = SPIx_ReadWriteByte(SPI1,TxData);
return temp;
}
/*
*********************************************************************************************************
* �� �� ��: SPI2_ReadWriteByte
* ����˵��: �� SPI ���߶�дһ���ֽ�
* �� ��: TxData:Ҫд����ֽ�
* �� �� ֵ: ��ȡ�����ֽ�
*********************************************************************************************************
*/
uint8_t SPI2_ReadWriteByte(uint8_t TxData)
{
uint8_t temp;
temp = SPIx_ReadWriteByte(SPI2,TxData);
return temp;
}
/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
