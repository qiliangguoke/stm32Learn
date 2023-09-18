/*
*********************************************************************************************************
*
*	ģ������ : usart1_cmdģ��
*	�ļ����� : usart1_cmd.h
*	˵    �� : usart1_cmdЭ�����
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/

#ifndef __USART1_CMD_H_
#define __USART1_CMD_H_

//////////////////////////////////////
//ͷ�ļ���

#include "bsp.h"

//////////////////////////////////
//������

//֡ͷ�ֽڳ���
//#define FRAME_HEADER_LEN		3
//֡�����ֽڳ���
//#define FRAME_DATA_LEN			1
//֡У���ֽڳ���
#define FRAME_CHECKSUM_LEN		1

//֡�̶����ֽڳ���
#define FRAME_CONST_BYTE_LEN	( FRAME_HEADER_LEN + FRAME_DATA_LEN + FRAME_CHECKSUM_LEN )

//֡����������ʼ��ַ
#define FRAME_DATA_FIELD_OFFSET	(FRAME_HEADER_LEN + FRAME_DATA_LEN )

/**********************************************************/

#define FRAME_HEADER_BYTE_1st	0x44
#define FRAME_HEADER_BYTE_2nd	0x5A
#define FRAME_HEADER_BYTE_3rd	0x4C


#define FUN_CODE_CMD		0x01
#define FUN_CODE_RSP		0x02


//#define FUNC_CODE_LEN				1
//#define FUNC_CODE_DEVICE_LEN		1
//#define FUNC_CODE_DEVICE_NUM_LEN	1

//#define FUNC_CODE_OFFSET			FRAME_DATA_FIELD_OFFSET
//#define FUNC_CODE_DEVICE_OFFSET		( FRAME_DATA_FIELD_OFFSET + FUNC_CODE_LEN )


//�豸Ϊ�̵���
#define FUN_CODE_DEVICE_RELAY		0x01
//�̵����պ�����
#define FUN_CODE_CMD_RELAY_ON		0x01
//�̵����Ͽ�����
#define FUN_CODE_CMD_RELAY_OFF		0x02
//�̵���״̬��ת����
#define FUN_CODE_CMD_RELAY_TOGGLE	0x03
//�̵���״̬��ѯ����
#define FUN_CODE_CMD_RELAY_QUERY	0x04
/**********************************************************/
//�̵���״̬�պϷ���
#define FUN_CODE_RSP_RELAY_ON		0xFF
//�̵���״̬�Ͽ�����
#define FUN_CODE_RSP_RELAY_OFF		0x00



//////////////////////////////////
//����������
void usart1_cmd(void);
//uint8_t CheckSum(uint8_t *buf,uint16_t len);

#endif


/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
