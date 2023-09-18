
/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : bsp��_key.h
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����2023-5-1        ���߹�����     ˵��
*		V1.0    
*
*	Copyright (C), 2014-2023, �����׵���
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
*	�� �� ��:IsKeyDown1
*	����˵��: �ж�wkup�Ƿ񱻰���
*	��    �Σ���
*	�� �� ֵ: ��ΰ��·���1�����򷵻�0
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
*	�� �� ��:IsKeyDown2
*	����˵��:�ж�key0�Ƿ񱻰��� 
*	��    �Σ�
*	�� �� ֵ: 
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
*	�� �� ��:IsKeyDown3
*	����˵��: �ж�key1�Ƿ񱻰���
*	��    �Σ���
*	�� �� ֵ: ��ΰ��·���1�����򷵻�0
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
*	�� �� ��:IsKeyDown4
*	����˵��: �ж�key2�Ƿ񱻰���
*	��    �Σ���
*	�� �� ֵ: ��ΰ��·���1�����򷵻�0
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
*	�� �� ��:IsKeyDown5
*	����˵��: �ж�wkup��key0�Ƿ񱻰���
*	��    �Σ���
*	�� �� ֵ: ��ΰ��·���1�����򷵻�0
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
*	�� �� ��:IsKeyDown6
*	����˵��: �ж�key0��key1�Ƿ񱻰���
*	��    �Σ���
*	�� �� ֵ: ��ΰ��·���1�����򷵻�0
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
*	�� �� ��:bsp_InitKey
*	����˵��: ��ʼ������
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
 void bsp_InitKey(void){
	bsp_InitKeyVar();
	 bsp_InitKeyHard();
		
	}
 /*
 *********************************************************************************************************
 *	�� �� ��:bsp_PutKey
 *	����˵��:���������������ǽ�����ɨ�赽�ļ��뱣�浽�����У��ȴ����������ȡ������ 
 *	��    �Σ�
 *	�� �� ֵ: 
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
*	�� �� ��:bsp_GetKey
*	����˵��: �ú����������ǴӰ���ɨ���ѭ�������л�ȡ����ļ���ֵ��������������Ӧ������ɾ����
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
uint8_t bsp_GetKey(void)
{
		uint8_t ret;					
	if(s_tKey.Read==s_tKey.Write)		//��ʾ������û�м������ݣ�ֱ�ӷ���ֵ
	{
		return KEY_NONE;
	}
	else{
		
		ret=s_tKey.Buf[s_tKey.Read];	//������ļ���ֵ����ret
		if(++s_tKey.Read>=KEY_FIFO_SIZE)//��������˶��еĴ�С KEY_FIFO_SIZE���� Read ��ֵ����Ϊ 0��ʵ��ѭ�����еĹ��ܡ�
		{
			s_tKey.Read=0;
		}
		return ret;
	}
}
/*
*********************************************************************************************************
*	�� �� ��:bsp_GetKey2
*	����˵��: �ú����������ǴӰ���ɨ���ѭ�������л�ȡ����ļ���ֵ��������������Ӧ������ɾ����
*	��    �Σ�
*	�� �� ֵ: 
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
*	�� �� ��:bsp_GetKeyState
*	����˵��: ��ȡ��������
*	��    �Σ�������id
*	�� �� ֵ: ״ֵ̬
********************************************************************************************************
*/
uint8_t bsp_GetKeyState(KEY_ID_E _ucKeyID){
	
	return s_tBtn[_ucKeyID].State;
}

/*
*********************************************************************************************************
*	�� �� ��:bsp_SetKeyParam
*	����˵��: ���ð�������
*	��    �Σ�_ucKeyID ����id   _LongTime   ����ʱ��   _RepeatSpeed�����ٶ�
*	�� �� ֵ: 
********************************************************************************************************
*/
void bsp_SetKeyParam(uint8_t _ucKeyID,uint16_t _LongTime,uint8_t _RepeatSpeed)
{
	s_tBtn[_ucKeyID].LongTime=_LongTime;//�����¼�
	s_tBtn[_ucKeyID].RepeatSpeed=_RepeatSpeed;//�������ٶ�
	s_tBtn[_ucKeyID].RepeatSpeed=0;//����������
}
/*
*********************************************************************************************************
*	�� �� ��:bsp_ClearKey
*	����˵��: ��հ�������
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
void bsp_ClearKey(void)
{
	s_tKey.Read=s_tKey.Write;
}
/*
*********************************************************************************************************
*	�� �� ��:bsp_InitKeyHard
*	����˵��: ��ʱ��
*	��    �Σ�
*	�� �� ֵ: 
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
*	�� �� ��:bsp_InitKeyVar
*	����˵��: ��ʼ������
*	��    �Σ�
*	�� �� ֵ: 
********************************************************************************************************
*/
static void bsp_InitKeyVar(void)
{
	uint8_t i;
	
	s_tKey.Read=0;//��ʼ��������ָ��s_tKey.Read
	s_tKey.Write=0;//��ʼ��������ָ��s_tKey.Write
	s_tKey.Read2=0;//��ʼ��������ָ��s_tKey.Read2
	for(i=0;i<KEY_COUNT;i++){
	s_tBtn[i].LongTime=KEY_LONG_TIME;//���ó����¼�
		s_tBtn[i].Count=KEY_FILTER_TIME/2;//�����˲�
		s_tBtn[i].State=0;//����״̬
		//s_tBtn[i].KeyCodeDown=3*i+1;
		//s_tBtn[i].KeyCodeUp=3*i+2;
		//s_tBtn[i].KeyCodeLong=3*i+3;
		
		s_tBtn[i].RepeatSpeed=0;//�����������ٶ�
		s_tBtn[i].RepeatCount=0;//������ʱ��
	
	}
	s_tBtn[KID_K1].LongTime=100;
	//s_tBtn[KID_K1].RepeatSpeed=5;
	
	//�жϰ��°���������
	s_tBtn[0].IsKeyDownFunc=IsKeyDown1;
	s_tBtn[1].IsKeyDownFunc=IsKeyDown2;
	s_tBtn[2].IsKeyDownFunc=IsKeyDown3;
	s_tBtn[3].IsKeyDownFunc=IsKeyDown4;
	
	s_tBtn[4].IsKeyDownFunc=IsKeyDown5;
	s_tBtn[5].IsKeyDownFunc=IsKeyDown6;
	
}
static void bsp_DetectKey(uint8_t i)
{
	KEY_T *pBtn;//������һ����ΪpBtn�İ����ṹ��ָ��
	
	pBtn=&s_tBtn[i];//�������ṹ������s_tBtn�еĵ�i��Ԫ�صĵ�ַ��ֵ��pBtn��
	if(pBtn->IsKeyDownFunc())//�жϰ����Ƿ񱻰���
	{
		//��鰴���Ƿ��ڹ���ʱ���ڣ�����ǣ��򽫼���������Ϊ����ʱ��
		if(pBtn->Count<KEY_FILTER_TIME)
		{
			pBtn->Count=KEY_FILTER_TIME;
		}
		else if(pBtn->Count<2*KEY_FILTER_TIME)
		{
			pBtn->Count++;
		}
		else{
			//�������stateΪ0
			if(pBtn->State==0)
			{
				//��state��ʾΪ����				
				pBtn->State=1;
				//����ֵ�ŵ�fifo��
				
				bsp_PutKey((uint8_t)(3*i+1));
							
			}
			
			//�������ʱ�����0�����ʾ�г���
			if(pBtn->LongTime>0){
				
				if(pBtn->LongCount<pBtn->LongTime)
				{
					//����������������ڳ����趨ʱ�䣬
					if(++pBtn->LongCount==pBtn->LongTime)
					{
						//��״̬�趨Ϊ3
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
	else									//����ɿ���ť
	{
		if (pBtn->Count>KEY_FILTER_TIME)	//���С���˲�����
        {
        	pBtn->Count=KEY_FILTER_TIME;
        }
		else if (pBtn->Count!=0)
        {
			pBtn->Count--;
        }			
        else
        {
			if (pBtn->State==1)				//�������״̬Ϊ1������ֵ����fifo
            {
				
            	pBtn->State=0;				
				
				bsp_PutKey((uint8_t)(3*i+2));
            }
			else if(pBtn->State==3){		//�������Ϊ3����Ϊ����
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
*	�� �� ��: bsp_KeyScan
*	����˵��: ɨ�����а���������������systick�ж������Եĵ���
*	��    �Σ�
*	�� �� ֵ: 
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

