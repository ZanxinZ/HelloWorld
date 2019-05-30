#include "View.h"
View::View()
{
	cout << "\n\t\tWelcome to use Student Manage system!" << endl;
	studentBiz.addStudent("大鹏", 1, 25);
	studentBiz.students[0].addLesson("高等数学", 70,4.0);
	studentBiz.students[0].addLesson("电路分析", 80,4.5);
	studentBiz.students[0].addLesson("复变函数", 90,3.0);
}
View::~View()
{
}
//显示信息
void View::showMess(UniversityStudent s1) {
	cout << endl;
	cout << "\t\t\t--------" << s1.getName() << " ID:" << s1.getID() << "---------" << endl;

	cout << "\t\t\t成绩：";
	if (s1.getLessonCount() == 0) {
		cout << "\t暂无" << endl;
	}
	else {
		cout << endl;
		cout << "\t\t\t名称\t\t分数\t学分" << endl;
		for (int i = 0; i < s1.getLessonCount(); i++)
		{
			cout << "\t\t\t";
			cout << i + 1 << ":" << s1.getLessons()[i].getName() << "\t" <<
				s1.getLessons()[i].getPerform() << "\t"<<s1.getLessons()[i].getScore() << endl;
		}
	}
	cout << "\t\t\t课程总数:\t" << s1.getLessonCount() << endl;
	cout << "\t\t\t总学分:\t\t" << s1.getScoreSum() << endl;
	cout << "\t\t\t平均绩点:\t" << s1.getPerformPoint() << endl;
	cout << "\t\t\t-----------------------------" << endl;
	cout << endl;
}
void View::showMess(StudentBiz biz) {
	cout << endl;
	cout << "\t\t\t[----系统信息---]" << endl;
	cout << "\t\t\t ----学生总数：" << biz.getStudentCount() << endl;
	cout << "\t\t\t ----男生人数：" << biz.getBoyCount() << endl;
	cout << "\t\t\t ----女生人数：" << biz.getGirlCount() << endl;
	cout << "\t\t\t[---------------]" << endl;
	cout << endl;
}
void View::showDetailMess(UniversityStudent s1) {
	cout << endl;
	cout << "\t\t\t-------------" << s1.getName() << "------------" << endl;
	cout << "\t\t\t成绩：";
	if (s1.getLessonCount() == 0) {
		cout << "\t暂无" << endl;
	}
	else {
		cout << endl;
		cout << "\t\t\t名称\t\t分数\t学分" << endl;
		for (int i = 0; i < s1.getLessonCount(); i++)
		{
			cout << "\t\t\t";
			cout << i + 1 << ":" << s1.getLessons()[i].getName() << "\t" <<
			s1.getLessons()[i].getPerform() << "\t" << s1.getLessons()[i].getScore() << endl;
		}
	}
	cout << "\t\t\t课程总数:\t" << s1.getLessonCount() << endl;
	cout << "\t\t\t总学分:\t\t" << s1.getScoreSum() << endl;
	cout << "\t\t\t平均绩点:\t" << s1.getPerformPoint() << endl;
	if (s1.getSex() == 1) { cout << "\t\t\t性别：\t男" << endl; }
	else if (s1.getSex() == 0) { cout << "\t\t\t性别：\t女" << endl; }
	cout << "\t\t\t年龄：\t" << s1.getAge() << "岁" << endl;
	cout << "\t\t\tID:\t" << s1.getID() << endl;

	cout << "\t\t\t-----------------------------" << endl;
	cout << endl;
}

//输入姓名
string View::inputName(void) {
	string temp;
	cout << "输入姓名：";
	cin >> temp;
	return temp;
}
//输入年龄
int View::inputAge(void) {
	int temp;
	cout << "输入年龄：";
	cin >> temp;
	return temp;
}
//输入性别
int View::inputSex(void) {
	string sex;
	cout << "输入性别：";
	cin >> sex;
	if (sex == "男") { return 1; }
	else if (sex == "女") { return 0; }
	else { return -1; }
}
//输入ID

int View::inputID(void) {
	int temp;
	cout << "输入要操作的学生ID:";
	cin >> temp;
	return temp;
}
//显示主菜单
void View:: showMenu(void) {
	cout << "\n\t\t\t\t-----主页------\n";
	cout << "\t1:查看所有学生";
	cout << "\t2:查看详细信息";
	cout << "\t3:修改学生信息";
	cout << "\t4:新增学生" << endl;
	cout << "\t5:删除学生";
	cout << "\t6:查看系统信息";
	cout << "\t7:退出系统" << endl;
}
//主菜单显示并选择
int View::doMenu(void) {
	int choice = 0;
	showMenu();
	cout << "选择操作->";
	while (!(choice>0 && choice<8)) {

		if (choice<0 || choice >= 8) { cout << "输出有误，重新输入->"; }
		cin >> choice;

	}
	return choice;
}
//界面主接口
bool View::doView(void) {
	int choice = doMenu();
	int tempId = 0;
	string tempName;
	int tempSexInt;
	bool tempSexBool;
	int tempAge;
	int searchIndex = -1;
	int confirm = -1;
	switch (choice)
	{
	case 1:				//查看所有学生
		cout << "查看所有学生->" << endl;

		for (int i = 0; i < studentBiz.getStudentCount(); i++)
		{
			studentBiz.students[i].calcuScoreSum();
			studentBiz.students[i].calcuPerformPoint();

			showMess(studentBiz.students[i]);

		}
		break;
	case 2:				//查看一个学生
		for (int i = 0; i < studentBiz.getStudentCount(); i++)
		{
			studentBiz.students[i].calcuScoreSum();
			studentBiz.students[i].calcuPerformPoint();
			showMess(studentBiz.students[i]);

		}
		cout << "查看一个学生的详细信息->" << endl;
		tempId = inputID();
		searchIndex = studentBiz.searchStudent(tempId);
		if (searchIndex == -1) { cout << "找不到ID" << endl; }
		else { 
			showDetailMess(studentBiz.students[searchIndex]);
		}
		break;
	case 3:				//修改学生信息
		cout << "修改学生信息->" << endl;
		tempId = inputID();
		if (studentBiz.searchStudent(tempId) != -1) {
			studentBiz.students[searchIndex].calcuScoreSum();
			studentBiz.students[searchIndex].calcuPerformPoint();
			showDetailMess(studentBiz.students[studentBiz.searchStudent(tempId)]);
		}
		studentBiz.changeStudent(tempId);
		break;
	case 4:				//新增学生
		cout << "新增学生->" << endl;
		tempName = inputName();
		tempSexInt = inputSex();
		if (tempSexInt == -1) { cout << "性别输入不正确" << endl; break; }
		if (tempSexInt == 1) { tempSexBool = 1; }
		if (tempSexInt == 0) { tempSexBool = 0; }
		tempAge = inputAge();
		studentBiz.addStudent(tempName, tempSexBool, tempAge);
		break;
	case 5:				//删除学生
		tempId = inputID();
		if (studentBiz.searchStudent(tempId) != -1) {
			showDetailMess(studentBiz.students[studentBiz.searchStudent(tempId)]);
		}
		cout << "确认删除请输入 0 ";
		cin >> confirm;
		if (confirm == 0) { studentBiz.deleteStudent(tempId); }
		else { cout << "删除操作未执行"; }
		break;
	case 6:				//查看系统信息
		showMess(studentBiz);
		break;
	case 7:
		cout << "系统退出..." << endl;
		exit(0);
		break;
	default:
		break;
	}
	return true;
}