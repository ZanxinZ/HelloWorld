#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	    
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ALIENTEK OLEDģ����������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/5
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////	

//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
		    						  
//-----------------OLED�˿ڶ���----------------  					   
//	 CK-OLED_SCLK-PA4-PF11//////DI- OLED_SDIN-PA5-PF12/////RST-PA6-PF13////DC-OLED_RS-PA7-PF14///CS--GND
//----------------4�߽ӿ�------------------
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOG,GPIO_Pin_11)
#define OLED_CS_Set()  GPIO_SetBits(GPIOG,GPIO_Pin_11)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOF,GPIO_Pin_13)
#define OLED_RST_Set() GPIO_SetBits(GPIOF,GPIO_Pin_13)

#define OLED_RS_Clr() GPIO_ResetBits(GPIOF,GPIO_Pin_14)   ////DC
#define OLED_RS_Set() GPIO_SetBits(GPIOF,GPIO_Pin_14)

#define OLED_WR_Clr() GPIO_ResetBits(GPIOF,GPIO_Pin_12)
#define OLED_WR_Set() GPIO_SetBits(GPIOF,GPIO_Pin_12)

#define OLED_RD_Clr() GPIO_ResetBits(GPIOF,GPIO_Pin_11)
#define OLED_RD_Set() GPIO_SetBits(GPIOF,GPIO_Pin_11)



//PC0~7,��Ϊ������
#define DATAOUT(x) GPIO_Write(GPIOC,x);//���  
//ʹ��4�ߴ��нӿ�ʱʹ�� 

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOF,GPIO_Pin_11)
#define OLED_SCLK_Set() GPIO_SetBits(GPIOF,GPIO_Pin_11)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOF,GPIO_Pin_12)
#define OLED_SDIN_Set() GPIO_SetBits(GPIOF,GPIO_Pin_12)

 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p);	 
#endif  
