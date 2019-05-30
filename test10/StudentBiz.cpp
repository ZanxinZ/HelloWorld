#include "StudentBiz.h"
StudentBiz::StudentBiz()
{
	studentCount = 0;
	boyCount = 0;
	girlCount = 0;
	idNum = 1000;
}
StudentBiz::~StudentBiz()
{
	
}
//增加学生
void StudentBiz::addStudent(string name, bool sex, int age) {
	UniversityStudent s(name, sex, age);
	students[studentCount] = s;
	students[studentCount].setID(idNum);
	if (sex == 1) { boyCount++; }
	else if (sex == 0) { girlCount++; }
	studentCount++;
	idNum++;
}
//查找学生,返回学生在数组里的索引
int StudentBiz::searchStudent(int id) {

	for (int i = 0; i < studentCount; i++)
	{
		if (id == students[i].getID()) { return i; }
	}
	return -1;
}
int StudentBiz::searchStudent(string name) {

	for (int i = 0; i < studentCount; i++)
	{
		if (name == students[i].getName()) { return i; }
	}
	return -1;
}
//删除学生
void StudentBiz::deleteStudent(int id) {
	int searchIndex = searchStudent(id);
	if (searchIndex == -1) { cout << "找不到ID,删除失败" << endl; }
	else {
		if (students[searchIndex].getSex() == 1) { boyCount--; }
		else if (students[searchIndex].getSex() == 0) { girlCount--; }
		for (int i = searchIndex; i < studentCount; i++)
		{
			students[i] = students[i + 1];
		}
		studentCount--;

		cout << "删除成功！" << endl;
	}

}
//修改学生
bool StudentBiz::changeStudent(int id) {
	int searchIndex = searchStudent(id);
	int choice = -1;
	
	int tempAge = 0;		//修改新年龄
	string tempSex;			//修改性别
	string tempName;		//修改新名字

	string  addLessonName;	//要添加的课的名字
	int addPerform = 0;			//要添加的课的分数
	double addScore = 0;		//要添加的课的学分
	string  deleteLessonName;//要删除的课的名字
	int confirm = -1;			//删除确认
	if (searchIndex == -1) { cout << "找不到ID,修改失败" << endl; return false; }
	else {
		cout << "\n1:修改姓名\n\n2:修改性别\n\n3:修改年龄\n\n4:" <<
			"修改课程\n\n5:增加课程\n\n6:删除课程\n\n7:返回主页\n" << endl;
		cout << "请选择：";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "姓名：" << students[searchIndex].getName() << endl;
			cout << "修改姓名为：";
			cin >> tempName;
			students[searchIndex].setName(tempName);
			break;
		case 2:
			cout << "性别：";
			if (students[searchIndex].getSex() == 1) { cout << "男" << endl; }
			else if (students[searchIndex].getSex() == 0) { cout << "女" << endl; }
			cout << "修改性别为：";
			cin >> tempSex;
			if (tempSex == "男")
				students[searchIndex].setSex(1);
			else if (tempSex == "女") {
				students[searchIndex].setSex(0);
			}
			else { cout << "请正确输入（男/女）" << endl; return false; }
			break;
		case 3:
			cout << "年龄：" << students[searchIndex].getAge() << endl;
			cout << "修改年龄为(0--150)：";
			cin >> tempAge;
			if (students[searchIndex].setAge(tempAge) == 0) {
				cout << "年龄输入错误,修改失败" << endl;
				return false;
			}

			break;
		case 4:										//修改课程
			if (students[searchIndex].changeLesson() == 1) { return true; }
			else { return false; }
			break;
		case 5:
			cout << "新增课程名称为:";
			cin >> addLessonName;
			cout << "新增课程成绩为:";
			cin >> addPerform;
			cout << "新增课程学分为:";
			cin >> addScore;
			students[searchIndex].addLesson(addLessonName, addPerform,addScore);
			break;
		case 6:
			students[searchIndex].showLesson();
			cout << "删除课程名称为:";
			cin >> deleteLessonName;
			cout << "确认删除课程请输入 0 ";
			cin >> confirm;
			if (confirm == 0) { students[searchIndex].deleteLesson(deleteLessonName); }
			else { cout << "课程未删除！"; return false; }
			break;

		default:
			break;
		}
		return true;//修改成功
	}

}