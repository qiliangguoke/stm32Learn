#include "bsp.h"

float Tem_Value = 0.0; //温度值
float RH_Value = 0.0; //湿度值

void SHT3X_WriteCMD(uint16_t cmd)
{
	IIC_Start();
	IIC_Send_Byte(i2cAddWrite_8bit);//发送写地址
	IIC_Wait_Ack();//等待 ack
	IIC_Send_Byte(cmd>>8);//发送命令 高 8 位
	IIC_Wait_Ack();//等待 ack
	IIC_Send_Byte(cmd);//发送命令 低 8 位
	IIC_Wait_Ack();//等待 ack
	IIC_Stop();
	delay_ms(10);
}

void SHT3X_SetPeriodicMeasurement(void)
{
	SHT3X_WriteCMD(CMD_MEAS_PERI_2_H);//高重现性，每秒读两次数据
}

void SHX3X_ReadResults(uint16_t cmd, uint8_t *p)
{
	u8 i = 0;
	u8 ack = 0;
	IIC_Start();
	IIC_Send_Byte(i2cAddWrite_8bit);//发送写地址
	IIC_Wait_Ack();//等待 ack
	IIC_Send_Byte(cmd>>8);//发送命令 高 8 位
	IIC_Wait_Ack();
	IIC_Send_Byte(cmd);//发送命令 低 8 位
	IIC_Wait_Ack();
	IIC_Stop();
	delay_ms(100);
	IIC_Start();
	IIC_Send_Byte(i2cAddRead_8bit);//发送读地址
	IIC_Wait_Ack();
	for(i=0;i<6;i++)
	{
		if(i<5)
		{
			ack = 1;
		}
		else
		{
			ack = 0;//最后一个发送 nack
		}
		p[i] = IIC_Read_Byte(ack);
	}
	IIC_Stop();
	delay_ms(100);
}

void bsp_InitSht3x(void)
{
 delay_ms(100); //必须加入延时
 SHT3X_SetPeriodicMeasurement();//设置 SHT3X 的周期读取方式
 delay_ms(100); //必须加入延时
}

uint8_t SHT3X_GetValue(void)
{
	uint8_t p[6];
	float cTemp,humidity;//摄氏度和湿度
	SHX3X_ReadResults(CMD_MEAS_CLOCKSTR_H,p);
	cTemp = ((((p[0] * 256.0) + p[1]) * 175) / 65535.0) - 45;//摄氏度 // T = -45 + 175 * rawValue / (2^16-1)
	humidity = ((((p[3] * 256.0) + p[4]) * 100) / 65535.0);//湿度 // RH = rawValue / (2^16-1) * 10
	Tem_Value = cTemp ;
	RH_Value = humidity ;
	if(Tem_Value > 129)//错误发生，初始化 发现错误时，温度为 130 度，湿度为 100
	{
		return 1;
	}
	return 0;
}