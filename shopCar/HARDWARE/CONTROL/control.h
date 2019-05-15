#ifndef __CONTORL_H
#define __CONTORL_H	 
#include "pid.h"
#include "sys.h"


#define dj_on   1250
#define dj_off  1900



extern PID_TypDef  Line_PID;
void start(void);
void walkwall(int turnmode);
void leave_wall(void);
void finding(int goods_shelf);
void turn(int timer,int direction);
void count_line(int numberline,int rmode,int pidflag);
void shuxian(u16 flag,u16 smode);
void buzheng(void);
void car_anticlockwise(void);//反时针
void car_clockwise(void);//顺时针
void Go_away(void);
void go_backwards(void);
void PWM_renovate(u16 M1,u16 M2) ; //电机PWM刷新
void Line_Following(u8 mode_line);
double get_error(u8 mode);
void take_photo(void);

#endif

