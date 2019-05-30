#pragma once
#include "Student.h"
#include "StudentBiz.h"
using namespace std;
#ifndef _View_
#define _View_
/*
*界面类
*用于显示信息
*/
class View
{
public:
	StudentBiz studentBiz;
	View();
	~View();
	//显示个人粗略信息
	void showMess(UniversityStudent s1);
	//显示所有人信息
	void showMess(StudentBiz biz);
	//显示个人细节信息
	void showDetailMess(UniversityStudent s1);

	//输入姓名
	string inputName(void);
	//输入年龄
	int inputAge(void);
	//输入性别
	int inputSex(void);
	//输入ID
	int inputID(void);
	
	//显示菜单
	void View::showMenu(void);
	//显示菜单并选择
	int doMenu(void);
	
	//界面主接口
	bool View::doView(void);
};


#endif

