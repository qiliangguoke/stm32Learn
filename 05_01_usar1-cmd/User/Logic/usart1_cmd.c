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
		if( (USART_RX_BUF[0] == FRAME_HEADER_BYTE_1st) && (USART_RX_BUF[1] == FRAME_HEADER_BYTE_2nd) && 
			(USART_RX_BUF[2] == FRAME_HEADER_BYTE_3rd) )
		{
			printf("字节协议--帧头正确\r\n");
			//判断校验和正确
			if(USART_RX_BUF[len-1] == CheckSum(&USART_RX_BUF[FRAME_DATA_FIELD_OFFSET],lenFRAME_CONST_BYTE_LEN))
			{
				printf("字节协议--校验和正确\r\n");
				//数据长度也正确
				if( USART_RX_BUF[3] == (len - FRAME_CONST_BYTE_LEN) )
				{
					printf("字节协议--数据长度正确\r\n");
					switch( USART_RX_BUF[FRAME_DATA_FIELD_OFFSET] )
					{
						//上位机->下位机的命令
						case FUN_CODE_CMD:
						{
							switch( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 1 ] )
							{
								//是继电器的命令
								case FUN_CODE_DEVICE_RELAY:
								{
									//继电器号参数正确 在 1~4 之间
									if( ( ( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 2 ] ) > 0 ) && 
										( ( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 2 ] ) < 5 ) )
									{
										//更新继电器号
											RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+2] = USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 2 ];
										//判断具体命令
										switch( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 3 ] )
										{
											//闭合命令
											case FUN_CODE_CMD_RELAY_ON:
											{
												printf("字节协议--继电器闭合命令\r\n");
												bsp_RelayOn( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 2 ] );
												//更新继电器状态
												RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+3] = 
												FUN_CODE_RSP_RELAY_ON;
												//计算校验位并更新
												RELAY_RSP_BYTE[8] = 
												CheckSum(&RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET],4);
												//发送反馈信息
												USART1_Send_Data(RELAY_RSP_BYTE,9);
												printf("\r\n");
												}break;
											//断开命令
											case FUN_CODE_CMD_RELAY_OFF:
											{
												printf("字节协议--继电器断开命令\r\n");
												bsp_RelayOff( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 2 ] );
												//更新继电器状态
												RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+3] = 
												FUN_CODE_RSP_RELAY_OFF;
												//计算校验位并更新
												RELAY_RSP_BYTE[8] = 
												CheckSum(&RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET],4);
												//发送反馈信息
												USART1_Send_Data(RELAY_RSP_BYTE,9);
												printf("\r\n");
											}break;
											//翻转命令
											case FUN_CODE_CMD_RELAY_TOGGLE:
											{
												printf("字节协议--继电器翻转命令\r\n");
												bsp_RelayToggle( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 2 ] );
												status = 
												bsp_IsRelayOn( RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+2] );//查询对应继电器状态
												if(status==0)
												{
													//更新继电器状态
													RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+3] = FUN_CODE_RSP_RELAY_OFF;
												}
												else if(status==1)
												{
													//更新继电器状态
													RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+3] = FUN_CODE_RSP_RELAY_ON;
												}
											//计算校验位并更新
											RELAY_RSP_BYTE[8] = 
											CheckSum(&RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET],4);
											//发送反馈信息
											USART1_Send_Data(RELAY_RSP_BYTE,9);
											printf("\r\n");
											}break;
											//查询命令
											case FUN_CODE_CMD_RELAY_QUERY:
{
printf("字节协议--继电器查询命令\r\n");
status = 
bsp_IsRelayOn( RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+2] );//查询对应继电器状态
	if(status==0)
{
//更新继电器状态
RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+3] = FUN_CODE_RSP_RELAY_OFF;
}
else if(status==1)
{
//更新继电器状态
RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+3] = FUN_CODE_RSP_RELAY_ON;
}
//计算校验位并更新
RELAY_RSP_BYTE[8] = 
CheckSum(&RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET],4);
//发送反馈信息
USART1_Send_Data(RELAY_RSP_BYTE,9);
printf("\r\n");
}break;
default:break;
}
}
else
{
//继电器号参数错误
}
}break;
default:break;
}
}break;
default:break;
}
}
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
