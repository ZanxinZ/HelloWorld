#include "control.h"
#include "pid.h"
#include "timer.h"
#include "math.h"
#include "led.h"
#include "oled.h"
#include "delay.h"
#include "smart.h"


PID_TypDef  Line_PID;
u16 f=0;
u16 js;//暂时无用
u16 mode=1;//小车模式具体可以看follow_line（）函数
u16 sx=0;//数线中用到的状态标志
u16 sx1=0;//备用的数线标志这里暂时没有用到
u16 js1=0;//暂时无用
double error=0;//误差
int rep[8];//灰度数组
int nline=0;//线条数量用于储存数线结果
int nline1=0;//线条数量暂时无用
int countflag=0;//计数标志用于显示需要数线在count_line(countflag)中使用，1代表数线，0代表nline清零
int timerflag=0;//使能定时器计数开始，计数器计的数在time里单位为ms
int time=0;//用于记定时器中断用于额外的计时保护
int smode=0;
int photoflag=0;//拍照标志

extern int fill[3];
extern int finishflag;
extern u16 aaa;//图像结果
extern int location[12];//位置数组用于储存各个位置上的物品代号

void Stop(void)
{
	  IN1=0;
		IN2=0;
		IN3=0;
		IN4=0;
}

void Go_away(void)
{
	  IN1=1;//右边
		IN2=0;
		IN3=1;//左边
		IN4=0;
}
void Go_back(void)
{
	  IN1=0;
		IN2=1;
		IN3=0;
		IN4=1;	

}
void turnleft(void)
{
	  IN1=1;
		IN2=0;
		IN3=0;
		IN4=1; 
}
void turnright(void)
{
	  IN1=0;
		IN2=1;
		IN3=1;
		IN4=0; 
}
void Go_backl(void)
{
    IN1=0;
		IN2=0;
		IN3=0;
		IN4=1;	

}
void Go_backr(void)
{

		IN1=0;
		IN2=1;
    IN3=0;
		IN4=0; 	

}
void Go_awayl(void)
{
	  IN1=0;//右边
		IN2=0;
		IN3=1;//左边
		IN4=0;
}
void Go_awayr(void)
{
	  IN1=1;//右边
		IN2=0;
		IN3=0;//左边
		IN4=0;
}
void Go_backll(void)
{
		IN3=0;
		IN4=1;	
}
void Go_backrr(void)
{
		IN1=0;
		IN2=1; 	
}
void Go_awayll(void)
{
		IN3=1;//左边
		IN4=0;
}
void Go_awayrr(void)
{
	  IN1=1;//右边
		IN2=0;
}
double get_error(u8 mode)//得到误差
{
	error=0;
	if(mode==0)
	{
	  rep[0]=FRROAD1;rep[1]=FRROAD2;rep[2]=FRROAD3;rep[3]=FRROAD4;rep[4]=FRROAD5;rep[5]=FRROAD6;rep[6]=FRROAD7;rep[7]=FRROAD8;
	}
	else if(mode==2)
	{
		rep[0]=REROAD1;rep[1]=REROAD2;rep[2]=REROAD3;rep[3]=REROAD4;rep[4]=REROAD5;rep[5]=REROAD6;rep[6]=REROAD7;rep[7]=REROAD8;
	}
	//白线后退+积分清零	
	if(rep[0]==1&&rep[1]==1&&rep[2]==1&&rep[3]==0&&rep[4]==0&&rep[5]==1&&rep[6]==1&&rep[7]==1) { Line_PID.ErrInt=0;error=0;}
	
	if(rep[0]==1&&rep[1]==1&&rep[2]==1&&rep[3]==1&&rep[4]==0&&rep[5]==1&&rep[6]==1&&rep[7]==1) error=1;
  if(rep[0]==1&&rep[1]==1&&rep[2]==1&&rep[3]==1&&rep[4]==0&&rep[5]==0&&rep[6]==1&&rep[7]==1) error=2;
	if(rep[0]==1&&rep[1]==1&&rep[2]==1&&rep[3]==1&&rep[4]==1&&rep[5]==0&&rep[6]==1&&rep[7]==1) error=3;
	if(rep[0]==1&&rep[1]==1&&rep[2]==1&&rep[3]==1&&rep[4]==1&&rep[5]==0&&rep[6]==0&&rep[7]==1) error=4;
	if(rep[0]==1&&rep[1]==1&&rep[2]==1&&rep[3]==1&&rep[4]==1&&rep[5]==1&&rep[6]==0&&rep[7]==1) error=5;
	if(rep[0]==1&&rep[1]==1&&rep[2]==1&&rep[3]==1&&rep[4]==1&&rep[5]==1&&rep[6]==0&&rep[7]==0) error=6;
	if(rep[0]==1&&rep[1]==1&&rep[2]==1&&rep[3]==1&&rep[4]==1&&rep[5]==1&&rep[6]==1&&rep[7]==0) error=7;
	
	if(rep[0]==1&&rep[1]==1&&rep[2]==1&&rep[3]==0&&rep[4]==1&&rep[5]==1&&rep[6]==1&&rep[7]==1) error=-1;
	if(rep[0]==1&&rep[1]==1&&rep[2]==0&&rep[3]==0&&rep[4]==1&&rep[5]==1&&rep[6]==1&&rep[7]==1) error=-2;
	if(rep[0]==1&&rep[1]==1&&rep[2]==0&&rep[3]==1&&rep[4]==1&&rep[5]==1&&rep[6]==1&&rep[7]==1) error=-3;
	if(rep[0]==1&&rep[1]==0&&rep[2]==0&&rep[3]==1&&rep[4]==1&&rep[5]==1&&rep[6]==1&&rep[7]==1) error=-4;
	if(rep[0]==1&&rep[1]==0&&rep[2]==1&&rep[3]==1&&rep[4]==1&&rep[5]==1&&rep[6]==1&&rep[7]==1) error=-5;
	if(rep[0]==0&&rep[0]==0&&rep[2]==1&&rep[3]==1&&rep[4]==1&&rep[5]==1&&rep[6]==1&&rep[7]==1) error=-6;
	if(rep[0]==0&&rep[1]==1&&rep[2]==1&&rep[3]==1&&rep[4]==1&&rep[5]==1&&rep[6]==1&&rep[7]==1) error=-7;
		
  if((mode==2)||(mode==6)||(mode==12))error=-error;//逻辑相反
	return error; 
}
double PID_value2;
void PWM_renovate(u16 M1,u16 M2)  //电机PWM刷新
{
	 		TIM_SetCompare1(TIM3,M1);	   
   		TIM_SetCompare2(TIM3,M2);	
}
double PID_value;
double PID_error;
void Line_Following(u8 mode_line)
{
	  switch(mode_line)  //电机初始化设置
	  {
			case 0:Go_away();break;//直走带PID
			case 1:Stop();break;//停车
			case 2:Go_back();break;//倒车带PID
			case 3:turnleft();break;//左转
			case 4:turnright();break;//右转
			case 5:Go_away();break;//高速直走带PID用于变速
			case 6:Go_back();break;//高速倒车带PID用于变速
			case 10:Go_away();break;//慢速直走PID未调
			case 12:Go_back();break;//慢速倒车PID未调
			case 22:Go_backl();break;//22-25为停车校正用
			case 23:Go_backr();break;
			case 24:Go_awayl();break;
			case 25:Go_awayr();break;
			case 26:Go_back();break;//26-29蹭边专用
			case 27:Go_back();break;
			case 28:Go_away();break;
			case 29:Go_away();break;
			case 30:Go_away();break;//延时专用无PID正直走
			case 31:Go_away();break;//延时专用无PID慢速直走
			case 32:Go_back();break;
			case 33:Go_back();break;
      default:break;				
	  };
		PID_error=get_error(mode_line);
    PID_value=PID_run(&Line_PID,PID_error);   //计算出误差	
		if(fabs(PID_value)>199) {PID_value=(PID_value>0?199:-199);}
		 switch(mode_line)//PWM刷新
	  {
		   case 0:PWM_renovate(233-PID_value,250+PID_value); break;
			 case 1:PWM_renovate(0,0);break;
			 case 2:PWM_renovate(233-PID_value,250+PID_value);break;
			 case 3:PWM_renovate(300,320);break;
			 case 4:PWM_renovate(300,320);break;
			 case 5:PWM_renovate(280-PID_value,300+PID_value); break;
			 case 6:PWM_renovate(280-PID_value,300+PID_value);break;
			 case 10:PWM_renovate(188-PID_value,200+PID_value); break;
			 case 12:PWM_renovate(188-PID_value,200+PID_value);break;
			 case 22:PWM_renovate(0,200);break;
			 case 23:PWM_renovate(188,0);break;
			 case 24:PWM_renovate(0,200);break;
			 case 25:PWM_renovate(188,0);break;
			 case 26:PWM_renovate(165,210);break;
			 case 27:PWM_renovate(220,650);break;
			 case 28:PWM_renovate(165,200);break;
			 case 29:PWM_renovate(250,180);break;
			 case 30:PWM_renovate(250,260); break;
			 case 31:PWM_renovate(200,220); break;
			 case 32:PWM_renovate(250,260); break;
			 case 33:PWM_renovate(200,220); break;
       default:break;	//跳出			
	  };
		
}

void count_line(int numberline,int rmode,int pidflag)//数线数停车rmode代表方向正向0倒车1
{
	smode=rmode;//将行走方向传给中断中的数线函数
	countflag=1;//数线函数数线标志
	if(numberline<6)
	{
		for(;/*(*/nline<numberline/*)&&(nline1<numberline)*/;)
		{
			if(rmode==0)
			{
				if(pidflag==1)
				{
					mode=0;//直走
				}
				else if(pidflag==0)//无PID模式
				{
					mode=31;//无PID直走
				}
			}
			else if(rmode==1)
			{
				if(pidflag==1)
				{
					mode=2;//倒退
				}
				else if(pidflag==0)//无PID模式
				{
					mode=33;//无PID倒退
				}
			}
		}
  }
	else
	{
		for(;nline<2;)
		{
			if(rmode==0)
			{
				if(pidflag==1)
				{
					mode=0;//直走
				}
				else if(pidflag==0)//无PID模式
				{
					mode=31;//无PID直走
				}
			}
			else if(rmode==1)
			{
				if(pidflag==1)
				{
					mode=2;//倒退
				}
				else if(pidflag==0)//无PID模式
				{
					mode=33;//无PID倒退
				}
			}
		}
		for(;nline<(numberline-2);)
		{
			if(rmode==0)
			{
				if(pidflag==1)
				{
					mode=5;//直走
				}
				else if(pidflag==0)//无PID模式
				{
					mode=31;//无PID直走
				}
			}
			else if(rmode==1)
			{
				if(pidflag==1)
				{
					mode=6;//倒退
				}
				else if(pidflag==0)//无PID模式
				{
					mode=33;//无PID倒退
				}
			}
		}
		for(;nline<numberline;)
		{
			if(rmode==0)
			{
				if(pidflag==1)
				{
					mode=0;//直走
				}
				else if(pidflag==0)//无PID模式
				{
					mode=31;//无PID直走
				}
			}
			else if(rmode==1)
			{
				if(pidflag==1)
				{
					mode=2;//倒退
				}
				else if(pidflag==0)//无PID模式
				{
					mode=33;//无PID倒退
				}
			}
		}
	}
	countflag=0;//数线函数关闭
	mode=1;//停车
	delay_ms(200);//延时停车缓冲
	if(rmode==0)//停车校正
	{
		if((RROAD1==1&&RROAD2==1&&RROAD3==1&&RROAD4==0)||(RROAD1==1&&RROAD2==1&&RROAD3==0&&RROAD4==0))
		{
			for(;(RROAD2!=0);)//右校正
			{
				mode=23;
			}
		}
		else if((RROAD1==0&&RROAD2==1&&RROAD3==1&&RROAD4==1)||(RROAD1==0&&RROAD2==0&&RROAD3==0&&RROAD4==0))
		{
			for(;(RROAD3!=0);)
		  {
			  mode=25;
		  }
		}
		if((LROAD5==1&&LROAD6==1&&LROAD7==1&&LROAD8==0)||(LROAD5==1&&LROAD6==1&&LROAD7==0&&LROAD8==0))
		{
			for(;(LROAD6!=0);)//左校正
			{
				mode=22;
			}
		}
		else if((LROAD5==0&&LROAD6==1&&LROAD7==1&&LROAD8==1)||(LROAD5==0&&LROAD6==0&&LROAD7==1&&LROAD8==1))
		{
			for(;(LROAD7!=0);)
		  {
			  mode=24;
		  }
		}
	}
	else if(rmode==1)
	{
		if((RROAD1==1&&RROAD2==1&&RROAD3==1&&RROAD4==0)||(RROAD1==1&&RROAD2==1&&RROAD3==0&&RROAD4==0))
		{
			for(;(RROAD2!=0);)//右校正
			{
				mode=23;
			}
		}
		else if((RROAD1==0&&RROAD2==1&&RROAD3==1&&RROAD4==1)||(RROAD1==0&&RROAD2==0&&RROAD3==0&&RROAD4==0))
		{
			for(;(RROAD3!=0);)
		  {
			  mode=25;
		  }
		}
		if((LROAD5==1&&LROAD6==1&&LROAD7==1&&LROAD8==0)||(LROAD5==1&&LROAD6==1&&LROAD7==0&&LROAD8==0))
		{
			for(;(LROAD6!=0);)//左校正
			{
				mode=22;
			}
		}
		else if((LROAD5==0&&LROAD6==1&&LROAD7==1&&LROAD8==1)||(LROAD5==0&&LROAD6==0&&LROAD7==1&&LROAD8==1))
		{
			for(;(LROAD7!=0);)
		  {
			  mode=24;
		  }
		}
	}
	mode=1;//停车缓冲
	delay_ms(500);
}
void walkwall(int turnmode)//贴墙的逻辑turnmode是转弯的方向因为只有右边有导轮故turnmode=0
{
	int i,FRROAD1flag=0,thingflag=0;
	mode=0;//直走带PID
	for(;;)
	{
		if(FRROAD1==0)//检测到白线
		{
			mode=1;//停车缓冲
			delay_ms(300);
			break;
		}
	}
	mode=2;//倒车带PID
	for(;;)
	{
		if(FRROAD1==0)//前灰度检测白线
		{
			delay_ms(210);//延时停止
			mode=1;//停车缓冲
			delay_ms(200);
			break;
		}
	}
	turn(1,0);//左转一次
	mode=31;
	delay_ms(150);
	count_line(1,0,0);//数线走一格
	mode=4;//延时转弯一小段使导轮贴住边
	delay_ms(100);
	mode=31;//直走直到检测到仓库墙壁
	for(;;)
	{
		if(THING==0)//检测到仓库墙壁
		{
			mode=1;//停车
			delay_ms(500);//延时缓冲
			break;
		}
	}
}
//void turn(int timer,int direction)//转弯timer为转弯次数direction为转弯方向0为左1为右
//{
//	int i,leftflag=0,rigthflag=0;
//	for(i=0;i<timer;i++)
//	{
//		delay_ms(300);//延时缓冲
//		if(direction==0)//选择方向
//		{
//			mode=3;//倒车
//		  delay_ms(400);//短暂延时
//			mode=100;//使模式进入空
//			for(;;)//检测停止
//		  {
//				timerflag=1;//计时定时器开始计时
//				if(time==370)//延时保险超出时间即停车
//				{
//					mode=1;
//					leftflag=0;
//					rigthflag=0;
//					break;
//				}
//				if((LROAD5==0)&&(leftflag==0))//左右检测停车
//				{
//						IN3=0;
//		        IN4=0;
//					  leftflag=1;
//				}
//				if((RROAD4==0)&&(rigthflag==0))
//				{
//					 IN1=0;//右边
//		       IN2=0;
//					 rigthflag=1;
//				}
//				if(((LROAD5==0)&&(RROAD4==0))||((rigthflag==1)&&(leftflag==1)))//满足停车条件停车
//				{
//				   mode=1;
//					 leftflag=0;
//					 rigthflag=0;
//					 break;
//				}
//		  }
//		}
//		else if(direction==1)
//		{
//			mode=4;
//		  delay_ms(400);
//			mode=100;
//			for(;;)
//		  {
//				timerflag=1;
//				if(time==370)
//				{
//					mode=1;
//					leftflag=0;
//					rigthflag=0;
//					break;
//				}
//				if((LROAD8==0)&&(leftflag==0))
//				{
//					IN3=0;//左边
//		      IN4=0;
//					leftflag=1;
//				}
//				if((RROAD1==0)&&(rigthflag==0))
//				{
//					 IN1=0;//右边
//		       IN2=0;
//					 rigthflag=1;
//				}
//				if(((LROAD8==0)&&(RROAD1==0))||((rigthflag==1)&&(leftflag==1)))//7 2
//				{
//				   mode=1;
//					 leftflag=0;
//					 rigthflag=0;
//					 break;
//				}
//		  }
//		}
//		
//	}
//	delay_ms(300);//延时缓冲
//	timerflag=0;//停止计时
//	time=0;//计时量清零
//}
void turn(int timer,int direction)//转弯timer为转弯次数direction为转弯方向0为左1为右（带软件滤波）
{
	int i,leftflag=0,rigthflag=0,timer_left=0,timer_right=0;
	for(i=0;i<timer;i++)
	{
		delay_ms(300);//延时缓冲
		if(direction==0)//选择方向
		{
			mode=3;//倒车
		  delay_ms(400);//短暂延时
			mode=100;//使模式进入空
			for(;;)//检测停止
		  {
				timerflag=1;//计时定时器开始计时
				if(time==370)//延时保险超出时间即停车
				{
					mode=1;
					leftflag=0;
					rigthflag=0;
					timer_left=0;
					timer_right=0;
					break;
				}
				if((LROAD5==0)&&(leftflag==0))//左右检测停车
				{
					timer_left++;
					if(timer_left==10)
					{
						IN3=0;
		        IN4=0;
					  leftflag=1;
						timer_left=0;
					}
				}
				if((RROAD4==0)&&(rigthflag==0))
				{
					timer_right++;
					if(timer_right==10)
					{
					  IN1=0;//右边
		        IN2=0;
					  rigthflag=1;
						timer_right=0;
					}
				}
				if((rigthflag==1)&&(leftflag==1))//满足停车条件停车
				{
				   mode=1;
					 leftflag=0;
					 rigthflag=0;
					 timer_left=0;
					 timer_right=0;
					 break;
				}
		  }
		}
		else if(direction==1)
		{
			mode=4;
		  delay_ms(400);
			mode=100;
			for(;;)
		  {
				timerflag=1;
				if(time==370)
				{
					mode=1;
					leftflag=0;
					rigthflag=0;
					timer_left=0;
					timer_right=0;
					break;
				}
				if((LROAD8==0)&&(leftflag==0))
				{
					timer_left++;
					if(timer_left==10)
					{
					  IN3=0;//左边
		        IN4=0;
					  leftflag=1;
						timer_left=0;
					}
				}
				if((RROAD1==0)&&(rigthflag==0))
				{
					timer_right++;
					if(timer_right==10)
					{
					  IN1=0;//右边
		        IN2=0;
					  rigthflag=1;
						timer_right=0;
					}
				}
				if((rigthflag==1)&&(leftflag==1))//7 2
				{
				   mode=1;
					 leftflag=0;
					 rigthflag=0;
					 timer_left=0;
					 timer_right=0;
					 break;
				}
		  }
		}
		
	}
	delay_ms(300);//延时缓冲
	timerflag=0;//停止计时
	time=0;//计时量清零
}
void leave_wall(void)//从仓库中离开切入货架的函数
{
	count_line(1,0,0);
	mode=4;
	delay_ms(750);
	mode=1;
	delay_ms(300);
	count_line(1,0,0);
	turn(1,1);
	count_line(2,1,1);
	turn(1,1);	
}
void finding(int goods_shelf)
{
	int first,second,third,fourthly;
	switch(goods_shelf)
	{
		case 0:first=0,second=1,third=2,fourthly=3;break;//货架A
		case 3:first=1,second=2,third=3,fourthly=0;break;//货架B
		case 2:first=2,second=3,third=0,fourthly=1;break;//货架C
		case 1:first=3,second=0,third=1,fourthly=2;break;//货架D
		default:break;	//跳出
	}
	if(goods_shelf==0)
	{
	}
	else
	{
		walkwall(0);//切入贴墙
	}
	warehouse_finding(goods_shelf,first);
	change_wall();//转弯换边
	warehouse_finding(goods_shelf,second);
	change_wall();
	warehouse_finding(goods_shelf,third);
	change_wall();
	warehouse_finding(goods_shelf,fourthly);
	leave_wall();
}
//void take_photo()//拍照函数
//{
//	int times=0,things=0,flag=0,i,photo_timers=0,sameflag=0;
//	int short_lived[20];
//	walkwall(0);//切入墙壁
//	take_photo_mechanical_grip();//机械臂拍照姿势
//	delay_ms(1000);//延时等待机械臂到达位置
//	delay_ms(1000);
//	delay_ms(1000);
//	for(;;)//找物循环
//	{
//		mode=31;//盲冲
//		for(;;)
//		{	
//			if(THING==1)//如果没检测到物品
//			{
//				flag=1;//标志为1
//			}
//			if((THING==0)&&(flag==1))//检测到物品且上次未检测到物品
//			{
//				
//				mode=1;//停车
//				delay_ms(500);//延时缓冲
//				things++;//记录物品个数
//				flag=0;//标志为0
//				break;//跳出找物循环
//			}
//		}
//		for(;;)//拍照循环
//		{
//			flicker=1;//高电平为闪光灯亮起
//			delay_ms(800);//延时等待灯达到最佳亮度
//			signal=1;//拍照信号
//			delay_ms(200);//延时消抖
//			signal=0;//关闭拍照信号以防止快速的重复拍照
//			delay_ms(1000);//延时等待
//			flicker=0;//关闭闪光灯
//			delay_ms(200);//延时等待防止拍照间隔过短
//			delay_ms(1000);
//			for(;;)
//			{
//				if(photoflag==1)//如果串口接收中断被触发
//				{
//					photoflag=0;//归零
//					break;//跳出等待循环
//				}
//			}
//			if(aaa==52)//如果图像反馈为未识别的信号52则补执行下面的逻辑
//			{
//				continue;
//			}
//			short_lived[photo_timers]=aaa;//暂存图像结果
//			for(i=0;i<photo_timers;i++)//循环检验是否有两个一样的结果若一样则为最终结果
//			{
//				if((aaa==short_lived[i])&&(photo_timers>0))
//				{
//					for(i=0;i<12;i++)//红牛和乐虎的转码
//					{
//							if((7==location[i])||(8==location[i]))
//							{
//								if(aaa==6)
//								{
//									aaa=7;
//								}
//								else if(aaa==7)
//								{
//									aaa=6;
//								}
//							}
//					}
//					if((aaa>0)&&(aaa<52))//将结果转为0到11的物品代号
//					{
//						if(aaa==1)
//						{
//							location[times]=0;
//						}
//						else if(aaa==2)
//						{
//							location[times]=1;
//						}
//						else if(aaa==3)
//						{
//							location[times]=2;
//						}
//						else if(aaa==4)
//						{
//							location[times]=9;
//						}
//						else if(aaa==5)
//						{
//							location[times]=6;
//						}
//						else if(aaa==6)
//						{
//							location[times]=7;
//						}
//						else if(aaa==7)
//						{
//							location[times]=8;
//						}
//						else if(aaa==8)
//						{
//							location[times]=3;
//						}
//						else if(aaa==9)
//						{
//							location[times]=11;
//						}
//						else if(aaa==49)
//						{
//							location[times]=4;
//						}
//						else if(aaa==50)
//						{
//							location[times]=5;
//						}
//						else if(aaa==51)
//						{
//							location[times]=10;
//						}
//						aaa=0;
//						times++;
//						sameflag=1;
//						break;
//					}
//				}
//			 }
//			 if(sameflag==1)//存在两个相同照片退出拍照循环
//			 {
//				 sameflag=0;
//				 break;
//			 }
//			 photo_timers++;
//	  }
//		for(i=0;i<10;i++)//初始化暂存数组
//		{
//			photo_timers=0;
//			short_lived[i]=0;
//		}
//		if(things%3==0)//如果已经拍了三个物品就换一面墙
//		{
//			count_line(1,0,0);
//			change_wall();
//		}
//		if(things==12)//拍完12个退出整个循环
//		{
//			break;
//		}
//	}
//}
void take_photo()//拍照函数
{
	int times=0,things=0,flag=0,i,photo_timers=0,sameflag=0,flickerflag=0;
	int short_lived[20];
	walkwall(0);//切入墙壁
	take_photo_mechanical_grip();//机械臂拍照姿势
	delay_ms(1000);//延时等待机械臂到达位置
	delay_ms(1000);
	delay_ms(1000);
	for(;;)//找物循环
	{
		mode=31;//盲冲
		for(;;)
		{	
			if(THING==1)//如果没检测到物品
			{
				flag=1;//标志为1
			}
			if((THING==0)&&(flag==1))//检测到物品且上次未检测到物品
			{
				
				mode=1;//停车
				delay_ms(500);//延时缓冲
				things++;//记录物品个数
				flag=0;//标志为0
				break;//跳出找物循环
			}
		}
		for(;;)//拍照循环
		{
			if(flickerflag==1)
			{
			   flicker=1;//高电平为闪光灯亮起
			}
			delay_ms(800);//延时等待灯达到最佳亮度
			signal=1;//拍照信号
			for(;;)
			{
				if(aaa==55)
				{
					aaa=0;
				  break;
				}
			}
			signal=0;//关闭拍照信号以防止快速的重复拍照
			delay_ms(1000);//延时等待
			flicker=0;//关闭闪光灯
			delay_ms(200);//延时等待防止拍照间隔过短
			delay_ms(1000);
			for(;;)
			{
				if(photoflag==1)//如果串口接收中断被触发
				{
					photoflag=0;//归零
					break;//跳出等待循环
				}
			}
			if(aaa==52)//如果图像反馈为未识别的信号52则补执行下面的逻辑
			{
				continue;
			}
			if((aaa==1)||(aaa==2)||(aaa==3)||(aaa==5)||(aaa==6)||(aaa==7))
			{
				flickerflag=1;
			}
			short_lived[photo_timers]=aaa;//暂存图像结果
			for(i=0;i<photo_timers;i++)//循环检验是否有两个一样的结果若一样则为最终结果
			{
				if((aaa==short_lived[i])&&(photo_timers>0))
				{
					for(i=0;i<12;i++)//红牛和乐虎的转码
					{
							if((7==location[i])||(8==location[i]))
							{
								if(aaa==6)
								{
									aaa=7;
								}
								else if(aaa==7)
								{
									aaa=6;
								}
							}
					}
					if((aaa>0)&&(aaa<52))//将结果转为0到11的物品代号
					{
						if(aaa==1)
						{
							location[times]=0;
						}
						else if(aaa==2)
						{
							location[times]=1;
						}
						else if(aaa==3)
						{
							location[times]=2;
						}
						else if(aaa==4)
						{
							location[times]=9;
						}
						else if(aaa==5)
						{
							location[times]=6;
						}
						else if(aaa==6)
						{
							location[times]=7;
						}
						else if(aaa==7)
						{
							location[times]=8;
						}
						else if(aaa==8)
						{
							location[times]=3;
						}
						else if(aaa==9)
						{
							location[times]=11;
						}
						else if(aaa==49)
						{
							location[times]=4;
						}
						else if(aaa==50)
						{
							location[times]=5;
						}
						else if(aaa==51)
						{
							location[times]=10;
						}
						aaa=0;
						times++;
						sameflag=1;
						flickerflag=0;
						break;
					}
				}
			 }
			 if(sameflag==1)//存在两个相同照片退出拍照循环
			 {
				 sameflag=0;
				 break;
			 }
			 photo_timers++;
	  }
		for(i=0;i<10;i++)//初始化暂存数组
		{
			photo_timers=0;
			short_lived[i]=0;
		}
		if(things%3==0)//如果已经拍了三个物品就换一面墙
		{
			count_line(1,0,0);
			change_wall();
		}
		if(things==12)//拍完12个退出整个循环
		{
			break;
		}
	}
}

void start(void)//启动函数延时约10s启动然后盲冲一段后开始循迹
{
	int i;
	for(i=0;i<10;i++)
	{
	  delay_ms(1000);
	}
	mode=30;
	delay_ms(700);
	mode=1;
}
//void shuxian(u16 flag,u16 smode)//数线函数flag是启动与清零标志1为启动0为清零smode代表前进与后退
//{
//	
//	if(flag==0)//清零模式
//	{
//		nline=0;
//		sx=0;
//	}
//	else//数线模式
//	{
//		if(smode==0)
//		{
//		  if((LROAD5==1)&&(sx==0))//检测黑色
//		  {
//			  sx=2;
//		  }
//		  if((LROAD5==0)&&(sx==2))//检测白色
//		  {
//			  nline++;
//			  sx=0;
//		  }
//		}
//		else
//		{
//			if((LROAD8==1)&&(sx==0))
//		  {
//			  sx=2;
//		  }
//		  if((LROAD8==0)&&(sx==2))
//		  {
//			  nline++;
//			  sx=0;
//		  }
//		}
//	}
//}
void shuxian(u16 flag,u16 smode)//数线函数flag是启动与清零标志1为启动0为清零smode代表前进与后退（带软件滤波）
{
	static int smoothing=0;//计数标志用于滤波，因为需要不断调用函数故使用局部静态变量保存计数次数
  if(flag==0)//清零模式
  {
		smoothing=0;
		nline=0;
		nline1=0;
		sx1=0;
		sx=0;
	}
	else//数线模式
	{
		if(smode==0)
		{
		  if((LROAD5==1)&&(sx==0))//检测黑色
		  {
				smoothing++;//检测次数
				if(smoothing==10)//当检测次数达到10次时才确定是黑色减少因为杂波或者干扰导致的不稳定现象
				{
			    sx=2;//确认进入下一步
					smoothing=0;//清零
				}
		  }
			if((LROAD5==0)&&(sx==2))//检测白色
		  {
				smoothing++;
				if(smoothing==10)
				{
					smoothing=0;
			    nline++;
			    sx=0;
				}
		  }
//			if((RROAD1==1)&&(sx1==0))//检测黑色
//		  {
//			  sx1=2;
//		  }
//		  if((RROAD1==0)&&(sx1==2))//检测白色
//		  {
//			  nline1++;
//			  sx1=0;
//		  }
		}
		else
		{
			if((LROAD8==1)&&(sx==0))
		  {
				smoothing++;//记录10次黑色
				if(smoothing==10)
				{
			    sx=2;
					smoothing=0;
				}
		  }
		  if((LROAD8==0)&&(sx==2))
		  {
				smoothing++;//记录十次白色为一条白线消抖处理
				if(smoothing==10)
				{
			    nline++;
			    sx=0;
					smoothing=0;
				}
		  }
//			if((RROAD4==1)&&(sx1==0))
//		  {
//			  sx1=2;
//		  }
//		  if((RROAD4==0)&&(sx1==2))
//		  {
//			  nline1++;
//			  sx1=0;
//		  }
		}
	}
}

void TIM4_IRQHandler(void)   //TIM4中断用于控制
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//检查指定的TIM中断发生与否:TIM 中断源 
		{
			shuxian(countflag,smode);//数线
			Line_Following(mode);//模式调整
		  TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );//清除TIMx的中断待处理位:TIM 中断源 
		}
}
void TIM6_IRQHandler(void)   //TIM6中断用于定时1ms一次
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)//检查指定的TIM中断发生与否:TIM 中断源 
		{
			if(timerflag==1)//计时计数
			{ 
			   time++;
			}
		  TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );//清除TIMx的中断待处理位:TIM 中断源 
		}
}
char dis_dj[20];


void TIM7_IRQHandler(void)   //TIM7用于OLED显示
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)//检查指定的TIM中断发生与否:TIM 中断源 
		{
			OLED_Refresh_Gram();
			OLED_ShowNum(0,40,photoflag,3,16);
			sprintf(dis_dj,"%d",aaa);//显示图像反值
			OLED_ShowString(0,2,(u8*)dis_dj);//与上一句连用显示图像反值
//		OLED_ShowNum(0,20,THING,1,16);//下层寻物光电开关状态显示
//		OLED_ShowNum(0,40,time,4,16);//计时器中断次数显示
//		OLED_ShowNum(0,40,FRROAD1,1,16);//前排灰度显示front
//		OLED_ShowNum(10,40,FRROAD2,1,16);
//		OLED_ShowNum(20,40,FRROAD3,1,16);
//	  OLED_ShowNum(30,40,FRROAD4,1,16);
//		OLED_ShowNum(40,40,FRROAD5,1,16);
//		OLED_ShowNum(50,40,FRROAD6,1,16);
//		OLED_ShowNum(60,40,FRROAD7,1,16);	
//		OLED_ShowNum(70,40,FRROAD8,1,16);
//		OLED_ShowNum(0,40,REROAD1,1,16);//后排灰度显示
//		OLED_ShowNum(10,40,REROAD2,1,16);
//		OLED_ShowNum(20,40,REROAD3,1,16);
//		OLED_ShowNum(30,40,REROAD4,1,16);
//		OLED_ShowNum(40,40,REROAD5,1,16);
//		OLED_ShowNum(50,40,REROAD6,1,16);
//		OLED_ShowNum(60,40,REROAD7,1,16);	
//		OLED_ShowNum(70,40,REROAD8,1,16);
//		OLED_ShowNum(0,40,RROAD1,1,16);//右边灰度
//		OLED_ShowNum(10,40,RROAD2,1,16);
//		OLED_ShowNum(20,40,RROAD3,1,16);
//		OLED_ShowNum(30,40,RROAD4,1,16);
//	  OLED_ShowNum(40,40,LROAD5,1,16);//左边灰度
//		OLED_ShowNum(50,40,LROAD6,1,16);
//		OLED_ShowNum(60,40,LROAD7,1,16);	
//		OLED_ShowNum(70,40,LROAD8,1,16);
		  TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );//清除TIMx的中断待处理位:TIM 中断源 
		}
}
