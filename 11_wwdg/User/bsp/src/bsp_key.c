
/*
*********************************************************************************************************
*
*	模块名称 : 模块
*	文件名称 : bsp—_key.h
*	说    明 : 
*	修改记录 :
*		版本号  日期2023-5-1        作者郭文龙     说明
*		V1.0    
*
*	Copyright (C), 2014-2023, 德致伦电子
*
*********************************************************************************************************
*/

#include "bsp.h"



static KEY_T s_tBtn[KEY_COUNT];
static KEY_FIFO_T s_tKey;

static void bsp_InitKeyVar(void);
static void bsp_InitKeyHard(void);
static void bsp_DetectKey(uint8_t i);
/*
*********************************************************************************************************
*	函 数 名:IsKeyDown1
*	功能说明: 判断wkup是否被按下
*	形    参：无
*	返 回 值: 如何按下返回1，否则返回0
********************************************************************************************************
*/
static uint8_t IsKeyDown1(void)
{
	if((WKUP==WKUP_ACTIVE_LEVEL)&&(KEY0!=KEY0_ACTIVE_LEVEL)
		&&(KEY1!=KEY1_ACTIVE_LEVEL)&&(KEY2!=KEY2_ACTIVE_LEVEL))
	return 1;
	else
		return 0;
}
/*
*********************************************************************************************************
*	函 数 名:IsKeyDown2
*	功能说明:判断key0是否被按下 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/

static uint8_t IsKeyDown2(void)
{
	if((WKUP!=WKUP_ACTIVE_LEVEL)&&(KEY0==KEY0_ACTIVE_LEVEL)
		&&(KEY1!=KEY1_ACTIVE_LEVEL)&&(KEY2!=KEY2_ACTIVE_LEVEL))
	return 1;
	else
		return 0;
}
/*
*********************************************************************************************************
*	函 数 名:IsKeyDown3
*	功能说明: 判断key1是否被按下
*	形    参：无
*	返 回 值: 如何按下返回1，否则返回0
********************************************************************************************************
*/
static uint8_t IsKeyDown3(void)
{
	if((WKUP!=WKUP_ACTIVE_LEVEL)&&(KEY0!=KEY0_ACTIVE_LEVEL)
		&&(KEY1==KEY1_ACTIVE_LEVEL)&&(KEY2!=KEY2_ACTIVE_LEVEL))
	return 1;
	else
		return 0;
}
/*
*********************************************************************************************************
*	函 数 名:IsKeyDown4
*	功能说明: 判断key2是否被按下
*	形    参：无
*	返 回 值: 如何按下返回1，否则返回0
********************************************************************************************************
*/
static uint8_t IsKeyDown4(void)
{
	if((WKUP!=WKUP_ACTIVE_LEVEL)&&(KEY0!=KEY0_ACTIVE_LEVEL)
		&&(KEY1!=KEY1_ACTIVE_LEVEL)&&(KEY2==KEY2_ACTIVE_LEVEL))
	return 1;
	else
		return 0;
}
/*
*********************************************************************************************************
*	函 数 名:IsKeyDown5
*	功能说明: 判断wkup和key0是否被按下
*	形    参：无
*	返 回 值: 如何按下返回1，否则返回0
********************************************************************************************************
*/
static uint8_t IsKeyDown5(void)
{
	if((WKUP==WKUP_ACTIVE_LEVEL)&&(KEY0==KEY0_ACTIVE_LEVEL)
		&&(KEY1!=KEY1_ACTIVE_LEVEL)&&(KEY2!=KEY2_ACTIVE_LEVEL))
	return 1;
	else
		return 0;
}
/*
*********************************************************************************************************
*	函 数 名:IsKeyDown6
*	功能说明: 判断key0和key1是否被按下
*	形    参：无
*	返 回 值: 如何按下返回1，否则返回0
********************************************************************************************************
*/
static uint8_t IsKeyDown6(void)
{
	if((WKUP!=WKUP_ACTIVE_LEVEL)&&(KEY0==KEY0_ACTIVE_LEVEL)
		&&(KEY1==KEY1_ACTIVE_LEVEL)&&(KEY2!=KEY2_ACTIVE_LEVEL))
	return 1;
	else
		return 0;
}
/*
*********************************************************************************************************
*	函 数 名:bsp_InitKey
*	功能说明: 初始化函数
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
 void bsp_InitKey(void){
	bsp_InitKeyVar();
	 bsp_InitKeyHard();
		
	}
 /*
 *********************************************************************************************************
 *	函 数 名:bsp_PutKey
 *	功能说明:整个函数的作用是将按键扫描到的键码保存到队列中，等待其他程序读取并处理。 
 *	形    参：
 *	返 回 值: 
 ********************************************************************************************************
 */
void bsp_PutKey(uint8_t _KeyCode){

	s_tKey.Buf[s_tKey.Write]=_KeyCode;
	if(++s_tKey.Write>=KEY_FIFO_SIZE){
			s_tKey.Write=0;
	}

}
/*
*********************************************************************************************************
*	函 数 名:bsp_GetKey
*	功能说明: 该函数的作用是从按键扫描的循环队列中获取最早的键码值，并将队列中相应的数据删除。
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
uint8_t bsp_GetKey(void)
{
		uint8_t ret;					
	if(s_tKey.Read==s_tKey.Write)		//表示队列中没有键码数据，直接返回值
	{
		return KEY_NONE;
	}
	else{
		
		ret=s_tKey.Buf[s_tKey.Read];	//将最早的键码值存入ret
		if(++s_tKey.Read>=KEY_FIFO_SIZE)//如果超出了队列的大小 KEY_FIFO_SIZE，则将 Read 的值重置为 0，实现循环队列的功能。
		{
			s_tKey.Read=0;
		}
		return ret;
	}
}
/*
*********************************************************************************************************
*	函 数 名:bsp_GetKey2
*	功能说明: 该函数的作用是从按键扫描的循环队列中获取最早的键码值，并将队列中相应的数据删除。
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
uint8_t bsp_GetKey2(void)
{
	uint8_t ret;
	if (s_tKey.Read2==s_tKey.Write)
    {
		return KEY_NONE;
    }
    else
    {
		ret=s_tKey.Buf[s_tKey.Read2+1];
		if (++s_tKey.Read2>=KEY_FIFO_SIZE)
        {
        	s_tKey.Read2=0;
        }
		return ret;
		
    }
}

/*
*********************************************************************************************************
*	函 数 名:bsp_GetKeyState
*	功能说明: 读取按键参数
*	形    参：按键的id
*	返 回 值: 状态值
********************************************************************************************************
*/
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID){
	
	return s_tBtn[_ucKeyID].State;
}

/*
*********************************************************************************************************
*	函 数 名:bsp_SetKeyParam
*	功能说明: 设置按键参数
*	形    参：_ucKeyID 按键id   _LongTime   长按时间   _RepeatSpeed连发速度
*	返 回 值: 
********************************************************************************************************
*/
void bsp_SetKeyParam(uint8_t _ucKeyID,uint16_t _LongTime,uint8_t _RepeatSpeed)
{
	s_tBtn[_ucKeyID].LongTime=_LongTime;//长按事件
	s_tBtn[_ucKeyID].RepeatSpeed=_RepeatSpeed;//连发的速度
	s_tBtn[_ucKeyID].RepeatSpeed=0;//连发计数器
}
/*
*********************************************************************************************************
*	函 数 名:bsp_ClearKey
*	功能说明: 清空按键缓存
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_ClearKey(void)
{
	s_tKey.Read=s_tKey.Write;
}
/*
*********************************************************************************************************
*	函 数 名:bsp_InitKeyHard
*	功能说明: 打开时钟
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
static void bsp_InitKeyHard(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_ALL_KEY,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	
	
	GPIO_InitStructure.GPIO_Pin=WKUP_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode=WKUP_GPIO_MODE;
	GPIO_Init(WKUP_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=KEY0_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode=KEY0_GPIO_MODE;
	GPIO_Init(KEY0_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=KEY1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode=KEY1_GPIO_MODE;
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=KEY2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode=KEY2_GPIO_MODE;
	GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStructure);
}
/*
*********************************************************************************************************
*	函 数 名:bsp_InitKeyVar
*	功能说明: 初始化按键
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
static void bsp_InitKeyVar(void)
{
	uint8_t i;
	
	s_tKey.Read=0;//初始化按键读指针s_tKey.Read
	s_tKey.Write=0;//初始化按键读指针s_tKey.Write
	s_tKey.Read2=0;//初始化按键读指针s_tKey.Read2
	for(i=0;i<KEY_COUNT;i++){
	s_tBtn[i].LongTime=KEY_LONG_TIME;//设置长按事件
		s_tBtn[i].Count=KEY_FILTER_TIME/2;//设置滤波
		s_tBtn[i].State=0;//设置状态
		//s_tBtn[i].KeyCodeDown=3*i+1;
		//s_tBtn[i].KeyCodeUp=3*i+2;
		//s_tBtn[i].KeyCodeLong=3*i+3;
		
		s_tBtn[i].RepeatSpeed=0;//按键连发的速度
		s_tBtn[i].RepeatCount=0;//连发计时器
	
	}
	s_tBtn[KID_K1].LongTime=100;
	//s_tBtn[KID_K1].RepeatSpeed=5;
	
	//判断按下按键的属性
	s_tBtn[0].IsKeyDownFunc=IsKeyDown1;
	s_tBtn[1].IsKeyDownFunc=IsKeyDown2;
	s_tBtn[2].IsKeyDownFunc=IsKeyDown3;
	s_tBtn[3].IsKeyDownFunc=IsKeyDown4;
	
	s_tBtn[4].IsKeyDownFunc=IsKeyDown5;
	s_tBtn[5].IsKeyDownFunc=IsKeyDown6;
	
}
static void bsp_DetectKey(uint8_t i)
{
	KEY_T *pBtn;//定义了一个名为pBtn的按键结构体指针
	
	pBtn=&s_tBtn[i];//将按键结构体数组s_tBtn中的第i个元素的地址赋值给pBtn：
	if(pBtn->IsKeyDownFunc())//判断按键是否被按下
	{
		//检查按键是否在过滤时间内，如果是，则将计数器重置为过滤时间
		if(pBtn->Count<KEY_FILTER_TIME)
		{
			pBtn->Count=KEY_FILTER_TIME;
		}
		else if(pBtn->Count<2*KEY_FILTER_TIME)
		{
			pBtn->Count++;
		}
		else{
			//如果按键state为0
			if(pBtn->State==0)
			{
				//则state表示为按下				
				pBtn->State=1;
				//将键值放到fifo里
				
				bsp_PutKey((uint8_t)(3*i+1));
							
			}
			
			//如果长按时间大于0，则表示有长按
			if(pBtn->LongTime>0){
				
				if(pBtn->LongCount<pBtn->LongTime)
				{
					//如果长按计数器等于长按设定时间，
					if(++pBtn->LongCount==pBtn->LongTime)
					{
						//将状态设定为3
						pBtn->State=3;
						bsp_PutKey((uint8_t)(3*i+3));
					}
					
				}
				else
				{
					if(pBtn->RepeatSpeed>0)
					{
						if (++pBtn->RepeatSpeed>=pBtn->RepeatSpeed)
						{
							pBtn->RepeatCount=0;
							//bsp_PutKey((uint8_t)(3*i+1));
						}
					}
				}
			}
		}
	}
	else									//如果松开按钮
	{
		if (pBtn->Count>KEY_FILTER_TIME)	//如果小于滤波，则将
        {
        	pBtn->Count=KEY_FILTER_TIME;
        }
		else if (pBtn->Count!=0)
        {
			pBtn->Count--;
        }			
        else
        {
			if (pBtn->State==1)				//如果按键状态为1，将键值传入fifo
            {
				
            	pBtn->State=0;				
				
				bsp_PutKey((uint8_t)(3*i+2));
            }
			else if(pBtn->State==3){		//如果按键为3，则为长按
				pBtn->State=0;	
				bsp_PutKey((uint8_t)(3*i+2));
			}
        }
		pBtn->LongCount=0;
		pBtn->RepeatCount=0;
	}
}
/*
*********************************************************************************************************
*	函 数 名: bsp_KeyScan
*	功能说明: 扫描所有按键。非阻塞，被systick中断周期性的调用
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
void bsp_KeyScan(void)
{
	uint8_t i;
	for(i=0;i<KEY_COUNT;i++)
    {
		bsp_DetectKey(i);
		
    }
}

