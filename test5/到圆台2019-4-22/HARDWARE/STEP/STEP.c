#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "pwm.h"
#include "timer.h"
#include "string.h"
#include "pid.h"
#include "adc.h"
#include "MOTO.h"
#include "STEP.h"
extern LightState lightState;//灰度的状态

extern int Roll,Pitch,Yaw,data,Angle[10],deltangle;//陀螺仪
void adjustSmall(char mode);
void bridge(void){
		int adcx1=0;
		int adcx2=0;
		int speedL=40;
		int speedR=45;
		char downFlag=0;//下坡标志
			
			//靠近且上坡
			goStraight(50,42,1);
			
			while(1){
				int temp=Pitch;
				
				if(temp>72&&temp<355){
					break;
				}
			}
			//在坡上
			TIM_Cmd(TIM5,DISABLE);//关闭巡线,基于灰度的pid不会调节
			onlyGo(54,45,800);
			forward();
			//stop();
			while(1){
				int temp=Pitch;
				int yaw=Yaw;
			
				setSpeed(speedL,speedR);
		/*adcx1=Get_Adc_Average(ADC_Channel_11,1);//zuo
		adcx2=Get_Adc_Average(ADC_Channel_10,1);//you
		if (adcx1>adcx2+300) gostraight0(38,50);
		if (adcx2>adcx1+300) gostraight0(53,35);
				*/
		//else gostraight0(38,35);	
				
		/*	if(yaw>150&&yaw<=357){//右偏
			TIM_SetCompare2(TIM3,42);	 
		  TIM_SetCompare1(TIM3,75);
				delay_ms(15);
				
				
			}
			else if (yaw>=3&&yaw<120){//左偏
			TIM_SetCompare2(TIM3,70);	 
		  TIM_SetCompare1(TIM3,42);
			delay_ms(15);
			}
			*/
			
			/*if(HR==0) {//右偏
			stop();
			//delay_ms(40);	
			forward();

			setSpeed(30,70);	
			delay_ms(180);	
			}	
			*/
			
			if(temp>13&&temp<100){//下坡
				/*	downFlag=1;
				}
			if(downFlag==1&&((temp>=0&&temp<20)||temp>355)){
			downFlag=0;*/
			
			setSpeed(38,28);	
			delay_ms(200);break;
			}	
			else if(HL==0)	{//左偏
			stop();
			delay_ms(40);	
			forward();
			
			setSpeed(60,30);
			delay_ms(150);	
			}
			}
			
			
			stop();
			TIM_Cmd(TIM5,ENABLE);//打开巡线
			delay_ms(600);
			adjustSmall(0);
}
//上台
void onboard(int upCount,int downCount,char mode){
	//upcount:加速时间
	//down:减速时间
	//mode 0:默认上台 1：回家的上台
	
	//
	
	int startAngle=0;//未转之前的角度
	char downFlag=0;//下坡标志
	int goLeft=55;
	int goRight=65;
	int turnLSpeed=80;
	int turnRSpeed=70;
	int count=44;//延时走
			//靠近并且爬坡
	goStraight(48,45,1);
			while(1){
				int temp=Pitch;//pitch是从串口缓冲区拿出来的，只拿一次，具有可比性
				if(HR==0){startAngle=Yaw;}
				if(temp>=300&&temp<=346){//上坡了
				
					break;
				}
				
			}
			/////////////////////////////////////////////////////
			TIM_Cmd(TIM5,DISABLE);//关闭巡线
			//上台
		//onlyGo(45,65,100);
			setSpeed(50,55);//慢走爬坡
			count=20;
			while(1){
			count--;
				if(count<=0){break;}
				delay_ms(30);
			}
			
			//上台直走
	goByCondition(goLeft,goRight,0);//直走，条件：判断灰度
			delay_ms(200);
			
			
			
			
			stop();
			//peopleDo();
			//move_head();
			//掉头,左转
			fastTurn(0);
	turn(0,turnLSpeed,turnRSpeed);
			stopByCondition(0,startAngle);//找寻特定角度
			
			//onlyGo(65,50,380);
			if(mode==0){	//正常下坡
			
			//准备下坡
			onlyGo(38,48,1000);
				stop();
				//delay_ms(200);
		//adjustSmall(0);	
			TIM_Cmd(TIM5,ENABLE);//启动巡线
			//////////////////////////////////////////////////////
			
			//下坡
			goStraight(30,27,1);
			count=44;
				while(1){
				int temp=Pitch;//pitch是从串口缓冲区拿出来的，只拿一次，具有可比性
				/*if(temp>5&&temp<30){
					downFlag=1;
				}
				if(downFlag==1&&((temp>=0&&temp<5)||temp>355)){downFlag=0;break;}
				*/
				//if(temp>12&&temp<350){break;}
				if(count<=0){break;}
				count--;
				
				delay_ms(30);
			}
			}
	TIM_Cmd(TIM5,ENABLE);//启动巡线
	stop();
	delay_ms(200);			
			
	
	
}
//障碍
void hump(int count,int left,int right){
	int i;
	int a=0;
	int start_Yaw=0;
	
		//探测起伏
		goStraight(43,40,1);
		while(1){
				int temp=Pitch;
				if(HR==0){start_Yaw=Yaw;}
				if(temp>=330&&temp<=355){//有向上起伏
					break;
				}
			}
		
			stop();
			delay_ms(150);
		
		//走障碍
			/*
			//方向朝前
			if(!(start_Yaw>85&&start_Yaw<275)){
					TIM_Cmd(TIM5,DISABLE);//关闭巡线,
					forward();
						while(1){
						int temp=Yaw;
						if(num==0){//2块板
							setSpeed(45,40);
							if(temp-start_Yaw>5){setSpeed(50,32);delay_ms(40);}
							else{if(start_Yaw-temp>5){setSpeed(28,50);delay_ms(40);}}
						}
						else if(num==1)//3块板
						{
							
							setSpeed(32,35);
							if(temp-start_Yaw>5){setSpeed(52,30);delay_ms(45);}//左偏
							else{if(start_Yaw-temp>5){setSpeed(28,50);delay_ms(45);}}//右偏
						}
			
						
					
						
						count--;
						
						if(count<=0){break;}
						delay_ms(42);
					}
					TIM_Cmd(TIM5,ENABLE);//打开巡线,
			}
			//方向朝后
			else{
					TIM_Cmd(TIM5,DISABLE);//关闭巡线,
					forward();
					while(1){
						int temp=Yaw;
						if(num==0){//2块板
							setSpeed(30,34);
							if(temp-start_Yaw>5){setSpeed(45,32);delay_ms(40);}
							else{if(start_Yaw-temp>5){setSpeed(28,45);delay_ms(40);}}
						}
						else if(num==1)//3块板
						{
							
							setSpeed(32,34);
							if(temp-start_Yaw>5){setSpeed(50,38);delay_ms(40);}//左偏
							else{if(start_Yaw-temp>5){setSpeed(32,50);delay_ms(40);}}//右偏
						}
			
						
					
						
						count--;
						
						if(count<=0){break;}
						delay_ms(42);
					}
					
					TIM_Cmd(TIM5,ENABLE);//打开巡线,
				
				
			}	*/
			
	/*	while(1){
				int temp=Yaw;
			/*
				int temp=Pitch;//pitch是从串口缓冲区拿出来的，只拿一次，具有可比性
				if(temp>310&&temp<358){
					upFlag=1;//检测两次上倾再水平，说明已经走过障碍
				}
				if(upFlag==1&&((temp>=0&&temp<4)||temp>357)){upFlag=0;countUpDown++;}
				if(countUpDown>=4){break;}
			*/
			
			
			goStraight(left,right,0);
			while(1){
			
			//使用数数延时走完障碍
			if(count<=0){break;}
			count--;
			delay_ms(40);
			}
			
			
			
			
			
			stop();		
			delay_ms(300);
			adjustSmall(0);
}
//路口
void crossing(u8 direction,int delay_time,int line){
	//direction 转弯方向 0:左 1：右  
	//delay_time:到达路口后延时 line:转弯时的数线
	char turnFlag=0;//转弯标志，说明已经开始碰到路口旁线
	
	
	int lineCount=0;
	goStraight(50,45,1);
	
	if(direction==0){				//左转
		//探线后停下
	
		while(1){
			if(lightState.canLeftTurn==1){break;}
			}
		delay_ms(delay_time);
		stop();
			delay_ms(100);
			/////////////////////////////////////
			TIM_Cmd(TIM5,DISABLE);//关闭巡线
			//转弯
			turn(0,80,82);
			delay_ms(100);
			while(1){
			if(lightState.light[1]==0){
			delay_ms(20);
			if(lightState.light[1]==0)
			turnFlag=1;}
			if(turnFlag==1&&lightState.light[3]==0){lineCount++;turnFlag=0;}
			if(lineCount>=line){break;}
			}
			stop();
			TIM_Cmd(TIM5,ENABLE);//打开巡线
			
	}
	else if(direction==1){			//右转
		lightState.canRightTurn=0;
	while(1){
			if(lightState.canRightTurn==1){break;}
			}
		delay_ms(delay_time);
		stop();
		delay_ms(30);	
		//////////////////////////////////////
		TIM_Cmd(TIM5,DISABLE);//关闭巡线
			//转弯
			turn(1,85,80);
			delay_ms(100);
			while(1){
			if(lightState.light[6]==0){
			delay_ms(20);
			if(lightState.light[6]==0)	
			turnFlag=1;}
			if(turnFlag==1&&lightState.light[4]==0){lineCount++;turnFlag=0;}
			if(lineCount>=line){break;}
			}
			stop();
			TIM_Cmd(TIM5,ENABLE);//打开巡线
			////////////////////////////////////
			delay_ms(300);
	}
	
	
	
}
//路口版本2
void crossing_2(u8 direction,int delay_time,int line,int crossCountSet){
	//direction 转弯方向 0:左 1：右  
	//delay_time:到达路口后延时 line:转弯时的数线
	//crossCountSet:经过路口数
	//int crossCount=0;
	//u8 crossingFlag=0;
	int lineCount=0;
	int turnFlag=0;
	goStraight(50,45,1);
	while(1){
	if(lightState.canLeftTurn==1){delay_ms(500);break;}
	}
	while(1){
	if(lightState.canRightTurn==1){delay_ms(delay_time);break;}
	}
	switch(direction){
		case 0:
			break;
		case 1:
			////////////////////////////////
			TIM_Cmd(TIM5,DISABLE);//关闭巡线
			//转弯
			turn(1,80,85);
			delay_ms(50);
			while(1){
			if(lightState.light[6]==0){
			delay_ms(5);
			if(lightState.light[6]==0)	
			turnFlag=1;}
			if(turnFlag==1&&lightState.light[4]==0){lineCount++;turnFlag=0;}
			if(lineCount>=line){break;}
			}
			stop();
			TIM_Cmd(TIM5,ENABLE);//打开巡线
			break;
		default:
			break;
	}
	
}
//跷跷板	
void teeterBoard(int left,int right){
	//Left：左轮速度 right :右轮速度
	//靠近并且爬坡
			int count=30;
			goStraight(48,45,1);
			while(1){
				//int temp=Pitch;//pitch是从串口缓冲区拿出来的，只拿一次，具有可比性
				//if(temp>=18&&temp<=345)
				if(lightState.num==0)
				{//上坡了
					break;
				}
			}
			stop();
			delay_ms(200);
			forward();
			TIM_Cmd(TIM5,DISABLE);//关闭巡线
			
			setSpeed(47,42);
			delay_ms(800);
			delay_ms(800);
			delay_ms(520);
			stop();
			
			/*while(1){
			int temp=Pitch;
				if(temp>0&&temp<20){
			back();
			setSpeed(50,50);
			delay_ms(350);		
				break;}
			}*/
			
			//delay_ms(800);
			//delay_ms(600);//上冲
		
			stop();
			/*
			delay_ms(560);//等待下降
			back();
			setSpeed(55,55);
			delay_ms(420);
			stop();*/
			delay_ms(1000);
			//adjustSmall(0);
			
			TIM_Cmd(TIM5,ENABLE);//打开巡线
			goStraight(43,40,0);
			while(1){
			if(count<=0){break;}
				count--;
				
				delay_ms(30);
			}
			
}
//回家
void goHome(int waitForTurn){
	
	int turnFlag=0;
	int lineCount=0;
	goStraight(48,45,1);
	
			while(1){
				
				if(lightState.canLeftTurn){
					break;
				}
			}
			delay_ms(waitForTurn);
			stop();
			delay_ms(100);
			
			TIM_Cmd(TIM5,DISABLE);//关闭巡线
			//转弯
			turn(1,65,65);//右转
			delay_ms(40);
			while(1){
			/*if(lightState.light[6]==0){	
			turnFlag=1;}
			if(turnFlag==1&&lightState.light[4]==0){lineCount++;turnFlag=0;}
			if(lineCount>=1){break;}
				*/
				if(lightState.light[3]==0){break;}
			}
			stop();
			TIM_Cmd(TIM5,ENABLE);//打开巡线
			delay_ms(200);
			
}
//数线,不停
void countLine(int line,int delayTime){
		int lineFlag=0;//线条标志位
		int count=0;//计线数
		goStraight(48,45,1);
		while(count<line){
		if(lightState.isCrossing==1){lineFlag=1;}
		if(lightState.isCrossing==0&&lineFlag==1){count++;lineFlag=0;}
		}
		delay_ms(delayTime);
}

//黑色斜坡，direction:目的方向,count:盲走次数
void black_xiepo(int direction,int count)
{
	//0:左转 ，1：右转 2：先斜后右，3：先斜后左，4：右倾前行 5，左倾前行
	int startAngle=0;
	int endAngle;
	char HL_dir=0;
	char HR_dir=0;//
	char HR_count=0;
	char turnFlag=0;//坡上转弯的标志，0：HL未碰到线
	int temp=0;//中间角度  //从TLY读取的角度值
	int delAngle=0;
	
	/*goStraight(45,35,1);
	while(1)
	{
		
		if(HL==0&&HR==0){delay_ms(count);stop();break;}
	}*/
		goStraight(45,35,1);
		
		
		
	
		switch(direction){
			  case 0:
					while(1)
		{
		
		//if(Pitch>300&&Pitch<350){startAngle=Yaw;break;}
			/*if(HR==0){HR_dir=1;}
			if(HR_dir==1&&HR==1){HR_dir=0;HR_count++;}
			if(HR_count>=2){startAngle=Yaw;delay_ms(50);break;}
			*/
			if(HDL==0){startAngle=Yaw;delay_ms(65);break;}
		}
		TIM_Cmd(TIM5,DISABLE);//关闭巡线	
					//转弯
				turn(0,10,65);
				while(1){
					temp=Yaw;
					/*if(HL==1){HL_dir=1;}
					else if(HL==0&&HL_dir==1){HL_dir=0;turnFlag=1;}
					if(turnFlag==1&&HR==0){turnFlag=0;break;}*/
					//if(HDL==0){break;}
					delAngle=abs(temp-startAngle);
					if(delAngle>=88&&delAngle<=200){
						
						break;
					}
				}
				
				//向前
				forward();
				/*while(1){
				int temp=Pitch;	
				setSpeed(60,45);
				if(HDL==0){setSpeed(75,45);delay_ms(120);}	
				if(!(temp>3&&temp<357)){break;}
				}*/
				setSpeed(65,42);
				delay_ms(450);
				
				//if(temp-startAngle)
				//stopByCondition(1,startAngle);
				
				//setSpeed(10,80);
	      
				/*delay_ms(750);
				forward();
				
				setSpeed(52,40);
				delay_ms(620);
				
				while(1){
				int temp=Pitch;	
				setSpeed(30,40);
				if(HL==0){
				setSpeed(60,40);
				delay_ms(80);	
				}	
				if(!(temp>5&&temp<355)){break;}
				}*/
				break;
			case 1:
				
			
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				while(1)
		{
			if(lightState.num==0){break;}
		}
		TIM_Cmd(TIM5,DISABLE);//关闭巡线
		
		while(count>=0)
		{
			count--;
			if(HL==0){setSpeed(50,40);delay_ms(40);}
			else{setSpeed(40,55);delay_ms(40);}
			
		}
				break;
			case 5:
				break;
			default:
				break;
		}
	
	
		
		stop();
	
		delay_ms(220);
		TIM_Cmd(TIM5,ENABLE);//打开巡线
}

//小崎岖的路，过门
void smallHump(int count){
	
	int i;
	//探测颠簸处
	goStraight(45,42,1);
	while(1)
	{
			if(HL==0) 
			{
				
				//stop();
					delay_ms(120);
				break;
			}
	}
	
	
	stop();
	delay_ms(50);
	//直走
	goStraight(40,38,1);	
	while(1){
		delay_ms(40);
			count--;
			if(count<=0){break;}
			
			}
	
	
	stop();
	adjustSmall(0);
	//delay_ms(100);
		
}
//小调整
void adjustSmall(char mode){
	//mode选择调整的程度
	//0：低档 1：中档 2：高档
	TIM_Cmd(TIM5,DISABLE);//关闭巡线	
	
	switch(mode)
	{
		case 0:
		if(lightState.num>2){lightState.num=0;}	
		else if(lightState.light[1]==0||lightState.light[0]==0){turn(0,70,80);delay_ms(90);}	
		else if(lightState.light[2]==0){
		turn(0,70,80);
		delay_ms(80);	
		}
		else if(lightState.light[7]==0||lightState.light[6]==0){turn(1,80,70);delay_ms(160);}
		else if(lightState.light[5]==0){
		turn(1,80,70);
		delay_ms(120);	
		}
			break;
		case 1:
			if(lightState.light[1]==0||lightState.light[0]==0||lightState.light[2]==0){
	turn(0,70,7);
	delay_ms(300);	
		
	}
	else if(lightState.light[6]==0||lightState.light[5]==0||lightState.light[7]==0){
	turn(1,80,70);
	delay_ms(300);	
		
	}
			break;
		case 2:
				if(lightState.light[1]==0||lightState.light[0]==0||lightState.light[2]==0){
	turn(0,70,7);
	delay_ms(150);	
		
	}
	else if(lightState.light[6]==0||lightState.light[5]==0||lightState.light[7]==0){
	turn(1,80,70);
	delay_ms(150);	
		
	}
			break;
		default :
			break;
	}
	
	
	stop();
	delay_ms(200);	
	TIM_Cmd(TIM5,ENABLE);//打开巡线	
}
//上舞台，中等高度
void climbStage(){
	int startAngle=0;//未转之前的角度
	int goLeft=40;//
	int goRight=48;//
	int turnLSpeed=88;//慢转左轮速度
	int turnRSpeed=75;//慢转右轮速度
	//靠近并且爬坡
	char upFlag=0;
	char downFlag=0;
	goStraight(60,53,1);
			while(1){
				int temp=Pitch;//pitch是从串口缓冲区拿出来的，只拿一次，具有可比性
				if(temp>=100&&temp<=345){//上坡了
					upFlag=1;
				}
				//if(upFlag==1&&(!(temp>6&&temp<350))){break;}
				if(lightState.num==0){break;}
				
			}
			/////////////////////////////////////////////////////
			TIM_Cmd(TIM5,DISABLE);//关闭巡线
			//上台
			onlyGo(45,50,100);
			//上台直走
	goByCondition(goLeft,goRight,0);//直走，条件：判断灰度
			delay_ms(1000);
			startAngle=Yaw;
			stop();
			//掉头,左转
			fastTurn(0);
	turn(0,turnLSpeed,turnRSpeed);
			stopByCondition(0,startAngle);//找寻特定角度
			
			

			//准备下坡
			onlyGo(70,62,300);
				stop();
				delay_ms(200);
	adjustSmall(0);	
			TIM_Cmd(TIM5,ENABLE);//启动巡线
			//////////////////////////////////////////////////////
			
			//下坡
			goStraight(20,18,1);
			while(1){
				int temp=Pitch;//pitch是从串口缓冲区拿出来的，只拿一次，具有可比性
				/*if(temp>5&&temp<30){
					downFlag=1;
				}
				if(downFlag==1&&((temp>=0&&temp<5)||temp>355)){downFlag=0;break;}
				*/
				if(temp>15&&temp<350){downFlag=1;}
				if(downFlag==1&&(!(temp>5&&temp<355))){break;}
			}
			
			
	TIM_Cmd(TIM5,ENABLE);//启动巡线
	stop();
	delay_ms(400);	
			
}
//上山，最高
void climbMountain(){
	int startAngle=0;//未转之前的角度
	int goLeft=55;//上台瞬间小冲刺速度
	int goRight=58;//上台瞬间小冲刺速度
	int turnLSpeed=88;//慢转左轮速度
	int turnRSpeed=75;//慢转右轮速度
	char upCount=0;//上台阶次数
	//int stageCount=0;
	//靠近并且爬坡
	char upFlag=0;
	goStraight(60,53,1);
			while(1){
				int temp=Pitch;//pitch是从串口缓冲区拿出来的，只拿一次，具有可比性
				if(temp>=100&&temp<=345){//上坡了
					upFlag=1;
				}
				if(upFlag==1&&(!(temp>6&&temp<350))){
				upCount++;upFlag=0;
				}
				if(upCount>=2){break;}
				
			}
			/////////////////////////////////////////////////////
			TIM_Cmd(TIM5,DISABLE);//关闭巡线
			//上台
			onlyGo(45,50,200);
			//上台直走
	goByCondition(goLeft,goRight,0);//直走，条件：判断灰度
			delay_ms(1000);
			startAngle=Yaw;
			onlyGo(45,50,400);
			//掉头,左转
			fastTurn(0);
	turn(0,turnLSpeed,turnRSpeed);
			stopByCondition(0,startAngle);//找寻特定角度
			
			

			//准备下坡
			onlyGo(70,62,400);
				stop();
				delay_ms(200);
	adjustSmall(0);	
			TIM_Cmd(TIM5,ENABLE);//启动巡线
			//////////////////////////////////////////////////////
			
			//下坡
			goStraight(45,38,1);
			while(1){
				int temp=Pitch;//pitch是从串口缓冲区拿出来的，只拿一次，具有可比性
				/*if(temp>5&&temp<30){
					downFlag=1;
				}
				if(downFlag==1&&((temp>=0&&temp<5)||temp>355)){downFlag=0;break;}
				*/
				if(temp>10&&temp<350){break;}
			}
			
	TIM_Cmd(TIM5,ENABLE);//启动巡线
	stop();
	delay_ms(400);	
}
//圆圈部分
void round(){
	int hump_count=35;//圆圈里的障碍
	int count=25000000;//转弯后延时巡线，避免色标误判
	int lineCount=0;
	
	int start_Yaw=0;
	char turnFlag=0;
	crossing(1,220,1);
	goStraight(28,50,3);
	while(count>=0)
	{
		count--;
	}
	while(1){
	int temp=Pitch;
	//if(temp>300&&temp<356){step=1;}
		if(HR==0){break;}
	}
	stop();
	delay_ms(100);
	////////////////////////////////
	
	TIM_Cmd(TIM5,DISABLE);//关闭巡线
	turn(0,60,55);//矫正
	while(1){
	if(HL==0){break;}
	}
	stop();
	delay_ms(100);
	forward();//上桥
	while(1){
		int temp=Pitch;
	setSpeed(64,62);
		//if(temp>300&&temp<345){break;}
		delay_ms(800);
		delay_ms(430);//上冲时间
		//delay_ms(100);
		break;
	}
	stop();
	delay_ms(180);//等待下降
	back();
	setSpeed(65,65);
	delay_ms(280);
	stop();
	delay_ms(1000);
	forward();
	setSpeed(30,30);
	delay_ms(400);
	stop();
	//delay_ms(200);
	//forward();//向前飘一下
	//setSpeed(30,60);
//	/*delay_ms(300);
//	stop();
//	delay_ms(200);
//	//下桥了
//	//turn(0,60,60);
//	//		delay_ms(200);
//	//		stop();	
//	//delay_ms(200);
//	adjustSmall(2); 
//	*/
	turn(0,50,50);
	while(1){
	if(lightState.light[3]==0){break;}
	}
	stop();
	delay_ms(100);
	
	
	/////////////////////////////////////
	//触碰第一个路口
	TIM_Cmd(TIM5,ENABLE);//打开巡线
	
	goStraight(25,42,3);//第三套走线pid//
	//延迟一下
	count=40;
	//count=count*3;
	while(count>=0){
		count--;
		delay_ms(20);
	}
	 
	while(1){
	if(HL==0){delay_ms(380);break;}
	}
	stop();
	delay_ms(100);
	/////////////////////////////////////
	
//////平台前的路口
			TIM_Cmd(TIM5,DISABLE);//关闭巡线
			//转弯
			turn(0,80,85);
			delay_ms(120);
			while(1){
			if(lightState.light[1]==0){
			delay_ms(5);
			if(lightState.light[1]==0)
			turnFlag=1;}
			if(turnFlag==1&&lightState.light[3]==0){lineCount++;turnFlag=0;}
			if(lineCount>=1){break;}
			}
			stop();
			delay_ms(200);
			TIM_Cmd(TIM5,ENABLE);//打开巡线
/////			
			onboard(0,0,0);
			
///////平台后的路口
//			goStraight(55,50,0);
//			while(1){
//			if(lightState.canLeftTurn==1){delay_ms(180);stop();break;}
//			}
//			stop();
//			delay_ms(1000);
//			TIM_Cmd(TIM5,DISABLE);//关闭巡线,
//			turn(0,80,80);
//			delay_ms(100);
//			while(1){
//				if(lightState.light[4]==0){break;}
//			}
//			stop();
//			delay_ms(1000);
//			TIM_Cmd(TIM5,ENABLE);//打开巡线,
//			
			crossing(0,200,1);
		
///////			
			
			//探测障碍
			goStraight(28,50,3);
			while(1){
				if(HL==0){break;}
			}
	////////////////////////////
			//start_Yaw=Yaw+44;

					
		//hump
		delay_ms(200);//延迟转弯
		left();
		setSpeed(60,60);
			delay_ms(260);	//转弯时间
			stop();
		delay_ms(80);
		goStraight(37,44,0);
			count=84;
		while(1){
		if(count<=0)break;
		count--;	
			delay_ms(20);
		}
		stop();
		//adjustSmall(0);	
/////	到达路口转弯				
			//stop();
			delay_ms(100);
			
			//
			TIM_Cmd(TIM5,ENABLE);//打开巡线,
			//stop();//		
			//触碰路口
			goStraight(32,52,0);
			count=40;
			while(1){
			if(count<=0)break;
			count--;	
			delay_ms(20);
			}
			while(1){
			if(lightState.light[6]==0||lightState.light[7]==0){
			break;
			}
			}
			delay_ms(200);//延迟刹车
			stop();
			delay_ms(80);
			
			
			turn(0,90,95);
			
			while(1){
				if(lightState.light[3]==0){break;}
			}
			
			stop();
			
			delay_ms(80);
			goStraight(45,40,1);
			count=40;
			while(count>=0){
			count--;
				delay_ms(40);
			}
			stop();
}