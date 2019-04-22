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
	int setSpeedLeft;//Ԥ���ٶ�,��goStraight����
	int setSpeedRight;
		u8 mode;//0: ���� 1�������ٶ� 2:���� 3:Բ
	}Pid;

typedef struct{
	float kp,ki,kd;//�����ٲ���
	float Lkp,Lki,Lkd;//���ٲ���
	float cir_kp,cir_ki,cir_kd;//Բ�β���
	float hump_kp,hump_ki,hump_kd;//���ϰ�pid
	
}PidParam;//pid����


////////////////////////////


//���״̬����//////////
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
