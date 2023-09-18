#ifndef __BSP_I2C_GPIO_H
#define __BSP_I2C_GPIO_H

///////////////////////////////////////
/* ͷ�ļ������� */

#include "sys.h"

///////////////////////////////////////
/* �궨������ */

//��ֲ�޸���
//����ʵ�ʶ˿��޸�
//��ǰ�汾����������ֲ(ע�⣬�˿ڽ��������ڷ� JTAG/SWD ���ţ������ JTAG ���ţ���Ҫ�� AFIO ʱ�ӣ���ʧ��
//JTAG)
#define SCL_GPIO_PIN GPIO_Pin_7 //SCL ���ź�
#define SCL_PIN_ID 7 //SCL �������
#define SCL_GPIO_PORT GPIOG //SCL �˿ں�
#define SCL_GPIO_CLK RCC_APB2Periph_GPIOG //SCL ʱ��
#define SCL_FUN_OUT PGout //SCL ����˿����ú���
////
#define SDA_GPIO_PIN GPIO_Pin_8 //SDA ���ź�
#define SDA_PIN_ID 8 //SDA �������
#define SDA_GPIO_PORT GPIOG //SDA �˿ں�
#define SDA_GPIO_CLK RCC_APB2Periph_GPIOG //SDA ʱ��
#define SDA_FUN_OUT PGout //SDA ����˿����ú���
#define SDA_FUN_IN PGin //SDA ����˿����ú���



//IO ��������
#if SDA_PIN_ID >= 8 //���˿ںŴ��ڵ��� 8���Ǹ� 8 λ�� �� CRH
	#define IIC_ROLBIT		( ( SDA_PIN_ID - 8 ) * 4 )
	#define IIC_CLR_VAL		( ~( (uint32_t)0XF << IIC_ROLBIT ))
	#define SDA_IN() {SDA_GPIO_PORT->CRH&=IIC_CLR_VAL;SDA_GPIO_PORT->CRH|=(u32)8<<IIC_ROLBIT;}
	#define SDA_OUT() {SDA_GPIO_PORT->CRH&=IIC_CLR_VAL;SDA_GPIO_PORT->CRH|=(u32)3<<IIC_ROLBIT;}
	
#else
	//���˿ں�С�� 8���ǵ� 8 λ�� �� CRL
	#define IIC_ROLBIT ( SDA_PIN_ID * 4 )
	#define IIC_CLR_VAL ( ~( (uint32_t)0XF << IIC_ROLBIT ) ) 
	#define SDA_IN() {SDA_GPIO_PORT->CRL&=IIC_CLR_VAL;SDA_GPIO_PORT->CRL|=(u32)8<<IIC_ROLBIT;}
	#define SDA_OUT() {SDA_GPIO_PORT->CRL&=IIC_CLR_VAL;SDA_GPIO_PORT->CRL|=(u32)3<<IIC_ROLBIT;}
#endif

#define IIC_SCL SCL_FUN_OUT(SCL_PIN_ID) //SCL
#define IIC_SDA SDA_FUN_OUT(SDA_PIN_ID) //SDA
#define READ_SDA SDA_FUN_IN(SDA_PIN_ID) //���� SDA
///////////////////////////////////////
/* �ⲿ���������� */

///////////////////////////////////////
/* ���������� */

void bsp_InitI2C(void); //��ʼ�� IIC �� IO ��	
void IIC_Start(void); //���� IIC ��ʼ�ź�
void IIC_Stop(void); //���� IIC ֹͣ�ź�
void IIC_Send_Byte(uint8_t txd); //IIC ����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);
uint8_t IIC_Wait_Ack(void); //IIC �ȴ� ACK �ź�
void IIC_Ack(void); //IIC ���� ACK �ź�
void IIC_NAck(void); //IIC ������ ACK �ź�
///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/