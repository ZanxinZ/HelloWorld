#include <iostream>
#include <math.h>
using namespace std;

class Point{
public :
virtual double getArea()=0;
virtual bool isCircle()=0;
};

class Square:public Point{
public :
	Square(){}
	Square(int a,int  b){x=a;y=b;}
	double getArea(){
	return x*y;
	};
	bool isCircle(){return false;}
private :
    double x,y;

};
class Circle:public Point{
public :
	Circle(){}
	Circle(int r){radius=r;}
	double getArea(){
	return radius*radius*3.14;
	};
	bool isCircle(){return true;}
private :
    double radius;

};
int main(){
	Square s1(2,4);
	Circle c1(5);
	Point *p;
	p=&s1;
	cout<<"是圆吗？"<<p->isCircle()<<"面积："<<p->getArea()<<endl;
	p=&c1;
	cout<<"是圆吗？"<<p->isCircle()<<"面积："<<p->getArea()<<endl;
	//cout<<s1.isCircle();
}
// 输出结果
//是圆吗？0 面积：8
//是圆吗？1 面积：78.5
