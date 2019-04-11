#pragma once
#ifndef _Point_H

/*
µãµÄÀà
*/
class Point {
public:
	Point() {
		x = 0;
		y = 0;
	}
	Point(double x, double y) {
		setX(x);
		setY(y);
	}
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
private:	
	double x;
	double y;

};
double calcuArea(Point *p1, Point *p2, Point *p3);
#endif // !_Point_H
