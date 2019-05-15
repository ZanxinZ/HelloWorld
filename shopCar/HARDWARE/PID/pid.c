#include "pid.h"
#include "math.h"

void PID_Init(PID_TypDef *PID)//初始化PID结构体参数
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
	//PID->Currn = currn;//从TIM3CCR寄存器获取解码器
	//PID->Expect = exp;
	PID->Err0 =error;//误差=实际速度与目标速度的差
	PID->ErrInt += PID->Err0;
	if(fabs(PID->ErrInt)>20) {PID->ErrInt=(PID->ErrInt>0?20:-20);}  //积分限制幅度30
	output =(PID->Kp*PID->Err0 + PID->Ki*PID->ErrInt + PID->Kd*(PID->Err0-PID->Err1));
	PID->Err1 = PID->Err0;//当前误差赋给下一误差
	return output;
}



