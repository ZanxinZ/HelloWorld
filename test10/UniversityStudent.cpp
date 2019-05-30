#include "UniversityStudent.h"



UniversityStudent::UniversityStudent()
{
	setName(" ");
	setSex(0);
	setAge(0);
	scoreSum = 0;
	performancePoint = 0;
}
UniversityStudent::UniversityStudent (string name, bool sex, int age){
	setName(name);
	setSex(sex);
	setAge(age);
	scoreSum = 0;
	performancePoint = 0;
}

UniversityStudent::~UniversityStudent()
{
}
//获得总学分
double UniversityStudent::getScoreSum(void) {
	return scoreSum;
}
//获得平均绩点
double UniversityStudent::getPerformPoint(void) {
	
	return performancePoint;
}

void UniversityStudent::calcuScoreSum(void) {
	double scoreSum = 0;
	Lesson *point;
	point = getLessons();
	for (int i = 0; i < getLessonCount(); i++)
	{
		scoreSum += point->getScore();
		point++;
	}
	this->scoreSum = scoreSum;
}
void UniversityStudent::calcuPerformPoint(void) {
	double performancePoint=0;
	Lesson *point;
	double rate = 0;
	double tempScore=0;
	point = getLessons();
	for (int i = 0; i < getLessonCount(); i++)
	{
		rate = point->getPerform()*0.01;		//成绩占100分之多少
		tempScore = rate*point->getScore();//某一课程，成绩比率乘以学分
		performancePoint += tempScore;
		point++;
	}
	this->performancePoint = performancePoint/getLessonCount();
}