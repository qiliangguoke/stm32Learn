

#ifndef _BSP_WWDG_H
#define _BSP_WWDG_H
#include "sys.h"
/* ≥ı ºªØ */
void bsp_InitWwdg(uint8_t _ucTreg, uint8_t _ucWreg, uint32_t WWDG_Prescaler);
void bsp_InitWwdgNVIC(FunctionalState NewState);
void WWDG_IRQHandler(void);
#endif
