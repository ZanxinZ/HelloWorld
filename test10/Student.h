#pragma once
#include "Lesson.h"
#ifndef _Student_H
#define	_Student_H
/*
*ѧ����
*/
class Student
{
public:
	Student();
	Student(string name, bool sex, int age);
	~Student();
	
	int getID() { return this->id; }
	int getAge() { return this->age; }
	bool getSex() { return this->sex; }
	string getName() { return this->name; }
	int getLessonCount() { return this->lessonCount; }
	
	Lesson *getLessons() { return this->lesson; }

	void setID(int id);
	void setName(string name);
	bool setAge(int age);
	void setSex(bool sex);

	//��ʾ�γ�
	void showLesson(void);
	//�����γ�
	void addLesson(string name, int perform,double score);
	//ɾ���γ�
	void deleteLesson(string name);
	//�޸Ŀγ�
	bool changeLesson(void);
private:
	
	int id;
	string name;
	int age;
	bool sex;				//1:�� 0��Ů
	Lesson lesson[50];
	int lessonCount;
};
#endif
