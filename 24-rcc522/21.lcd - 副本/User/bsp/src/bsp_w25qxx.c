#include "bsp.h"
void W25QXX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd( RCC_ALL_W25QXX, ENABLE ); //W25QXX 时钟使能
GPIO_InitStructure.GPIO_Pin = W25QXX_CS_GPIO_PIN; // W25QXX_CS 推挽
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(W25QXX_CS_GPIO_PORT, &GPIO_InitStructure);
GPIO_SetBits(W25QXX_CS_GPIO_PORT,W25QXX_CS_GPIO_PIN);
W25QXX_CS = 1; //SPI FLASH 不选中
bsp_InitSPIx(W25QXX_SPIx); //初始化 SPI
SPIx_SetSpeed(W25QXX_SPIx,SPI_BaudRatePrescaler_2); //设置为 18M 时钟,高速模式
SPIx_SetCPOL_CPHA(W25QXX_SPIx,SPI_CPOL_High,SPI_CPHA_2Edge);//串行同步时钟的空闲状态为高电平
//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
}

/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
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
* 函 数 名: W25QXX_ReadSR
* 功能说明: 读取 W25QXX 的状态寄存器
* 形 参: 无
* 返 回 值: 无
* 备 注：
*
* BIT7 6 5 4 3 2 1 0
* SPR RV TB BP2 BP1 BP0 WEL BUSY
* SPR:默认 0,状态寄存器保护位,配合 WP 使用
* TB,BP2,BP1,BP0:FLASH 区域写保护设置
* WEL:写使能锁定
* BUSY:忙标记位(1,忙;0,空闲)
* 默认:0x00
*********************************************************************************************************
*/
uint8_t W25QXX_ReadSR(void) 
{ 
uint8_t byte = 0;
W25QXX_CS = 0; //使能器件 
W25QXX_SPIx_ReadWriteByte(W25X_ReadStatusReg); //发送读取状态寄存器命令 
byte = W25QXX_SPIx_ReadWriteByte(Dummy_Byte); //读取一个字节 
W25QXX_CS = 1; //取消片选 
return byte; 
} 
/*
*********************************************************************************************************
* 函 数 名: W25QXX_Write_SR
* 功能说明: 写 W25QXX 状态寄存器
* 形 参: sr 需要写入的寄存器值
* 返 回 值: 无
* 备 注：只有 SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
*********************************************************************************************************
*/
void W25QXX_Write_SR(uint8_t sr) 
{
	W25QXX_CS = 0; //使能器件 
W25QXX_SPIx_ReadWriteByte(W25X_WriteStatusReg); //发送写取状态寄存器命令 
W25QXX_SPIx_ReadWriteByte(sr); //写入一个字节 
W25QXX_CS = 1; //取消片选 
} 
/*
*********************************************************************************************************
* 函 数 名: W25QXX_Write_Enable
* 功能说明: W25QXX 写使能,将 WEL 置位
* 形 参: 无
* 返 回 值: 无
*********************************************************************************************************
*/
void W25QXX_Write_Enable(void) 
{
W25QXX_CS = 0; //使能器件 
 W25QXX_SPIx_ReadWriteByte(W25X_WriteEnable); //发送写使能 
W25QXX_CS = 1; //取消片选 
} 
 
/*
*********************************************************************************************************
* 函 数 名: W25QXX_Write_Disable
* 功能说明: W25QXX 写禁止,将 WEL 清零
* 形 参: 无
* 返 回 值: 无
*********************************************************************************************************
*/
void W25QXX_Write_Disable(void) 
{ 
W25QXX_CS = 0; //使能器件 
 W25QXX_SPIx_ReadWriteByte(W25X_WriteDisable); //发送写禁止指令 
W25QXX_CS = 1; //取消片选 
} 
/*
*********************************************************************************************************
* 函 数 名: W25QXX_ReadID
* 功能说明: 读取芯片 ID
* 形 参: 无
* 返 回 值: 如下
* 0XEF13,表示芯片型号为 W25Q80 
* 0XEF14,表示芯片型号为 W25Q16 
* 0XEF15,表示芯片型号为 W25Q32 
* 0XEF16,表示芯片型号为 W25Q64 
* 0XEF17,表示芯片型号为 W25Q128 
*********************************************************************************************************
*/
uint16_t W25QXX_ReadID(void)
{
uint16_t Temp = 0;
W25QXX_CS = 0; 
W25QXX_SPIx_ReadWriteByte(W25X_ManufactDeviceID); //发送读取 ID 命令
W25QXX_SPIx_ReadWriteByte(0x00); //发送 24bits 地址 0x000000，即 3 个字节 0x00
W25QXX_SPIx_ReadWriteByte(0x00); 
W25QXX_SPIx_ReadWriteByte(0x00); 
Temp |= W25QXX_SPIx_ReadWriteByte(Dummy_Byte)<<8; 
Temp |= W25QXX_SPIx_ReadWriteByte(Dummy_Byte);
W25QXX_CS = 1;
return Temp;
} 
/*
*********************************************************************************************************
* 函 数 名: W25QXX_Write_Disable
* 功能说明: 读取 SPI FLASH,在指定地址开始读取指定长度的数据
* 形 参: pBuffer:数据存储区
* ReadAddr:开始读取的地址(24bit)
* NumByteToRead:要读取的字节数(最大 65535)
* 返 回 值: 无
*********************************************************************************************************
*/
void W25QXX_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead) 
{ 
uint16_t i;
W25QXX_CS = 0; //使能器件 
 W25QXX_SPIx_ReadWriteByte(W25X_ReadData); //发送读取命令 
 W25QXX_SPIx_ReadWriteByte((uint8_t)((ReadAddr)>>16)); //发送 24bit 地址 
 W25QXX_SPIx_ReadWriteByte((uint8_t)((ReadAddr)>>8)); 
 W25QXX_SPIx_ReadWriteByte((uint8_t)ReadAddr); 
 for(i=0;i<NumByteToRead;i++)
{ 
 pBuffer[i]=W25QXX_SPIx_ReadWriteByte(0XFF); //循环读数 
 }
W25QXX_CS = 1; 
} 
/*
*********************************************************************************************************
* 函 数 名: W25QXX_Write_Disable
* 功能说明: SPI 在一页(0~65535)内写入少于 256 个字节的数据 在指定地址开始写入最大 256 字节的数据
* 形 参: pBuffer:数据存储区
* WriteAddr:开始写入的地址(24bit)
* NumByteToWrite:要写入的字节数(最大 256),该数不应该超过该页的剩余字节数!!!
* 返 回 值: 无
*********************************************************************************************************
*/
void W25QXX_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{
uint16_t i;
 W25QXX_Write_Enable(); //SET WEL 
W25QXX_CS = 0; //使能器件 
 W25QXX_SPIx_ReadWriteByte(W25X_PageProgram); //发送写页命令 
 W25QXX_SPIx_ReadWriteByte((uint8_t)((WriteAddr)>>16)); //发送 24bit 地址 
 W25QXX_SPIx_ReadWriteByte((uint8_t)((WriteAddr)>>8)); 
 W25QXX_SPIx_ReadWriteByte((uint8_t)WriteAddr); 
 for(i=0;i<NumByteToWrite;i++)
{
W25QXX_SPIx_ReadWriteByte(pBuffer[i]);//循环写数
}
W25QXX_CS = 1; //取消片选
W25QXX_Wait_Busy(); //等待写入结束
}
/*
*********************************************************************************************************
* 函 数 名: W25QXX_Write_NoCheck
* 功能说明: 无检验写 SPI FLASH
* 形 参: pBuffer:数据存储区
* WriteAddr:开始写入的地址(24bit)
* NumByteToWrite:要写入的字节数(最大 65535) 
* 返 回 值: 无
* 注 意:
* 必须确保所写的地址范围内的数据全部为 0XFF,否则在非 0XFF 处写入的数据将失败!
* 具有自动换页功能
* 在指定地址开始写入指定长度的数据,但是要确保地址不越界!
*********************************************************************************************************
*/
void W25QXX_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite) 
{ 
uint16_t pageremain;
pageremain = 256 - WriteAddr%256; //单页剩余的字节数 
if(NumByteToWrite<=pageremain)
{
pageremain=NumByteToWrite;//不大于 256 个字节
}
while(1)
{ 
W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
if(NumByteToWrite == pageremain)
{
break;//写入结束了
}
else //NumByteToWrite>pageremain
{
	pBuffer+=pageremain;
WriteAddr+=pageremain;
NumByteToWrite-=pageremain; //减去已经写入了的字节数
if(NumByteToWrite>256)
{
pageremain=256; //一次可以写入 256 个字节
}
else 
{
pageremain=NumByteToWrite; //不够 256 个字节了
}
}
}; 
} 
/*
*********************************************************************************************************
* 函 数 名: W25QXX_Write
* 功能说明: 写 SPI FLASH,在指定地址开始写入指定长度的数据
* 形 参: pBuffer:数据存储区
* WriteAddr:开始写入的地址(24bit)
* NumByteToWrite:要写入的字节数(最大 65535) 
* 返 回 值: 无
* 注 意: 该函数带擦除操作!
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
secpos = WriteAddr/4096;//扇区地址 
secoff = WriteAddr%4096;//在扇区内的偏移
secremain = 4096 - secoff;//扇区剩余空间大小 
BSP_Printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//测试用
if(NumByteToWrite<=secremain)
{
secremain=NumByteToWrite;//不大于 4096 个字节
}
while(1) 
{
W25QXX_Read(W25QXX_BUF,secpos*4096,4096);//读出整个扇区的内容
for(i=0;i<secremain;i++)//校验数据
{
if(W25QXX_BUF[secoff+i]!=0XFF)break;//需要擦除 
}
if(i<secremain)//需要擦除
{
W25QXX_Erase_Sector(secpos); //擦除这个扇区
for(i=0;i<secremain;i++) //复制
{
W25QXX_BUF[i+secoff]=pBuffer[i]; 
}
W25QXX_Write_NoCheck(W25QXX_BUF,secpos*4096,4096);//写入整个扇区 
}else 
{
W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain);//写已经擦除了的,直接写入扇区剩余区间. 
}
if(NumByteToWrite == secremain)
{
break;//写入结束了
}
else//写入未结束
{
secpos++;//扇区地址增 1
	secoff = 0;//偏移位置为 0 
 pBuffer+=secremain; //指针偏移
WriteAddr+=secremain; //写地址偏移 
 NumByteToWrite-=secremain; //字节数递减
if(NumByteToWrite>4096)
{
secremain=4096;//下一个扇区还是写不完
}
else 
{
secremain=NumByteToWrite; //下一个扇区可以写完了
}
}
};
}
/*
*********************************************************************************************************
* 函 数 名: W25QXX_Erase_Chip
* 功能说明: 擦除整个芯片
* 形 参: 无
* 返 回 值: 无
* 注 意: 等待时间超长...
*********************************************************************************************************
*/
void W25QXX_Erase_Chip(void) 
{ 
 W25QXX_Write_Enable(); //SET WEL 
 W25QXX_Wait_Busy(); 
 W25QXX_CS = 0; //使能器件 
 W25QXX_SPIx_ReadWriteByte(W25X_ChipErase); //发送片擦除命令 
W25QXX_CS = 1; //取消片选 
W25QXX_Wait_Busy(); //等待芯片擦除结束
} 
/*
*********************************************************************************************************
* 函 数 名: W25QXX_Erase_Sector
* 功能说明: 擦除一个扇区
* 形 参: Dst_Addr:扇区地址 根据实际容量设置
* 返 回 值: 无
* 注 意: 擦除一个扇区的最少时间:150ms
*********************************************************************************************************
*/
void W25QXX_Erase_Sector(uint32_t Dst_Addr) 
{ 
//监视 falsh 擦除情况,测试用 
BSP_Printf("fe:%x\r\n",Dst_Addr);
Dst_Addr*=4096;
 W25QXX_Write_Enable(); //SET WEL 
 W25QXX_Wait_Busy(); 
 W25QXX_CS = 0; //使能器件 
 W25QXX_SPIx_ReadWriteByte(W25X_SectorErase); //发送扇区擦除指令
 W25QXX_SPIx_ReadWriteByte((uint8_t)((Dst_Addr)>>16)); //发送 24bit 地址 
 W25QXX_SPIx_ReadWriteByte((uint8_t)((Dst_Addr)>>8)); 
 W25QXX_SPIx_ReadWriteByte((uint8_t)Dst_Addr); 
W25QXX_CS = 1; //取消片选 
 W25QXX_Wait_Busy(); //等待擦除完成
} 
/*
*********************************************************************************************************
* 函 数 名: W25QXX_Wait_Busy
* 功能说明: 等待空闲
* 形 参: 无
* 返 回 值: 无
*********************************************************************************************************
*/
void W25QXX_Wait_Busy(void) 
{ 
while((W25QXX_ReadSR()&0x01) == 0x01); // 等待 BUSY 位清空
}
/*
*********************************************************************************************************
* 函 数 名: W25QXX_PowerDown
* 功能说明: 进入掉电模式
* 形 参: 无
* 返 回 值: 无
*********************************************************************************************************
*/
void W25QXX_PowerDown(void) 
{ 
 W25QXX_CS = 0; //使能器件 
 W25QXX_SPIx_ReadWriteByte(W25X_PowerDown); //发送掉电命令 
W25QXX_CS = 1; //取消片选 
 delay_us(3); //等待 TPD 
} 
/*
*********************************************************************************************************
* 函 数 名: W25QXX_WAKEUP
* 功能说明: 唤醒
* 形 参: 无
* 返 回 值: 无
*********************************************************************************************************
*/
void W25QXX_WAKEUP(void) 
{ 
 W25QXX_CS = 0; //使能器件 
 W25QXX_SPIx_ReadWriteByte(W25X_ReleasePowerDown); // send W25X_PowerDown command 0xAB 
W25QXX_CS = 1; //取消片选 
 delay_us(3); //等待 TRES1
} 
/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
