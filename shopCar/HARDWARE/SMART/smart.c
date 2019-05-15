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


int location[12]={13,13,13,13,13,13,13,13,13,13,13,13};//位置数组
int hope[4][3]={{0,1,2},{3,4,5},{6,7,8},{9,10,11}};//期望数组按照货架顺序排布
extern u8 finishflag;
extern u16 mode;

void take_photo_mechanical_grip(void)//机械手拍照姿势不能与初始化连用不然会有bug
{
	int flag=0;//状态标志
	for(;;)
	{
		  if(flag==0)//发送允许
				{
				  USART_SendData(USART2,30);//发送信号      
		      while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);//等待信号发送完毕 
				}
				if((finishflag<99)&&(finishflag>0))//机械臂开始动作信号
				{
					flag=1;//关闭发送
				}
				if(finishflag==30)//动做完成标志99和复位完成标志1
				{
					finishflag=0;//标志位清除
					flag=0;
					break;
				}
	}
}
void init_mechanical_grip()///机械手初始化函数
{
	int flag=0;//状态标志
	for(;;)
	{
		  if(flag==0)//发送允许
				{
				  USART_SendData(USART2,1);//发送信号      
		      while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);//等待信号发送完毕 
				}
				if(finishflag==10)//机械臂开始动作信号
				{
					flag=1;//关闭发送
				}
				if(finishflag==1)//动做完成标志99和复位完成标志1
				{
					finishflag=0;//标志位清除
					flag=0;
					break;
				}
	}
}
void mechanical_grip(int mode)//舵机驱动通讯函数(抓取)
{
	int flag=0;//状态标志
	for(;;)
	{
		  if(flag==0)//发送允许
				{
				  USART_SendData(USART2,mode+2);//发送信号      
		      while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);//等待信号发送完毕 
				}
				if((finishflag<99)&&(finishflag>0))//机械臂开始动作信号
				{
					flag=1;//关闭发送
				}
				if(finishflag==99)//动做完成标志99和复位完成标志1
				{
					finishflag=0;//标志位清除
					flag=0;
					break;
				}
	}
}
//void put_thing(int goods)
//{
//	int first,second,thrid;
//	int flag=0;
//	switch(goods)
//	{
//		case 1:first=22;second=23;thrid=24;break;
//		case 2:first=17;second=18;thrid=19;break;
//		case 3:first=17;second=18;thrid=19;break;
//		case 4:first=12;second=20;thrid=19;break;
//	}
//	delay_ms(100);
//	mechanical_grip(first);
//	mode=26;
//	for(;;)
//	{
//		if(REROAD1==1)
//		{
//			flag=1;
//			delay_ms(50);
//		}
//		if((REROAD1==0)&&(flag==1))
//		{
//			flag=0;
//			mode=1;
//			delay_ms(300);
//			break;
//		}
//	}
//	mechanical_grip(second);
//	mode=26;
//	for(;;)
//	{
//		if(REROAD1==1)
//		{
//			flag=1;
//			delay_ms(50);
//		}
//		if((REROAD1==0)&&(flag==1))
//		{
//			flag=0;
//			mode=1;
//			delay_ms(300);
//			break;
//		}
//	}
//	mechanical_grip(thrid);
//	count_line(4,0,1);
//}
void put_thing(int goods)//放物函数goods代表货架号码
{
	int first,second,thrid;
	int flag=0,top=0,behind=0,line=0,move_timer=0,putflag=0;
	for(;;)//盲走后冲使后灰度碰到白线
	{
		delay_ms(100);
		mode=26;
		for(;;)
		{
			if(REROAD1==0)
			{
				mode=1;//停车
				break;
			}
		}
		delay_ms(100);//延时缓冲
		mode=26;//盲走后冲
		for(;;)
		{
			if(TOP==0)//检测货架上层有没有物品
			{
				top=1;
			}
			if(THING==0)//检测货架下层有没有货物
			{
				behind=1;
			}
			if(RROAD3==1)//侧灰度先检测到黑色
			{
				flag=1;
				delay_ms(50);
			}
			if((RROAD3==0)&&(flag==1))//测灰度检测到白线
			{
				mode=1;
				delay_ms(200);
				for(;(RROAD3!=0);)//停车校正减少数线错误可能性
		    {
			    mode=25;
		    }
		    for(;(LROAD7!=0);)
		    {
			    mode=24;
		    }
				flag=0;
				mode=1;//停车并延时缓冲
				delay_ms(300);
				break;
			}
		}
		move_timer++;//移动次数自加
		if(top==0)//如果上层没有货物执行智能放物
		{
			smart_put_thing(0);
			putflag++;//放置次数增加
			if(putflag==3)//当放置次数达到三跳出循环完成放物
		  {
			  break;
		  }
		}
		else
		{
			top=0;//如果有货物标志清零
		}
		if(behind==0)
		{
			smart_put_thing(1);
			putflag++;
			if(putflag==3)
		  {
			  break;
		  }
		}
		else
		{
			behind=0;
		}
	}
	count_line(move_timer+1,0,1);//放物完成根据移动次数数线离开货架
}
void smart_put_thing(int view_flag)//“智能“放物函数�
{
	static int put_timer=0;//用来记录函数被调用多少次全程总共12次
	int loaction=0;
	if(view_flag==0)//判断是上层还是下层
	{
		switch(put_timer)//选取要发送的数字
		{
			case 0:loaction=24;break;//左木上26
			case 1:loaction=23;break;//中木上25
			case 2:loaction=22;break;//右木上24
			case 3:loaction=19;break;//左通上21
			case 4:loaction=18;break;//中通上20
			case 5:loaction=17;break;//右通上19
			case 6:loaction=19;break;
			case 7:loaction=18;break;
			case 8:loaction=17;break;
			case 9:loaction=19;break;
			case 10:loaction=20;break;//球上22
			case 11:loaction=12;break;//魔方上14
		}
	}
	else
	{
		switch(put_timer)
		{
			case 0:loaction=27;break;//左木下29
			case 1:loaction=26;break;//中木下28
			case 2:loaction=25;break;//右木下27
			case 3:loaction=16;break;//左通下18
			case 4:loaction=15;break;//中通下17
			case 5:loaction=14;break;//右通下16
			case 6:loaction=16;break;
			case 7:loaction=15;break;
			case 8:loaction=14;break;
			case 9:loaction=16;break;
			case 10:loaction=21;break;//球下23
			case 11:loaction=13;break;//魔方下15
		}
	}
	mechanical_grip(loaction);//机械抓放物
	put_timer++;//函数调用次数增加
}
void thing_loction(int point1,int point2,int point3)//仓库一面抓物函数
{
	int flag=0;
	if((point1==0)||(point1==3)||(point1==6)||(point1==9))//第一位置抓取物
	{
		mode=31;//盲走寻物
		for(;;)
		{
			if(THING==1)//没有检测到物品
			{
				flag=1;
			}
			if((THING==0)&&(flag==1))//检测到物品
			{
				mode=1;//停车
				break;
			}
		}
		mode=33;
		delay_ms(70);
		mode=1;
		mechanical_grip(location[point1]);//执行相应动作
	}
	if((point2==1)||(point2==4)||(point2==7)||(point2==10))//第二位置抓取物
	{
		count_line(1,0,0);//数线一格
		mode=31;//盲走检测
		for(;;)
		{
			if(THING==0)
			{
				 mode=1;
				 break;
			}
		}
		mode=33;
		delay_ms(70);
		mode=1;
		mechanical_grip(location[point2]);//执行相应抓取物
	}
	else if(point2==13)//若为空标志则直走一格
	{
		count_line(1,0,0);
	}
	if((point3==2)||(point3==5)||(point3==8)||(point3==11))//第三位置抓取物
	{
		mode=31;//盲走
		for(;;)
		{
			if(REROAD8==0)//后灰度检测到白线
			{
				 mode=1;
				 break;
			}
		}
		mode=31;//盲走
		for(;;)
		{
			if(THING==0)//检测到物品
			{
				 mode=1;//停车
				 break;
			}
		}
		mode=33;
		delay_ms(70);
		mode=1;
		mechanical_grip(location[point3]);//执行相应抓取
		count_line(1,0,0);//盲走一格
	}
	else if(point3==13)//若为空标志则直走一格
	{
		count_line(1,0,0);
	}
	
}
int fill[3]={13,13,13};//货舱单面位置标识，13代表空
void change_wall(void)//货舱墙面转换函数
{
	mode=4;//延时盲转
	delay_ms(1200);
	mode=1;
	delay_ms(300);
	mode=31;
	for(;;)//直走直到检测到仓库墙壁
	{
		if(THING==0)
		{
			mode=1;
			break;
		}
	}
	delay_ms(300);
}
void clearfill(void)//初始化货仓单面数组
{
	int i;
	for(i=0;i<3;i++)
	{
		fill[i]=13;
	}
}
void warehouse_finding(int start_location,int corner)//货仓找物，corner代表货仓面号，start_location代表货架序号
{
  int i,j,flag=0,hopeflag=0;
	clearfill();
	if(corner==0)
	{
		for(i=0;i<3;i++)//通过期望数组与图像识别返回的包含货物信息的位置数组比较判断该货仓面是否需要抓取
		{
			for(j=0;j<3;j++)
			{
				 if(hope[start_location][j]==location[i])
				 {
						fill[flag]=i;
						hopeflag=1;
				 }
			}
			flag++;
		 }
		 if(hopeflag!=0)//如果需要抓取执行抓取逻辑
		 {
			 thing_loction(fill[0],fill[1],fill[2]);
			 clearfill();
			 hopeflag=0;
			 flag=0;
		 }
		 else//如果不需要抓取则略过该面
		 {
			 count_line(2,0,0);
			 flag=0;
		 }
	 }
	 else if(corner==1)
	 {
		 for(i=3;i<6;i++)
		 {
			 for(j=0;j<3;j++)
			 {
				 if(hope[start_location][j]==location[i])
				 {
						fill[flag]=i;
					  hopeflag=1;
				 }
			 }
			 flag++;
		 }
		 if(hopeflag!=0)
		 {
			 thing_loction(fill[0],fill[1],fill[2]);
			 clearfill();
			 hopeflag=0;
			 flag=0;
		 }
		 else
		 {
			 count_line(2,0,0);
			 flag=0;
		 }
	 }
	 else if(corner==2)
	 {
		 for(i=6;i<9;i++)
		 {
			 for(j=0;j<3;j++)
			 {
				 if(hope[start_location][j]==location[i])
				 {
						fill[flag]=i;
					  hopeflag=1;
				 }
			 }
			 flag++;
		 }
		 if(hopeflag!=0)
		 {
			 thing_loction(fill[0],fill[1],fill[2]);
			 clearfill();
			 hopeflag=0;
			 flag=0;
		 }
		 else
		 {
			 count_line(2,0,0);
			 flag=0;
		 }
	 }
	 else if(corner==3)
	 {
		 for(i=9;i<12;i++)
		 {
			 for(j=0;j<3;j++)
			 {
				 if(hope[start_location][j]==location[i])
				 {
						fill[flag]=i;
					  hopeflag=1;
				 }
			 }
			 flag++;
		 }
		 if(hopeflag!=0)
		 {
			 thing_loction(fill[0],fill[1],fill[2]);
			 clearfill();
			 hopeflag=0;
			 flag=0;
		 }
		 else
		 {
			 count_line(2,0,0);
			 flag=0;
		 }
	 }
}

