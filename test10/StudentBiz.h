#pragma once
//#include "Student.h"
#include "UniversityStudent.h"
using std::string;
#ifndef _StudentBiz_
#define _StudentBiz_
/*
*ѧ��ҵ����
*���һЩ��ѧ����Ϣ�Ĳ�������
*/
class StudentBiz
{
public:
	
	StudentBiz();
	~StudentBiz();
	//����ѧ��
	void addStudent(string name, bool sex, int age);
	//����ѧ��,����ѧ���������������
	int searchStudent(int id);
	int searchStudent(string name);
	//ɾ��ѧ��
	void deleteStudent(int id);
	//�޸�ѧ��
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

