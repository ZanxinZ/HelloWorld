#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED端口定义
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
#define HDL	  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//左边中间的灰度，两轮之间

#define KEY1 	  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define KEY2 	  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)

#define JG 	  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)


#define DIR1 PCout(11)	// YOU
#define DIR2 PCout(10)	//			in4
#define DIR3 PCout(12)	//   ZUO
#define DIR4 PCout(4)	// 					in1


void HUIDU_Init(void);
void LED_Init(void);//初始化函数
void DIR_Init(void);
#endif
