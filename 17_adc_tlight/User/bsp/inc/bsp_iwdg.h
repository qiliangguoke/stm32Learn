#ifndef _BSP_IWDG_H
#define _BSP_IWDG_H

#include "sys.h"

/*�������Ź���ʼ��*/
void bsp_InitIwdg(uint8_t _uIWDGPrer,uint32_t _ulIWDGRlr);

/* ι�������Ź�*/

void IWDG_Feed(void);

#endif