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
		if( ( memcmp(USART_RX_BUF,HELP_CMD,4) == 0 ) && ( len == 4 ) )
			{
				PrintfHelp();
			}
//�жϼ̵������Ʊպϵ�����,�ַ����Ⱥ��ַ�����
		else if( ( memcmp(USART_RX_BUF,RELAY_ON_CMD,9) == 0 ) && ( len == 10 ) )
		{
//�������Ϊ 1~4,ע���� ASCII ֵ
			if( ( USART_RX_BUF[9] > '0' ) && ( USART_RX_BUF[9] < '5' ) )
			{
				bsp_RelayOn( ( USART_RX_BUF[9]- '0' ) );//��Ӧ�̵����պ�
				RELAY_ON_RSP[6] = USART_RX_BUF[9];
				printf("%s\r\n",RELAY_ON_RSP);
			}
		}
		//�жϼ̵������ƶϿ�������,�ַ����Ⱥ��ַ�����
			else if( ( memcmp(USART_RX_BUF,RELAY_OFF_CMD,10) == 0 ) && ( len == 11 ) )
			{
			//�������Ϊ 1~4,ע���� ASCII ֵ
				if( ( USART_RX_BUF[10] > '0' ) && ( USART_RX_BUF[10] < '5' ) )
				{
					bsp_RelayOff( ( USART_RX_BUF[10]- '0' ) );//��Ӧ�̵����Ͽ�
					RELAY_OFF_RSP[6] = USART_RX_BUF[10];
					printf("%s\r\n",RELAY_OFF_RSP);
				}
			}
			//�жϼ̵������Ʒ�ת������,�ַ����Ⱥ��ַ�����
			else if( ( memcmp(USART_RX_BUF,RELAY_TOGGLE_CMD,13) == 0 ) && ( len == 14 ) )
			{
				//�������Ϊ 1~4,ע���� ASCII ֵ
				if( ( USART_RX_BUF[13] > '0' ) && ( USART_RX_BUF[13] < '5' ) )
				{
					bsp_RelayToggle( ( USART_RX_BUF[13]- '0' ) );//��Ӧ�̵����Ͽ�
					status = bsp_IsRelayOn( ( USART_RX_BUF[13]- '0' ) );//��ѯ��Ӧ�̵���״̬
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
			//�жϼ̵���״̬������,�ַ����Ⱥ��ַ�����
			else if( ( memcmp(USART_RX_BUF,RELAY_STATE_CMD,12) == 0 ) && ( len == 13 ) )
			{
				//�������Ϊ 1~4,ע���� ASCII ֵ
				if( ( USART_RX_BUF[12] > '0' ) && ( USART_RX_BUF[12] < '5' ) )
				{
					status = bsp_IsRelayOn( ( USART_RX_BUF[12]- '0' ) );//��ѯ��Ӧ�̵���״̬
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
			Uart0_STA_Clr();//���� 0 ״̬���
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
