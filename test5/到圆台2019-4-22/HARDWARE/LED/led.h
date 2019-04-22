#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED�˿ڶ���
//#define LED0 PBout(8)	// DS0
//#define LED1 PFout(10)	// DS1	 
#define HD1 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) 
#define HD2 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)	
#define HD3 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define HD4 	  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)	
#define HD5 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define HD6 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)	
#define HD7 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) 
#define HD8 	  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)

#define HDH1 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1) 
#define HDH2 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)	 
#define HDH3 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3) 
#define HDH4 	  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)	
#define HDH5 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5) 
#define HDH6 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)	
#define HDH7 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7) 
#define HDH8 	  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)

#define HL 	  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
#define HR 	  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)
#define HDL	  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//����м�ĻҶȣ�����֮��

#define KEY1 	  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define KEY2 	  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)

#define JG 	  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)


#define DIR1 PCout(11)	// YOU
#define DIR2 PCout(10)	//			in4
#define DIR3 PCout(12)	//   ZUO
#define DIR4 PCout(4)	// 					in1


void HUIDU_Init(void);
void LED_Init(void);//��ʼ������
void DIR_Init(void);
#endif
