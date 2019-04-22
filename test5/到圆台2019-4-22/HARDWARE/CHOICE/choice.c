#include "choice.h" 
#include "led.h"
#include "oled.h"
#include "timer.h"
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
extern CarState carState;
int choice(){
	int choice=0;
	int point=0;
	char HL_dir=0,HR_dir=0;
	
	while(1){
		OLED_ShowChar(0,0,'M');
		OLED_ShowChar(8,0,'E');
		OLED_ShowChar(16,0,'N');
		OLED_ShowChar(24,0,'U');
		OLED_ShowChar(0,2,'C');
		OLED_ShowChar(8,2,'o');
		OLED_ShowChar(16,2,'d');
		OLED_ShowChar(24,2,'e');
		OLED_ShowChar(32,2,':');
		switch(point){
			case 0:
				OLED_Clear();
				OLED_ShowChar(40,2,'A');
				OLED_ShowChar(48,2,'l');
				OLED_ShowChar(56,2,'l');
			
				break;
			case 1:
				OLED_Clear();
				OLED_ShowChar(40,2,'o');
				OLED_ShowChar(48,2,'n');
				OLED_ShowChar(56,2,'B');
				OLED_ShowChar(64,2,'o');
				break;
			case 2:
				OLED_Clear();
				OLED_ShowChar(40,2,'c');
				OLED_ShowChar(48,2,'r');
				OLED_ShowChar(56,2,'o');
				OLED_ShowChar(64,2,'s');
				OLED_ShowChar(72,2,'s');
				break;
			case 3:
				OLED_Clear();
				OLED_ShowChar(40,2,'h');
				OLED_ShowChar(48,2,'u');
				OLED_ShowChar(56,2,'m');
				OLED_ShowChar(64,2,'p');
				break;
			case 4:
				OLED_Clear();
				OLED_ShowChar(40,2,'x');
				OLED_ShowChar(48,2,'_');
				OLED_ShowChar(56,2,'p');
				OLED_ShowChar(64,2,'o');
				break;
			case 5:
				OLED_Clear();
				OLED_ShowChar(40,2,'L');
				OLED_ShowChar(48,2,'_');
				OLED_ShowChar(56,2,'H');
				OLED_ShowChar(64,2,'u');
				OLED_ShowChar(72,2,'m');
				OLED_ShowChar(80,2,'p');
				break;
			case 6:
				OLED_Clear();
				OLED_ShowChar(40,2,'S');
				OLED_ShowChar(48,2,'t');
				OLED_ShowChar(56,2,'a');
				OLED_ShowChar(64,2,'g');
				OLED_ShowChar(72,2,'e');
				break;
			case 7:
				OLED_Clear();
				OLED_ShowChar(40,2,'C');
				OLED_ShowChar(48,2,'i');
				OLED_ShowChar(56,2,'r');
				OLED_ShowChar(64,2,'c');
				OLED_ShowChar(72,2,'l');
				OLED_ShowChar(80,2,'e');
				break;
			
			case 8://3个台
				OLED_Clear();
				OLED_ShowChar(40,2,'T');
				OLED_ShowChar(48,2,'h');
				OLED_ShowChar(56,2,'r');
				OLED_ShowChar(64,2,'e');	
				OLED_ShowChar(75,2,'e');
				break;
			case 9://4个台
				OLED_Clear();
				OLED_ShowChar(40,2,'F');
				OLED_ShowChar(48,2,'o');
				OLED_ShowChar(56,2,'u');
				OLED_ShowChar(64,2,'r');	
				
			break;//5个台，到圆圈
			case 10:
				OLED_Clear();
				OLED_ShowChar(40,2,'F');
				OLED_ShowChar(48,2,'i');
				OLED_ShowChar(56,2,'v');
				OLED_ShowChar(64,2,'e');	
				
			break;//到一级台阶，6个台
			case 11:
				OLED_Clear();
				OLED_ShowChar(40,2,'S');
				OLED_ShowChar(48,2,'i');
				OLED_ShowChar(56,2,'x');	
			break;
			case 12://调试模式
				OLED_Clear();
				OLED_ShowChar(40,2,'T');
				OLED_ShowChar(48,2,'e');
				OLED_ShowChar(56,2,'s');
				OLED_ShowChar(64,2,'t');
			default :

				break;
		}
		//左翻
		if(HL==1){HL_dir=1;}
		if(HL==0&&HL_dir==1){HL_dir=0;point--;}
		//右翻
		if(HR==1){HR_dir=1;}
		if(HR==0&&HR_dir==1){HR_dir=0;point++;}
		//////////////////////////////////////
		if(point<0){point=12;}//到达下边界 控制选数范围
		if(point>12){point=0;}	//到达上边界
		//////////////////////////////////////
		
		//if(!KEY1){OLED_Clear();OLED_ShowNum(0,6,404,4,16);break;}
		if(JG==0){carState.isHoldJG=1;}
		if(JG==1&&carState.isHoldJG==1){
		OLED_ShowNum(0,6,402,4,16);
		break;}
	}
		return point;
}



