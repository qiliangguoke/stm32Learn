/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : bsp_key.h
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    xxx-xx-xx
*
*
*********************************************************************************************************
*/
#ifndef __bsp_key_H
#define __bsp_key_H

///////////////////////////////////////
/* ͷ�ļ������� */
#include "sys.h"
///////////////////////////////////////
/* �궨������ */
#define RCC_ALL_KEY  (WKUP_GPIO_CLK|KEY0_GPIO_CLK|KEY1_GPIO_CLK|KEY2_GPIO_CLK)

#define WKUP_GPIO_PIN       GPIO_Pin_0       		 //WKUP���ź�
#define WKUP_PIN_ID         0                		 //WKUP�������
#define WKUP_GPIO_PORT      GPIOA            		 //WKUP�˿ں�
#define WKUP_GPIO_CLK       RCC_APB2Periph_GPIOA     //WKUPʱ��
//#define WKUP_FUN_OUT        PAout                  //WKUP����˿����ú���
#define WKUP_FUN_IN         PAin                     //WKUP����˿����ú���
#define WKUP_GPIO_MODE      GPIO_Mode_IPD            //WKUP�˿�����ģʽ
#define WKUP_ACTIVE_LEVEL   1                        //WKUP������Ч��ƽΪ�ߵ�ƽ

//////
#define KEY0_GPIO_PIN       GPIO_Pin_4                //KEY0���ź�
#define KEY0_PIN_ID         4                         //KEY0�������
#define KEY0_GPIO_PORT      GPIOE                     //KEY0�˿ں�
#define KEY0_GPIO_CLK       RCC_APB2Periph_GPIOE      //KEY0ʱ��
#define KEY0_FUN_OUT        PEout                     //KEY0����˿ں����ú���
#define KEY0_FUN_IN         PEin                      //KEY0����˿ں����ú���
#define KEY0_GPIO_MODE		GPIO_Mode_IPU             //KEY0�˿�����ģʽ
#define KEY0_ACTIVE_LEVEL   0 	                       //KEY0������Ч��ƽΪ�͵�ƽ
//////
#define KEY1_GPIO_PIN       GPIO_Pin_3                //KEY1���ź�
#define KEY1_PIN_ID         3                         //KEY1�������
#define KEY1_GPIO_PORT      GPIOE                     //KEY1�˿ں�
#define KEY1_GPIO_CLK       RCC_APB2Periph_GPIOE      //KEY1ʱ��
#define KEY1_FUN_OUT        PEout                     //KEY1����˿ں����ú���
#define KEY1_FUN_IN         PEin                      //KEY1����˿ں����ú���
#define KEY1_GPIO_MODE		GPIO_Mode_IPU             //KEY1�˿�����ģʽ
#define KEY1_ACTIVE_LEVEL   0 	                       //KEY1������Ч��ƽΪ�͵�ƽ
//////
#define KEY2_GPIO_PIN       GPIO_Pin_2                 //KEY2���ź�
#define KEY2_PIN_ID         2                          //KEY2�������
#define KEY2_GPIO_PORT      GPIOE                      //KEY2�˿ں�
#define KEY2_GPIO_CLK       RCC_APB2Periph_GPIOE       //KEY2ʱ��
#define KEY2_FUN_OUT        PEout                      //KEY2����˿ں����ú���
#define KEY2_FUN_IN         PEin                       //KEY2����˿ں����ú���
#define KEY2_GPIO_MODE		GPIO_Mode_IPU              //KEY2�˿�����ģʽ
#define KEY2_ACTIVE_LEVEL   0 	                       //KEY2������Ч��ƽΪ�͵�ƽ
///////////////////////////
//IO��������
#define WKUP               	WKUP_FUN_IN(WKUP_PIN_ID)	//WKUP//��ȡ����1��WK_UP��
#define KEY0                KEY0_FUN_IN(KEY0_PIN_ID)    //KEY0//��ȡ����2
#define KEY1                KEY1_FUN_IN(KEY1_PIN_ID)    //KEY1//��ȡ����3
#define KEY2                KEY2_FUN_IN(KEY2_PIN_ID)    //KEY2//��ȡ����4
//////////////////////////
#define KEY_COUNT			6							/*����������4��������+2����ϼ�*/

/*����Ӧ�ó���Ĺ���������������*/
#define WKUP_DOWN			KEY_1_DOWN
#define WKUP_UP				KEY_1_UP
#define WKUP_LONG			KEY_1_LONG

#define KEY0_DOWN			KEY_2_DOWN
#define KEY0_UP				KEY_2_UP
#define KEY0_LONG			KEY_2_LONG

#define KEY1_DOWN			KEY_3_DOWN
#define KEY1_UP				KEY_3_UP
#define KEY1_LONG			KEY_3_LONG

#define KEY2_DOWN			KEY_4_DOWN
#define KEY2_UP				KEY_4_UP
#define KEY2_LONG			KEY_4_LONG

#define SYS_DOWN_WKUP_KEY0			KEY_5_DOWN	/*WKUP KEY0 ��ϼ�*/
#define SYS_UP_WKUP_KEY0			KEY_5_UP
#define SYS_LONG_WKUP_KEY0			KEY_5_LONG

#define SYS_DOWN_KEY0_KEY1			KEY_6_DOWN /*KEY0 KEY1 ��ϼ�*/
#define SYS_UP_KEY0_KEY1			KEY_6_UP
#define SYS_LONG_KEY0_KEY1			KEY_6_LONG

///////////////////////////////////////
/* �ⲿ���������� */
/*����ID����Ҫ����bsp_KeyState()��������ڲ���*/
typedef enum
{
	KID_K1=0,
	KID_K2,
	KID_K3,
	KID_K4,
}KEY_ID_E;
/*
	�����˲�ʱ��50ms,��λ10ms.
	ֻ��������⵽50ms״̬�������Ϊ��Ч����������Ͱ��������¼�
	��ʹ������·����Ӳ���˲������˲�����Ҳ���Ա�֤�ɿ��ؼ�⵽�����¼�
*/
#define KEY_FILTER_TIME		5
#define KEY_LONG_TIME		100				/*��λ10ms, ����1�룬��Ϊ�����¼�*/

/*ÿ��������Ӧ1��ȫ�ֵĽṹ�����*/
typedef struct
{
	/*������һ������ָ�룬ָ���жϰ����Ƿ��µĺ���*/
	uint8_t(*IsKeyDownFunc)(void);	/*�������µ��жϺ�����1��ʾ����*/	
	uint8_t		Count;				/*�˲���������*/	
	uint16_t	LongCount;			/*����������*/	
	uint16_t	LongTime;			/*�������³���ʱ�䣬0��ʾ����ⳤ��*/	
	uint8_t		State;				/*������ǰ״̬�����»��ǵ���*/
	uint8_t		RepeatSpeed;		/*������������*/
	uint8_t		RepeatCount;		/*��������������*/
}KEY_T;
/*
	�����ֵ���룬���밴���´���ʱÿ�����İ��¡�����ͳ����¼�

	�Ƽ�enum������#define,ԭ��
	��1������������ֵ���������˳��ʹ���뿴���������
	��2���������ɰ����Ǳ����ֵ�ظ���
*/

typedef enum
{
	KEY_NONE =0,	/*0��ʾ�����¼�*/
	KEY_1_DOWN,		/*1������*/
	KEY_1_UP,		/*1������*/	
	KEY_1_LONG,		/*1������*/	
	
	KEY_2_DOWN,		/*2������*/
	KEY_2_UP,		/*2������*/
	KEY_2_LONG,		/*2������*/
	
	KEY_3_DOWN,		/*3������*/
	KEY_3_UP,		/*3������*/
	KEY_3_LONG,		/*3������*/
	
	KEY_4_DOWN,		/*4������*/
	KEY_4_UP,		/*4������*/
	KEY_4_LONG,		/*4������*/
	
	/*��ϼ�*/
	KEY_5_DOWN,		/*5������*/
	KEY_5_UP,		/*5������*/
	KEY_5_LONG,		/*5������*/
	
	KEY_6_DOWN,		/*6������*/
	KEY_6_UP,		/*6������*/
	KEY_6_LONG,		/*6������*/
	
}KEY_ENUM;

/*����FIFO�õ�����*/
#define KEY_FIFO_SIZE    10
typedef struct
{
	uint8_t Buf[KEY_FIFO_SIZE];		/*��ֵ������*/
	uint8_t Read;					/*��������ָ��1*/
	uint8_t Write;					/*������дָ��*/
	uint8_t Read2;					/*��������ָ��2*/
}KEY_FIFO_T;
///////////////////////////////////////
/* ���ⲿ���õĺ������� */
void bsp_InitKey(void);
void bsp_KeyScan(void);
void bsp_PutKey(uint8_t _KeyCode);
uint8_t bsp_GetKey(void);
uint8_t bsp_GetKey2(void);
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID);
void bsp_SetKeyParam(uint8_t _ucKeyID,uint16_t _LongTime,uint8_t _RepeatSpeed);
void bsp_ClearKey(void);

///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/


