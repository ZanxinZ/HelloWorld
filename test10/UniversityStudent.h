#pragma once
#include "Student.h"
/*
*大学生类
*继承自学生
*/
class UniversityStudent :
	public Student
{
public:
	UniversityStudent();
	UniversityStudent (string name, bool sex, int age);
	~UniversityStudent();

	//获得总学分
	double getScoreSum(void);
	//获得平均绩点
	double getPerformPoint(void);

	void calcuScoreSum(void);
	void calcuPerformPoint(void);
private:
	double scoreSum;		//总学分
	double performancePoint;//绩点
};

