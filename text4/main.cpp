#include <iostream>
#include "Point.h"
using namespace std;
Point getPoint();
//实验4
int main() {
	Point points[3];
	Point *_points[3];//指向对象的指针
	double area;
	int i;
	for ( i = 0; i < sizeof(points)/sizeof(Point); i++)
	{
		_points[i] = &points[i];
		*_points[i] = getPoint();
	}

	for ( i = 0; i < sizeof(points) / sizeof(Point); i++)
	{
		cout << " X:" << _points[i]->getX() << "\tY:" << _points[i]->getY() << endl;
	}
	area=calcuArea(_points[0],_points[1],_points[2]);
	cout << area << endl;
	

	Point line[3][2];
	void *_line[3];
	line[0][0].setX(2);
	line[0][0].setY(4);
	_line[0] = &line[0][0];
	
	double a;
	cout << _line[0]<< endl;
	
}
//获得输入的点
Point getPoint() {
	Point p1;
	double x, y;
	cin >> x;
	cin >> y;
	p1.setX(x);
	p1.setY(y);
	return p1;
}
