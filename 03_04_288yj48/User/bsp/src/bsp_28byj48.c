

#include "bsp.h"

void bsp_InitSM28BYJ48(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//实例化结构体
	
	
}
设置一下通电状态
static void motPowerOn(uint8_t _ucMode)
{
if (_ucMode == SM_OFF)
{
SM28BYJ48_A = 0;
SM28BYJ48_B = 0;
SM28BYJ48_C = 0;
SM28BYJ48_D = 0;
}
else if (_ucMode == SM_A)
{
SM28BYJ48_A = 1;
SM28BYJ48_B = 0;
SM28BYJ48_C = 0;
SM28BYJ48_D = 0;
}
//还有其它状态，自行补全，总共 9 个状态呢，对应头文件里步进电机导通控制定义
}