#ifndef _BSP_IWDG_H
#define _BSP_IWDG_H

#include "sys.h"

/*独立看门狗初始化*/
void bsp_InitIwdg(uint8_t _uIWDGPrer,uint32_t _ulIWDGRlr);

/* 喂独立看门狗*/

void IWDG_Feed(void);

#endif
