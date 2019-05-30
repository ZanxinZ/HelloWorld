#pragma once
//#include "Student.h"
#include "UniversityStudent.h"
using std::string;
#ifndef _StudentBiz_
#define _StudentBiz_
/*
*学生业务类
*存放一些对学生信息的操作方法
*/
class StudentBiz
{
public:
	
	StudentBiz();
	~StudentBiz();
	//增加学生
	void addStudent(string name, bool sex, int age);
	//查找学生,返回学生在数组里的索引
	int searchStudent(int id);
	int searchStudent(string name);
	//删除学生
	void deleteStudent(int id);
	//修改学生
	bool changeStudent(int id);


	int getStudentCount(void) {return studentCount;}
	int getBoyCount(void) { return boyCount; }
	int getGirlCount(void) { return girlCount; }

	UniversityStudent students[300];
private:
	int studentCount;
	int boyCount;
	int girlCount;
	int idNum;
};
#endif

