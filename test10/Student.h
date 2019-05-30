#pragma once
#include "Lesson.h"
#ifndef _Student_H
#define	_Student_H
/*
*学生类
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

	//显示课程
	void showLesson(void);
	//新增课程
	void addLesson(string name, int perform,double score);
	//删除课程
	void deleteLesson(string name);
	//修改课程
	bool changeLesson(void);
private:
	
	int id;
	string name;
	int age;
	bool sex;				//1:男 0：女
	Lesson lesson[50];
	int lessonCount;
};
#endif
