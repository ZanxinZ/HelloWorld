#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
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


#define P1 150//���
#define P2 165//�ұ�

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
#define RROAD4 PBin(1)//�Ҳ�
#define RROAD3 PBin(2)
#define RROAD2 PBin(3)
#define RROAD1 PBin(4)
#define LROAD5 PBin(5)//���
#define LROAD6 PBin(6)
#define LROAD7 PBin(7)
#define LROAD8 PBin(8)

void LED_Init(void);//��ʼ��

		 				    
#endif
