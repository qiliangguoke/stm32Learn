#ifndef __BSP_SYN6288_H
#define __BSP_SYN6288_H
#include "sys.h" 
#define SYN6288_TEMP_BUF_LEN 10 //定义 CO2_TEMP_BUF_LEN 缓冲长度为 10 个字节
//CO2 读取数据
uint16_t SYN6288_READ(void);
#endif