#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

typedef struct {
	char light[8];//灯的亮灭
	int num;//亮的灯数量
	char isCrossing;//是否为路口，0：不是，1：是
	char canLeftTurn;//是否能左转，0：不能，1：能
	char canRightTurn;//是否能右转，0：不能，1：能
	char isLongHump;
	
}LightState;//存储灰度的状态
typedef struct{
	float error;//初始偏差
	float resultSpeed; //计算后速度
}LightError;//偏差,与pid构建联系


typedef struct{
	char isGoline;//是否正在走直线 0:不在走直线，1：在走直线
	char isHoldJG;//前方激光是否被挡住 0：未被挡住 1：曾被挡住
	char isDoOption;//最开始时，是否做OLED上的选择 0：不做选择  1：做选择
}CarState;//车子状态,做标志位
////////////////////////////////////////////////////////////////////////////////// 	
void TIM2_Int_Initl(u16 arr,u16 psc);
void getLightNum(void);
void getError(void);

#endif
