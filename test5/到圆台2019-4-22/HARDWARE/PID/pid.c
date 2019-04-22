#include "pid.h"
#include "led.h"
#include "delay.h"
#include "adc.h"
#include "oled.h"
#include "delay.h"
Pid pid;//����pid

PidParam pidSetParam;

///////////////////////////////
void left()//���ת״̬������
{
	DIR1=1;
	DIR2=0;
	DIR3=0;
	DIR4=1;
}

void right()
{
	DIR1=0;
	DIR2=1;
	DIR3=1;
	DIR4=0;
}
void forward()
{
	DIR1=1;
	DIR2=0;
	DIR3=1;
	DIR4=0;
}

void back()
{
	DIR1=0;
	DIR2=1;
	DIR3=0;
	DIR4=1;
}

void stop()
{
	DIR1=0;
	DIR2=0;
	DIR3=0;
	DIR4=0;
	//TIM_SetCompare1(TIM3,0);
	//TIM_SetCompare2(TIM3,0);
	setSpeed(0,0);
	pid.voltage=0;
	pid.errlast=0;
	pid.ActualSpeed=0;
}



/////////////////////////////

////////////////////////////////

//////////////////////////////////////////////////



void PID_Init(float kp ,float ki,float kd)
	{
		pid.mode=1;
    pid.SetSpeed=0.0;
    pid.ActualSpeed=0.0;
    pid.err=0.0;
    pid.errlast=0.0;
    pid.voltage=0.0;
    pid.integral=0.0;
    pid.Kp=kp;
    pid.Ki=ki;
    pid.Kd=kd;
		
		pidSetParam.kp=kp;
		pidSetParam.ki=ki;
		pidSetParam.kd=kd;
		
		pidSetParam.Lkp=20;
		pidSetParam.Lki=0;
		pidSetParam.Lkd=0;
		
		pidSetParam.cir_kp=80;
		pidSetParam.cir_ki=0;
		pidSetParam.cir_kd=35;
		
		pidSetParam.hump_kp=20;
		pidSetParam.hump_ki=0;
		pidSetParam.hump_kd=0;
		
		
   }
float PID_realize(float err)
{

		switch(pid.mode)
		{
			case 0: pid.Kp=pidSetParam.Lkp;pid.Ki=pidSetParam.Lki;pid.Kd=pidSetParam.Lkd; break;
			case 1: pid.Kp=pidSetParam.kp; pid.Ki=pidSetParam.ki; pid.Kd=pidSetParam.kd; break;
			case 2: pid.Kp=pidSetParam.cir_kp; pid.Ki=pidSetParam.cir_ki; pid.Kd=pidSetParam.cir_kd;break;
			case 3: break;//��ԲȦ
			
    }
	
	  pid.err = err;//���
    pid.integral+=pid.err;//����
		if(pid.integral>10)  pid.integral=9;   //�����޷�
		if(pid.integral<-10)pid.integral=-9;   //�����޷�
	  
		pid.voltage = pid.Kp*pid.err + pid.Ki*pid.integral + pid.Kd*(pid.err-pid.errlast);//PID���
    pid.errlast = pid.err;//��ֵ����һ�����
    
		pid.ActualSpeed=pid.voltage*1.0;//С��//����pid�ṹ������
   
		return pid.ActualSpeed;
}	 





