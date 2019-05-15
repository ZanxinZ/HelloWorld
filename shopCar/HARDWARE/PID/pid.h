#ifndef __PID_H
#define __PID_H	 
#include "sys.h"
typedef struct 
{
	double Expect;//����������Ĵ�����ֵ
	double Currn;//TIM3����Ĵ�����ֵ����Ӧ���ת�٣�
	double Err0;  //��ǰ���
	double Err1;  //�ϴ����
	double ErrInt;
	double Kp;    //Pϵ��
	double Ki;    //Iϵ��
	double Kd;    //Dϵ��
}PID_TypDef;

void PID_Init(PID_TypDef*PID);//PID������ʼ��

double PID_run(PID_TypDef* PID,double error);  //PID���к���

void PID_Set(PID_TypDef *PID,double Kp,double Ki,double Kd);//PID  ��������

#endif

