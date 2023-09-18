#include "bsp.h"
/*
*********************************************************************************************************
* �� �� ��: bsp_InitRc522
* ����˵��: ��ʼ�� RC522 �� IO �ں� SPI ��������
* �� ��: ��
* �� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitRc522(void)
{
SPI_InitTypeDef SPI_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd( RCC_ALL_RC522, ENABLE ); //RC522 ʱ��ʹ��
GPIO_InitStructure.GPIO_Pin = RC522_CS_GPIO_PIN; // RC522_CS ����
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(RC522_CS_GPIO_PORT, &GPIO_InitStructure);
GPIO_InitStructure.GPIO_Pin = RC522_RST_GPIO_PIN; // RC522_RST ����
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(RC522_RST_GPIO_PORT, &GPIO_InitStructure);
RC522_CS = 1; //RC522 ��ѡ��
RC522_RST = 1; //RC522 ����λ
bsp_InitSPIx(RC522_SPIx); //��ʼ�� CLK,MISO,MOSI �����˿ں� SPI ʱ��
/* SPI ģʽ���� */
	// FLASH оƬ ֧�� SPI ģʽ 0���ݴ����� CPOL CPHA
SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
SPI_InitStructure.SPI_CRCPolynomial = 7;
SPI_Init(RC522_SPIx , &SPI_InitStructure);
/* ʹ�� SPI */
SPI_Cmd(RC522_SPIx , ENABLE);
}
/*
*********************************************************************************************************
* �� �� ��: SPI_RC522_SendByte
* ����˵��: �� SPI ����д��һ���ֽ�
* �� ��: byte:Ҫд����ֽ�
* �� �� ֵ: ���ؽ��յ�������
*********************************************************************************************************
*/
uint8_t SPI_RC522_SendByte(uint8_t byte)
{
 return SPIx_ReadWriteByte(RC522_SPIx,byte);
}
/*
*********************************************************************************************************
* �� �� ��: SPI_RC522_ReadByte
* ����˵��: �� SPI ���߶�ȡһ���ֽ�
* �� ��: ��
* �� �� ֵ: ��ȡ�����ֽ�
*********************************************************************************************************
*/
uint8_t SPI_RC522_ReadByte(void)
{
 return (SPI_RC522_SendByte(RC522_Dummy_Byte));
}
/*
*********************************************************************************************************
* �� �� ��: ReadRawRC
* ����˵��: �� RC522 �Ĵ���
* �� ��: Address:�Ĵ�����ַ
* �� �� ֵ: ������ֵ
*********************************************************************************************************
*/
uint8_t ReadRawRC(uint8_t Address)
{
uint8_t ucAddr;
uint8_t ucResult=0;
ucAddr = ( ( ( Address <<1 ) & 0x7E ) | 0x80 );
/*ѡ�� RC522: CS �� */
/* ͨѶ��ʼ��CS �� */
RC522_CS = 0;
SPI_RC522_SendByte( ucAddr );
ucResult = SPI_RC522_ReadByte();
/* ֹͣ�ź� RC522: CS �� */
/* ͨѶ��ʼ��CS �� */
RC522_CS = 1;
return ucResult;
}
/*
*********************************************************************************************************
* �� �� ��: ReadRawRC
* ����˵��: д RC522 �Ĵ���
* �� ��: uint8_t Address:�Ĵ�����ַ
* uint8_t value:д���ֵ
* �� �� ֵ: ��
*********************************************************************************************************
*/
void WriteRawRC(uint8_t Address, uint8_t value)
{ 
uint8_t ucAddr;
ucAddr = ( ( Address << 1 ) & 0x7E );
/*ѡ�� RC522: CS �� */
/* ͨѶ��ʼ��CS �� */
RC522_CS = 0;
SPI_RC522_SendByte( ucAddr );
SPI_RC522_SendByte( value );
/* ֹͣ�ź� RC522: CS �� */
/* ͨѶ��ʼ��CS �� */
RC522_CS = 1;
}
/*
*********************************************************************************************************
* �� �� ��: SetBitMask
* ����˵��: �� RC522 �Ĵ�����λ
* �� ��: uint8_t ucReg���Ĵ�����ַ
* uint8_t ucMask����λֵ
* �� �� ֵ: ��
*********************************************************************************************************
*/
void SetBitMask ( uint8_t ucReg, uint8_t ucMask ) 
{
 uint8_t ucTemp = 0;
 ucTemp = ReadRawRC ( ucReg );
 WriteRawRC ( ucReg, ucTemp | ucMask ); // set bit mask
}
/*
*********************************************************************************************************
* �� �� ��: ClearBitMask
* ����˵��: �� RC522 �Ĵ�����λ
* �� ��: uint8_t ucReg���Ĵ�����ַ
* uint8_t ucMask����λֵ
* �� �� ֵ: ��
*********************************************************************************************************
*/
void ClearBitMask ( uint8_t ucReg, uint8_t ucMask ) 
{
 uint8_t ucTemp = 0;
 ucTemp = ReadRawRC ( ucReg );
 WriteRawRC ( ucReg, ucTemp & ( ~ ucMask) ); // clear bit mask
}
/*
*********************************************************************************************************
* �� �� ��: PcdAntennaOn
* ����˵��: ��������
* �� ��: ��
* �� �� ֵ: ��
* ע �⣺ÿ��������ر����շ���֮��Ӧ������ 1ms �ļ��
*********************************************************************************************************
*/
void PcdAntennaOn ( void )
{
 uint8_t uc;
 uc = ReadRawRC ( TxControlReg );
 if ( ! ( uc & 0x03 ) )
{
SetBitMask( TxControlReg, 0x03 );
}
}
/*
*********************************************************************************************************
* �� �� ��: PcdAntennaOff
* ����˵��: �ر�����
* �� ��: ��
* �� �� ֵ: ��
* ע �⣺ÿ��������ر����շ���֮��Ӧ������ 1ms �ļ��
*********************************************************************************************************
*/
void PcdAntennaOff ( void )
{
ClearBitMask ( TxControlReg, 0x03 );
}
/*
*********************************************************************************************************
* �� �� ��: PcdReset
* ����˵��: ��λ RC522 
* �� ��: ��
* �� �� ֵ: ��
*********************************************************************************************************
*/
void PcdReset ( void )
{
/* ��λ RC522: RST �� */
RC522_RST = 1;
delay_us(10); //_NOP();
/* ȡ����λ RC522: RST �� */
RC522_RST = 0;
delay_us(10); //_NOP();
/* ��λ RC522: RST �� */
RC522_RST = 1;
delay_us(10); //_NOP();
WriteRawRC ( CommandReg, 0x0f );
while ( ReadRawRC ( CommandReg ) & 0x10 );
delay_us(10); //_NOP();
WriteRawRC ( ModeReg, 0x3D ); //���巢�ͺͽ��ճ���ģʽ �� Mifare ��ͨѶ��CRC ��ʼֵ 0x6363
WriteRawRC ( TReloadRegL, 30 ); //16 λ��ʱ����λ 
WriteRawRC ( TReloadRegH, 0 ); //16 λ��ʱ����λ
WriteRawRC ( TModeReg, 0x8D ); //�����ڲ���ʱ��������
WriteRawRC ( TPrescalerReg, 0x3E ); //���ö�ʱ����Ƶϵ��
WriteRawRC ( TxAutoReg, 0x40 ); //���Ʒ����ź�Ϊ 100%ASK
	}
/*
*********************************************************************************************************
* �� �� ��: PcdComMF522
* ����˵��: ͨ�� RC522 �� ISO14443 ��ͨѶ
* �� ��: ucCommand��RC522 ������
* pInData��ͨ�� RC522 ���͵���Ƭ������
* ucInLenByte���������ݵ��ֽڳ���
* pOutData�����յ��Ŀ�Ƭ��������
* pOutLenBit���������ݵ�λ����
* �� �� ֵ: ״ֵ̬= MI_OK���ɹ�
*********************************************************************************************************
*/
char PcdComMF522 ( uint8_t ucCommand, uint8_t * pInData, uint8_t ucInLenByte, uint8_t * pOutData, uint32_t * pOutLenBit )
{
 char cStatus = MI_ERR;
 uint8_t ucIrqEn = 0x00;
 uint8_t ucWaitFor = 0x00;
 uint8_t ucLastBits;
 uint8_t ucN;
 uint32_t ul;
switch ( ucCommand )
{
case PCD_AUTHENT: //Mifare ��֤
{
ucIrqEn = 0x12; //��������ж����� ErrIEn ��������ж� IdleIEn
ucWaitFor = 0x10; //��֤Ѱ���ȴ�ʱ�� ��ѯ�����жϱ�־λ
}break;
case PCD_TRANSCEIVE: //���շ��� ���ͽ���
{
ucIrqEn = 0x77; //���� TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
ucWaitFor = 0x30; //Ѱ���ȴ�ʱ�� ��ѯ�����жϱ�־λ�� �����жϱ�־λ
}break;
default:break;
}
 
 WriteRawRC ( ComIEnReg, ucIrqEn | 0x80 ); //IRqInv ��λ�ܽ� IRQ �� Status1Reg �� IRq λ��ֵ�෴
 ClearBitMask ( ComIrqReg, 0x80 ); //Set1 ��λ����ʱ��CommIRqReg ������λ����
 WriteRawRC ( CommandReg, PCD_IDLE ); //д��������
 SetBitMask ( FIFOLevelReg, 0x80 ); //��λ FlushBuffer ����ڲ� FIFO �Ķ���дָ���Լ� ErrReg ��BufferOvfl ��־λ�����
 
 for ( ul = 0; ul < ucInLenByte; ul ++ )
{
WriteRawRC ( FIFODataReg, pInData [ ul ] ); //д���ݽ� FIFOdata
}
 WriteRawRC ( CommandReg, ucCommand ); //д����
 
 
 if ( ucCommand == PCD_TRANSCEIVE )
{
SetBitMask(BitFramingReg,0x80); //StartSend ��λ�������ݷ��� ��λ���շ�����ʹ��ʱ����Ч
}
 
 ul = 1000;//����ʱ��Ƶ�ʵ��������� M1 �����ȴ�ʱ�� 25ms
 do //��֤ ��Ѱ���ȴ�ʱ��
 {
ucN = ReadRawRC ( ComIrqReg ); //��ѯ�¼��ж�
ul --;
 } while ( ( ul != 0 ) && ( ! ( ucN & 0x01 ) ) && ( ! ( ucN & ucWaitFor ) ) ); //�˳����� i=0,��ʱ���жϣ���д��������
 ClearBitMask ( BitFramingReg, 0x80 ); //�������� StartSend λ
  if ( ul != 0 )
 {
if ( ! ( ReadRawRC ( ErrorReg ) & 0x1B ) ) // �� �� �� �� ־ �� �� �� BufferOfI CollErr ParityErr ProtocolErr
{
cStatus = MI_OK;
if ( ucN & ucIrqEn & 0x01 ) //�Ƿ�����ʱ���ж�
{
cStatus = MI_NOTAGERR;
}
if ( ucCommand == PCD_TRANSCEIVE )
{
ucN = ReadRawRC ( FIFOLevelReg ); //�� FIFO �б�����ֽ���
ucLastBits = ReadRawRC ( ControlReg ) & 0x07; //�����յ����ֽڵ���Чλ��
if ( ucLastBits )
{
* pOutLenBit = ( ucN - 1 ) * 8 + ucLastBits; //N ���ֽ�����ȥ 1�����һ���ֽڣ�+���һλ��λ�� ��ȡ����������λ��
}
else
{
* pOutLenBit = ucN * 8; //�����յ����ֽ������ֽ���Ч
}
if ( ucN == 0 )
{
ucN = 1; 
}
if ( ucN > MAXRLEN )
{
ucN = MAXRLEN; 
}
for ( ul = 0; ul < ucN; ul ++ )
{
pOutData [ ul ] = ReadRawRC ( FIFODataReg ); 
}
}
}
else
{
cStatus = MI_ERR; 
}
 
 }
 
SetBitMask ( ControlReg, 0x80 ); // stop timer now
WriteRawRC ( CommandReg, PCD_IDLE ); 
return cStatus;
}
/*
*********************************************************************************************************
* �� �� ��: M500PcdConfigISOType
* ����˵��: ���� RC522 �Ĺ�����ʽ
* �� ��: ucType��������ʽ
* �� �� ֵ: ��
*********************************************************************************************************
*/
void M500PcdConfigISOType ( uint8_t ucType )
{
if ( ucType == 'A') //ISO14443_A
{
ClearBitMask ( Status2Reg, 0x08 );
	WriteRawRC ( ModeReg, 0x3D ); //3F
WriteRawRC ( RxSelReg, 0x86 ); //84
WriteRawRC( RFCfgReg, 0x7F ); //4F
WriteRawRC( TReloadRegL, 30 );//tmoLength);// TReloadVal = 'h6a =tmoLength(dec) 
WriteRawRC ( TReloadRegH, 0 );
WriteRawRC ( TModeReg, 0x8D );
WriteRawRC ( TPrescalerReg, 0x3E );
delay_us ( 2 );
PcdAntennaOn ();//������
}
}
/*
*********************************************************************************************************
* �� �� ��: PcdRequest
* ����˵��: Ѱ��
* �� ��: ucReq_code��Ѱ����ʽ
* = 0x52��Ѱ��Ӧ�������з��� 14443A ��׼�Ŀ�
* = 0x26��Ѱδ��������״̬�Ŀ�
* pTagType����Ƭ���ʹ���
* = 0x4400��Mifare_UltraLight
* = 0x0400��Mifare_One(S50)
* = 0x0200��Mifare_One(S70)
* = 0x0800��Mifare_Pro(X))
* = 0x4403��Mifare_DESFire
* �� �� ֵ: ״ֵ̬= MI_OK���ɹ�
*********************************************************************************************************
*/
char PcdRequest ( uint8_t ucReq_code, uint8_t * pTagType )
{
char cStatus; 
uint8_t ucComMF522Buf [ MAXRLEN ]; 
uint32_t ulLen;
ClearBitMask ( Status2Reg, 0x08 ); //����ָʾ MIFARECyptol ��Ԫ��ͨ�Լ����п�������ͨ�ű����ܵ����
WriteRawRC ( BitFramingReg, 0x07 ); // ���͵����һ���ֽڵ� ��λ
SetBitMask ( TxControlReg, 0x03 ); //TX1,TX2 �ܽŵ�����źŴ��ݾ����͵��Ƶ� 13.56 �������ز��ź�
ucComMF522Buf [ 0 ] = ucReq_code; //���� ��Ƭ������
cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 1, ucComMF522Buf, & ulLen ); //Ѱ�� 
if ( ( cStatus == MI_OK ) && ( ulLen == 0x10 ) ) //Ѱ���ɹ����ؿ�����
{ 
*pTagType = ucComMF522Buf [ 0 ];
*( pTagType + 1 ) = ucComMF522Buf [ 1 ];
}
else
{
cStatus = MI_ERR;
}
return cStatus;
}
/*
*********************************************************************************************************
* �� �� ��: PcdAnticoll
* ����˵��: ����ײ
* �� ��: pSnr����Ƭ���кţ�4 �ֽ�
* �� �� ֵ: ״ֵ̬= MI_OK���ɹ�
*********************************************************************************************************
*/
char PcdAnticoll ( uint8_t * pSnr )
{
char cStatus;
uint8_t uc, ucSnr_check = 0;
uint8_t ucComMF522Buf [ MAXRLEN ]; 
uint32_t ulLen;
ClearBitMask ( Status2Reg, 0x08 ); //�� MFCryptol On λ ֻ�гɹ�ִ�� MFAuthent ����󣬸�λ������λ
WriteRawRC ( BitFramingReg, 0x00); //����Ĵ��� ֹͣ�շ�
ClearBitMask ( CollReg, 0x80 ); //�� ValuesAfterColl ���н��յ�λ�ڳ�ͻ�����
ucComMF522Buf [ 0 ] = 0x93; //��Ƭ����ͻ����
ucComMF522Buf [ 1 ] = 0x20;
cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 2, ucComMF522Buf, & ulLen);//�뿨Ƭͨ��
if ( cStatus == MI_OK) //ͨ�ųɹ�
{
for ( uc = 0; uc < 4; uc ++ )
{
* ( pSnr + uc ) = ucComMF522Buf [ uc ]; //���� UID
ucSnr_check ^= ucComMF522Buf [ uc ];
}
if ( ucSnr_check != ucComMF522Buf [ uc ] )
{
cStatus = MI_ERR; 
}
}
SetBitMask ( CollReg, 0x80 );
return cStatus;
}
/*
*********************************************************************************************************
* �� �� ��: CalulateCRC
* ����˵��: �� RC522 ���� CRC16 
* �� ��: 
* pIndata������ CRC16 ������
* ucLen������ CRC16 �������ֽڳ���
* pOutData����ż�������ŵ��׵�ַ
* �� �� ֵ: ��
*********************************************************************************************************
*/
void CalulateCRC ( uint8_t * pIndata, uint8_t ucLen, uint8_t * pOutData )
{
 uint8_t uc, ucN;
 ClearBitMask(DivIrqReg,0x04);
 WriteRawRC(CommandReg,PCD_IDLE);
 SetBitMask(FIFOLevelReg,0x80);
 for ( uc = 0; uc < ucLen; uc ++)
{
WriteRawRC ( FIFODataReg, * ( pIndata + uc ) );
}
 WriteRawRC ( CommandReg, PCD_CALCCRC );
 uc = 0xFF;
 do 
 {
 ucN = ReadRawRC ( DivIrqReg );
 uc --;
 } while ( ( uc != 0 ) && ! ( ucN & 0x04 ) );
  pOutData [ 0 ] = ReadRawRC ( CRCResultRegL );
 pOutData [ 1 ] = ReadRawRC ( CRCResultRegM );
}
/*
*********************************************************************************************************
* �� �� ��: PcdSelect
* ����˵��: ѡ����Ƭ
* �� ��: pSnr����Ƭ���кţ�4 �ֽ�
* �� �� ֵ: ״ֵ̬= MI_OK���ɹ�
*********************************************************************************************************
*/
char PcdSelect ( uint8_t * pSnr )
{
char ucN;
uint8_t uc;
uint8_t ucComMF522Buf [ MAXRLEN ]; 
uint32_t ulLen;
ucComMF522Buf [ 0 ] = PICC_ANTICOLL1;
ucComMF522Buf [ 1 ] = 0x70;
ucComMF522Buf [ 6 ] = 0;
for ( uc = 0; uc < 4; uc ++ )
{
ucComMF522Buf [ uc + 2 ] = * ( pSnr + uc );
ucComMF522Buf [ 6 ] ^= * ( pSnr + uc );
}
CalulateCRC ( ucComMF522Buf, 7, & ucComMF522Buf [ 7 ] );
ClearBitMask ( Status2Reg, 0x08 );
ucN = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 9, ucComMF522Buf, & ulLen );
if ( ( ucN == MI_OK ) && ( ulLen == 0x18 ) )
{
ucN = MI_OK;
}
else
{
ucN = MI_ERR; 
}
return ucN;

}

/*
*********************************************************************************************************
* �� �� ��: PcdSelect
* ����˵��: ��֤��Ƭ����
* �� ��: 
* ucAuth_mode��������֤ģʽ
* = 0x60����֤ A ��Կ
* = 0x61����֤ B ��Կ
* ucAddr�����ַ
* pKey������
* pSnr����Ƭ���кţ�4 �ֽ�
* �� �� ֵ: ״ֵ̬= MI_OK���ɹ�
*********************************************************************************************************
*/
char PcdAuthState ( uint8_t ucAuth_mode, uint8_t ucAddr, uint8_t * pKey, uint8_t * pSnr )
{
 char cStatus;
uint8_t uc, ucComMF522Buf [ MAXRLEN ];
uint32_t ulLen;
 
 ucComMF522Buf [ 0 ] = ucAuth_mode;
 ucComMF522Buf [ 1 ] = ucAddr;
 for ( uc = 0; uc < 6; uc ++ )
{
	ucComMF522Buf [ uc + 2 ] = * ( pKey + uc );
} 
 for ( uc = 0; uc < 6; uc ++ )
{
ucComMF522Buf [ uc + 8 ] = * ( pSnr + uc );
}
 cStatus = PcdComMF522 ( PCD_AUTHENT, ucComMF522Buf, 12, ucComMF522Buf, & ulLen );
 if ( ( cStatus != MI_OK ) || ( ! ( ReadRawRC ( Status2Reg ) & 0x08 ) ) )
{
cStatus = MI_ERR;
}
 return cStatus;
}
/*
*********************************************************************************************************
* �� �� ��: PcdWrite
* ����˵��: д���ݵ� M1 ��һ��
* �� ��: 
* ucAddr�����ַ
* pData��д������ݣ�16 �ֽ�
* �� �� ֵ: ״ֵ̬= MI_OK���ɹ�
*********************************************************************************************************
*/
char PcdWrite ( uint8_t ucAddr, uint8_t * pData )
{
char cStatus;
uint8_t uc, ucComMF522Buf [ MAXRLEN ];
uint32_t ulLen;
ucComMF522Buf [ 0 ] = PICC_WRITE;
ucComMF522Buf [ 1 ] = ucAddr;
CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );
if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
{
cStatus = MI_ERR; 
}
if ( cStatus == MI_OK )
{
//memcpy(ucComMF522Buf, pData, 16);
for ( uc = 0; uc < 16; uc ++ )
{
ucComMF522Buf [ uc ] = * ( pData + uc ); 
}
CalulateCRC ( ucComMF522Buf, 16, & ucComMF522Buf [ 16 ] );
cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 18, ucComMF522Buf, & ulLen );
if ( ( cStatus != MI_OK ) || ( ulLen != 4 ) || ( ( ucComMF522Buf [ 0 ] & 0x0F ) != 0x0A ) )
{
	cStatus = MI_ERR;
}

} 
return cStatus;
}
/*
*********************************************************************************************************
* �� �� ��: PcdRead
* ����˵��: ��ȡ M1 ��һ������
* �� ��: 
* ucAddr�����ַ
* pData�����������ݣ�16 �ֽ�
* �� �� ֵ: ״ֵ̬= MI_OK���ɹ�
*********************************************************************************************************
*/
char PcdRead ( uint8_t ucAddr, uint8_t * pData )
{
char cStatus;
uint8_t uc, ucComMF522Buf [ MAXRLEN ]; 
uint32_t ulLen;
ucComMF522Buf [ 0 ] = PICC_READ;
ucComMF522Buf [ 1 ] = ucAddr;
CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );
if ( ( cStatus == MI_OK ) && ( ulLen == 0x90 ) )
{
for ( uc = 0; uc < 16; uc ++ )
* ( pData + uc ) = ucComMF522Buf [ uc ]; 
}
else
{
cStatus = MI_ERR; 
}
 
return cStatus;
}
/*
*********************************************************************************************************
* �� �� ��: PcdHalt
* ����˵��: ���Ƭ��������״̬
* �� ��: ��
* �� �� ֵ: ״ֵ̬= MI_OK���ɹ�
*********************************************************************************************************
*/
char PcdHalt( void )
{
uint8_t ucComMF522Buf [ MAXRLEN ]; 
uint32_t ulLen;
	ucComMF522Buf [ 0 ] = PICC_HALT;
	ucComMF522Buf [ 1 ] = 0;
	CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
	PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, & ulLen );
return MI_OK;
}
/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
