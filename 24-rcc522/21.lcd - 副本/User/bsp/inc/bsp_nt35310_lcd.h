/*
*********************************************************************************************************
*
*	ģ������ : ģ��
*	�ļ����� : .h
*	˵    �� : 
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    xxx-xx-xx
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/

#ifndef _BSP_NT35310_LCD_H_
#define _BSP_NT35310_LCD_H_

///////////////////////////////////////
/* ͷ�ļ������� */
#include "bsp.h"
#include "sys.h"
///////////////////////////////////////
/* �궨������ */
#define RCC_ALL_LCD ( LCD_CS_GPIO_CLK | LCD_RS_GPIO_CLK | LCD_WR_GPIO_CLK | LCD_RD_GPIO_CLK | LCD_LED_GPIO_CLK \
| LCD_D0_GPIO_CLK | LCD_D1_GPIO_CLK | LCD_D2_GPIO_CLK | LCD_D3_GPIO_CLK \
| LCD_D4_GPIO_CLK | LCD_D5_GPIO_CLK | LCD_D6_GPIO_CLK | LCD_D7_GPIO_CLK \
| LCD_D8_GPIO_CLK | LCD_D9_GPIO_CLK | LCD_D10_GPIO_CLK | LCD_D11_GPIO_CLK \
| LCD_D12_GPIO_CLK | LCD_D13_GPIO_CLK | LCD_D14_GPIO_CLK | LCD_D15_GPIO_CLK \
)


/******�����ź���******/
//��������
#define LCD_LED_GPIO_PIN 	GPIO_Pin_0 //Һ���������ź�
#define LCD_LED_PIN_ID		0 		   //Һ�������������
#define LCD_LED_GPIO_PORT 	GPIOB //Һ������˿ں�
#define LCD_LED_GPIO_CLK 	RCC_APB2Periph_GPIOB //Һ������ʱ��
#define LCD_LED_FUN_OUT 	PBout //Һ����������˿����ú���
//#define LCD_LED_FUN_IN 	PBin //Һ����������˿����ú���

//Ƭѡ����
//FSMC_NE4 Ϊ PG12
#define LCD_CS_GPIO_PIN 	GPIO_Pin_12 //Һ��Ƭѡ���ź�
#define LCD_CS_PIN_ID 		12 //Һ��Ƭѡ�������
#define LCD_CS_GPIO_PORT 	GPIOG //Һ��Ƭѡ�˿ں�
#define LCD_CS_GPIO_CLK 	RCC_APB2Periph_GPIOG //Һ��Ƭѡʱ��
#define LCD_CS_FUN_OUT 		PGout //Һ��Ƭѡ����˿����ú���
//#define LCD_CS_FUN_IN 	PGin //Һ��Ƭѡ����˿����ú���
#define LCD_CS_FSMC_NE_ID 	4 //����Ϊ NE4�������������Ҫ���޸ģ������Ӧ��

//RS ����/�������ţ�ʹ�� FSMC �ĵ�ַ�źſ��ƣ������ž������� LCD ʱʹ�õĵ�ַ������/���
//FSMC_A10 Ϊ PG0
#define LCD_RS_GPIO_PIN 	GPIO_Pin_0 //Һ�� RS ���ź�
#define LCD_RS_PIN_ID 		0 //Һ�� RS �������
#define LCD_RS_GPIO_PORT 	GPIOG //Һ�� RS �˿ں�
#define LCD_RS_GPIO_CLK 	RCC_APB2Periph_GPIOG //Һ�� RS ʱ��
#define LCD_RS_FUN_OUT 		PGout //Һ�� RS ����˿����ú���
//#define LCD_RS_FUN_IN 	PGin //Һ�� RS ����˿����ú���
#define LCD_RS_FSMC_ADDR_ID 	10 //����Ϊ A10��������������޸�,�����Ӧ��

//дʹ������
#define LCD_WR_GPIO_PIN 	GPIO_Pin_5 //Һ��дʹ�����ź�
#define LCD_WR_PIN_ID 		5 //Һ��дʹ���������
#define LCD_WR_GPIO_PORT 	GPIOD //Һ��дʹ�ܶ˿ں�
#define LCD_WR_GPIO_CLK 	RCC_APB2Periph_GPIOD //Һ��дʹ��ʱ��
#define LCD_WR_FUN_OUT 		PDout //Һ��дʹ������˿����ú���
//#define LCD_WR_FUN_IN 	PDin //Һ��дʹ������˿����ú���

//��ʹ������
#define LCD_RD_GPIO_PIN 	GPIO_Pin_4 //Һ����ʹ�����ź�
#define LCD_RD_PIN_ID 		4 //Һ����ʹ���������
#define LCD_RD_GPIO_PORT 	GPIOD //Һ����ʹ�ܶ˿ں�
#define LCD_RD_GPIO_CLK 	RCC_APB2Periph_GPIOD //Һ����ʹ��ʱ��
#define LCD_RD_FUN_OUT 		PDout //Һ����ʹ������˿����ú���
//#define LCD_WR_FUN_IN 	PDin //Һ����ʹ������˿����ú���

/******�����ź���******/
//Dx ����
#define LCD_D0_GPIO_PIN 	GPIO_Pin_14 //Һ�� ���� Dx ���ź�
#define LCD_D0_GPIO_PORT 	GPIOD //Һ�� ���� Dx �˿ں�
#define LCD_D0_GPIO_CLK 	RCC_APB2Periph_GPIOD //Һ�� ���� Dx ʱ��
#define LCD_D1_GPIO_PIN 	GPIO_Pin_15 //Һ�� ���� Dx ���ź�
#define LCD_D1_GPIO_PORT 	GPIOD //Һ�� ���� Dx �˿ں�
#define LCD_D1_GPIO_CLK 	RCC_APB2Periph_GPIOD //Һ�� ���� Dx ʱ��
#define LCD_D2_GPIO_PIN 	GPIO_Pin_0 //Һ�� ���� Dx ���ź�
#define LCD_D2_GPIO_PORT 	GPIOD //Һ�� ���� Dx �˿ں�
#define LCD_D2_GPIO_CLK 	RCC_APB2Periph_GPIOD //Һ�� ���� Dx ʱ��
#define LCD_D3_GPIO_PIN 	GPIO_Pin_1 //Һ�� ���� Dx ���ź�
#define LCD_D3_GPIO_PORT 	GPIOD //Һ�� ���� Dx �˿ں�
#define LCD_D3_GPIO_CLK 	RCC_APB2Periph_GPIOD //Һ�� ���� Dx ʱ��
#define LCD_D4_GPIO_PIN 	GPIO_Pin_7 //Һ�� ���� Dx ���ź�
#define LCD_D4_GPIO_PORT 	GPIOE //Һ�� ���� Dx �˿ں�
#define LCD_D4_GPIO_CLK 	RCC_APB2Periph_GPIOE //Һ�� ���� Dx ʱ��
#define LCD_D5_GPIO_PIN 	GPIO_Pin_8 //Һ�� ���� Dx ���ź�
#define LCD_D5_GPIO_PORT 	GPIOE //Һ�� ���� Dx �˿ں�

#define LCD_D5_GPIO_CLK 	RCC_APB2Periph_GPIOE //Һ�� ���� Dx ʱ��
#define LCD_D6_GPIO_PIN 	GPIO_Pin_9 //Һ�� ���� Dx ���ź�
#define LCD_D6_GPIO_PORT	GPIOE //Һ�� ���� Dx �˿ں�
#define LCD_D6_GPIO_CLK 	RCC_APB2Periph_GPIOE //Һ�� ���� Dx ʱ��
#define LCD_D7_GPIO_PIN 	GPIO_Pin_10 //Һ�� ���� Dx ���ź�
#define LCD_D7_GPIO_PORT 	GPIOE //Һ�� ���� Dx �˿ں�
#define LCD_D7_GPIO_CLK 	RCC_APB2Periph_GPIOE //Һ�� ���� Dx ʱ��
#define LCD_D8_GPIO_PIN 	GPIO_Pin_11 //Һ�� ���� Dx ���ź�
#define LCD_D8_GPIO_PORT 	GPIOE //Һ�� ���� Dx �˿ں�
#define LCD_D8_GPIO_CLK 	RCC_APB2Periph_GPIOE //Һ�� ���� Dx ʱ��
#define LCD_D9_GPIO_PIN 	GPIO_Pin_12 //Һ�� ���� Dx ���ź�
#define LCD_D9_GPIO_PORT 	GPIOE //Һ�� ���� Dx �˿ں�
#define LCD_D9_GPIO_CLK 	RCC_APB2Periph_GPIOE //Һ�� ���� Dx ʱ��
#define LCD_D10_GPIO_PIN 	GPIO_Pin_13 //Һ�� ���� Dx ���ź�
#define LCD_D10_GPIO_PORT 	GPIOE //Һ�� ���� Dx �˿ں�
#define LCD_D10_GPIO_CLK 	RCC_APB2Periph_GPIOE //Һ�� ���� Dx ʱ��
#define LCD_D11_GPIO_PIN 	GPIO_Pin_14 //Һ�� ���� Dx ���ź�
#define LCD_D11_GPIO_PORT 	GPIOE //Һ�� ���� Dx �˿ں�
#define LCD_D11_GPIO_CLK 	RCC_APB2Periph_GPIOE //Һ�� ���� Dx ʱ��
#define LCD_D12_GPIO_PIN 	GPIO_Pin_15 //Һ�� ���� Dx ���ź�
#define LCD_D12_GPIO_PORT 	GPIOE //Һ�� ���� Dx �˿ں�
#define LCD_D12_GPIO_CLK 	RCC_APB2Periph_GPIOE //Һ�� ���� Dx ʱ��
#define LCD_D13_GPIO_PIN 	GPIO_Pin_8 //Һ�� ���� Dx ���ź�
#define LCD_D13_GPIO_PORT 	GPIOD //Һ�� ���� Dx �˿ں�
#define LCD_D13_GPIO_CLK 	RCC_APB2Periph_GPIOD //Һ�� ���� Dx ʱ��
#define LCD_D14_GPIO_PIN 	GPIO_Pin_9 //Һ�� ���� Dx ���ź�
#define LCD_D14_GPIO_PORT 	GPIOD //Һ�� ���� Dx �˿ں�
#define LCD_D14_GPIO_CLK 	RCC_APB2Periph_GPIOD //Һ�� ���� Dx ʱ��
#define LCD_D15_GPIO_PIN 	GPIO_Pin_10 //Һ�� ���� Dx ���ź�
#define LCD_D15_GPIO_PORT 	GPIOD //Һ�� ���� Dx �˿ں�
#define LCD_D15_GPIO_CLK 	RCC_APB2Periph_GPIOD //Һ�� ���� Dx ʱ��

/////////////////////////////////////////////////////////////////////////////////////////////////
//��ֲ�޸�������//////
//////////////////////
//�������������޸ģ�������//////
////////////////////////////////
////////////////////////////////
/******************************* NT35310 ��ʾ���� FSMC �������� ***************************/

#if	LCD_CS_FSMC_NE_ID == 1

//��Ƭѡ���ž����� NOR/SRAM ��
#define FSMC_Bank1_NORSRAMx 	FSMC_Bank1_NORSRAM1
#define FSMC_Bank1_ADDRx 		0x60000000

#elif	LCD_CS_FSMC_NE_ID == 2

//��Ƭѡ���ž����� NOR/SRAM ��
#define FSMC_Bank1_NORSRAMx 	FSMC_Bank1_NORSRAM2
#define FSMC_Bank1_ADDRx 		0x64000000

#elif LCD_CS_FSMC_NE_ID == 3

//��Ƭѡ���ž����� NOR/SRAM ��
#define FSMC_Bank1_NORSRAMx 	FSMC_Bank1_NORSRAM3
#define FSMC_Bank1_ADDRx 		0x68000000

#elif LCD_CS_FSMC_NE_ID == 4

//��Ƭѡ���ž����� NOR/SRAM ��
#define FSMC_Bank1_NORSRAMx 	FSMC_Bank1_NORSRAM4
#define FSMC_Bank1_ADDRx 		0x6C000000

#endif

//FSMC_Bank1_NORSRAM ���� LCD ��������ĵ�ַ
#define FSMC_Addr_NT35310_CMD ( ( uint32_t ) ( FSMC_Bank1_ADDRx | ( ( ( 1 << LCD_RS_FSMC_ADDR_ID ) - 1 ) << 1 ) ) )

//FSMC_Bank1_NORSRAM ���� LCD ���ݲ����ĵ�ַ 
#define FSMC_Addr_NT35310_DATA ( ( uint32_t ) ( FSMC_Bank1_ADDRx | ( ( 1 << LCD_RS_FSMC_ADDR_ID ) << 1 ) ) )

/////////////////////////////////////////////////////////////////////////////////////////////////

//IO ��������
#define LCD_LED LCD_LED_FUN_OUT(LCD_LED_PIN_ID) //LCD_LED LCD ����

///////////////////////////////////////
/* �ⲿ���������� */

//LCD��Ҫ������
typedef struct  
{										    
	uint16_t	width;			//LCD ���
	uint16_t	height;			//LCD �߶�
	uint16_t	id;				//LCD ID
	uint8_t		dir;			//���������������ƣ�0��������1��������	
	uint16_t	wramcmd;		//��ʼдgramָ��
	uint16_t	setxcmd;		//����x����ָ��
	uint16_t	setycmd;		//����y����ָ�� 
}_lcd_dev; 	  

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����
//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern uint16_t  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern uint16_t  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

///////////////////////////////////////
//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���	 

#define DFT_SCAN_DIR  L2R_U2D  //Ĭ�ϵ�ɨ�跽��

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0xF81F
#define GRED 			 0xFFE0
#define GBLUE			 0x07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0xBC40 //��ɫ
#define BRRED 			 0xFC07 //�غ�ɫ
#define GRAY  			 0x8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0x01CF	//����ɫ
#define LIGHTBLUE      	 0x7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0x5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0x841F //ǳ��ɫ
#define LGRAY 			 0xC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0xA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0x2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
///////////////////////////////////////
/* ���������� */
void TFTLCD_Init(void);													//��ʼ��
void LCD_DisplayOn (void);													//����ʾ
void LCD_DisplayOff (void);													//����ʾ
void LCD_Clear(uint16_t Color);	 												//����
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);										//���ù��
void LCD_DrawPoint(uint16_t x,uint16_t y);											//����
void LCD_Fast_DrawPoint(uint16_t x,uint16_t y,uint16_t color);								//���ٻ���
uint16_t  LCD_ReadPoint(uint16_t x,uint16_t y); 											//���� 
void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);						 			//��Բ
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);							//����
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);		   				//������
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);		   				//��䵥ɫ
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);				//���ָ����ɫ
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode);						//��ʾһ���ַ�
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);  						//��ʾһ������
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);				//��ʾ ����
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p);		//��ʾһ���ַ���,12/16����

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);
uint16_t LCD_ReadReg(uint16_t LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
void LCD_Scan_Dir(uint8_t dir);									//������ɨ�跽��
void LCD_Display_Dir(uint8_t dir);								//������Ļ��ʾ����
void LCD_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);	//���ô���					   						   																			 

///////////////////////////////////////
#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
