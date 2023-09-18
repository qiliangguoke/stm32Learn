/*
*********************************************************************************************************
*
*	模块名称 : 模块
*	文件名称 : bsp_wwdg.h
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/
#ifndef _BSP_WWDG_H
#define _BSP_WWDG_H

#include "sys.h"

/* 初始化 */
void bsp_InitWwdg(uint8_t _ucTreg, uint8_t _ucWreg, uint32_t WWDG_Prescaler);

void bsp_InitWwdgNVIC(FunctionalState NewState);

#endif
