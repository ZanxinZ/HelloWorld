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
//����ѧ��
void StudentBiz::addStudent(string name, bool sex, int age) {
	UniversityStudent s(name, sex, age);
	students[studentCount] = s;
	students[studentCount].setID(idNum);
	if (sex == 1) { boyCount++; }
	else if (sex == 0) { girlCount++; }
	studentCount++;
	idNum++;
}
//����ѧ��,����ѧ���������������
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
//ɾ��ѧ��
void StudentBiz::deleteStudent(int id) {
	int searchIndex = searchStudent(id);
	if (searchIndex == -1) { cout << "�Ҳ���ID,ɾ��ʧ��" << endl; }
	else {
		if (students[searchIndex].getSex() == 1) { boyCount--; }
		else if (students[searchIndex].getSex() == 0) { girlCount--; }
		for (int i = searchIndex; i < studentCount; i++)
		{
			students[i] = students[i + 1];
		}
		studentCount--;

		cout << "ɾ���ɹ���" << endl;
	}

}
//�޸�ѧ��
bool StudentBiz::changeStudent(int id) {
	int searchIndex = searchStudent(id);
	int choice = -1;
	
	int tempAge = 0;		//�޸�������
	string tempSex;			//�޸��Ա�
	string tempName;		//�޸�������

	string  addLessonName;	//Ҫ��ӵĿε�����
	int addPerform = 0;			//Ҫ��ӵĿεķ���
	double addScore = 0;		//Ҫ��ӵĿε�ѧ��
	string  deleteLessonName;//Ҫɾ���Ŀε�����
	int confirm = -1;			//ɾ��ȷ��
	if (searchIndex == -1) { cout << "�Ҳ���ID,�޸�ʧ��" << endl; return false; }
	else {
		cout << "\n1:�޸�����\n\n2:�޸��Ա�\n\n3:�޸�����\n\n4:" <<
			"�޸Ŀγ�\n\n5:���ӿγ�\n\n6:ɾ���γ�\n\n7:������ҳ\n" << endl;
		cout << "��ѡ��";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "������" << students[searchIndex].getName() << endl;
			cout << "�޸�����Ϊ��";
			cin >> tempName;
			students[searchIndex].setName(tempName);
			break;
		case 2:
			cout << "�Ա�";
			if (students[searchIndex].getSex() == 1) { cout << "��" << endl; }
			else if (students[searchIndex].getSex() == 0) { cout << "Ů" << endl; }
			cout << "�޸��Ա�Ϊ��";
			cin >> tempSex;
			if (tempSex == "��")
				students[searchIndex].setSex(1);
			else if (tempSex == "Ů") {
				students[searchIndex].setSex(0);
			}
			else { cout << "����ȷ���루��/Ů��" << endl; return false; }
			break;
		case 3:
			cout << "���䣺" << students[searchIndex].getAge() << endl;
			cout << "�޸�����Ϊ(0--150)��";
			cin >> tempAge;
			if (students[searchIndex].setAge(tempAge) == 0) {
				cout << "�����������,�޸�ʧ��" << endl;
				return false;
			}

			break;
		case 4:										//�޸Ŀγ�
			if (students[searchIndex].changeLesson() == 1) { return true; }
			else { return false; }
			break;
		case 5:
			cout << "�����γ�����Ϊ:";
			cin >> addLessonName;
			cout << "�����γ̳ɼ�Ϊ:";
			cin >> addPerform;
			cout << "�����γ�ѧ��Ϊ:";
			cin >> addScore;
			students[searchIndex].addLesson(addLessonName, addPerform,addScore);
			break;
		case 6:
			students[searchIndex].showLesson();
			cout << "ɾ���γ�����Ϊ:";
			cin >> deleteLessonName;
			cout << "ȷ��ɾ���γ������� 0 ";
			cin >> confirm;
			if (confirm == 0) { students[searchIndex].deleteLesson(deleteLessonName); }
			else { cout << "�γ�δɾ����"; return false; }
			break;

		default:
			break;
		}
		return true;//�޸ĳɹ�
	}

}