
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
 ALIENTEKս��STM32������ʵ��9
 PWM���ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
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
		delay_init();	               //��ʱ������ʼ��	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		uart1_init(9600);         //���ڳ�ʼ��Ϊ115200
	  uart2_init(115200);
		TIM1_PWM_Init(999,719);     //��ʱ����ʼ��
		TIM2_PWM_Init(19999,71);
		TIM3_PWM_Init(799,17);
		TIM4_Int_Init(99,719);
		TIM5_PWM_Init(19999,71);
	  TIM6_Int_Init(99,719);
	  TIM7_Int_Init(999,7199);
		OLED_Init();                //OLED��ʼ	 
		OLED_Clear();
		PID_Init(&Line_PID);       //��ʼ��PID�ṹ�����
		PID_Set(&Line_PID,35,0,0); //����PID����	  
	  LED_Init();		//����˿ڳ�ʼ��
	  signal=0;
		while(1)
		{

/*			init_mechanical_grip();//����һ���߷�
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

