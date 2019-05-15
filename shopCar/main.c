
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "oled.h"
#include "math.h"
#include "pid.h"
#include "control.h"
#include "smart.h"
/************************************************
 ALIENTEK战舰STM32开发板实验9
 PWM输出实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
extern int time;
extern u16 mode;
extern double PID_value;
extern double PID_error;
extern u8 finishflag;
extern u16 aaa;
extern int location[12];
extern int fill[3];
extern int hope[4][3];
extern int timerflag;
extern int time;
extern int photoflag;
int main(void)
{		
		delay_init();	               //延时函数初始化	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		uart1_init(9600);         //串口初始化为115200
	  uart2_init(115200);
		TIM1_PWM_Init(999,719);     //定时器初始化
		TIM2_PWM_Init(19999,71);
		TIM3_PWM_Init(799,17);
		TIM4_Int_Init(99,719);
		TIM5_PWM_Init(19999,71);
	  TIM6_Int_Init(99,719);
	  TIM7_Int_Init(999,7199);
		OLED_Init();                //OLED初始	 
		OLED_Clear();
		PID_Init(&Line_PID);       //初始化PID结构体参数
		PID_Set(&Line_PID,35,0,0); //设置PID参数	  
	  LED_Init();		//各类端口初始化
	  signal=0;
		while(1)
		{

/*			init_mechanical_grip();//完整一套走法
			start();
			count_line(7,0,1);
			turn(1,0);
			take_photo();
			finding(0);
		  put_thing(1);
			turn(1,0);
			count_line(7,0,1);
			turn(1,0);
			finding(1);
			put_thing(2);
			turn(1,0);
			count_line(7,0,1);
			turn(1,0);
			finding(2);
			put_thing(3);
			turn(1,0);
			count_line(7,0,1);
			turn(1,0);
			finding(3);
			put_thing(4);*/
			init_mechanical_grip();
      turn(1,0);
      while(1); 
		}	 
}

