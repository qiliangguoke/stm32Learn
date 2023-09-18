/*
*********************************************************************************************************
*
*	模块名称 : 独立按键驱动模块
*	文件名称 : bsp_key.c
*	说    明 : 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/
#include "bsp.h"
/*
*/
static KEY_T s_tBtn[KEY_COUNT];
static KEY_FIFO_T s_tKey;

static void bsp_InitKeyVar(void);
static void bsp_InitKeyHard(void);
static void bsp_DetectKey(uint8_t i);
/*
*********************************************************************************************************
*	函 数 名: IsKeyDownX
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static uint8_t IsKeyDown1(void)
{
	if((WKUP==WKUP_ACTIVE_LEVEL)&&(KEY0!=KEY0_ACTIVE_LEVEL)&&(KEY1!=KEY1_ACTIVE_LEVEL)
		&&(KEY2!=KEY2_ACTIVE_LEVEL))
		return 1;
	else
		return 0;
}
static uint8_t IsKeyDown2(void)
{
	if((WKUP!=WKUP_ACTIVE_LEVEL)&&(KEY0==KEY0_ACTIVE_LEVEL)&&(KEY1!=KEY1_ACTIVE_LEVEL)
		&&(KEY2!=KEY2_ACTIVE_LEVEL))
		return 1;
	else
		return 0;
}
static uint8_t IsKeyDown3(void)
{
	if((WKUP!=WKUP_ACTIVE_LEVEL)&&(KEY0!=KEY0_ACTIVE_LEVEL)&&(KEY1==KEY1_ACTIVE_LEVEL)
		&&(KEY2!=KEY2_ACTIVE_LEVEL))
		return 1;
	else
		return 0;
}
static uint8_t IsKeyDown4(void)
{
	if((WKUP!=WKUP_ACTIVE_LEVEL)&&(KEY0!=KEY0_ACTIVE_LEVEL)&&(KEY1!=KEY1_ACTIVE_LEVEL)
		&&(KEY2==KEY2_ACTIVE_LEVEL))
		return 1;
	else
		return 0;
}
static uint8_t IsKeyDown5(void)/**/
{
	if((WKUP==WKUP_ACTIVE_LEVEL)&&(KEY0==KEY0_ACTIVE_LEVEL)&&(KEY1!=KEY1_ACTIVE_LEVEL)
		&&(KEY2!=KEY2_ACTIVE_LEVEL))
		return 1;
	else
		return 0;
}
static uint8_t IsKeyDown6(void)/**/
{
	if((WKUP!=WKUP_ACTIVE_LEVEL)&&(KEY0==KEY0_ACTIVE_LEVEL)&&(KEY1==KEY1_ACTIVE_LEVEL)
		&&(KEY2!=KEY2_ACTIVE_LEVEL))
		return 1;
	else
		return 0;
}
/*
*********************************************************************************************************
*	函 数 名: bsp_InitKey
*	功能说明: 初始化按键，该函数被bsp_Init()调用。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitKey(void)
{

	bsp_InitKeyVar();/**/
	bsp_InitKeyHard();/**/
	
}
/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_PutKey(uint8_t _KeyCode)
{
	s_tKey.Buf[s_tKey.Write] = _KeyCode;
	if(++s_tKey.Write >= KEY_FIFO_SIZE)
	{
		s_tKey.Write = 0;
	}
}
/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
uint8_t bsp_GetKey(void)
{
	uint8_t ret;
	if(s_tKey.Read == s_tKey.Write)
	{
		return KEY_NONE;
	}else
	{
		ret = s_tKey.Buf[s_tKey.Read];
		if(++s_tKey.Read >= KEY_FIFO_SIZE)
		{
			s_tKey.Read = 0;
		}
		return ret;
	}
}
/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
uint8_t bsp_GetKey2(void)
{
	uint8_t ret;
	if(s_tKey.Read2 == s_tKey.Write)
	{
		return KEY_NONE;
	}else
	{
		ret = s_tKey.Buf[s_tKey.Read2];
		if(++s_tKey.Read2 >= KEY_FIFO_SIZE)
		{
			s_tKey.Read2 = 0;
		}
		return ret;
	}
}
/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID)
{
	return s_tBtn[_ucKeyID].State;
}
/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_SetKeyParam(uint8_t _ucKeyID,uint16_t _LongTime,uint8_t _RepeatSpeed)
{
	s_tBtn[_ucKeyID].LongTime=_LongTime;
	s_tBtn[_ucKeyID].RepeatSpeed=_RepeatSpeed;
	s_tBtn[_ucKeyID].RepeatCount = 0;
}
/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_ClearKey(void)
{
	s_tKey.Read=s_tKey.Write;
}
/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void bsp_InitKeyHard(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 第一步：打开GPIO时钟*/
	RCC_APB2PeriphClockCmd(RCC_ALL_KEY,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	/*关闭 jtag,使能SWD，可以用SWD模式调试*/
	
	/*第二步：配置所有按键GPIO*/
	GPIO_InitStructure.GPIO_Pin = KEY0_GPIO_PIN;   //KEY0端口
	GPIO_InitStructure.GPIO_Mode = KEY0_GPIO_MODE; //KEY0端口模式
	GPIO_Init(KEY0_GPIO_PORT,&GPIO_InitStructure); //初始化KEY0
	
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;   //KEY1端口
	GPIO_InitStructure.GPIO_Mode = KEY1_GPIO_MODE; //KEY1端口模式
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStructure); //初始化KEY1
	
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;   //KEY2端口
	GPIO_InitStructure.GPIO_Mode = KEY2_GPIO_MODE; //KEY2端口模式
	GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStructure); //初始化KEY2
	
	GPIO_InitStructure.GPIO_Pin = WKUP_GPIO_PIN;   //WKUP端口
	GPIO_InitStructure.GPIO_Mode = WKUP_GPIO_MODE; //WKUP端口模式
	GPIO_Init(WKUP_GPIO_PORT,&GPIO_InitStructure); //初始化WKUP
}
/**/
static void bsp_InitKeyVar(void)
{
	uint8_t i;
	/**/
	s_tKey.Read=0;
	s_tKey.Write=0;
	s_tKey.Read2=0;
	/**/
	for(i=0;i<KEY_COUNT;i++)
	{
		s_tBtn[i].LongTime=KEY_LONG_TIME;
		s_tBtn[i].Count=KEY_FILTER_TIME/2;
		s_tBtn[i].State=0;
		s_tBtn[i].RepeatSpeed=0;
		s_tBtn[i].RepeatCount=0;
	}
	/**/
	s_tBtn[0].IsKeyDownFunc=IsKeyDown1;
	s_tBtn[1].IsKeyDownFunc=IsKeyDown2;
	s_tBtn[2].IsKeyDownFunc=IsKeyDown3;
	s_tBtn[3].IsKeyDownFunc=IsKeyDown4;
		
	/**/
	s_tBtn[4].IsKeyDownFunc=IsKeyDown5;
	s_tBtn[5].IsKeyDownFunc=IsKeyDown6;
}
/*
*********************************************************************************************************
*	函 数 名: 
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void bsp_DetectKey(uint8_t i)
{
	KEY_T *pBtn;
	/**/
	pBtn=&s_tBtn[i];
	if(pBtn ->IsKeyDownFunc())
	{
		if(pBtn->Count<KEY_FILTER_TIME)
		{
			pBtn->Count=KEY_FILTER_TIME;
		}
		else if(pBtn->Count<2*KEY_FILTER_TIME)
		{
			pBtn ->Count++;
		}
		else
		{
			if(pBtn->State==0)
			{
				pBtn->State=1;
				/**/
				bsp_PutKey((uint8_t)(3*i+1));
			}
			if(pBtn->LongTime>0)
			{
				if(pBtn->LongCount < pBtn->LongTime)
				{
					if(++pBtn->LongCount == pBtn->LongTime)
					{
						bsp_PutKey((uint8_t)(3*i+3));
					}
				}
				else
				{
					if(pBtn->RepeatSpeed>0)
					{
						if(++pBtn->RepeatCount >= pBtn->RepeatSpeed)
						{
							pBtn->RepeatCount=0;
							bsp_PutKey((uint8_t)(3*i+1));
						}
					}
				}
			}
		}
	}	
			else{
				if(pBtn->Count>KEY_FILTER_TIME)
				{
					pBtn->Count=KEY_FILTER_TIME;
				}else if(pBtn->Count!=0)
				{
					pBtn->Count--;
				}else
				{
					if(pBtn ->State==1)
				{
					pBtn->State=0;
					/**/
					bsp_PutKey((uint8_t)(3*i+2));
				}
			}
				pBtn->LongCount=0;
				pBtn->RepeatCount=0;
		}
	}

/*
***************************************************************************
*          函 数 名:bsp_KeyScan
*          功能说明：扫描指定按键
*          形   参：按键形参
*          返 回 值：有键盘还是无键按下 
***************************************************************************
*/
void bsp_KeyScan(void)
{
	uint8_t i;
	for(i=0;i<KEY_COUNT;i++)
	{
		bsp_DetectKey(i);
	}
}
/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
