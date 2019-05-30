
#include "Lesson.h"
#include "Student.h"
#include <iostream>
using namespace std;
Student::Student()
{
	lessonCount = 0;
	
	setName(" ");
	setSex(0);
	setAge(0);
}
Student::Student(string name, bool sex, int age) {
	lessonCount = 0;
	setName(name);
	setSex(sex);
	setAge(age);
}
Student::~Student()
{
	
}

//设置
void Student::setName(string name) { this->name = name; }
bool Student::setAge(int age) {
	if (age >= 0 && age < 150) {
		this->age = age;
		return 1;
	}
	else {
		
		return 0;
	}
}
void Student::setSex(bool sex) { this->sex = sex; }
void Student::setID(int id) { this->id = id; }

//显示课程
void Student::showLesson(void) {
	cout << "\n\t\t\t-----------------------------\n" << endl;
	for (int i = 0; i < lessonCount; i++)
	{
		cout << "\t\t\t\t" << i + 1 << ":"
			<< getLessons()[i].getName() << "\t"
			<< getLessons()[i].getPerform() << endl;
	}
	cout << "\t\t\t-----------------------------\n" << endl;
}
//新增课程
void Student::addLesson(string name, int perform,double score) {
	Lesson L(name, perform,score);
	lesson[lessonCount] = L;
	lessonCount++;
}
//删除课程
void Student::deleteLesson(string name) {
	int searchIndex = -1;
	for (int i = 0; i < lessonCount; i++)
	{
		if (lesson[i].getName() == name) { searchIndex = i; }
	}
	if (searchIndex == -1) { 
		cout << "没有找到课程,删除失败" << endl;
	}
	else {
		for (int i = searchIndex; i <lessonCount; i++)
		{
			lesson[i] = lesson[i + 1];
		}
		lessonCount--;
		cout << "课程删除成功" << endl;
	}
}
//修改课程
bool Student::changeLesson(void) {
	int choice1 = -1;
	int choice2 = -1;
	string tempLessonName;

	cout << "\n\t\t\t--------选择修改课程----------" << endl;
	for (int i = 0; i < getLessonCount(); i++)
	{
		cout << "\t\t\t\t" << i + 1 << ":"
			<< getLessons()[i].getName() << "\t"
			<< getLessons()[i].getPerform() << endl;

	}
	cout << "\t\t\t-----------------------------\n" << endl;

	cout << "修改课程->填写课程序号:";
	cin >> choice1;

	if (getLessons()[choice1 - 1].getName() == "") {
		cout << "代号不不正确" << endl;
		
		return false;
	}

	cout << "\t\t\t\t" << getLessons()[choice1 - 1].getName() << "\t"
		<< getLessons()[choice1 - 1].getPerform()
		<< endl;
	cout << "\t\t\t\t1:修改课程名称" << endl;
	cout << "\t\t\t\t2:修改课程成绩" << endl;
	cout << "选择操作->";
	cin >> choice2;
	if (choice2 == 1) {
		cout << "修改课程名称为:";
		cin >> tempLessonName;
		getLessons()[choice1 - 1].setName(tempLessonName);
		return true;
	}
	else if (choice2 == 2) {
		int tempPerform = 0;
		cout << "修改课程成绩为:";
		cin >> tempPerform;
		getLessons()[choice1 - 1].setPerform(tempPerform);
	}
}