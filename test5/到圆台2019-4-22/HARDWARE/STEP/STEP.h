#ifndef __PID_H
#define __PID_H
#include "sys.h"
#include "stdlib.h"	
#include "timer.h"	
///////////////////////////////


void bridge(void);//��һ������
void onboard(int speedown,int speedup);//��Сƽ̨
void crossing(int lr,int delay,int line);//·��
void humps(int count);//�ϰ�
void countLine(int line);//���ߣ���ͣ
void smallHump(int count);//С�ϰ�������
void black_xiepo();
enum {Low,Normal,High};//����ѡ�񣬵��и�
/////////////////////////////////////////////////


#endif
