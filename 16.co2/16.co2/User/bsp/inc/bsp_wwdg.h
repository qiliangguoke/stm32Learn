/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : bsp_wwdg.h
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/
#ifndef _BSP_WWDG_H
#define _BSP_WWDG_H

#include "sys.h"

/* ��ʼ�� */
void bsp_InitWwdg(uint8_t _ucTreg, uint8_t _ucWreg, uint32_t WWDG_Prescaler);

void bsp_InitWwdgNVIC(FunctionalState NewState);

#endif
