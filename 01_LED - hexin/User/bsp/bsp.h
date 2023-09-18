/*
*********************************************************************************************************
*
*	ģ������ : BSPģ��
*	�ļ����� : bsp.h
*	˵    �� : ���ǵײ�����ģ�����е�h�ļ��Ļ����ļ��� Ӧ�ó���ֻ�� #include bsp.h ���ɣ�
*			  ����Ҫ#include ÿ��ģ��� h �ļ�
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/

#ifndef _BSP_H_
#define _BSP_H_


/* ���� BSP �汾�� */
#define __STM32F1_BSP_VERSION		"1.1"

/* CPU����ʱִ�еĺ��� */
//#define CPU_IDLE()		bsp_Idle()

/* ����ȫ���жϵĺ� */
#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */

/* ���������ڵ��Խ׶��Ŵ� */
//#define BSP_Printf		printf
#define BSP_Printf(...)

//#include "stm32f10x.h"
#include "sys.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

/* ��������ͷ�ļ����� START OF AREA*/

#include "bsp_led.h"
#include "bsp_timer.h"


/* ��������ͷ�ļ����� END OF AREA */


/* �ṩ������C�ļ����õĺ��� */
void bsp_Init(void);
void bsp_Idle(void);
void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);

#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/