#ifndef __BSP_SYN6288_H
#define __BSP_SYN6288_H
#include "sys.h" 
#define SYN6288_TEMP_BUF_LEN 10 //���� CO2_TEMP_BUF_LEN ���峤��Ϊ 10 ���ֽ�
//CO2 ��ȡ����
uint16_t SYN6288_READ(void);
#endif