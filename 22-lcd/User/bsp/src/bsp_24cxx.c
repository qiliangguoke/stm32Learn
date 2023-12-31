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
		IIC_Send_Byte(0XA0); //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//发送高地址
		IIC_Wait_Ack();
	}
	else 
		IIC_Send_Byte(0XA0+((ReadAddr/256)<<1)); //发送器件地址 0XA0,写数据
	
	IIC_Wait_Ack(); 
	IIC_Send_Byte(ReadAddr%256); //发送低地址
	IIC_Wait_Ack(); 
	IIC_Start(); 
	IIC_Send_Byte(0XA1); //进入接收模式 
	IIC_Wait_Ack();
	temp=IIC_Read_Byte(0); 
	IIC_Stop();//产生一个停止条件 
	
	return temp;
}
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{ 
	IIC_Start(); 
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0); //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//发送高地址
	}
	else
	{
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1)); //发送器件地址 0XA0,写数据
	}
	IIC_Wait_Ack(); 
	IIC_Send_Byte(WriteAddr%256); //发送低地址
	IIC_Wait_Ack(); 
	IIC_Send_Byte(DataToWrite); //发送字节 
	IIC_Wait_Ack(); 
	IIC_Stop();//产生一个停止条件
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
	temp=AT24CXX_ReadOneByte(255);//避免每次开机都写 AT24CXX 
	if(temp==0X55)return 0; 
	else//排除第一次初始化的情况
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