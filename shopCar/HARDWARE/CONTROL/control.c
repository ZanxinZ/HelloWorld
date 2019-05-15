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
u16 js;//��ʱ����
u16 mode=1;//С��ģʽ������Կ�follow_line��������
u16 sx=0;//�������õ���״̬��־
u16 sx1=0;//���õ����߱�־������ʱû���õ�
u16 js1=0;//��ʱ����
double error=0;//���
int rep[8];//�Ҷ�����
int nline=0;//�����������ڴ������߽��
int nline1=0;//����������ʱ����
int countflag=0;//������־������ʾ��Ҫ������count_line(countflag)��ʹ�ã�1�������ߣ�0����nline����
int timerflag=0;//ʹ�ܶ�ʱ��������ʼ���������Ƶ�����time�ﵥλΪms
int time=0;//���ڼǶ�ʱ���ж����ڶ���ļ�ʱ����
int smode=0;
int photoflag=0;//���ձ�־

extern int fill[3];
extern int finishflag;
extern u16 aaa;//ͼ����
extern int location[12];//λ���������ڴ������λ���ϵ���Ʒ����

void Stop(void)
{
	  IN1=0;
		IN2=0;
		IN3=0;
		IN4=0;
}

void Go_away(void)
{
	  IN1=1;//�ұ�
		IN2=0;
		IN3=1;//���
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
	  IN1=0;//�ұ�
		IN2=0;
		IN3=1;//���
		IN4=0;
}
void Go_awayr(void)
{
	  IN1=1;//�ұ�
		IN2=0;
		IN3=0;//���
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
		IN3=1;//���
		IN4=0;
}
void Go_awayrr(void)
{
	  IN1=1;//�ұ�
		IN2=0;
}
double get_error(u8 mode)//�õ����
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
	//���ߺ���+��������	
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
		
  if((mode==2)||(mode==6)||(mode==12))error=-error;//�߼��෴
	return error; 
}
double PID_value2;
void PWM_renovate(u16 M1,u16 M2)  //���PWMˢ��
{
	 		TIM_SetCompare1(TIM3,M1);	   
   		TIM_SetCompare2(TIM3,M2);	
}
double PID_value;
double PID_error;
void Line_Following(u8 mode_line)
{
	  switch(mode_line)  //�����ʼ������
	  {
			case 0:Go_away();break;//ֱ�ߴ�PID
			case 1:Stop();break;//ͣ��
			case 2:Go_back();break;//������PID
			case 3:turnleft();break;//��ת
			case 4:turnright();break;//��ת
			case 5:Go_away();break;//����ֱ�ߴ�PID���ڱ���
			case 6:Go_back();break;//���ٵ�����PID���ڱ���
			case 10:Go_away();break;//����ֱ��PIDδ��
			case 12:Go_back();break;//���ٵ���PIDδ��
			case 22:Go_backl();break;//22-25Ϊͣ��У����
			case 23:Go_backr();break;
			case 24:Go_awayl();break;
			case 25:Go_awayr();break;
			case 26:Go_back();break;//26-29���ר��
			case 27:Go_back();break;
			case 28:Go_away();break;
			case 29:Go_away();break;
			case 30:Go_away();break;//��ʱר����PID��ֱ��
			case 31:Go_away();break;//��ʱר����PID����ֱ��
			case 32:Go_back();break;
			case 33:Go_back();break;
      default:break;				
	  };
		PID_error=get_error(mode_line);
    PID_value=PID_run(&Line_PID,PID_error);   //��������	
		if(fabs(PID_value)>199) {PID_value=(PID_value>0?199:-199);}
		 switch(mode_line)//PWMˢ��
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
       default:break;	//����			
	  };
		
}

void count_line(int numberline,int rmode,int pidflag)//������ͣ��rmode����������0����1
{
	smode=rmode;//�����߷��򴫸��ж��е����ߺ���
	countflag=1;//���ߺ������߱�־
	if(numberline<6)
	{
		for(;/*(*/nline<numberline/*)&&(nline1<numberline)*/;)
		{
			if(rmode==0)
			{
				if(pidflag==1)
				{
					mode=0;//ֱ��
				}
				else if(pidflag==0)//��PIDģʽ
				{
					mode=31;//��PIDֱ��
				}
			}
			else if(rmode==1)
			{
				if(pidflag==1)
				{
					mode=2;//����
				}
				else if(pidflag==0)//��PIDģʽ
				{
					mode=33;//��PID����
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
					mode=0;//ֱ��
				}
				else if(pidflag==0)//��PIDģʽ
				{
					mode=31;//��PIDֱ��
				}
			}
			else if(rmode==1)
			{
				if(pidflag==1)
				{
					mode=2;//����
				}
				else if(pidflag==0)//��PIDģʽ
				{
					mode=33;//��PID����
				}
			}
		}
		for(;nline<(numberline-2);)
		{
			if(rmode==0)
			{
				if(pidflag==1)
				{
					mode=5;//ֱ��
				}
				else if(pidflag==0)//��PIDģʽ
				{
					mode=31;//��PIDֱ��
				}
			}
			else if(rmode==1)
			{
				if(pidflag==1)
				{
					mode=6;//����
				}
				else if(pidflag==0)//��PIDģʽ
				{
					mode=33;//��PID����
				}
			}
		}
		for(;nline<numberline;)
		{
			if(rmode==0)
			{
				if(pidflag==1)
				{
					mode=0;//ֱ��
				}
				else if(pidflag==0)//��PIDģʽ
				{
					mode=31;//��PIDֱ��
				}
			}
			else if(rmode==1)
			{
				if(pidflag==1)
				{
					mode=2;//����
				}
				else if(pidflag==0)//��PIDģʽ
				{
					mode=33;//��PID����
				}
			}
		}
	}
	countflag=0;//���ߺ����ر�
	mode=1;//ͣ��
	delay_ms(200);//��ʱͣ������
	if(rmode==0)//ͣ��У��
	{
		if((RROAD1==1&&RROAD2==1&&RROAD3==1&&RROAD4==0)||(RROAD1==1&&RROAD2==1&&RROAD3==0&&RROAD4==0))
		{
			for(;(RROAD2!=0);)//��У��
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
			for(;(LROAD6!=0);)//��У��
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
			for(;(RROAD2!=0);)//��У��
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
			for(;(LROAD6!=0);)//��У��
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
	mode=1;//ͣ������
	delay_ms(500);
}
void walkwall(int turnmode)//��ǽ���߼�turnmode��ת��ķ�����Ϊֻ���ұ��е��ֹ�turnmode=0
{
	int i,FRROAD1flag=0,thingflag=0;
	mode=0;//ֱ�ߴ�PID
	for(;;)
	{
		if(FRROAD1==0)//��⵽����
		{
			mode=1;//ͣ������
			delay_ms(300);
			break;
		}
	}
	mode=2;//������PID
	for(;;)
	{
		if(FRROAD1==0)//ǰ�Ҷȼ�����
		{
			delay_ms(210);//��ʱֹͣ
			mode=1;//ͣ������
			delay_ms(200);
			break;
		}
	}
	turn(1,0);//��תһ��
	mode=31;
	delay_ms(150);
	count_line(1,0,0);//������һ��
	mode=4;//��ʱת��һС��ʹ������ס��
	delay_ms(100);
	mode=31;//ֱ��ֱ����⵽�ֿ�ǽ��
	for(;;)
	{
		if(THING==0)//��⵽�ֿ�ǽ��
		{
			mode=1;//ͣ��
			delay_ms(500);//��ʱ����
			break;
		}
	}
}
//void turn(int timer,int direction)//ת��timerΪת�����directionΪת�䷽��0Ϊ��1Ϊ��
//{
//	int i,leftflag=0,rigthflag=0;
//	for(i=0;i<timer;i++)
//	{
//		delay_ms(300);//��ʱ����
//		if(direction==0)//ѡ����
//		{
//			mode=3;//����
//		  delay_ms(400);//������ʱ
//			mode=100;//ʹģʽ�����
//			for(;;)//���ֹͣ
//		  {
//				timerflag=1;//��ʱ��ʱ����ʼ��ʱ
//				if(time==370)//��ʱ���ճ���ʱ�伴ͣ��
//				{
//					mode=1;
//					leftflag=0;
//					rigthflag=0;
//					break;
//				}
//				if((LROAD5==0)&&(leftflag==0))//���Ҽ��ͣ��
//				{
//						IN3=0;
//		        IN4=0;
//					  leftflag=1;
//				}
//				if((RROAD4==0)&&(rigthflag==0))
//				{
//					 IN1=0;//�ұ�
//		       IN2=0;
//					 rigthflag=1;
//				}
//				if(((LROAD5==0)&&(RROAD4==0))||((rigthflag==1)&&(leftflag==1)))//����ͣ������ͣ��
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
//					IN3=0;//���
//		      IN4=0;
//					leftflag=1;
//				}
//				if((RROAD1==0)&&(rigthflag==0))
//				{
//					 IN1=0;//�ұ�
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
//	delay_ms(300);//��ʱ����
//	timerflag=0;//ֹͣ��ʱ
//	time=0;//��ʱ������
//}
void turn(int timer,int direction)//ת��timerΪת�����directionΪת�䷽��0Ϊ��1Ϊ�ң�������˲���
{
	int i,leftflag=0,rigthflag=0,timer_left=0,timer_right=0;
	for(i=0;i<timer;i++)
	{
		delay_ms(300);//��ʱ����
		if(direction==0)//ѡ����
		{
			mode=3;//����
		  delay_ms(400);//������ʱ
			mode=100;//ʹģʽ�����
			for(;;)//���ֹͣ
		  {
				timerflag=1;//��ʱ��ʱ����ʼ��ʱ
				if(time==370)//��ʱ���ճ���ʱ�伴ͣ��
				{
					mode=1;
					leftflag=0;
					rigthflag=0;
					timer_left=0;
					timer_right=0;
					break;
				}
				if((LROAD5==0)&&(leftflag==0))//���Ҽ��ͣ��
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
					  IN1=0;//�ұ�
		        IN2=0;
					  rigthflag=1;
						timer_right=0;
					}
				}
				if((rigthflag==1)&&(leftflag==1))//����ͣ������ͣ��
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
					  IN3=0;//���
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
					  IN1=0;//�ұ�
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
	delay_ms(300);//��ʱ����
	timerflag=0;//ֹͣ��ʱ
	time=0;//��ʱ������
}
void leave_wall(void)//�Ӳֿ����뿪������ܵĺ���
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
		case 0:first=0,second=1,third=2,fourthly=3;break;//����A
		case 3:first=1,second=2,third=3,fourthly=0;break;//����B
		case 2:first=2,second=3,third=0,fourthly=1;break;//����C
		case 1:first=3,second=0,third=1,fourthly=2;break;//����D
		default:break;	//����
	}
	if(goods_shelf==0)
	{
	}
	else
	{
		walkwall(0);//������ǽ
	}
	warehouse_finding(goods_shelf,first);
	change_wall();//ת�任��
	warehouse_finding(goods_shelf,second);
	change_wall();
	warehouse_finding(goods_shelf,third);
	change_wall();
	warehouse_finding(goods_shelf,fourthly);
	leave_wall();
}
//void take_photo()//���պ���
//{
//	int times=0,things=0,flag=0,i,photo_timers=0,sameflag=0;
//	int short_lived[20];
//	walkwall(0);//����ǽ��
//	take_photo_mechanical_grip();//��е����������
//	delay_ms(1000);//��ʱ�ȴ���е�۵���λ��
//	delay_ms(1000);
//	delay_ms(1000);
//	for(;;)//����ѭ��
//	{
//		mode=31;//ä��
//		for(;;)
//		{	
//			if(THING==1)//���û��⵽��Ʒ
//			{
//				flag=1;//��־Ϊ1
//			}
//			if((THING==0)&&(flag==1))//��⵽��Ʒ���ϴ�δ��⵽��Ʒ
//			{
//				
//				mode=1;//ͣ��
//				delay_ms(500);//��ʱ����
//				things++;//��¼��Ʒ����
//				flag=0;//��־Ϊ0
//				break;//��������ѭ��
//			}
//		}
//		for(;;)//����ѭ��
//		{
//			flicker=1;//�ߵ�ƽΪ���������
//			delay_ms(800);//��ʱ�ȴ��ƴﵽ�������
//			signal=1;//�����ź�
//			delay_ms(200);//��ʱ����
//			signal=0;//�ر������ź��Է�ֹ���ٵ��ظ�����
//			delay_ms(1000);//��ʱ�ȴ�
//			flicker=0;//�ر������
//			delay_ms(200);//��ʱ�ȴ���ֹ���ռ������
//			delay_ms(1000);
//			for(;;)
//			{
//				if(photoflag==1)//������ڽ����жϱ�����
//				{
//					photoflag=0;//����
//					break;//�����ȴ�ѭ��
//				}
//			}
//			if(aaa==52)//���ͼ����Ϊδʶ����ź�52��ִ��������߼�
//			{
//				continue;
//			}
//			short_lived[photo_timers]=aaa;//�ݴ�ͼ����
//			for(i=0;i<photo_timers;i++)//ѭ�������Ƿ�������һ���Ľ����һ����Ϊ���ս��
//			{
//				if((aaa==short_lived[i])&&(photo_timers>0))
//				{
//					for(i=0;i<12;i++)//��ţ���ֻ���ת��
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
//					if((aaa>0)&&(aaa<52))//�����תΪ0��11����Ʒ����
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
//			 if(sameflag==1)//����������ͬ��Ƭ�˳�����ѭ��
//			 {
//				 sameflag=0;
//				 break;
//			 }
//			 photo_timers++;
//	  }
//		for(i=0;i<10;i++)//��ʼ���ݴ�����
//		{
//			photo_timers=0;
//			short_lived[i]=0;
//		}
//		if(things%3==0)//����Ѿ�����������Ʒ�ͻ�һ��ǽ
//		{
//			count_line(1,0,0);
//			change_wall();
//		}
//		if(things==12)//����12���˳�����ѭ��
//		{
//			break;
//		}
//	}
//}
void take_photo()//���պ���
{
	int times=0,things=0,flag=0,i,photo_timers=0,sameflag=0,flickerflag=0;
	int short_lived[20];
	walkwall(0);//����ǽ��
	take_photo_mechanical_grip();//��е����������
	delay_ms(1000);//��ʱ�ȴ���е�۵���λ��
	delay_ms(1000);
	delay_ms(1000);
	for(;;)//����ѭ��
	{
		mode=31;//ä��
		for(;;)
		{	
			if(THING==1)//���û��⵽��Ʒ
			{
				flag=1;//��־Ϊ1
			}
			if((THING==0)&&(flag==1))//��⵽��Ʒ���ϴ�δ��⵽��Ʒ
			{
				
				mode=1;//ͣ��
				delay_ms(500);//��ʱ����
				things++;//��¼��Ʒ����
				flag=0;//��־Ϊ0
				break;//��������ѭ��
			}
		}
		for(;;)//����ѭ��
		{
			if(flickerflag==1)
			{
			   flicker=1;//�ߵ�ƽΪ���������
			}
			delay_ms(800);//��ʱ�ȴ��ƴﵽ�������
			signal=1;//�����ź�
			for(;;)
			{
				if(aaa==55)
				{
					aaa=0;
				  break;
				}
			}
			signal=0;//�ر������ź��Է�ֹ���ٵ��ظ�����
			delay_ms(1000);//��ʱ�ȴ�
			flicker=0;//�ر������
			delay_ms(200);//��ʱ�ȴ���ֹ���ռ������
			delay_ms(1000);
			for(;;)
			{
				if(photoflag==1)//������ڽ����жϱ�����
				{
					photoflag=0;//����
					break;//�����ȴ�ѭ��
				}
			}
			if(aaa==52)//���ͼ����Ϊδʶ����ź�52��ִ��������߼�
			{
				continue;
			}
			if((aaa==1)||(aaa==2)||(aaa==3)||(aaa==5)||(aaa==6)||(aaa==7))
			{
				flickerflag=1;
			}
			short_lived[photo_timers]=aaa;//�ݴ�ͼ����
			for(i=0;i<photo_timers;i++)//ѭ�������Ƿ�������һ���Ľ����һ����Ϊ���ս��
			{
				if((aaa==short_lived[i])&&(photo_timers>0))
				{
					for(i=0;i<12;i++)//��ţ���ֻ���ת��
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
					if((aaa>0)&&(aaa<52))//�����תΪ0��11����Ʒ����
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
			 if(sameflag==1)//����������ͬ��Ƭ�˳�����ѭ��
			 {
				 sameflag=0;
				 break;
			 }
			 photo_timers++;
	  }
		for(i=0;i<10;i++)//��ʼ���ݴ�����
		{
			photo_timers=0;
			short_lived[i]=0;
		}
		if(things%3==0)//����Ѿ�����������Ʒ�ͻ�һ��ǽ
		{
			count_line(1,0,0);
			change_wall();
		}
		if(things==12)//����12���˳�����ѭ��
		{
			break;
		}
	}
}

void start(void)//����������ʱԼ10s����Ȼ��ä��һ�κ�ʼѭ��
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
//void shuxian(u16 flag,u16 smode)//���ߺ���flag�������������־1Ϊ����0Ϊ����smode����ǰ�������
//{
//	
//	if(flag==0)//����ģʽ
//	{
//		nline=0;
//		sx=0;
//	}
//	else//����ģʽ
//	{
//		if(smode==0)
//		{
//		  if((LROAD5==1)&&(sx==0))//����ɫ
//		  {
//			  sx=2;
//		  }
//		  if((LROAD5==0)&&(sx==2))//����ɫ
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
void shuxian(u16 flag,u16 smode)//���ߺ���flag�������������־1Ϊ����0Ϊ����smode����ǰ������ˣ�������˲���
{
	static int smoothing=0;//������־�����˲�����Ϊ��Ҫ���ϵ��ú�����ʹ�þֲ���̬���������������
  if(flag==0)//����ģʽ
  {
		smoothing=0;
		nline=0;
		nline1=0;
		sx1=0;
		sx=0;
	}
	else//����ģʽ
	{
		if(smode==0)
		{
		  if((LROAD5==1)&&(sx==0))//����ɫ
		  {
				smoothing++;//������
				if(smoothing==10)//���������ﵽ10��ʱ��ȷ���Ǻ�ɫ������Ϊ�Ӳ����߸��ŵ��µĲ��ȶ�����
				{
			    sx=2;//ȷ�Ͻ�����һ��
					smoothing=0;//����
				}
		  }
			if((LROAD5==0)&&(sx==2))//����ɫ
		  {
				smoothing++;
				if(smoothing==10)
				{
					smoothing=0;
			    nline++;
			    sx=0;
				}
		  }
//			if((RROAD1==1)&&(sx1==0))//����ɫ
//		  {
//			  sx1=2;
//		  }
//		  if((RROAD1==0)&&(sx1==2))//����ɫ
//		  {
//			  nline1++;
//			  sx1=0;
//		  }
		}
		else
		{
			if((LROAD8==1)&&(sx==0))
		  {
				smoothing++;//��¼10�κ�ɫ
				if(smoothing==10)
				{
			    sx=2;
					smoothing=0;
				}
		  }
		  if((LROAD8==0)&&(sx==2))
		  {
				smoothing++;//��¼ʮ�ΰ�ɫΪһ��������������
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

void TIM4_IRQHandler(void)   //TIM4�ж����ڿ���
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
			shuxian(countflag,smode);//����
			Line_Following(mode);//ģʽ����
		  TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );//���TIMx���жϴ�����λ:TIM �ж�Դ 
		}
}
void TIM6_IRQHandler(void)   //TIM6�ж����ڶ�ʱ1msһ��
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)//���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
			if(timerflag==1)//��ʱ����
			{ 
			   time++;
			}
		  TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );//���TIMx���жϴ�����λ:TIM �ж�Դ 
		}
}
char dis_dj[20];


void TIM7_IRQHandler(void)   //TIM7����OLED��ʾ
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)//���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
			OLED_Refresh_Gram();
			OLED_ShowNum(0,40,photoflag,3,16);
			sprintf(dis_dj,"%d",aaa);//��ʾͼ��ֵ
			OLED_ShowString(0,2,(u8*)dis_dj);//����һ��������ʾͼ��ֵ
//		OLED_ShowNum(0,20,THING,1,16);//�²�Ѱ���翪��״̬��ʾ
//		OLED_ShowNum(0,40,time,4,16);//��ʱ���жϴ�����ʾ
//		OLED_ShowNum(0,40,FRROAD1,1,16);//ǰ�ŻҶ���ʾfront
//		OLED_ShowNum(10,40,FRROAD2,1,16);
//		OLED_ShowNum(20,40,FRROAD3,1,16);
//	  OLED_ShowNum(30,40,FRROAD4,1,16);
//		OLED_ShowNum(40,40,FRROAD5,1,16);
//		OLED_ShowNum(50,40,FRROAD6,1,16);
//		OLED_ShowNum(60,40,FRROAD7,1,16);	
//		OLED_ShowNum(70,40,FRROAD8,1,16);
//		OLED_ShowNum(0,40,REROAD1,1,16);//���ŻҶ���ʾ
//		OLED_ShowNum(10,40,REROAD2,1,16);
//		OLED_ShowNum(20,40,REROAD3,1,16);
//		OLED_ShowNum(30,40,REROAD4,1,16);
//		OLED_ShowNum(40,40,REROAD5,1,16);
//		OLED_ShowNum(50,40,REROAD6,1,16);
//		OLED_ShowNum(60,40,REROAD7,1,16);	
//		OLED_ShowNum(70,40,REROAD8,1,16);
//		OLED_ShowNum(0,40,RROAD1,1,16);//�ұ߻Ҷ�
//		OLED_ShowNum(10,40,RROAD2,1,16);
//		OLED_ShowNum(20,40,RROAD3,1,16);
//		OLED_ShowNum(30,40,RROAD4,1,16);
//	  OLED_ShowNum(40,40,LROAD5,1,16);//��߻Ҷ�
//		OLED_ShowNum(50,40,LROAD6,1,16);
//		OLED_ShowNum(60,40,LROAD7,1,16);	
//		OLED_ShowNum(70,40,LROAD8,1,16);
		  TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );//���TIMx���жϴ�����λ:TIM �ж�Դ 
		}
}
