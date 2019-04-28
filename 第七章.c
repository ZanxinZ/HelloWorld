//7-4
//在多继承路径上有一个公共的基类，在路径中某几个汇合处，这个公共的基类会产生多个副本，
//而若声明这个公共基类为虚基类，则只继承这个基类的一份拷贝
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
{cout << "mammal构造" << endl;}
Mammal::~Mammal(){cout << "mammal析构" << endl;}
class Dog:public Mammal
{
public:
	Dog();
	~Dog();
};
Dog::Dog()
{
	cout << "dog构造" << endl;
}
Dog::~Dog()
{
	cout << "dog析构" << endl;
}
int main() {
	Dog dog;
}
//结果为：
//mammal构造
//dog构造
//dog析构
//mammal析构
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
	void fun1() { cout << "基类fun1" << endl; };
	void fun2() { cout << "基类fun2" << endl; };
};
class DerivedClass:BaseClass
{
public:
	DerivedClass() {};
	~DerivedClass() {};
	void fun1() { cout << "派生类fun1" << endl; };
	void fun2() { cout << "派生类fun2" << endl; };
};
int main() {
	DerivedClass a1;
	a1.fun1();
	a1.fun2();
	
	BaseClass *a=new BaseClass;
	
	a->fun1();
	a->fun2();
}