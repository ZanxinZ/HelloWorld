#pragma once
#include "Student.h"
#include "StudentBiz.h"
using namespace std;
#ifndef _View_
#define _View_
/*
*������
*������ʾ��Ϣ
*/
class View
{
public:
	StudentBiz studentBiz;
	View();
	~View();
	//��ʾ���˴�����Ϣ
	void showMess(UniversityStudent s1);
	//��ʾ��������Ϣ
	void showMess(StudentBiz biz);
	//��ʾ����ϸ����Ϣ
	void showDetailMess(UniversityStudent s1);

	//��������
	string inputName(void);
	//��������
	int inputAge(void);
	//�����Ա�
	int inputSex(void);
	//����ID
	int inputID(void);
	
	//��ʾ�˵�
	void View::showMenu(void);
	//��ʾ�˵���ѡ��
	int doMenu(void);
	
	//�������ӿ�
	bool View::doView(void);
};


#endif

