//-----------------------------8-5
#include <iostream>
using namespace std;
class Mammal
{
public:
	Mammal() {};
	~Mammal() {};
	virtual void speak() ;

};
void Mammal::speak()
{
	 cout << "Mammal speak" << endl; 
}
class Dog :
	public Mammal
{
public:
	Dog() {};
	~Dog() {};
	void speak() {
		cout << "Dog speak" << endl;
	};
};

int main() {
	Dog dog;
	dog.speak();
}
//����ǣ� Dog speak


//-----------------------------------8-6
#include <iostream>

using namespace std;

class Shape
{
public:
	Shape() {};
	~Shape() {};
	virtual double getArea()const=0;
	virtual double getPerim()const = 0;
};
class Rectangle:public Shape
{
public:
	Rectangle() { length = 4; width = 4; };
	~Rectangle() {};
	double getArea()const { return length*width; }
	double getPerim()const { return 2 * (length + width); }
private:
	double length;
	double width;
};

class Cirle:public Shape
{
public:
	Cirle() { radius = 5; };
	~Cirle() {};
	double getArea()const { return 3.14*radius*radius; }
	double getPerim()const { return 3.14 * 2 * radius; };
private:
	double radius;
};


int main() {
	Rectangle r1;
	Cirle c1;
	cout << "���������" << r1.getArea()<<" �����ܳ���"<<r1.getPerim()<< endl;
	cout << "Բ�����" <<c1.getArea() << " Բ�ܳ���" << c1.getPerim() << endl;
}
//���н��
//���������16 �����ܳ���16
//Բ�����78.5 Բ�ܳ���31.4


//8-7
#include <iostream>

using namespace std;

class Point
{
public:
	Point() { x = 5; y = 5; }
	~Point() {}
	Point& operator++() {//ǰ��
		x++;
		y++;
		return *this;
	};
	Point operator++(int) {//����
		Point old = *this;
		++(*this);
		return old;
	}
	int getX() { return x; }
	int getY() { return y; }
private:
	int x;
	int y;
};



int main() {
	Point p1;
	cout << "��ʼ X: " << p1.getX() << " Y:" << p1.getX() << endl;
	
	++p1;
	cout << "ǰ�� X: " << p1.getX() << " Y:" << p1.getX() << endl;
	cout << "���� X: " << p1++.getX() << " Y:" << p1++.getX() << endl;
}



