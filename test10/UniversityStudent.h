#pragma once
#include "Student.h"
/*
*��ѧ����
*�̳���ѧ��
*/
class UniversityStudent :
	public Student
{
public:
	UniversityStudent();
	UniversityStudent (string name, bool sex, int age);
	~UniversityStudent();

	//�����ѧ��
	double getScoreSum(void);
	//���ƽ������
	double getPerformPoint(void);

	void calcuScoreSum(void);
	void calcuPerformPoint(void);
private:
	double scoreSum;		//��ѧ��
	double performancePoint;//����
};

