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
//结果是： Dog speak


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
	cout << "矩形面积：" << r1.getArea()<<" 矩形周长："<<r1.getPerim()<< endl;
	cout << "圆面积：" <<c1.getArea() << " 圆周长：" << c1.getPerim() << endl;
}
//运行结果
//矩形面积：16 矩形周长：16
//圆面积：78.5 圆周长：31.4



//8-7
#include <iostream>

using namespace std;

class Point
{
public:
	Point() { x = 5; y = 5; }
	~Point() {}
	Point& operator++() {//前置
		x++;
		y++;
		return *this;
	}
	Point& operator--() {//前置
		x--;
		y--;
		return *this;
	}
	Point operator++(int) {//后置
		Point old = *this;
		++(*this);
		return old;
	}
	Point operator--(int) {//后置
		Point old = *this;
		--(*this);
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
	cout << "起始 X: " << p1.getX() << " Y:" << p1.getY() << endl;
	cout << "前置 X: " <<(++p1).getX() << " Y:" <<(++p1).getY() << endl;
	cout << "后置 X: " << p1++.getX() << " Y:" << p1++.getY() << endl;
	Point p2;
	cout << "起始 X: " << p2.getX() << " Y:" << p2.getY() << endl;
	cout << "前置 X: " <<(--p2).getX() << " Y:" <<(--p2).getY() << endl;
	cout << "后置 X: " << p2--.getX() << " Y:" << p2--.getY() << endl;
}
//结果：
//起始  X:5 Y:5
//前置  X:6 Y:7
//后置  X:7 Y:8
//起始  X:5 Y:5
//前置  X:4 Y:3
//后置  X:3 Y:2


