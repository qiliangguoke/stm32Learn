#include "bsp.h"

float Tem_Value = 0.0; //�¶�ֵ
float RH_Value = 0.0; //ʪ��ֵ

void SHT3X_WriteCMD(uint16_t cmd)
{
	IIC_Start();
	IIC_Send_Byte(i2cAddWrite_8bit);//����д��ַ
	IIC_Wait_Ack();//�ȴ� ack
	IIC_Send_Byte(cmd>>8);//�������� �� 8 λ
	IIC_Wait_Ack();//�ȴ� ack
	IIC_Send_Byte(cmd);//�������� �� 8 λ
	IIC_Wait_Ack();//�ȴ� ack
	IIC_Stop();
	delay_ms(10);
}

void SHT3X_SetPeriodicMeasurement(void)
{
	SHT3X_WriteCMD(CMD_MEAS_PERI_2_H);//�������ԣ�ÿ�����������
}

void SHX3X_ReadResults(uint16_t cmd, uint8_t *p)
{
	u8 i = 0;
	u8 ack = 0;
	IIC_Start();
	IIC_Send_Byte(i2cAddWrite_8bit);//����д��ַ
	IIC_Wait_Ack();//�ȴ� ack
	IIC_Send_Byte(cmd>>8);//�������� �� 8 λ
	IIC_Wait_Ack();
	IIC_Send_Byte(cmd);//�������� �� 8 λ
	IIC_Wait_Ack();
	IIC_Stop();
	delay_ms(100);
	IIC_Start();
	IIC_Send_Byte(i2cAddRead_8bit);//���Ͷ���ַ
	IIC_Wait_Ack();
	for(i=0;i<6;i++)
	{
		if(i<5)
		{
			ack = 1;
		}
		else
		{
			ack = 0;//���һ������ nack
		}
		p[i] = IIC_Read_Byte(ack);
	}
	IIC_Stop();
	delay_ms(100);
}

void bsp_InitSht3x(void)
{
 delay_ms(100); //���������ʱ
 SHT3X_SetPeriodicMeasurement();//���� SHT3X �����ڶ�ȡ��ʽ
 delay_ms(100); //���������ʱ
}

uint8_t SHT3X_GetValue(void)
{
	uint8_t p[6];
	float cTemp,humidity;//���϶Ⱥ�ʪ��
	SHX3X_ReadResults(CMD_MEAS_CLOCKSTR_H,p);
	cTemp = ((((p[0] * 256.0) + p[1]) * 175) / 65535.0) - 45;//���϶� // T = -45 + 175 * rawValue / (2^16-1)
	humidity = ((((p[3] * 256.0) + p[4]) * 100) / 65535.0);//ʪ�� // RH = rawValue / (2^16-1) * 10
	Tem_Value = cTemp ;
	RH_Value = humidity ;
	if(Tem_Value > 129)//����������ʼ�� ���ִ���ʱ���¶�Ϊ 130 �ȣ�ʪ��Ϊ 100
	{
		return 1;
	}
	return 0;
}