#include "timer.h"
#include "led.h"
#include "oled.h"
#include "delay.h"
#include "pid.h"
#include "MOTO.h"
extern Pid pid;
extern PidParam pidSetParam;
int clr_pid_voltage=0;//清除积分项


LightState lightState;//灰度的状态
LightError lightError;//通过灰度，设定的偏差
CarState carState;//车子状态标志
extern int Roll,Pitch,Yaw,data,Angle[10],hd_front[];
//定时器初始化////////////////////
//定时器2
void TIM2_Int_Initl(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM2,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; //子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
//定时器5
void TIM5_Int_Initl(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM5,ENABLE); //使能定时器5
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
void TIM6_Int_Initl(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=4;//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM6,ENABLE); //使能定时器5
	
}
////////////////////////////////////



//定时器中断服务函数/////////////

void TIM2_IRQHandler(void)//定时器2，扫灰度,存数据
{
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
  {
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志
			//采集灰度信息，放入数组
		lightState.light[0]=HD1;
		lightState.light[1]=HD2;
		lightState.light[2]=HD3;
		lightState.light[3]=HD4;
		lightState.light[4]=HD5;
		lightState.light[5]=HD6;
		lightState.light[6]=HD7;
		lightState.light[7]=HD8;
		
		getError();	
		lightState.num=0;
		getLightNum();
		
				
		//if((lightState.light[3]==0||lightState.light[4]==0)&&lightState.light[7]==1)   flagr=1;
		
		if((lightState.light[3]==0||lightState.light[4]==0)&&lightState.light[0]==1)
			{lightState.isCrossing=0;}//不是路口
		if((lightState.light[1]==0&&lightState.light[3]==0&&lightState.light[6]==0)||
			(lightState.light[1]==0&&lightState.light[4]==0&&lightState.light[6]==0))
			{lightState.isCrossing=1;}//是路口
		if(lightState.num>2){lightError.error=0;}	
		}			
}			


	       
					 
	void TIM5_IRQHandler(void)//定时器5,pid 的执行，取数据，计算，执行
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
  {
		int leftResult,rightResult;//结果
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志
		
		clr_pid_voltage++;
		if(clr_pid_voltage>=200){pid.voltage=0;clr_pid_voltage=0;}//清除积分项
		
		PID_realize(lightError.error);//计算偏差
		TIM_SetCompare4(TIM3, pid.setSpeedLeft- pid.ActualSpeed);	 
		TIM_SetCompare3(TIM3, pid.setSpeedRight + pid.ActualSpeed);
		//leftResult=pid.setSpeedLeft-pid.ActualSpeed;
		//rightResult=pid.setSpeedRight + pid.ActualSpeed;
		//setSpeed(leftResult,rightResult);
		
		
		
		
		
	}		
}		

void TIM6_DAC_IRQHandler(void)//定时器6计时
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET) //溢出中断
  {
		TIM_SetCompare2(TIM4,18);
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	}	
		else{
		TIM_SetCompare2(TIM4,28);
		}
}		
//////////////////////////////////
//初始化灰度模块

void init_light_block(){
	int i;
	for(i=0;i<8;i++){
		lightState.light[i]=1;
	}
	lightState.canLeftTurn=0;
	lightState.canRightTurn=0;
	lightState.num=0;
	lightState.isCrossing=0;
	lightState.isCrossing=0;
	
	lightError.error=0;
	lightError.resultSpeed=0;
	
	carState.isGoline=0;
	carState.isHoldJG=0;
	carState.isDoOption=1;
}


////////////////////////	
//偏差来源
void getError(void)
		{
			int light=-1;
			int L0,L1,L2,L3,L4,L5,L6,L7;
			light=lightState.light[0]*10000000+
					lightState.light[1]*1000000+
					lightState.light[2]*100000+
					lightState.light[3]*10000+
					lightState.light[4]*1000+
					lightState.light[5]*100+
					lightState.light[6]*10+
					lightState.light[7];
		
				L0=HD1;
				L1=HD2;
				L2=HD3;
				L3=HD4;
				L4=HD5;
				L5=HD6;
				L6=HD7;
				L7=HD8;
			/*//滤波
			if(lightState.num>2){lightError.error=0;}//三个灯以上亮，偏差为0
			//不相邻的两个灯亮，偏差置零
			else if((L0==0&&(L4==0||L5==0||L6==0||L7==0)))
			{lightError.error=0;}
			else if((L1==0&&(L5==0||L6==0||L7==0)))
			{lightError.error=0;}
			else if((L2==0&&(L6==0||L7==0)))
			{lightError.error=0;}
			else if((L3==0&&(L7==0)))
			{lightError.error=0;}
			*/
		//灰度的状态决定了偏差
		 switch(light){
			//多灯判断路口时，需要把error置0
			//先多灯，再少灯
			/////////////////
			//两灯
			case 11100111://3,4
				lightError.error=0;pidSetParam.Lkd=0;pidSetParam.Lkp=0;	
				break;
			case 11001111://2,3
				lightError.error=0.08;pidSetParam.Lkp=15;pidSetParam.Lkd=5;		
				break;
			case 11110011://4,5
				lightError.error=-0.08;pidSetParam.Lkp=15;	pidSetParam.Lkd=5;
				break;
			case 111111://0,1
				lightError.error=1;pidSetParam.Lkp=0;	pidSetParam.Lkd=0;
				break;
			case 11111100://6,7
				lightError.error=-1;pidSetParam.Lkp=0;	pidSetParam.Lkd=0;
				break;
			case 10011111://1,2
				lightError.error=0.5;pidSetParam.Lkp=0;	pidSetParam.Lkd=0;
				break;
			case 11111001://5,6
				lightError.error=-0.5;pidSetParam.Lkp=0;pidSetParam.Lkd=0;
				break;
			////////////////
			
			/////////////////
			//单灯
			case 01111111://0
				lightError.error=2;
				break;
			case 10111111://1
				lightError.error=1.5;pidSetParam.Lkp=0;pidSetParam.Lkd=0;
				break;
			case 11011111://2
				lightError.error=1.2;pidSetParam.Lkp=0;pidSetParam.Lkd=0;
				break;
			case 11101111://3
				lightError.error=0.1;
				break;
			case 11110111://4
				lightError.error=-0.1;
				break;
			case 11111011://5
				lightError.error=-1.2;pidSetParam.Lkp=0;pidSetParam.Lkd=0;
				break;
			case 11111101://6
				lightError.error=-1.5;pidSetParam.Lkp=0;pidSetParam.Lkd=0;
				break;
			case 11111110://7
				lightError.error=-2;
				break;
			/////////////////
			default:
				lightError.error=0;
				break;
		}
		
		//if(((L0==0||L1==0)&&L3==0)||((L0==0||L1==0)&&L4==0)) 
		if(L0==0)
			{ 
			lightState.canLeftTurn=1; //可以左转
			pidSetParam.Lkd=0;	
			pidSetParam.Lkp=25;		
			
			}
			else if(((L7==0||L6==0)&&L3==0)||((L7==0||L1==6)&&L4==0))
			//else if(L7==0)
			{ 
			lightState.canRightTurn=1;//可以右转
			pidSetParam.Lkd=0;	
			pidSetParam.Lkp=25;	
			
			}	
			else {
			lightState.canLeftTurn=0;
			lightState.canRightTurn=0;
			pidSetParam.Lkd=0;	
			pidSetParam.Lkp=0;		
			}
			if(L0==0&&L1==0&&L2==0||L5==0&&L6==0&&L7==0){lightError.error=0;}
			
		}
	
void getLightNum(void)//得到检测到白线灰度的数量
{
	int h;
	for(h=0;h<8;h++)
	{
		if(lightState.light[h]==0)
		{
			lightState.num++;
		}
	
	}
	}