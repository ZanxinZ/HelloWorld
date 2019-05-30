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

	//���ÿγ�����
	void setName(string name) {this->name = name;}
	//���ÿγ̳ɼ�
	bool setPerform(int perform) {
		if (perform >= 0 && perform <= 100) {
			this->perform = perform;
			return true;
		}
		else { 
			cout << "�ɼ����벻��ȷ..."; 
			return false;
		}
	}
	void setScore(double score) {
		this->score = score;
	}
private:
	int perform;//ĳһ�γɼ�
	string name;//��Ŀ����
	double score;//��Ŀѧ��
};

#endif // !_Score_H



