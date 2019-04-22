#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

#include "pwm.h"
#include "timer.h"
#include "string.h"
#include "pid.h"
#include "adc.h"
#include "MOTO.h"
#include "STEP.h"
#include "oled.h"

/**
一些主要参数放在相关的结构体里面
如：灰度的参数：放在time.h 包含了（各个灯亮灭情况、灯的情况的标志位、灯的数目）
*/
extern int Roll,Pitch,Yaw,data,Angle[10],deltangle;//陀螺仪
extern LightState lightState;
extern CarState carState;
int hd_front[8];
const int humpTime;
int main(void)
{ 
	int adcx1=0;
	int adcx2=0;
	int option=0;
	delay_init(168);		  //初始化延时函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	HUIDU_Init();//灰度
	DIR_Init();
	//PID_Init(80,0.001,60);
	PID_Init(70,0,35);
	TIM2_Int_Initl(500-1,84-1);
	TIM5_Int_Initl(1000-1,79);
	TIM3_PWM_Init(899,719);
	
	//TIM6_Int_Initl(4999,7199);//
	
	TIM4_PWM_Init(49,7199);//50HZ
	//初始化结构体/////////////////
	init_light_block();
	OLED_Init();//OLED 屏幕初始化
	
	uart2_init(115200);	//串口初始化波特率为115200
	//uart2_init(9600);
	forward();
	stop();
	delay_ms(1000);
	/*TIM_SetCompare3(TIM3,165*0.99);//you
	TIM_SetCompare4(TIM3,165);//*/
	
	TIM_SetCompare2(TIM4,25);
	TIM_SetCompare3(TIM4,15);
	TIM_SetCompare4(TIM4,10);


	//初始化完成
	//test();
	
	option=choice();//使用色标进行选择
	/*peopleDo();
	peopleDo();
	peopleDo();
	while(1);*/
	switch(option){
		case 0://all
		/*	onlyGo(48,45,800);
			bridge();
	//goStraight(40,40,1);
	onboard(0,0,0);
	crossing(1,70,1);
	hump(44,38,37);//标准过障碍
		crossing(1,210,1);
		onboard(0,0,0);
		onboard(0,0,0);
		crossing(0,160,2);
		
		smallHump(33);
		crossing(0,160,1);
		onboard(0,0,0);
		countLine(1,120);
		crossing(0,120,1);
		countLine(1,820);
		black_xiepo(0,0);
		hump(60,38,42);//标准去程
		
		climbStage();
		hump(60,38,38);//标准回程
		*/
		black_xiepo(4,38);
		climbMountain();
		
		
		break;
		case 1://onbo
			onboard(0,0,0);
			break;
		case 2://cross
			crossing(0,160,2);
			break;
		case 3://hump
			hump(44,38,35);
			break;
		case 4://xiepo
			black_xiepo(0,0);
			
			break;
		case 5://bighump
			hump(60,38,37);
			//round();
		break;
		case 6:
		climbMountain();
			//climbStage();
		case 7://circle////////////////圆
			//onboard(0,0,0);
			//countLine(2,200);
			round();
			//回城
			crossing(0,120,2);
			smallHump(33);
			crossing(1,160,1);
			crossing(0,200,1);
			delay_ms(200);
			teeterBoard(47,42);
			goHome(300);
			onboard(0,0,1);
		
		break;
		case 8://3个台
			onlyGo(48,45,800);
			bridge();	
			onboard(0,0,0);
			crossing(1,70,1);
			hump(44,38,35);//标准过障碍
			crossing(1,180,1);
			onboard(0,0,0);
			onboard(0,0,0);
			crossing_2(1,100,1,0);
			
			teeterBoard(56,50);
			
			goHome(300);
			onboard(0,0,1);
			break;
		case 9://4个台
			onlyGo(48,45,800);
			bridge();	
			onboard(0,0,0);
			crossing(1,70,1);
			hump(44,38,35);//标准过障碍
			crossing(1,180,1);
			onboard(0,0,0);
			onboard(0,0,0);
			
			crossing(0,160,2);
		
			
			smallHump(33);
			crossing(0,160,1);
			onboard(0,0,0);
			
			//回城
			crossing(1,100,2);
			smallHump(33);
			crossing(0,180,1);
			
			crossing(1,160,2);
			teeterBoard(55,50);
			goHome(300);
			onboard(0,0,1);
			break;
		case 10://5个台，到圆
			onlyGo(48,45,800);
			bridge();	
			onboard(0,0,0);
			crossing(1,70,1);
			hump(44,38,37);//标准过障碍
			crossing(1,210,1);
			onboard(0,0,0);
			onboard(0,0,0);
			
			crossing(0,160,2);
		
			
			smallHump(33);
			crossing(0,160,1);
			onboard(0,0,0);
			countLine(2,400);
			
			round();
			//回城
			crossing(0,120,2);
			smallHump(33);
			crossing(1,200,1);
			
			crossing(0,200,1);
			
			
			teeterBoard(47,42);
			goHome(300);
			onboard(0,0,1);
		
			break;
		case 11:////*****************6个台
			onlyGo(48,45,800);
			bridge();	
			onboard(0,0,0);
			crossing(1,70,1);
			hump(humpTime,30,32);
			crossing(1,180,1);
			onboard(0,0,0);
			onboard(0,0,0);
			
			crossing(0,160,2);
		
			
			smallHump(33);
			crossing(0,160,1);
			onboard(0,0,0);
			countLine(2,400);
			round(0);
			countLine(1,400);
			crossing(0,120,1);
			countLine(1,300);
			black_xiepo(0,0);
			hump(60,38,38);//标准过障碍
			climbStage();
			hump(60,38,39);//标准回程
			
			
			break;
		case 12://*******************调试
			/*black_xiepo(0,0);
			hump(humpTime+14,30,32);
			climbStage();
			hump(humpTime+16,34,30);
			black_xiepo(4,38);*/
			teeterBoard(47,42);
			goHome(300);
			onboard(0,0,1);
			break;
		default:
			break;
	
	}

	//forward();
	/*onlyGo(48,45,800);
	bridge();
	//goStraight(40,40,1);*/
	/*onboard(0,0,0);
	crossing(1,20,1);
	hump(9000);
	crossing(1,160,1);
	while(1){};
*/
	/*OLED_Init();//OLED 屏幕初始化
	OLED_Clear();//OLED 屏幕预设
	
	Adc_Init();  
	//PID_Init(0,0,0);
	
	/*
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	

	TIM_SetCompare1(TIM3,165*0.99);//you
	TIM_SetCompare2(TIM3,165);//
	stop();
	OLED_ShowNum(0,0,403,4,16);
	while(1);
	delay_ms(1000);
	delay_ms(1000);*/
	//goStraight(42,38,1);
	//onboard(0,0,0);
	/*onlyGo(50,45,1000);
	bridge();

	onboard(0,0,0);
	crossing(1,60,1);
	hump(9000);
	adjustSmall();
	
	//hump(12000);
	crossing(1,160,1);
	onboard(0,0,0);
	onboard(0,0,0);
	//while(1);
	*/
	/*onlyGo(45,42,1000);
bridge();
onboard(0,0,0);
crossing(1,40,1);
hump(9000);
crossing(1,160,1);
onboard(0,0,0);
onboard(0,0,0);

crossing(0,120,2);
smallHump(8000);
crossing(0,120,1);
onboard(0,0,0);
countLine(1);
crossing(0,110,1);
countLine(1);
stop();
delay_ms(1000);
black_xiepo(0,570);
//onboard(0,0,0);*/

while(1){
				/*OLED_ShowNum(0,0,HD1,1,16); 
				OLED_ShowNum(16,0,HD2,1,16);
				OLED_ShowNum(32,0,HD3,1,16);
				OLED_ShowNum(48,0,HD4,1,16);
				OLED_ShowNum(64,0,HD5,1,16);
				OLED_ShowNum(80,0,HD6,1,16);
				OLED_ShowNum(96,0,HD7,1,16);
				OLED_ShowNum(112,0,HD8,1,16);*/
				int L[8];
			int i;
			for(i=0;i<8;i++){
				L[i]=lightState.light[i];
			}
				OLED_ShowNum(0,0,L[0],1,16); 
				OLED_ShowNum(16,0,L[1],1,16);
				OLED_ShowNum(32,0,L[2],1,16);
				OLED_ShowNum(48,0,L[3],1,16);
				OLED_ShowNum(64,0,L[4],1,16);
				OLED_ShowNum(80,0,L[5],1,16);
				OLED_ShowNum(96,0,L[6],1,16);
				OLED_ShowNum(112,0,L[7],1,16);
				OLED_ShowNum(0,2,HL,1,16);
				OLED_ShowNum(16,2,HR,1,16);
				OLED_ShowNum(48,2,HDL,1,16);
				OLED_ShowNum(96,2,JG,1,16);
				OLED_ShowNum(0,4,Pitch,4,16);
				OLED_ShowNum(48,4,Yaw,4,16);
				OLED_ShowNum(96,4,Roll,4,16);
				
	}
	
	//OLED_Clear();
	//显示信息	
	while(1){
			int L[8];
			int i;
			for(i=0;i<8;i++){
				L[i]=lightState.light[i];
			}
			adcx1=Get_Adc_Average(ADC_Channel_11,1);//zuo
			adcx2=Get_Adc_Average(ADC_Channel_10,1);//you
			OLED_ShowNum(0,0,Roll,4,16);//侧面
			OLED_ShowNum(32,0,Pitch,4,16);//上下（上坡减，下坡加）
			OLED_ShowNum(64,0,Yaw,4,16);//左右（顺时针是加）（0-359）
			
			
			OLED_ShowNum(16,2,L[0],1,16);
			OLED_ShowNum(26,2,L[1],1,16);
			OLED_ShowNum(36,2,L[2],1,16);
			OLED_ShowNum(46,2,L[3],1,16);
			OLED_ShowNum(56,2,L[4],1,16);
			OLED_ShowNum(66,2,L[5],1,16);
			OLED_ShowNum(76,2,L[6],1,16);
			OLED_ShowNum(86,2,L[7],1,16);
			OLED_ShowNum(0,4,HR,1,16);
			OLED_ShowNum(10,4,HL,1,16);
			OLED_ShowNum(40,4,HDL,1,16);
			OLED_ShowNum(16,6,adcx1,4,16);
			OLED_ShowNum(56,6,adcx2,4,16);
			
		}
	
		

	
	{GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOF时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
	}
 GPIO_SetBits(GPIOB,GPIO_Pin_9);
	

	
	//OLED_Clear();//OLED 屏幕预设
	OLED_ShowNum(0,2,404,4,16);

while(1){OLED_ShowNum(4,2,404,4,16); }
}


