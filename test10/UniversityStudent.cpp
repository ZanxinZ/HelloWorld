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
//�����ѧ��
double UniversityStudent::getScoreSum(void) {
	return scoreSum;
}
//���ƽ������
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
		rate = point->getPerform()*0.01;		//�ɼ�ռ100��֮����
		tempScore = rate*point->getScore();//ĳһ�γ̣��ɼ����ʳ���ѧ��
		performancePoint += tempScore;
		point++;
	}
	this->performancePoint = performancePoint/getLessonCount();
}