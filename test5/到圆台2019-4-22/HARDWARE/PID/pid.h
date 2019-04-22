#ifndef __PID_H
#define __PID_H
#include "sys.h"
//////////////////////////
typedef struct
	{
  float SetSpeed; 
  float ActualSpeed; 
  float err; 
  float errlast; 
  float Kp,Ki,Kd; 
  float voltage; 
  float integral;
	int setSpeedLeft;//预设速度,由goStraight设置
	int setSpeedRight;
		u8 mode;//0: 低速 1：正常速度 2:快速 3:圆
	}Pid;

typedef struct{
	float kp,ki,kd;//正常速参数
	float Lkp,Lki,Lkd;//低速参数
	float cir_kp,cir_ki,cir_kd;//圆形参数
	float hump_kp,hump_ki,hump_kd;//走障碍pid
	
}PidParam;//pid参数


////////////////////////////


//电机状态设置//////////
void left(void);
void right(void);
void forward(void);
/////////////////////////
void gethdnum(void);
void error(void);
//////////////////////////////////////////////////////////////////
void PID_init(float Kp,float Ki,float Kd,float Speed);
void PID_Init(float kp ,float ki,float kd);
float PID_realize( float err);

float speed_LR(void);
float speed_LR_S(void);


/////////////////////////////////////////////////
void turn(int lr, int l, int r);
void gostraight(int l,int r,int speed);
void gostraight0(int l,int r);



#endif
