#include "bsp.h"

static const uint8_t CO2_READ_CMD[9]={0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};//��ȡ CO2 ����
uint8_t CO2_TEMP_BUF[CO2_TEMP_BUF_LEN]={0x00};//CO2 ����


void CO2_TEMP_BUF_Clear(void)
{
	uint8_t i=0;
	for(i=0;i<CO2_TEMP_BUF_LEN;i++)
	{
		CO2_TEMP_BUF[i]=0;
	}	
}

uint8_t getCheckSum(uint8_t *packet)
{
	uint8_t i,checksum=0;
	for(i=1;i<8;i++)
	{
		checksum += packet[i];
	}
	checksum = 0xff - checksum;
	checksum += 1;
	return checksum;
}
uint16_t CO2_READ(void)
{
	
	uint16_t co2_value = 0;
	uint8_t len3 = 0;
	UART4_Send_Data( (uint8_t*)CO2_READ_CMD,9);//��ȡ CO2 ��ֵ
	delay_ms(20);
	UART4_Receive_Data(CO2_TEMP_BUF,&len3);
	if( ( len3 == 9 ) && ( getCheckSum( CO2_TEMP_BUF ) == CO2_TEMP_BUF[8] ) )
	{
		printf("dddd");
		co2_value = CO2_TEMP_BUF[2];
		co2_value = ( co2_value << 8 ) + CO2_TEMP_BUF[3];
		//printf("CO2 value is %d \r\n",co2_value);
		len3 = 0;
		CO2_TEMP_BUF_Clear();//��� buf
		return co2_value;//������ȷ��ֵ
	}
	else
	{
		//printf("len3 = %d\r\n",len3);
		co2_value = 65535;//���ش�����ֵ
		CO2_TEMP_BUF_Clear();//��� buf
		return co2_value;//�����ش�����ֵ
	}
}