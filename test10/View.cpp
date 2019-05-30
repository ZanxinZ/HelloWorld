#include "View.h"
View::View()
{
	cout << "\n\t\tWelcome to use Student Manage system!" << endl;
	studentBiz.addStudent("����", 1, 25);
	studentBiz.students[0].addLesson("�ߵ���ѧ", 70,4.0);
	studentBiz.students[0].addLesson("��·����", 80,4.5);
	studentBiz.students[0].addLesson("���亯��", 90,3.0);
}
View::~View()
{
}
//��ʾ��Ϣ
void View::showMess(UniversityStudent s1) {
	cout << endl;
	cout << "\t\t\t--------" << s1.getName() << " ID:" << s1.getID() << "---------" << endl;

	cout << "\t\t\t�ɼ���";
	if (s1.getLessonCount() == 0) {
		cout << "\t����" << endl;
	}
	else {
		cout << endl;
		cout << "\t\t\t����\t\t����\tѧ��" << endl;
		for (int i = 0; i < s1.getLessonCount(); i++)
		{
			cout << "\t\t\t";
			cout << i + 1 << ":" << s1.getLessons()[i].getName() << "\t" <<
				s1.getLessons()[i].getPerform() << "\t"<<s1.getLessons()[i].getScore() << endl;
		}
	}
	cout << "\t\t\t�γ�����:\t" << s1.getLessonCount() << endl;
	cout << "\t\t\t��ѧ��:\t\t" << s1.getScoreSum() << endl;
	cout << "\t\t\tƽ������:\t" << s1.getPerformPoint() << endl;
	cout << "\t\t\t-----------------------------" << endl;
	cout << endl;
}
void View::showMess(StudentBiz biz) {
	cout << endl;
	cout << "\t\t\t[----ϵͳ��Ϣ---]" << endl;
	cout << "\t\t\t ----ѧ��������" << biz.getStudentCount() << endl;
	cout << "\t\t\t ----����������" << biz.getBoyCount() << endl;
	cout << "\t\t\t ----Ů��������" << biz.getGirlCount() << endl;
	cout << "\t\t\t[---------------]" << endl;
	cout << endl;
}
void View::showDetailMess(UniversityStudent s1) {
	cout << endl;
	cout << "\t\t\t-------------" << s1.getName() << "------------" << endl;
	cout << "\t\t\t�ɼ���";
	if (s1.getLessonCount() == 0) {
		cout << "\t����" << endl;
	}
	else {
		cout << endl;
		cout << "\t\t\t����\t\t����\tѧ��" << endl;
		for (int i = 0; i < s1.getLessonCount(); i++)
		{
			cout << "\t\t\t";
			cout << i + 1 << ":" << s1.getLessons()[i].getName() << "\t" <<
			s1.getLessons()[i].getPerform() << "\t" << s1.getLessons()[i].getScore() << endl;
		}
	}
	cout << "\t\t\t�γ�����:\t" << s1.getLessonCount() << endl;
	cout << "\t\t\t��ѧ��:\t\t" << s1.getScoreSum() << endl;
	cout << "\t\t\tƽ������:\t" << s1.getPerformPoint() << endl;
	if (s1.getSex() == 1) { cout << "\t\t\t�Ա�\t��" << endl; }
	else if (s1.getSex() == 0) { cout << "\t\t\t�Ա�\tŮ" << endl; }
	cout << "\t\t\t���䣺\t" << s1.getAge() << "��" << endl;
	cout << "\t\t\tID:\t" << s1.getID() << endl;

	cout << "\t\t\t-----------------------------" << endl;
	cout << endl;
}

//��������
string View::inputName(void) {
	string temp;
	cout << "����������";
	cin >> temp;
	return temp;
}
//��������
int View::inputAge(void) {
	int temp;
	cout << "�������䣺";
	cin >> temp;
	return temp;
}
//�����Ա�
int View::inputSex(void) {
	string sex;
	cout << "�����Ա�";
	cin >> sex;
	if (sex == "��") { return 1; }
	else if (sex == "Ů") { return 0; }
	else { return -1; }
}
//����ID

int View::inputID(void) {
	int temp;
	cout << "����Ҫ������ѧ��ID:";
	cin >> temp;
	return temp;
}
//��ʾ���˵�
void View:: showMenu(void) {
	cout << "\n\t\t\t\t-----��ҳ------\n";
	cout << "\t1:�鿴����ѧ��";
	cout << "\t2:�鿴��ϸ��Ϣ";
	cout << "\t3:�޸�ѧ����Ϣ";
	cout << "\t4:����ѧ��" << endl;
	cout << "\t5:ɾ��ѧ��";
	cout << "\t6:�鿴ϵͳ��Ϣ";
	cout << "\t7:�˳�ϵͳ" << endl;
}
//���˵���ʾ��ѡ��
int View::doMenu(void) {
	int choice = 0;
	showMenu();
	cout << "ѡ�����->";
	while (!(choice>0 && choice<8)) {

		if (choice<0 || choice >= 8) { cout << "���������������->"; }
		cin >> choice;

	}
	return choice;
}
//�������ӿ�
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
	case 1:				//�鿴����ѧ��
		cout << "�鿴����ѧ��->" << endl;

		for (int i = 0; i < studentBiz.getStudentCount(); i++)
		{
			studentBiz.students[i].calcuScoreSum();
			studentBiz.students[i].calcuPerformPoint();

			showMess(studentBiz.students[i]);

		}
		break;
	case 2:				//�鿴һ��ѧ��
		for (int i = 0; i < studentBiz.getStudentCount(); i++)
		{
			studentBiz.students[i].calcuScoreSum();
			studentBiz.students[i].calcuPerformPoint();
			showMess(studentBiz.students[i]);

		}
		cout << "�鿴һ��ѧ������ϸ��Ϣ->" << endl;
		tempId = inputID();
		searchIndex = studentBiz.searchStudent(tempId);
		if (searchIndex == -1) { cout << "�Ҳ���ID" << endl; }
		else { 
			showDetailMess(studentBiz.students[searchIndex]);
		}
		break;
	case 3:				//�޸�ѧ����Ϣ
		cout << "�޸�ѧ����Ϣ->" << endl;
		tempId = inputID();
		if (studentBiz.searchStudent(tempId) != -1) {
			studentBiz.students[searchIndex].calcuScoreSum();
			studentBiz.students[searchIndex].calcuPerformPoint();
			showDetailMess(studentBiz.students[studentBiz.searchStudent(tempId)]);
		}
		studentBiz.changeStudent(tempId);
		break;
	case 4:				//����ѧ��
		cout << "����ѧ��->" << endl;
		tempName = inputName();
		tempSexInt = inputSex();
		if (tempSexInt == -1) { cout << "�Ա����벻��ȷ" << endl; break; }
		if (tempSexInt == 1) { tempSexBool = 1; }
		if (tempSexInt == 0) { tempSexBool = 0; }
		tempAge = inputAge();
		studentBiz.addStudent(tempName, tempSexBool, tempAge);
		break;
	case 5:				//ɾ��ѧ��
		tempId = inputID();
		if (studentBiz.searchStudent(tempId) != -1) {
			showDetailMess(studentBiz.students[studentBiz.searchStudent(tempId)]);
		}
		cout << "ȷ��ɾ�������� 0 ";
		cin >> confirm;
		if (confirm == 0) { studentBiz.deleteStudent(tempId); }
		else { cout << "ɾ������δִ��"; }
		break;
	case 6:				//�鿴ϵͳ��Ϣ
		showMess(studentBiz);
		break;
	case 7:
		cout << "ϵͳ�˳�..." << endl;
		exit(0);
		break;
	default:
		break;
	}
	return true;
}