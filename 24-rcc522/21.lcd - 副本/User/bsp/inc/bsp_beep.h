#ifndef __BSP_BEEP_H
#define __BSP_BEEP_H

///////////////////////////////////////
/* ͷ�ļ������� */
#include "sys.h"
///////////////////////////////////////
/* �궨������ */
#define RCC_ALL_BEEP (BEEP_GPIO_CLK)

#define BEEP_GPIO_PIN         GPIO_Pin_11             //BEEP���ź�
#define BEEP_PIN_ID           11                      //BEEF�������
#define BEEP_GPIO_PORT        GPIOG                   //BEEP�˿ں�
#define BEEP_GPIO_CLK         RCC_APB2Periph_GPIOG    //BEEPʱ��
#define BEEP_FUN_OUT          PGout                   //BEEP����˿����ú���
//#define BEEP_FUN_IN           PGin                    //BEEP����˿����ú���

////////////////////////////////////////////////////

//IO��������
#define BEEP                  BEEP_FUN_OUT(BEEP_PIN_ID)		//BEEP


/*���ⲿ���õĺ�������*/
void bsp_InitBeep(void);
void bsp_BeepOn(void);
void bsp_BeepOff(void);
void bsp_BeepToggle(void);
uint8_t bsp_IsBeepOn(void);

///////////////////////////////////////
/* �ⲿ���������� */

///////////////////////////////////////
/* ���������� */

///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
