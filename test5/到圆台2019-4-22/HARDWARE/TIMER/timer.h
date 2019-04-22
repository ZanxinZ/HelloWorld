#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

typedef struct {
	char light[8];//�Ƶ�����
	int num;//���ĵ�����
	char isCrossing;//�Ƿ�Ϊ·�ڣ�0�����ǣ�1����
	char canLeftTurn;//�Ƿ�����ת��0�����ܣ�1����
	char canRightTurn;//�Ƿ�����ת��0�����ܣ�1����
	char isLongHump;
	
}LightState;//�洢�Ҷȵ�״̬
typedef struct{
	float error;//��ʼƫ��
	float resultSpeed; //������ٶ�
}LightError;//ƫ��,��pid������ϵ


typedef struct{
	char isGoline;//�Ƿ�������ֱ�� 0:������ֱ�ߣ�1������ֱ��
	char isHoldJG;//ǰ�������Ƿ񱻵�ס 0��δ����ס 1��������ס
	char isDoOption;//�ʼʱ���Ƿ���OLED�ϵ�ѡ�� 0������ѡ��  1����ѡ��
}CarState;//����״̬,����־λ
////////////////////////////////////////////////////////////////////////////////// 	
void TIM2_Int_Initl(u16 arr,u16 psc);
void getLightNum(void);
void getError(void);

#endif
