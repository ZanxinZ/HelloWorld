#pragma once
#include "string"
#include <iostream>
using namespace std;
using std::string;

#ifndef _Lesson_H
#define _Lesson_H
class Lesson
{
public:
	Lesson();
	Lesson(string name, int perform,double score);
	~Lesson();

	int getPerform() { return perform; }
	string getName() { return name; }
	double getScore(void) { return score; }

	//设置课程名称
	void setName(string name) {this->name = name;}
	//设置课程成绩
	bool setPerform(int perform) {
		if (perform >= 0 && perform <= 100) {
			this->perform = perform;
			return true;
		}
		else { 
			cout << "成绩输入不正确..."; 
			return false;
		}
	}
	void setScore(double score) {
		this->score = score;
	}
private:
	int perform;//某一课成绩
	string name;//科目名称
	double score;//科目学分
};

#endif // !_Score_H



