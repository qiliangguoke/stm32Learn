#ifndef _BSP_28BYJ48_H_
#define _BSP_28BYJ48_H_

///////////////////////////////////////
/* ͷ�ļ������� */
#include "sys.h"
///////////////////////////////////////
/* �궨������ */

//IO ��������
#define SM28BYJ48_A         SM28BYJ48_A_FUN_OUT(SM28BYJ48_A_PIN_ID) //SM28BYJ48_A
#define SM28BYJ48_B         SM28BYJ48_B_FUN_OUT(SM28BYJ48_B_PIN_ID) //SM28BYJ48_B
#define SM28BYJ48_C         SM28BYJ48_C_FUN_OUT(SM28BYJ48_C_PIN_ID) //SM28BYJ48_C
#define SM28BYJ48_D         SM28BYJ48_D_FUN_OUT(SM28BYJ48_D_PIN_ID) //SM28BYJ48_D


typedef struct
{
		uint8_t ucSpeed; /* ����ٶ� */
		uint8_t ucDir; /* ������� 0 ��ת�� 1 ��ת 2 ֹͣ */
		uint8_t ucStop; /* 0 ���У� 1 ֹͣ */
}MOTOR_T;
/* ���������ͨ���ƶ��� */
enum
{
		SM_OFF = 0, /* A B C D �������ͨ */
		SM_A, /* A �ർͨ */
		SM_B, /* B �ർͨ */
		SM_C,
		SM_D,
		SM_AB, /* AB �ർͨ */
		SM_BC,
		SM_CD,
		SM_DA
};

///////////////////////////////////////
/* �ⲿ���������� */

///////////////////////////////////////
/* ���������� */

///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/