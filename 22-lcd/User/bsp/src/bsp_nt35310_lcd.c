#include "bsp.h"
#include "font.h" 
	   
//////////////////////////////////////////////////////////////////////////////////	 
//3.5��TFTҺ������ 
//֧������IC�ͺ�:NT35310	    	
//********************************************************************************

//LCD�Ļ�����ɫ�ͱ���ɫ	   
uint16_t POINT_COLOR = 0x0000;	//������ɫ
uint16_t BACK_COLOR = 0xFFFF;	//����ɫ 
  
//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;

//���ڱ��ļ���ʹ�õĺ���
static void TFTLCD_GPIO_Config ( void );
static void TFTLCD_FSMC_Config ( void );
static void NT35310_REG_Config ( void );


/*
*********************************************************************************************************
*	�� �� ��: LCD_WR_REG
*	����˵��: д�Ĵ�������
*	��    ��: regval:�Ĵ���ֵ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_WR_REG(uint16_t regval)
{	
	* ( __IO uint16_t * ) ( FSMC_Addr_NT35310_CMD ) = regval;//д��Ҫд�ļĴ������
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_WR_DATA
*	����˵��: дLCD����
*	��    ��: data:Ҫд���ֵ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_WR_DATA(uint16_t data)
{
	* ( __IO uint16_t * ) ( FSMC_Addr_NT35310_DATA ) = data;
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_RD_DATA
*	����˵��: ��CD����
*	��    ��: ��
*	�� �� ֵ: ����ֵ:������ֵ
*********************************************************************************************************
*/
uint16_t LCD_RD_DATA(void)
{
	return ( * ( __IO uint16_t * ) ( FSMC_Addr_NT35310_DATA ) );
}					   
/*
*********************************************************************************************************
*	�� �� ��: LCD_WriteReg
*	����˵��: д�Ĵ���
*	��    ��: LCD_Reg:�Ĵ�����ַ
*				LCD_RegValue:Ҫд�������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_WriteReg(uint16_t LCD_Reg,uint16_t LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);		//д��Ҫд�ļĴ������
	LCD_WR_DATA(LCD_RegValue);	//д������
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_ReadReg
*	����˵��: ���Ĵ���
*	��    ��: LCD_Reg:�Ĵ�����ַ
*	�� �� ֵ: ����ֵ:����������
*********************************************************************************************************
*/
uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{										   
	LCD_WR_REG(LCD_Reg);		//д��Ҫ���ļĴ������
	delay_us(5);		  
	return LCD_RD_DATA();		//���ض�����ֵ
}   
/*
*********************************************************************************************************
*	�� �� ��: LCD_WriteRAM_Prepare
*	����˵��: ��ʼдGRAM
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_WriteRAM
*	����˵��: LCDдGRAM
*	��    ��: RGB_Code:��ɫֵ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_WriteRAM(uint16_t RGB_Code)
{
	LCD_WR_DATA(RGB_Code);	//дʮ��λGRAM
}
/*
*********************************************************************************************************
*	�� �� ��: opt_delay
*	����˵��: ��mdk -O1ʱ���Ż�ʱ��Ҫ����
*	��    ��: ��ʱi
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void opt_delay(uint8_t i)
{
	while(i--);
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_ReadPoint
*	����˵��: ��ȡ��ĳ�����ɫֵ
*	��    ��: x,y:����
*	�� �� ֵ: ����ֵ:�˵����ɫ
*********************************************************************************************************
*/
uint16_t LCD_ReadPoint(uint16_t x,uint16_t y)
{
 	uint16_t r=0,g=0,b=0;
	if(x>=lcddev.width||y>=lcddev.height)
		return 0;	//�����˷�Χ,ֱ�ӷ���
	
	LCD_SetCursor(x,y);
	LCD_WR_REG(0X2E);//5310���Ͷ�GRAMָ��
    
 	r=LCD_RD_DATA();								//dummy Read	   
	opt_delay(2);	  
 	r=LCD_RD_DATA();  		  						//ʵ��������ɫ
	
 	///NT35310Ҫ��2�ζ���
 	{
		opt_delay(2);	  
		b=LCD_RD_DATA(); 
		g=r&0XFF;		//����NT35310,��һ�ζ�ȡ����RG��ֵ,R��ǰ,G�ں�,��ռ8λ
		g<<=8;
	} 
	return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));	//NT35310��Ҫ��ʽת��һ��
	
}			 
/*
*********************************************************************************************************
*	�� �� ��: LCD_DisplayOn
*	����˵��: LCD������ʾ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_DisplayOn(void)
{					   
	LCD_WR_REG(0X29);	//������ʾ
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_DisplayOff
*	����˵��: LCD�ر���ʾ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_DisplayOff(void)
{	   
	LCD_WR_REG(0X28);	//�ر���ʾ
}   
/*
*********************************************************************************************************
*	�� �� ��: LCD_SetCursor
*	����˵��: ���ù��λ��
*	��    ��: 	Xpos:������
*				Ypos:������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	LCD_WR_REG(lcddev.setxcmd); 
	LCD_WR_DATA(Xpos>>8);LCD_WR_DATA(Xpos&0XFF); 			 
	LCD_WR_REG(lcddev.setycmd); 
	LCD_WR_DATA(Ypos>>8);LCD_WR_DATA(Ypos&0XFF); 		
} 		 
/*
*********************************************************************************************************
*	�� �� ��: LCD_Scan_Dir
*	����˵��: ����LCD���Զ�ɨ�跽��һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.��
*	��    ��: dir:0~7,����8������(���嶨���lcd.h)
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_Scan_Dir(uint8_t dir)
{
	uint16_t regval=0;
	uint16_t temp;  
	
	if( lcddev.dir==1 )
	{
		switch(dir)//����ת��
		{
			case 0:dir=6;break;
			case 1:dir=7;break;
			case 2:dir=4;break;
			case 3:dir=5;break;
			case 4:dir=1;break;
			case 5:dir=0;break;
			case 6:dir=3;break;
			case 7:dir=2;break;	     
		}
	}
	
	switch(dir)//����ת��
	{
		case L2R_U2D://������,���ϵ���
			regval|=(0<<7)|(0<<6)|(0<<5); 
			break;
		case L2R_D2U://������,���µ���
			regval|=(1<<7)|(0<<6)|(0<<5); 
			break;
		case R2L_U2D://���ҵ���,���ϵ���
			regval|=(0<<7)|(1<<6)|(0<<5); 
			break;
		case R2L_D2U://���ҵ���,���µ���
			regval|=(1<<7)|(1<<6)|(0<<5); 
			break;	 
		case U2D_L2R://���ϵ���,������
			regval|=(0<<7)|(0<<6)|(1<<5); 
			break;
		case U2D_R2L://���ϵ���,���ҵ���
			regval|=(0<<7)|(1<<6)|(1<<5); 
			break;
		case D2U_L2R://���µ���,������
			regval|=(1<<7)|(0<<6)|(1<<5); 
			break;
		case D2U_R2L://���µ���,���ҵ���
			regval|=(1<<7)|(1<<6)|(1<<5); 
			break;	 
	}
		   
	LCD_WriteReg(0x36,regval);

	if(regval&0X20)
	{
		if(lcddev.width<lcddev.height)//����X,Y
		{
			temp=lcddev.width;
			lcddev.width=lcddev.height;
			lcddev.height=temp;
		}
	}else  
	{
		if(lcddev.width>lcddev.height)//����X,Y
		{
			temp=lcddev.width;
			lcddev.width=lcddev.height;
			lcddev.height=temp;
		}
	}  
		
	LCD_WR_REG(lcddev.setxcmd); 
	LCD_WR_DATA(0);LCD_WR_DATA(0);
	LCD_WR_DATA((lcddev.width-1)>>8);LCD_WR_DATA((lcddev.width-1)&0XFF);
	LCD_WR_REG(lcddev.setycmd); 
	LCD_WR_DATA(0);LCD_WR_DATA(0);
	LCD_WR_DATA((lcddev.height-1)>>8);LCD_WR_DATA((lcddev.height-1)&0XFF);  
		
  	
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_DrawPoint
*	����˵��: ����
*	��    ��: x,y:����	POINT_COLOR:�˵����ɫ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	LCD_SetCursor(x,y);		//���ù��λ�� 
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	LCD_WR_DATA(POINT_COLOR);
	
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_Fast_DrawPoint
*	����˵��: ���ٻ���
*	��    ��: x,y:����	color:��ɫ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_Fast_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{	   
	LCD_WR_REG(lcddev.setxcmd); 
	LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF);  			 
	LCD_WR_REG(lcddev.setycmd); 
	LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF); 		 	 
	
	LCD_WriteReg(lcddev.wramcmd,color);
	
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_Display_Dir
*	����˵��: ����LCD��ʾ����
*	��    ��: dir:0,������1,����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_Display_Dir(uint8_t dir)
{
	if(dir==0)			//����
	{
		lcddev.dir=0;	//����
		
		lcddev.wramcmd=0X2C;
		lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;  	 

		lcddev.width=320;
		lcddev.height=480;
		
	}else 				//����
	{	  				
		lcddev.dir=1;	//����

		lcddev.wramcmd=0X2C;
		lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;
		
		lcddev.width=480;
		lcddev.height=320; 			
	} 
	LCD_Scan_Dir(DFT_SCAN_DIR);	//Ĭ��ɨ�跽��
}

/*
*********************************************************************************************************
*	�� �� ��: LCD_Set_Window
*	����˵��: ���ô���,���Զ����û������굽�������Ͻ�(sx,sy).�������С:width*height. ��
*	��    ��: 	sx,sy:������ʼ����(���Ͻ�)
*				width,height:���ڿ�Ⱥ͸߶�,�������0!!
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
	uint16_t twidth,theight;
	twidth=sx+width-1;
	theight=sy+height-1;
	
	LCD_WR_REG(lcddev.setxcmd); 
	LCD_WR_DATA(sx>>8); 
	LCD_WR_DATA(sx&0XFF);	 
	LCD_WR_DATA(twidth>>8); 
	LCD_WR_DATA(twidth&0XFF);  
	LCD_WR_REG(lcddev.setycmd); 
	LCD_WR_DATA(sy>>8); 
	LCD_WR_DATA(sy&0XFF); 
	LCD_WR_DATA(theight>>8); 
	LCD_WR_DATA(theight&0XFF); 
}
/*
*********************************************************************************************************
*	�� �� ��: TFTLCD_GPIO_Config
*	����˵��: ��ʼ��IO���ţ�ʱ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void TFTLCD_GPIO_Config ( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE); //ʹ�� FSMC ʱ��
	RCC_APB2PeriphClockCmd(RCC_ALL_LCD,ENABLE); //ʹ�ܶ˿�ʱ��
	/* ���� LCD ������ƹܽ� Ϊ������� */ 
	GPIO_InitStructure.GPIO_Pin = LCD_LED_GPIO_PIN; //������� ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_LED_GPIO_PORT, &GPIO_InitStructure);
	/* ���� FSMC ���Ӧ�Ŀ����� Ϊ�����������
	* FSMC_NEx :LCD-CS
	* FSMC_Ax :LCD-RS
	* FSMC_NWE :LCD-WR
	* FSMC_NOE :LCD-RD
	*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = LCD_CS_GPIO_PIN;
	GPIO_Init(LCD_CS_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_RS_GPIO_PIN;
	GPIO_Init(LCD_RS_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_CS_GPIO_PIN;
	GPIO_Init(LCD_CS_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_WR_GPIO_PIN;
	GPIO_Init(LCD_WR_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_RD_GPIO_PIN;
	GPIO_Init(LCD_RD_GPIO_PORT, &GPIO_InitStructure);
	/* ���� FSMC ���Ӧ��������,FSMC-D0~D15 Ϊ�����������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = LCD_D0_GPIO_PIN;
	GPIO_Init ( LCD_D0_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D1_GPIO_PIN;
	GPIO_Init ( LCD_D1_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D2_GPIO_PIN;
	GPIO_Init ( LCD_D2_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D3_GPIO_PIN;
	GPIO_Init ( LCD_D3_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D4_GPIO_PIN;
	GPIO_Init ( LCD_D4_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D5_GPIO_PIN;
	GPIO_Init ( LCD_D5_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D6_GPIO_PIN;
	GPIO_Init ( LCD_D6_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D7_GPIO_PIN;
	GPIO_Init ( LCD_D7_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D8_GPIO_PIN;
	GPIO_Init ( LCD_D8_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D9_GPIO_PIN;
	GPIO_Init ( LCD_D9_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D10_GPIO_PIN;
	GPIO_Init ( LCD_D10_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D11_GPIO_PIN;
	GPIO_Init ( LCD_D11_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D12_GPIO_PIN;
	GPIO_Init ( LCD_D12_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D13_GPIO_PIN;
	GPIO_Init ( LCD_D13_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D14_GPIO_PIN;
	GPIO_Init ( LCD_D14_GPIO_PORT, & GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = LCD_D15_GPIO_PIN;
	GPIO_Init ( LCD_D15_GPIO_PORT, & GPIO_InitStructure );
	/* �������ź�ʱ������ ------------------------------------*/
}
/*
*********************************************************************************************************
*	�� �� ��: TFTLCD_FSMC_Config
*	����˵��: ��ʼ��FSMC����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void TFTLCD_FSMC_Config ( void )
{
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef writeTiming;
	readWriteTiming.FSMC_AddressSetupTime = 0x01; //��ַ����ʱ�䣨ADDSET��Ϊ 2 �� HCLK 1/36M=27ns
	readWriteTiming.FSMC_AddressHoldTime = 0x00; //��ַ����ʱ�䣨ADDHLD��ģʽ A δ�õ�
	readWriteTiming.FSMC_DataSetupTime = 0x0f; // ���ݱ���ʱ��Ϊ 16 �� HCLK,��ΪҺ������ IC �Ķ����ݵ�ʱ���ٶȲ���̫��
	readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
	readWriteTiming.FSMC_CLKDivision = 0x00;
	readWriteTiming.FSMC_DataLatency = 0x00;
	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A; //ģʽ A 
	 
	writeTiming.FSMC_AddressSetupTime = 0x00; //��ַ����ʱ�䣨ADDSET��Ϊ 1 �� HCLK 
	writeTiming.FSMC_AddressHoldTime = 0x00; //��ַ����ʱ�䣨A
	writeTiming.FSMC_DataSetupTime = 0x03; //���ݱ���ʱ��Ϊ 4 �� HCLK
	writeTiming.FSMC_BusTurnAroundDuration = 0x00;
	writeTiming.FSMC_CLKDivision = 0x00;
	writeTiming.FSMC_DataLatency = 0x00;
	writeTiming.FSMC_AccessMode = FSMC_AccessMode_A; //ģʽ A 
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAMx;// �� �� �� �� ʹ �� NE4 �� Ҳ �� �� ӦBTCR[6],[7]��
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
	FSMC_NORSRAMInitStructure.FSMC_MemoryType=FSMC_MemoryType_SRAM;//
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ 16bit 
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode=FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState; 
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable; //�洢��дʹ��
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ��дʹ�ò�ͬ��ʱ��
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //��дʱ��
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming; //дʱ��
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); //��ʼ�� FSMC ����
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAMx, ENABLE); // ʹ�� BANK1
}

/*
*********************************************************************************************************
*	�� �� ��: NT35310_REG_Config
*	����˵��: ��ʼ��NT35310�Ĵ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void NT35310_REG_Config ( void )
{
	LCD_WR_REG(0xED);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0xFE);

	LCD_WR_REG(0xEE);
	LCD_WR_DATA(0xDE);
	LCD_WR_DATA(0x21);

	LCD_WR_REG(0xF1);
	LCD_WR_DATA(0x01);
	LCD_WR_REG(0xDF);
	LCD_WR_DATA(0x10);

	//VCOMvoltage//
	LCD_WR_REG(0xC4);
	LCD_WR_DATA(0x8F);	  //5f

	LCD_WR_REG(0xC6);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0xE2);LCD_WR_DATA(0xE2);LCD_WR_DATA(0xE2);
	
	LCD_WR_REG(0xBF);
	LCD_WR_DATA(0xAA);

	LCD_WR_REG(0xB0);
	LCD_WR_DATA(0x0D);LCD_WR_DATA(0x00);LCD_WR_DATA(0x0D);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x11);LCD_WR_DATA(0x00);LCD_WR_DATA(0x19);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x21);LCD_WR_DATA(0x00);LCD_WR_DATA(0x2D);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x3D);LCD_WR_DATA(0x00);LCD_WR_DATA(0x5D);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x5D);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xB1);
	LCD_WR_DATA(0x80);LCD_WR_DATA(0x00);LCD_WR_DATA(0x8B);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x96);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x02);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x03);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xB3);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xB4);
	LCD_WR_DATA(0x8B);LCD_WR_DATA(0x00);LCD_WR_DATA(0x96);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xA1);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xB5);
	LCD_WR_DATA(0x02);LCD_WR_DATA(0x00);LCD_WR_DATA(0x03);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x04);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xB6);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xB7);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x3F);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x5E);LCD_WR_DATA(0x00);LCD_WR_DATA(0x64);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x8C);LCD_WR_DATA(0x00);LCD_WR_DATA(0xAC);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xDC);LCD_WR_DATA(0x00);LCD_WR_DATA(0x70);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x90);LCD_WR_DATA(0x00);LCD_WR_DATA(0xEB);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xDC);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xB8);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xBA);
	LCD_WR_DATA(0x24);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xC1);
	LCD_WR_DATA(0x20);LCD_WR_DATA(0x00);LCD_WR_DATA(0x54);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xFF);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA(0x0A);LCD_WR_DATA(0x00);LCD_WR_DATA(0x04);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA(0x3C);LCD_WR_DATA(0x00);LCD_WR_DATA(0x3A);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x39);LCD_WR_DATA(0x00);LCD_WR_DATA(0x37);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x3C);LCD_WR_DATA(0x00);LCD_WR_DATA(0x36);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x32);LCD_WR_DATA(0x00);LCD_WR_DATA(0x2F);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x2C);LCD_WR_DATA(0x00);LCD_WR_DATA(0x29);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x26);LCD_WR_DATA(0x00);LCD_WR_DATA(0x24);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x24);LCD_WR_DATA(0x00);LCD_WR_DATA(0x23);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x3C);LCD_WR_DATA(0x00);LCD_WR_DATA(0x36);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x32);LCD_WR_DATA(0x00);LCD_WR_DATA(0x2F);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x2C);LCD_WR_DATA(0x00);LCD_WR_DATA(0x29);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x26);LCD_WR_DATA(0x00);LCD_WR_DATA(0x24);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x24);LCD_WR_DATA(0x00);LCD_WR_DATA(0x23);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xC4);
	LCD_WR_DATA(0x62);LCD_WR_DATA(0x00);LCD_WR_DATA(0x05);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x84);LCD_WR_DATA(0x00);LCD_WR_DATA(0xF0);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x18);LCD_WR_DATA(0x00);LCD_WR_DATA(0xA4);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x18);LCD_WR_DATA(0x00);LCD_WR_DATA(0x50);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x0C);LCD_WR_DATA(0x00);LCD_WR_DATA(0x17);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x95);LCD_WR_DATA(0x00);LCD_WR_DATA(0xF3);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xE6);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xC5);
	LCD_WR_DATA(0x32);LCD_WR_DATA(0x00);LCD_WR_DATA(0x44);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x65);LCD_WR_DATA(0x00);LCD_WR_DATA(0x76);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x88);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xC6);
	LCD_WR_DATA(0x20);LCD_WR_DATA(0x00);LCD_WR_DATA(0x17);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x01);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xC7);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xC8);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xC9);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0x16);LCD_WR_DATA(0x00);LCD_WR_DATA(0x1C);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x21);LCD_WR_DATA(0x00);LCD_WR_DATA(0x36);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x46);LCD_WR_DATA(0x00);LCD_WR_DATA(0x52);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x64);LCD_WR_DATA(0x00);LCD_WR_DATA(0x7A);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x8B);LCD_WR_DATA(0x00);LCD_WR_DATA(0x99);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xA8);LCD_WR_DATA(0x00);LCD_WR_DATA(0xB9);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xC4);LCD_WR_DATA(0x00);LCD_WR_DATA(0xCA);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xD2);LCD_WR_DATA(0x00);LCD_WR_DATA(0xD9);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xE0);LCD_WR_DATA(0x00);LCD_WR_DATA(0xF3);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA(0x16);LCD_WR_DATA(0x00);LCD_WR_DATA(0x1C);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x22);LCD_WR_DATA(0x00);LCD_WR_DATA(0x36);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x45);LCD_WR_DATA(0x00);LCD_WR_DATA(0x52);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x64);LCD_WR_DATA(0x00);LCD_WR_DATA(0x7A);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x8B);LCD_WR_DATA(0x00);LCD_WR_DATA(0x99);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xA8);LCD_WR_DATA(0x00);LCD_WR_DATA(0xB9);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xC4);LCD_WR_DATA(0x00);LCD_WR_DATA(0xCA);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xD2);LCD_WR_DATA(0x00);LCD_WR_DATA(0xD8);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xE0);LCD_WR_DATA(0x00);LCD_WR_DATA(0xF3);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xE2);
	LCD_WR_DATA(0x05);LCD_WR_DATA(0x00);LCD_WR_DATA(0x0B);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x1B);LCD_WR_DATA(0x00);LCD_WR_DATA(0x34);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x44);LCD_WR_DATA(0x00);LCD_WR_DATA(0x4F);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x61);LCD_WR_DATA(0x00);LCD_WR_DATA(0x79);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x88);LCD_WR_DATA(0x00);LCD_WR_DATA(0x97);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xA6);LCD_WR_DATA(0x00);LCD_WR_DATA(0xB7);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xC2);LCD_WR_DATA(0x00);LCD_WR_DATA(0xC7);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xD1);LCD_WR_DATA(0x00);LCD_WR_DATA(0xD6);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xDD);LCD_WR_DATA(0x00);LCD_WR_DATA(0xF3);LCD_WR_DATA(0x00);
	
	LCD_WR_REG(0xE3);
	LCD_WR_DATA(0x05);LCD_WR_DATA(0x00);LCD_WR_DATA(0xA);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x1C);LCD_WR_DATA(0x00);LCD_WR_DATA(0x33);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x44);LCD_WR_DATA(0x00);LCD_WR_DATA(0x50);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x62);LCD_WR_DATA(0x00);LCD_WR_DATA(0x78);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x88);LCD_WR_DATA(0x00);LCD_WR_DATA(0x97);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xA6);LCD_WR_DATA(0x00);LCD_WR_DATA(0xB7);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xC2);LCD_WR_DATA(0x00);LCD_WR_DATA(0xC7);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xD1);LCD_WR_DATA(0x00);LCD_WR_DATA(0xD5);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xDD);LCD_WR_DATA(0x00);LCD_WR_DATA(0xF3);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xE4);
	LCD_WR_DATA(0x01);LCD_WR_DATA(0x00);LCD_WR_DATA(0x01);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x02);LCD_WR_DATA(0x00);LCD_WR_DATA(0x2A);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x3C);LCD_WR_DATA(0x00);LCD_WR_DATA(0x4B);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x5D);LCD_WR_DATA(0x00);LCD_WR_DATA(0x74);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x84);LCD_WR_DATA(0x00);LCD_WR_DATA(0x93);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xA2);LCD_WR_DATA(0x00);LCD_WR_DATA(0xB3);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xBE);LCD_WR_DATA(0x00);LCD_WR_DATA(0xC4);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xCD);LCD_WR_DATA(0x00);LCD_WR_DATA(0xD3);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xDD);LCD_WR_DATA(0x00);LCD_WR_DATA(0xF3);LCD_WR_DATA(0x00);
	
	LCD_WR_REG(0xE5);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x02);LCD_WR_DATA(0x00);LCD_WR_DATA(0x29);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x3C);LCD_WR_DATA(0x00);LCD_WR_DATA(0x4B);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x5D);LCD_WR_DATA(0x00);LCD_WR_DATA(0x74);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x84);LCD_WR_DATA(0x00);LCD_WR_DATA(0x93);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xA2);LCD_WR_DATA(0x00);LCD_WR_DATA(0xB3);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xBE);LCD_WR_DATA(0x00);LCD_WR_DATA(0xC4);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xCD);LCD_WR_DATA(0x00);LCD_WR_DATA(0xD3);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xDC);LCD_WR_DATA(0x00);LCD_WR_DATA(0xF3);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xE6);
	LCD_WR_DATA(0x11);LCD_WR_DATA(0x00);LCD_WR_DATA(0x34);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x56);LCD_WR_DATA(0x00);LCD_WR_DATA(0x76);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x77);LCD_WR_DATA(0x00);LCD_WR_DATA(0x66);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x88);LCD_WR_DATA(0x00);LCD_WR_DATA(0x99);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xBB);LCD_WR_DATA(0x00);LCD_WR_DATA(0x99);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x66);LCD_WR_DATA(0x00);LCD_WR_DATA(0x55);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x55);LCD_WR_DATA(0x00);LCD_WR_DATA(0x45);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x43);LCD_WR_DATA(0x00);LCD_WR_DATA(0x44);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xE7);
	LCD_WR_DATA(0x32);LCD_WR_DATA(0x00);LCD_WR_DATA(0x55);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x76);LCD_WR_DATA(0x00);LCD_WR_DATA(0x66);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x67);LCD_WR_DATA(0x00);LCD_WR_DATA(0x67);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x87);LCD_WR_DATA(0x00);LCD_WR_DATA(0x99);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xBB);LCD_WR_DATA(0x00);LCD_WR_DATA(0x99);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x77);LCD_WR_DATA(0x00);LCD_WR_DATA(0x44);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x56);LCD_WR_DATA(0x00);LCD_WR_DATA(0x23); LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x33);LCD_WR_DATA(0x00);LCD_WR_DATA(0x45);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xE8);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x99);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x87);LCD_WR_DATA(0x00);LCD_WR_DATA(0x88);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x77);LCD_WR_DATA(0x00);LCD_WR_DATA(0x66);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x88);LCD_WR_DATA(0x00);LCD_WR_DATA(0xAA);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xBB);LCD_WR_DATA(0x00);LCD_WR_DATA(0x99);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x66);LCD_WR_DATA(0x00);LCD_WR_DATA(0x55);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x55);LCD_WR_DATA(0x00);LCD_WR_DATA(0x44);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x44);LCD_WR_DATA(0x00);LCD_WR_DATA(0x55);LCD_WR_DATA(0x00);

	LCD_WR_REG(0xE9);
	LCD_WR_DATA(0xAA);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);

	LCD_WR_REG(0x00);
	LCD_WR_DATA(0xAA);

	LCD_WR_REG(0xCF);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0xF0);
	LCD_WR_DATA(0x00);LCD_WR_DATA(0x50);LCD_WR_DATA(0x00);LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0xF3);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0xF9);
	LCD_WR_DATA(0x06);LCD_WR_DATA(0x10);LCD_WR_DATA(0x29);LCD_WR_DATA(0x00);

	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55);	//66

	LCD_WR_REG(0x11);
	delay_ms(100);
	LCD_WR_REG(0x29);
	LCD_WR_REG(0x35);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0x51);
	LCD_WR_DATA(0xFF);
	LCD_WR_REG(0x53);
	LCD_WR_DATA(0x2C);
	LCD_WR_REG(0x55);
	LCD_WR_DATA(0x82);

}
/*
*********************************************************************************************************
*	�� �� ��: TFTLCD_Init
*	����˵��: ��ʼ��TFT LCD
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void TFTLCD_Init ( void )
{
	TFTLCD_GPIO_Config();
	TFTLCD_FSMC_Config();
	delay_ms(50); // delay 50 ms 
	//���Կ����ǲ��� NT35510
	LCD_WR_REG(0XD4); 
	lcddev.id=LCD_RD_DATA(); //dummy read 
	lcddev.id=LCD_RD_DATA(); //���� 0x01
	lcddev.id=LCD_RD_DATA(); //���� 0x53
	lcddev.id<<=8;
	lcddev.id|=LCD_RD_DATA(); //������� 0x10
	BSP_Printf(" LCD ID:%x\r\n",lcddev.id); //��ӡ LCD ID 
	NT35310_REG_Config ();
	LCD_Display_Dir(0); //ʵ��Ĭ������Ϊ����
	LCD_LED=1; //��������
	LCD_Clear(WHITE);
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_Clear
*	����˵��: ��������
*	��    ��: color:Ҫ���������ɫ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_Clear(uint16_t color)
{
	uint32_t index=0;      
	uint32_t totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 			//�õ��ܵ���
	LCD_SetCursor(0x00,0x0000);			//���ù��λ�� 
	LCD_WriteRAM_Prepare();     		//��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD_WR_DATA(color);
	}
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_Fill
*	����˵��: ��ָ����������䵥����ɫ
*	��    ��: 	(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)  
*				color:Ҫ������ɫ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
	uint16_t i,j;
	uint16_t xlen=0;
	
	xlen=ex-sx+1;	 
	for(i=sy;i<=ey;i++)
	{
		LCD_SetCursor(sx,i);      	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	  
		for(j=0;j<xlen;j++)
		{
			LCD_WR_DATA(color);		//��ʾ��ɫ 
		}	    
	}
	 
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_Color_Fill
*	����˵��: ��ָ�����������ָ����ɫ��
*	��    ��: 	(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)  
*				color:Ҫ������ɫ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{  
	uint16_t height,width;
	uint16_t i,j;
	width=ex-sx+1; 			//�õ����Ŀ��
	height=ey-sy+1;			//�߶�
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)
		{
			LCD_WR_DATA(color[i*width+j]);	//д������
		}
		
	}		  
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_DrawLine
*	����˵��: ����
*	��    ��: 	x1,y1:������� 
*				x2,y2:�յ�����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)
	{
		incx=1; //���õ������� 
	}
	else if(delta_x==0)
	{
		incx=0;//��ֱ��
	}		
	else 
	{
		incx=-1;
		delta_x=-delta_x;
	} 
	if(delta_y>0)
	{
		incy=1;
	}		
	else if(delta_y==0)
	{
		incy=0;//ˮƽ��
	}		
	else
	{
		incy=-1;
		delta_y=-delta_y;
	} 
	if( delta_x>delta_y)
	{
		distance=delta_x; //ѡȡ�������������� 
	}
	else 
	{
		distance=delta_y;
	}		
	for(t=0;t<=distance+1;t++)//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_DrawRectangle
*	����˵��: ������
*	��    ��: (x1,y1),(x2,y2):���εĶԽ�����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_Draw_Circle
*	����˵��: ��ָ��λ�û�һ��ָ����С��Բ
*	��    ��: 	(x,y):���ĵ�
*				r:�뾶
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  
/*
*********************************************************************************************************
*	�� �� ��: LCD_ShowChar
*	����˵��: ��ָ��λ����ʾһ���ַ�
*	��    ��: 	x,y:��ʼ����
*				num:Ҫ��ʾ���ַ�:" "--->"~"
*				size:�����С 12/16/24
*				mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode)
{  							  
    uint8_t temp,t1,t;
	uint16_t y0=y;
	uint8_t csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)
		{
			temp=asc2_1206[num][t]; 	 	//����1206����
		}
		else if(size==16)
		{
			temp=asc2_1608[num][t];	//����1608����
		}
		else if(size==24)
		{
			temp=asc2_2412[num][t];	//����2412����
		}
		else
		{ 
			return;								//û�е��ֿ�
		}
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)
			{
				LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			}
			else if(mode==0)
			{
				LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			}
			temp<<=1;
			y++;
			if(y>=lcddev.height)
			{
				return;		//��������
			}
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev.width)
				{
					return;	//��������
				}
				break;
			}
		}  	 
	}  	    	   	 	  
}   
/*
*********************************************************************************************************
*	�� �� ��: LCD_Pow
*	����˵��: m^n����
*	��    ��: m ���� n ����
*	�� �� ֵ: ����ֵ:m^n�η�.
*********************************************************************************************************
*/
uint32_t LCD_Pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)
	{
		result*=m;    
	}
	return result;
}	
/*
*********************************************************************************************************
*	�� �� ��: LCD_ShowNum
*	����˵��: ��ʾ����,��λΪ0,����ʾ
*	��    ��: 	x,y:��ʼ����
*				num:��ֵ(0~4294967295)
*				len :���ֵ�λ��
*				size:�����С 12/16/24
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
}
/*
*********************************************************************************************************
*	�� �� ��: LCD_ShowxNum
*	����˵��: ��ʾ����,��λΪ0,������ʾ
*	��    ��: 	x,y:��ʼ����
*				num:��ֵ(0~999999999);
*				len:����(��Ҫ��ʾ��λ��)
*				size:�����С 12/16/24
*				mode:	[7]:0,�����;1,���0.
*						[6:1]:����
*						[0]:0,�ǵ�����ʾ;1,������ʾ.
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode)
{  
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)
				{
					LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				}
				else 
				{
					LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
				}
 				continue;
			}else 
			{
				enshow=1;
			}				
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
}		
/*
*********************************************************************************************************
*	�� �� ��: LCD_ShowString
*	����˵��: ��ʾ�ַ���
*	��    ��: 	x,y:��ʼ����
*				width,height:�����С 
*				size:�����С 12/16/24
*				*p:�ַ�����ʼ��ַ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p)
{         
	uint8_t x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width)
		{	x=x0;
			y+=size;
		}
        if(y>=height)
		{
			break;//�˳�
		}
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}


/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
