#ifndef __BSP_I2C_GPIO_H
#define __BSP_I2C_GPIO_H

///////////////////////////////////////
/* 头文件包含区 */

#include "sys.h"

///////////////////////////////////////
/* 宏定义区域 */

//移植修改区
//按照实际端口修改
//较前版本更加容易移植(注意，端口仅仅适用于非 JTAG/SWD 引脚，如果是 JTAG 引脚，需要打开 AFIO 时钟，并失能
//JTAG)
#define SCL_GPIO_PIN GPIO_Pin_7 //SCL 引脚号
#define SCL_PIN_ID 7 //SCL 引脚序号
#define SCL_GPIO_PORT GPIOG //SCL 端口号
#define SCL_GPIO_CLK RCC_APB2Periph_GPIOG //SCL 时钟
#define SCL_FUN_OUT PGout //SCL 输出端口配置函数
////
#define SDA_GPIO_PIN GPIO_Pin_8 //SDA 引脚号
#define SDA_PIN_ID 8 //SDA 引脚序号
#define SDA_GPIO_PORT GPIOG //SDA 端口号
#define SDA_GPIO_CLK RCC_APB2Periph_GPIOG //SDA 时钟
#define SDA_FUN_OUT PGout //SDA 输出端口配置函数
#define SDA_FUN_IN PGin //SDA 输入端口配置函数



//IO 方向设置
#if SDA_PIN_ID >= 8 //当端口号大于等于 8，是高 8 位的 用 CRH
	#define IIC_ROLBIT		( ( SDA_PIN_ID - 8 ) * 4 )
	#define IIC_CLR_VAL		( ~( (uint32_t)0XF << IIC_ROLBIT ))
	#define SDA_IN() {SDA_GPIO_PORT->CRH&=IIC_CLR_VAL;SDA_GPIO_PORT->CRH|=(u32)8<<IIC_ROLBIT;}
	#define SDA_OUT() {SDA_GPIO_PORT->CRH&=IIC_CLR_VAL;SDA_GPIO_PORT->CRH|=(u32)3<<IIC_ROLBIT;}
	
#else
	//当端口号小于 8，是低 8 位的 用 CRL
	#define IIC_ROLBIT ( SDA_PIN_ID * 4 )
	#define IIC_CLR_VAL ( ~( (uint32_t)0XF << IIC_ROLBIT ) ) 
	#define SDA_IN() {SDA_GPIO_PORT->CRL&=IIC_CLR_VAL;SDA_GPIO_PORT->CRL|=(u32)8<<IIC_ROLBIT;}
	#define SDA_OUT() {SDA_GPIO_PORT->CRL&=IIC_CLR_VAL;SDA_GPIO_PORT->CRL|=(u32)3<<IIC_ROLBIT;}
#endif

#define IIC_SCL SCL_FUN_OUT(SCL_PIN_ID) //SCL
#define IIC_SDA SDA_FUN_OUT(SDA_PIN_ID) //SDA
#define READ_SDA SDA_FUN_IN(SDA_PIN_ID) //输入 SDA
///////////////////////////////////////
/* 外部变量申明区 */

///////////////////////////////////////
/* 函数申明区 */

void bsp_InitI2C(void); //初始化 IIC 的 IO 口	
void IIC_Start(void); //发送 IIC 开始信号
void IIC_Stop(void); //发送 IIC 停止信号
void IIC_Send_Byte(uint8_t txd); //IIC 发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);
uint8_t IIC_Wait_Ack(void); //IIC 等待 ACK 信号
void IIC_Ack(void); //IIC 发送 ACK 信号
void IIC_NAck(void); //IIC 不发送 ACK 信号
///////////////////////////////////////
#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/