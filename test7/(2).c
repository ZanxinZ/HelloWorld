#include<iostream>
using namespace std;

class Rectangle{
public:
	Rectangle(){}
	Rectangle(double l,double w){length=l;width=w;}
	virtual double getArea(){return length*width;}
	~Rectangle(){}
	double getLength(){return length;}
private:
	double length;
	double width;
};
class Square:public Rectangle{
public:	Square(){}
	Square(double a):Rectangle(a,a){}
	
	~Square(){}
	double getArea(){return getLength()*getLength();}
};

int main(){
	
	Square s1(4);
	cout<<"area:"<<s1.getArea()<<endl;
}