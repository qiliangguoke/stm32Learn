#include "bsp.h"

void AT24CXX_Init(void)
{
bsp_InitI2C();
}

uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)
{ 
	uint8_t temp=0; 
	IIC_Start(); 
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0); //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//���͸ߵ�ַ
		IIC_Wait_Ack();
	}
	else 
		IIC_Send_Byte(0XA0+((ReadAddr/256)<<1)); //����������ַ 0XA0,д����
	
	IIC_Wait_Ack(); 
	IIC_Send_Byte(ReadAddr%256); //���͵͵�ַ
	IIC_Wait_Ack(); 
	IIC_Start(); 
	IIC_Send_Byte(0XA1); //�������ģʽ 
	IIC_Wait_Ack();
	temp=IIC_Read_Byte(0); 
	IIC_Stop();//����һ��ֹͣ���� 
	
	return temp;
}
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{ 
	IIC_Start(); 
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0); //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//���͸ߵ�ַ
	}
	else
	{
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1)); //����������ַ 0XA0,д����
	}
	IIC_Wait_Ack(); 
	IIC_Send_Byte(WriteAddr%256); //���͵͵�ַ
	IIC_Wait_Ack(); 
	IIC_Send_Byte(DataToWrite); //�����ֽ� 
	IIC_Wait_Ack(); 
	IIC_Stop();//����һ��ֹͣ����
	delay_ms(10);
}

void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len)
{ 
	uint8_t t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	} 
}

uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len)
{ 
	uint8_t t;
	uint32_t temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 
	}
	return temp; 
}
uint8_t AT24CXX_Check(void)
{
	uint8_t temp;
	temp=AT24CXX_ReadOneByte(255);//����ÿ�ο�����д AT24CXX 
	if(temp==0X55)return 0; 
	else//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(255,0X55);
		temp=AT24CXX_ReadOneByte(255); 
		if(temp==0X55)
			return 0;
	}
	return 1; 
}
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);
		NumToRead--;
	}
}
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}