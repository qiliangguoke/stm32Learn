/*
*********************************************************************************************************
*
*	ģ������ : usart1_cmdģ��
*	�ļ����� : usart1_cmd.c
*	˵    �� : usart1_cmdЭ�����
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2019-08-02 waroyal  ��ʽ����
*	Copyright (C), 2014-2019, �����׵���
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

//�趨�ֽ�Э��������ݴ���Ϣ��ע�⹲�Ÿ��ֽڣ�����λ����Ҫ�޸�
uint8_t RELAY_RSP_BYTE[9] = {FRAME_HEADER_BYTE_1st,FRAME_HEADER_BYTE_2nd,FRAME_HEADER_BYTE_3rd,0x04,0x02,0x01,0x01,0xFF,0xFF};


static void PrintfHelp(void)
{
	printf("\r\n");
	printf("*************************************************************\r\n");
	printf("* �̵����պ� ��relay_on_X\r\n");
	printf("* �̵����Ͽ� : relay_off_X\r\n");
	printf("* �̵�����ת : relay_toggle_X\r\n");
	printf("* �̵���״̬ : relay_state_X\r\n");
	printf("* �պϻ�Ӧ���� : relay_X_state_on\r\n");
	printf("* �Ͽ���Ӧ���� : relay_X_state_off\r\n");
	printf("* ע�� : ���������е� X ȡֵΪ 1~4\r\n");
	printf("*************************************************************\r\n");
}
void usart1_cmd(void)
{
	//����һ������ �ݴ�֡���ݳ���
	//����һ������ �ݴ�̵���״̬
	
	//1.�ж������Ƿ���ȷ�������Ƿ���ȷ
	
	//2.�ж�����Ĳ����Ƿ���ȷ���籾���еļ̵�����ţ�
	
	//3.����Э�������Ӧ���ֽڣ������Ӧ�Ĺ���
	
	//4.ע���������1�Ľ���״̬��֡���ݳ���
	
	u16 len = 0;//�����ݴ�
	uint8_t status = 0;//״̬�ݴ�
	
	if ( ReceiveState )
	{
		len = RxCounter;
		
		//�ж�֡ͷ�Ƿ���ȷ
		if( (USART_RX_BUF[0] == FRAME_HEADER_BYTE_1st) && (USART_RX_BUF[1] == FRAME_HEADER_BYTE_2nd) && 
			(USART_RX_BUF[2] == FRAME_HEADER_BYTE_3rd) )
		{
			printf("�ֽ�Э��--֡ͷ��ȷ\r\n");
			//�ж�У�����ȷ
			if(USART_RX_BUF[len-1] == CheckSum(&USART_RX_BUF[FRAME_DATA_FIELD_OFFSET],lenFRAME_CONST_BYTE_LEN))
			{
				printf("�ֽ�Э��--У�����ȷ\r\n");
				//���ݳ���Ҳ��ȷ
				if( USART_RX_BUF[3] == (len - FRAME_CONST_BYTE_LEN) )
				{
					printf("�ֽ�Э��--���ݳ�����ȷ\r\n");
					switch( USART_RX_BUF[FRAME_DATA_FIELD_OFFSET] )
					{
						//��λ��->��λ��������
						case FUN_CODE_CMD:
						{
							switch( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 1 ] )
							{
								//�Ǽ̵���������
								case FUN_CODE_DEVICE_RELAY:
								{
									//�̵����Ų�����ȷ �� 1~4 ֮��
									if( ( ( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 2 ] ) > 0 ) && 
										( ( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 2 ] ) < 5 ) )
									{
										//���¼̵�����
											RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+2] = USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 2 ];
										//�жϾ�������
										switch( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 3 ] )
										{
											//�պ�����
											case FUN_CODE_CMD_RELAY_ON:
											{
												printf("�ֽ�Э��--�̵����պ�����\r\n");
												bsp_RelayOn( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 2 ] );
												//���¼̵���״̬
												RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+3] = 
												FUN_CODE_RSP_RELAY_ON;
												//����У��λ������
												RELAY_RSP_BYTE[8] = 
												CheckSum(&RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET],4);
												//���ͷ�����Ϣ
												USART1_Send_Data(RELAY_RSP_BYTE,9);
												printf("\r\n");
												}break;
											//�Ͽ�����
											case FUN_CODE_CMD_RELAY_OFF:
											{
												printf("�ֽ�Э��--�̵����Ͽ�����\r\n");
												bsp_RelayOff( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 2 ] );
												//���¼̵���״̬
												RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+3] = 
												FUN_CODE_RSP_RELAY_OFF;
												//����У��λ������
												RELAY_RSP_BYTE[8] = 
												CheckSum(&RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET],4);
												//���ͷ�����Ϣ
												USART1_Send_Data(RELAY_RSP_BYTE,9);
												printf("\r\n");
											}break;
											//��ת����
											case FUN_CODE_CMD_RELAY_TOGGLE:
											{
												printf("�ֽ�Э��--�̵�����ת����\r\n");
												bsp_RelayToggle( USART_RX_BUF[ FRAME_DATA_FIELD_OFFSET + 2 ] );
												status = 
												bsp_IsRelayOn( RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+2] );//��ѯ��Ӧ�̵���״̬
												if(status==0)
												{
													//���¼̵���״̬
													RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+3] = FUN_CODE_RSP_RELAY_OFF;
												}
												else if(status==1)
												{
													//���¼̵���״̬
													RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+3] = FUN_CODE_RSP_RELAY_ON;
												}
											//����У��λ������
											RELAY_RSP_BYTE[8] = 
											CheckSum(&RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET],4);
											//���ͷ�����Ϣ
											USART1_Send_Data(RELAY_RSP_BYTE,9);
											printf("\r\n");
											}break;
											//��ѯ����
											case FUN_CODE_CMD_RELAY_QUERY:
{
printf("�ֽ�Э��--�̵�����ѯ����\r\n");
status = 
bsp_IsRelayOn( RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+2] );//��ѯ��Ӧ�̵���״̬
	if(status==0)
{
//���¼̵���״̬
RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+3] = FUN_CODE_RSP_RELAY_OFF;
}
else if(status==1)
{
//���¼̵���״̬
RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET+3] = FUN_CODE_RSP_RELAY_ON;
}
//����У��λ������
RELAY_RSP_BYTE[8] = 
CheckSum(&RELAY_RSP_BYTE[FRAME_DATA_FIELD_OFFSET],4);
//���ͷ�����Ϣ
USART1_Send_Data(RELAY_RSP_BYTE,9);
printf("\r\n");
}break;
default:break;
}
}
else
{
//�̵����Ų�������
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
*	�� �� ����CheckSum
*	����˵������У��
*	��    �Σ�	u8* buf �����׵�ַ��ַ
*				u16 len ��ҪУ����ֽڳ���
*	�� �� ֵ��u8 sum �ۼӺ�
*********************************************************************************************************
*/
uint8_t CheckSum(uint8_t *buf,uint16_t len)
{
	//�����ۼӱ���SUM��������forѭ������������
	
	//forѭ�������ۼӺͣ�ע����Ϊ�������巶Χ�����Զ����������ֽڵ�ʣ������
	
	//���return SUM
	
}

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
