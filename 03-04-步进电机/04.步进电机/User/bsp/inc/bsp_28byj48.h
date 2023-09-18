#ifndef _BSP_28BYJ48_H_
#define _BSP_28BYJ48_H_

///////////////////////////////////////
/* ͷ�ļ������� */
#include "sys.h"
///////////////////////////////////////
/* �궨������ */

#define RCC_ALL_SM28BYJ48 				( SM28BYJ48_A_GPIO_CLK | SM28BYJ48_B_GPIO_CLK | SM28BYJ48_C_GPIO_CLK | SM28BYJ48_D_GPIO_CLK )
#define SM28BYJ48_OUT_GPIO_MODE 		GPIO_Mode_Out_PP 			//SM28BYJ48_A_OUT ����ģʽ
//��ɫA��
#define SM28BYJ48_A_GPIO_PIN			GPIO_Pin_7 //FAN1 ���ź�
#define SM28BYJ48_A_PIN_ID 				7 //FAN1 �������
#define SM28BYJ48_A_GPIO_PORT 			GPIOC //FAN1 �˿ں�
#define SM28BYJ48_A_GPIO_CLK 			RCC_APB2Periph_GPIOC //FAN1 ʱ��
#define SM28BYJ48_A_FUN_OUT 			PCout //FAN1 ����˿����ú���

#define SM28BYJ48_A_OUT_ACTIVE_LEVEL				0 						//SM28BYJ48_A ��Ч��ƽΪ�͵�ƽ
//��ɫB��
#define SM28BYJ48_B_GPIO_PIN			GPIO_Pin_6 //FAN1 ���ź�
#define SM28BYJ48_B_PIN_ID 				6 //FAN1 �������
#define SM28BYJ48_B_GPIO_PORT 			GPIOC //FAN1 �˿ں�
#define SM28BYJ48_B_GPIO_CLK 			RCC_APB2Periph_GPIOC //FAN1 ʱ��
#define SM28BYJ48_B_FUN_OUT 			PCout //FAN1 ����˿����ú���
#define SM28BYJ48_B_OUT_ACTIVE_LEVEL				0 						//SM28BYJ48_B ��Ч��ƽΪ�͵�ƽ
//��ɫC��
#define SM28BYJ48_C_GPIO_PIN			GPIO_Pin_5 //FAN1 ���ź�
#define SM28BYJ48_C_PIN_ID 				5 //FAN1 �������
#define SM28BYJ48_C_GPIO_PORT 			GPIOC //FAN1 �˿ں�
#define SM28BYJ48_C_GPIO_CLK 			RCC_APB2Periph_GPIOC //FAN1 ʱ��
#define SM28BYJ48_C_FUN_OUT 			PCout //FAN1 ����˿����ú���
#define SM28BYJ48_C_OUT_ACTIVE_LEVEL				0 						//SM28BYJ48_c ��Ч��ƽΪ�͵�ƽ
//��ɫD��
#define SM28BYJ48_D_GPIO_PIN			GPIO_Pin_4 //FAN1 ���ź�
#define SM28BYJ48_D_PIN_ID 				4 //FAN1 �������
#define SM28BYJ48_D_GPIO_PORT 			GPIOC //FAN1 �˿ں�
#define SM28BYJ48_D_GPIO_CLK 			RCC_APB2Periph_GPIOC //FAN1 ʱ��
#define SM28BYJ48_D_FUN_OUT 			PCout //FAN1 ����˿����ú���
#define SM28BYJ48_D_OUT_ACTIVE_LEVEL				0 						//SM28BYJ48_D  ��Ч��ƽΪ�͵�ƽ
//IO ��������
#define SM28BYJ48_A SM28BYJ48_A_FUN_OUT(SM28BYJ48_A_PIN_ID) //SM28BYJ48_A
#define SM28BYJ48_B SM28BYJ48_B_FUN_OUT(SM28BYJ48_B_PIN_ID) //SM28BYJ48_B
#define SM28BYJ48_C SM28BYJ48_C_FUN_OUT(SM28BYJ48_C_PIN_ID) //SM28BYJ48_C
#define SM28BYJ48_D SM28BYJ48_D_FUN_OUT(SM28BYJ48_D_PIN_ID) //SM28BYJ48_D

///////////////////////////////////////
/* �ⲿ���������� */



/* ����ṹ�����ȫ�ֱ�������
*/
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
	SM_A=1, /* A �ർͨ */
	SM_B=2, /* B �ർͨ */
	SM_C=3,
	SM_D=4,
	SM_AB=5, /* AB �ർͨ */
	SM_BC=6,
	SM_CD=7,
	SM_DA=8
};

extern MOTOR_T g_tMot; /* ����ȫ�ֱ��� */
///////////////////////////////////////
/* ���������� */
void bsp_Init_28byj48(void);
void dirction(void);
static void motPowerOn(uint8_t _ucMode);
///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
