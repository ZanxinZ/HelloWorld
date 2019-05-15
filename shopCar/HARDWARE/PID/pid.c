#include "pid.h"
#include "math.h"

void PID_Init(PID_TypDef *PID)//��ʼ��PID�ṹ�����
{
	PID->Expect = 0;
	PID->Currn = 0;
	PID->Err0 = 0.0;
	PID->Err1 = 0.0;
	PID->Kp = 0;
	PID->Ki = 0;
	PID->Kd = 0;
}

void PID_Set(PID_TypDef *PID,double Kp,double Ki,double Kd)
{
	PID->Kp = Kp;
	PID->Ki = Ki;
	PID->Kd = Kd;
}

double PID_run(PID_TypDef* PID,double error)
{
	double output = 0;
	//PID->Currn = currn;//��TIM3CCR�Ĵ�����ȡ������
	//PID->Expect = exp;
	PID->Err0 =error;//���=ʵ���ٶ���Ŀ���ٶȵĲ�
	PID->ErrInt += PID->Err0;
	if(fabs(PID->ErrInt)>20) {PID->ErrInt=(PID->ErrInt>0?20:-20);}  //�������Ʒ���30
	output =(PID->Kp*PID->Err0 + PID->Ki*PID->ErrInt + PID->Kd*(PID->Err0-PID->Err1));
	PID->Err1 = PID->Err0;//��ǰ������һ���
	return output;
}



