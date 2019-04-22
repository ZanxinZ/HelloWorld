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
extern Pid pid;
extern LightState lightState;
extern int Roll,Pitch,Yaw,data,Angle[10],deltangle;//������
void setSpeed(int left,int right);
void onlyTurn(char direction,int count){//��ʱת,�������Ե��
	//count:����ת��ʱ��
	int i;
	TIM_Cmd(TIM4,DISABLE);//�ر�Ѳ��
	if(direction==0){
		left();
	//TIM_SetCompare2(TIM3,90);//zuo
	//TIM_SetCompare1(TIM3,80);//you
		setSpeed(60,58);
	while(count>0){
	for(i=0;i<8000;i++){}
		count--;
	
	}
	
		
	}
	if(direction==1){right();
	//TIM_SetCompare2(TIM3,90);//zuo
	//TIM_SetCompare1(TIM3,80);//you
	setSpeed(90,80);
	while(count>0){
	for(i=0;i<8000;i++){}
		count--;
	
	}
	
	}
	stop();
	TIM_Cmd(TIM4,ENABLE);//�ر�Ѳ��
}
void goStraight(int left,int right,int mode) //Ѳ����
{
		//mode//0: ���� 1�������ٶ� 2:����
		pid.mode=mode;
		forward();
		pid.setSpeedLeft=left;
		pid.setSpeedRight=right;

}
void gostraight0(int l, int r) 
{
	
		pid.mode=1;
		forward();
		//TIM_SetCompare2(TIM3,l);	 
		//TIM_SetCompare1(TIM3,r);
		setSpeed(l,r);
}


void turn(int lr, int l, int r)
{
		
		if(lr==0)//��ת
		{
				left();
				//TIM_SetCompare2(TIM3,l);	 
				//TIM_SetCompare1(TIM3,r);
				setSpeed(l,r);
		}
		if(lr==1)//��ת
		{
				right();
				//TIM_SetCompare2(TIM3,l);	 
				//TIM_SetCompare1(TIM3,r);
			  setSpeed(l,r);
		}


}
void fastTurn(int direction){
	//direction 0:��  1����
	
	if(direction==0){
	left();
				//TIM_SetCompare2(TIM3,120);	 
				//TIM_SetCompare1(TIM3,100);
				setSpeed(90,75);
		delay_ms(750);
		
	}
	if(direction==1){
	    right();
				//TIM_SetCompare2(TIM3,110);	 
				//TIM_SetCompare1(TIM3,100);
				setSpeed(110,100);
		delay_ms(330);
		
	}
	
}
//ä��,��ʱ
void onlyGo(int left,int right,int time){
		
		forward();
		TIM_SetCompare2(TIM3,left);	 
		TIM_SetCompare1(TIM3,right);
		delay_ms(time);
		
}
//��������ֱ��
void goByCondition(int left,int right, u8 condition){
	//condition: ����ѡ��0�����Ҷ� 1�� ����ǰ�۾�
		int count=0;//������������
		int flag=0;//��־λ
		
	  forward();
		while(1){
		int temp=Pitch;	
		//TIM_SetCompare2(TIM3,left);	 
		//TIM_SetCompare1(TIM3,right);
		setSpeed(left,right);
		if(condition==0){
			
		/*if(HDL==1){flag=1;}
		if(HDL==0&&flag==1){flag=0;count++;}
		if(count>=1){break;}
			*/
		/*if(!(temp>5&&temp<355))	{
			delay_ms(120);
			break;
		}*/
			
		if(HDL==0){
		delay_ms(50);
		break;}	
		
		//if(HL==0){break;}	
		}
	}
		
		stop();
		delay_ms(800);
}
//��������ֹͣ
void stopByCondition(u8 condition,int param){
	//condition 0:ƽ̨�ϵ�ת�� 1����ɫб���ϵ�ת�� 2:δ����
	if(condition==0){
	/*int delAngle=0;
	int reserveAngle=0;	
	char lineDir=0;	
		int count=0;
	//�Ƕ�Ԥ����
	if((param>=0&&param<45)||(param>315)){//315--45
		if(param>=0&&param<45)reserveAngle=0;//0--45
		if(param>315)reserveAngle=1;	//315--0
		param=0;	
	}
	else if(param>=45&&param<135){//45--135
	reserveAngle=0;
		param=90;
	}
	else if(param>=135&&param<225){//135--225
		reserveAngle=0;
		param=180;
	}
	
	delAngle=reserveAngle;
	//condition 0:ת180
	while(1){
	int temp=Yaw;//ˮƽ�Ƕ�
	
	if(abs(temp-param)>=177+delAngle)	{stop();delay_ms(200);break;}
		
	//if(lightState.light[3]==0){lineDir=1;}
	//if(lineDir==1&&lightState.light[3]==1){count++;lineDir=0;}
	//if(count>=2){stop();break;}
		
		//if(lightState.light[7]==0){stop();break;}
	}*/
	while(1){
		int temp=Yaw;
		int delAngle=temp-param;
		if(delAngle<0){delAngle+=360;}
		if(delAngle>175&&delAngle<190){stop();delay_ms(100);break;}
	}
	
	}
	else if(condition==1){
	
	int delAngle=0;
	int reserveAngle=0;	
	char lineDir=0;	
		int count=0;
	//�Ƕ�Ԥ����
	if((param>=0&&param<45)||(param>315)){//315--45
		if(param>=0&&param<45)reserveAngle=0;//0--45
		if(param>315)reserveAngle=1;	//315--0
		param=0;	
	}
	else if(param>=45&&param<135){//45--135
	reserveAngle=0;
		param=90;
	}
	else if(param>=135&&param<225){//135--225
		reserveAngle=0;
		param=180;
	}
	
	delAngle=reserveAngle;
	
	while(1){
	int temp=Yaw;//ˮƽ�Ƕ�
		
	if(abs(temp-param)>=88+delAngle)	{stop();delay_ms(200);break;}
		
	/*if(lightState.light[3]==0){lineDir=1;}
	if(lineDir==1&&lightState.light[3]==1){count++;lineDir=0;}
	if(count>=2){stop();break;}
		*/
		//if(lightState.light[7]==0){stop();break;}
	}
	
}
	
	if(condition==2){
	
	}
}
//ֱ�������������ٶ�
void setSpeed(int left,int right){
		TIM_SetCompare4(TIM3, left);	 
		TIM_SetCompare3(TIM3, right);
}