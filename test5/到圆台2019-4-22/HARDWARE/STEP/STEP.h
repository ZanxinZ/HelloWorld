#ifndef __PID_H
#define __PID_H
#include "sys.h"
#include "stdlib.h"	
#include "timer.h"	
///////////////////////////////


void bridge(void);//第一道长桥
void onboard(int speedown,int speedup);//上小平台
void crossing(int lr,int delay,int line);//路口
void humps(int count);//障碍
void countLine(int line);//数线，不停
void smallHump(int count);//小障碍，数线
void black_xiepo();
enum {Low,Normal,High};//三档选择，低中高
/////////////////////////////////////////////////


#endif
