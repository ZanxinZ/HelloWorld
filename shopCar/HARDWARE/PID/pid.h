#ifndef __PID_H
#define __PID_H	 
#include "sys.h"
typedef struct 
{
	double Expect;//保存输出带寄存器的值
	double Currn;//TIM3捕获寄存器的值（反应电机转速）
	double Err0;  //当前误差
	double Err1;  //上次误差
	double ErrInt;
	double Kp;    //P系数
	double Ki;    //I系数
	double Kd;    //D系数
}PID_TypDef;

void PID_Init(PID_TypDef*PID);//PID参数初始化

double PID_run(PID_TypDef* PID,double error);  //PID运行函数

void PID_Set(PID_TypDef *PID,double Kp,double Ki,double Kd);//PID  参数设置

#endif

