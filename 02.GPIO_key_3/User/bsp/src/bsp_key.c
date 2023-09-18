#include "bsp.h"


/*
*********************************************************************************************************
*	函 数 名:
*	功能说明: 
*	形    参：
*	返 回 值: 
********************************************************************************************************
*/
static KEY_T s_tBtn[KEY_COUNT];
static KEY_FIFO_T s_tKey;

static void bsp_InitKeyVar(void);
static void bsp_InitKeyHard(void);
static void bsp_DetectKey(uint8_t i);

static uint8_t IsKeyDown1(void)
{
	if((WKUP==WKUP_ACTIVE_LEVEL)&&(KEY0!=KEY0_ACTIVE_LEVEL)
		&&(KEY1!=KEY1_ACTIVE_LEVEL)&&(KEY2!=KEY2_ACTIVE_LEVEL))
	return 1;
	else
		return 0;
}


static uint8_t IsKeyDown2(void)
{
	if((WKUP!=WKUP_ACTIVE_LEVEL)&&(KEY0==KEY0_ACTIVE_LEVEL)
		&&(KEY1!=KEY1_ACTIVE_LEVEL)&&(KEY2!=KEY2_ACTIVE_LEVEL))
	return 1;
	else
		return 0;
}

static uint8_t IsKeyDown3(void)
{
	if((WKUP!=WKUP_ACTIVE_LEVEL)&&(KEY0!=KEY0_ACTIVE_LEVEL)
		&&(KEY1==KEY1_ACTIVE_LEVEL)&&(KEY2!=KEY2_ACTIVE_LEVEL))
	return 1;
	else
		return 0;
}
static uint8_t IsKeyDown4(void)
{
	if((WKUP!=WKUP_ACTIVE_LEVEL)&&(KEY0!=KEY0_ACTIVE_LEVEL)
		&&(KEY1!=KEY1_ACTIVE_LEVEL)&&(KEY2==KEY2_ACTIVE_LEVEL))
	return 1;
	else
		return 0;
}
static uint8_t IsKeyDown5(void)
{
	if((WKUP==WKUP_ACTIVE_LEVEL)&&(KEY0==KEY0_ACTIVE_LEVEL)
		&&(KEY1!=KEY1_ACTIVE_LEVEL)&&(KEY2!=KEY2_ACTIVE_LEVEL))
	return 1;
	else
		return 0;
}
static uint8_t IsKeyDown6(void)
{
	if((WKUP!=WKUP_ACTIVE_LEVEL)&&(KEY0==KEY0_ACTIVE_LEVEL)
		&&(KEY1==KEY1_ACTIVE_LEVEL)&&(KEY2!=KEY2_ACTIVE_LEVEL))
	return 1;
	else
		return 0;
}

 void bsp_InitKey(void){
	bsp_InitKeyVar();
	 bsp_InitKeyHard();
		
		
	}
 
void bsp_PutKey(uint8_t _KeyCode){

	s_tKey.Buf[s_tKey.Write]=_KeyCode;
	if(++s_tKey.Write>=KEY_FIFO_SIZE){
			s_tKey.Write=0;
	}

}
uint8_t bsp_GetKey(void)
{
		uint8_t ret;
	if(s_tKey.Read==s_tKey.Write)
	{
		return KEY_NONE;
	}
	else{
		
		ret=s_tKey.Buf[s_tKey.Read];
		if(++s_tKey.Read>=KEY_FIFO_SIZE)
		{
			s_tKey.Read=0;
		}
		return ret;
	}
}
uint8_t bsp_GetKey2(void)
{
	uint8_t ret;
	if (s_tKey.Read2==s_tKey.Write)
    {
		return KEY_NONE;
    }
    else
    {
		ret=s_tKey.Buf[s_tKey.Read2];
		if (++s_tKey.Read2>=KEY_FIFO_SIZE)
        {
        	s_tKey.Read2=0;
        }
		return ret;
    }
}
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID){
	
	return s_tBtn[_ucKeyID].State;
}
void bsp_SetKeyParam(uint8_t _ucKeyID,uint16_t _LongTime,uint8_t _RepeatSpeed)
{
	s_tBtn[_ucKeyID].LongTime=_LongTime;
	s_tBtn[_ucKeyID].RepeatSpeed=_RepeatSpeed;
	s_tBtn[_ucKeyID].RepeatSpeed=0;
}

void bsp_ClearKey(void)
{
	s_tKey.Read=s_tKey.Write;
}
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
static void bsp_InitKeyVar(void)
{
	uint8_t i;
	
	s_tKey.Read=0;
	s_tKey.Write=0;
	s_tKey.Read2=0;
	for(i=0;i<KEY_COUNT;i++){
	s_tBtn[i].LongTime=KEY_LONG_TIME;
		s_tBtn[i].Count=KEY_FILTER_TIME/2;
		s_tBtn[i].State=0;
		
		
		s_tBtn[i].RepeatSpeed=0;
		s_tBtn[i].RepeatSpeed=0;
	
	}
	
	s_tBtn[0].IsKeyDownFunc=IsKeyDown1;
	s_tBtn[1].IsKeyDownFunc=IsKeyDown2;
	s_tBtn[2].IsKeyDownFunc=IsKeyDown3;
	s_tBtn[3].IsKeyDownFunc=IsKeyDown4;
	
	s_tBtn[4].IsKeyDownFunc=IsKeyDown5;
	s_tBtn[5].IsKeyDownFunc=IsKeyDown6;
	
}
static void bsp_DetectKey(uint8_t i)
{
	KEY_T *pBtn;
	
	pBtn=&s_tBtn[i];
	if(pBtn->IsKeyDownFunc())
	{
		if(pBtn->Count<KEY_FILTER_TIME)
		{
			pBtn->Count=KEY_FILTER_TIME;
		}
		else if(pBtn->Count<2*KEY_FILTER_TIME)
		{
			pBtn->Count++;
		}
		else{
			if(pBtn->State==0)
			{
				pBtn->State=1;
				bsp_PutKey((uint8_t)(3*i+1));
			}
			if(pBtn->LongTime>0){
				if(pBtn->LongCount<pBtn->LongTime)
				{
					if(++pBtn->LongCount==pBtn->LongTime)
					{
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
							bsp_PutKey((uint8_t)(3*i+1));
						}
					}
				}
			}
		}
	}
	else
	{
		if (pBtn->Count>KEY_FILTER_TIME)
        {
        	pBtn->Count=KEY_FILTER_TIME;
        }
		else if (pBtn->Count!=0)
        {
			pBtn->Count--;
        }
        else
        {
			if (pBtn->State==1)
            {
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
*	函 数 名:
*	功能说明: 
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
