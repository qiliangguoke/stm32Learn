

#include "bsp.h"

void bsp_InitSM28BYJ48(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//ʵ�����ṹ��
	
	
}
����һ��ͨ��״̬
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
//��������״̬�����в�ȫ���ܹ� 9 ��״̬�أ���Ӧͷ�ļ��ﲽ�������ͨ���ƶ���
}