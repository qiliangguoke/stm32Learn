/*
*********************************************************************************************************
*
*	模块名称 : usart1_cmd模块
*	文件名称 : usart1_cmd.c
*	说    明 : usart1_cmd协议控制
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2019-08-02 waroyal  正式发布
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/

#include "usart1_cmd.h"

const uint8_t RELAY_ON_CMD[] = "relay_on_";
const uint8_t RELAY_OFF_CMD[] = "relay_off_";
const uint8_t RELAY_TOGGLE_CMD[] = "relay_toggle_";
const uint8_t RELAY_STATE_CMD[] = "relay_state_";
const uint8_t HELP_CMD[] = "help";
uint8_t RELAY_ON_RSP[] = "relay_X_state_on";
uint8_t RELAY_OFF_RSP[] ="relay_X_state_off";

//设定字节协议回馈的暂存信息，注意共九个字节，部分位置需要修改
uint8_t RELAY_RSP_BYTE[9] = {FRAME_HEADER_BYTE_1st,FRAME_HEADER_BYTE_2nd,FRAME_HEADER_BYTE_3rd,0x04,0x02,0x01,0x01,0xFF,0xFF};


static void PrintfHelp(void)
{
	printf("\r\n");
	printf("*************************************************************\r\n");
	printf("* 继电器闭合 ：relay_on_X\r\n");
	printf("* 继电器断开 : relay_off_X\r\n");
	printf("* 继电器翻转 : relay_toggle_X\r\n");
	printf("* 继电器状态 : relay_state_X\r\n");
	printf("* 闭合回应命令 : relay_X_state_on\r\n");
	printf("* 断开回应命令 : relay_X_state_off\r\n");
	printf("* 注意 : 以上命令中的 X 取值为 1~4\r\n");
	printf("*************************************************************\r\n");
}
void usart1_cmd(void)
{
	//定义一个变量 暂存帧数据长度
	//定义一个变量 暂存继电器状态
	
	//1.判断命令是否正确，长度是否正确
	
	//2.判断命令的参数是否正确（如本例中的继电器序号）
	
	//3.按照协议解析对应的字节，完成相应的功能
	
	//4.注意清除串口1的接收状态和帧数据长度
	
	u16 len = 0;//长度暂存
	uint8_t status = 0;//状态暂存
	
	if ( ReceiveState )
	{
		len = RxCounter;
		
		//判断帧头是否正确
		if( ( memcmp(USART_RX_BUF,HELP_CMD,4) == 0 ) && ( len == 4 ) )
			{
				PrintfHelp();
			}
//判断继电器控制闭合的命令,字符长度和字符内容
		else if( ( memcmp(USART_RX_BUF,RELAY_ON_CMD,9) == 0 ) && ( len == 10 ) )
		{
//如果参数为 1~4,注意是 ASCII 值
			if( ( USART_RX_BUF[9] > '0' ) && ( USART_RX_BUF[9] < '5' ) )
			{
				bsp_RelayOn( ( USART_RX_BUF[9]- '0' ) );//对应继电器闭合
				RELAY_ON_RSP[6] = USART_RX_BUF[9];
				printf("%s\r\n",RELAY_ON_RSP);
			}
		}
		//判断继电器控制断开的命令,字符长度和字符内容
			else if( ( memcmp(USART_RX_BUF,RELAY_OFF_CMD,10) == 0 ) && ( len == 11 ) )
			{
			//如果参数为 1~4,注意是 ASCII 值
				if( ( USART_RX_BUF[10] > '0' ) && ( USART_RX_BUF[10] < '5' ) )
				{
					bsp_RelayOff( ( USART_RX_BUF[10]- '0' ) );//对应继电器断开
					RELAY_OFF_RSP[6] = USART_RX_BUF[10];
					printf("%s\r\n",RELAY_OFF_RSP);
				}
			}
			//判断继电器控制翻转的命令,字符长度和字符内容
			else if( ( memcmp(USART_RX_BUF,RELAY_TOGGLE_CMD,13) == 0 ) && ( len == 14 ) )
			{
				//如果参数为 1~4,注意是 ASCII 值
				if( ( USART_RX_BUF[13] > '0' ) && ( USART_RX_BUF[13] < '5' ) )
				{
					bsp_RelayToggle( ( USART_RX_BUF[13]- '0' ) );//对应继电器断开
					status = bsp_IsRelayOn( ( USART_RX_BUF[13]- '0' ) );//查询对应继电器状态
					switch(status)
					{
						case 0:
							{
								RELAY_OFF_RSP[6] = USART_RX_BUF[13];
								printf("%s\r\n",RELAY_OFF_RSP);
							}break;
						case 1:
							{
								RELAY_ON_RSP[6] = USART_RX_BUF[13];
								printf("%s\r\n",RELAY_ON_RSP);
							}break;
						default:break;
					}
				}
			}
			//判断继电器状态的命令,字符长度和字符内容
			else if( ( memcmp(USART_RX_BUF,RELAY_STATE_CMD,12) == 0 ) && ( len == 13 ) )
			{
				//如果参数为 1~4,注意是 ASCII 值
				if( ( USART_RX_BUF[12] > '0' ) && ( USART_RX_BUF[12] < '5' ) )
				{
					status = bsp_IsRelayOn( ( USART_RX_BUF[12]- '0' ) );//查询对应继电器状态
					switch(status)
					{
						case 0:
						{
							RELAY_OFF_RSP[6] = USART_RX_BUF[12];
							printf("%s\r\n",RELAY_OFF_RSP);
						}break;
						case 1:
						{
							RELAY_ON_RSP[6] = USART_RX_BUF[12];
							printf("%s\r\n",RELAY_ON_RSP);
						}break;
						default:break;
					}
				}
			}
			Uart0_STA_Clr();//串口 0 状态清除
	}
}


/*
*********************************************************************************************************
*	函 数 名：CheckSum
*	功能说明：和校验
*	形    参：	u8* buf 数组首地址地址
*				u16 len 需要校验的字节长度
*	返 回 值：u8 sum 累加和
*********************************************************************************************************
*/
uint8_t CheckSum(uint8_t *buf,uint16_t len)
{
	//定义累加变量SUM，和用于for循环的自增变量
	
	//for循环计算累加和，注意因为变量定义范围，会自动舍弃除低字节的剩余数据
	
	//最后return SUM
	
}

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
