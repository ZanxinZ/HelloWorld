//7-4
//�ڶ�̳�·������һ�������Ļ��࣬��·����ĳ������ϴ�����������Ļ����������������
//�������������������Ϊ����࣬��ֻ�̳���������һ�ݿ���
//7-5
class Shape
{
public:
	Shape();
	double area;
private:
};
Shape::Shape(){}
class Circle:public Shape
{
public:
	Circle();
	double getArea() { return area; };
private:
};
Circle::Circle(){}
class Rectangle :public Shape {
public :
	Rectangle();
	double getArea() { return area; }
private:
};
Rectangle::Rectangle() {
}
class Square:public Rectangle
{
public:
	Square();
private:
};
Square::Square(){}
//7-6
#include <iostream>
using namespace std;
class Mammal
{
public:
	Mammal();
	~Mammal();
};
Mammal::Mammal()
{cout << "mammal����" << endl;}
Mammal::~Mammal(){cout << "mammal����" << endl;}
class Dog:public Mammal
{
public:
	Dog();
	~Dog();
};
Dog::Dog()
{
	cout << "dog����" << endl;
}
Dog::~Dog()
{
	cout << "dog����" << endl;
}
int main() {
	Dog dog;
}
//���Ϊ��
//mammal����
//dog����
//dog����
//mammal����
//7-8
class Document
{
public:
	Document() {};
	~Document() {};
	string name;

};
class Book:Document
{
public:
	Book() {};
	~Book() {};
	int pageCount;
};
//7-11
#include <iostream>
using namespace std;
class BaseClass
{
public:
	BaseClass() {};
	~BaseClass() {};
	void fun1() { cout << "����fun1" << endl; };
	void fun2() { cout << "����fun2" << endl; };
};
class DerivedClass:BaseClass
{
public:
	DerivedClass() {};
	~DerivedClass() {};
	void fun1() { cout << "������fun1" << endl; };
	void fun2() { cout << "������fun2" << endl; };
};
int main() {
	DerivedClass a1;
	a1.fun1();
	a1.fun2();
	
	BaseClass *a=new BaseClass;
	
	a->fun1();
	a->fun2();
}