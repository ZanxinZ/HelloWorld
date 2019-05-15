#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

#define IN1 PGout(5)
#define IN2 PGout(6)
#define IN3 PGout(4)
#define IN4 PGout(2)
#define signal PCout(11)
#define flicker PEout(7)
#define key4 PAin(4)
#define key3 PAin(5)
#define key2 PAin(6)
#define key1 PAin(7)
#define TOP PCin(0)
#define THING PCin(1)


#define P1 150//左边
#define P2 165//右边

#define REROAD1 PDin(1)
#define REROAD2 PDin(2)
#define REROAD3 PDin(3)
#define REROAD4 PDin(4)
#define REROAD5 PDin(5)
#define REROAD6 PDin(6)
#define REROAD7 PDin(7)
#define REROAD8 PDin(8)
#define FRROAD1 PFin(3)
#define FRROAD2 PFin(4)
#define FRROAD3 PFin(5)
#define FRROAD4 PFin(6)
#define FRROAD5 PFin(7)
#define FRROAD6 PFin(8)
#define FRROAD7 PFin(9)
#define FRROAD8 PFin(10)
#define RROAD4 PBin(1)//右侧
#define RROAD3 PBin(2)
#define RROAD2 PBin(3)
#define RROAD1 PBin(4)
#define LROAD5 PBin(5)//左侧
#define LROAD6 PBin(6)
#define LROAD7 PBin(7)
#define LROAD8 PBin(8)

void LED_Init(void);//初始化

		 				    
#endif
