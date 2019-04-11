#include "Point.h"
#include <math.h>
#include <iostream>
using namespace std;
double Point::getX() {
	return x;
}
double Point::getY() {
	return y;
}
void Point::setX(double temp) {
	x = temp;
}
void Point::setY(double temp) {
	y = temp;
}
double calcuArea(Point *p1,Point *p2,Point *p3) {
	double area=3;
	double line1 = sqrt(pow((p1->getX() - p2->getX()), 2) + pow((p1->getY() - p2->getY()), 2));
	double line2 = sqrt(pow((p2->getX() - p3->getX()), 2) + pow((p2->getY() - p3->getY()), 2));
	double line3 = sqrt(pow((p1->getX() - p3->getX()), 2) + pow((p1->getY() - p3->getY()), 2));
	cout << line1 << endl;
	cout << line2 << endl;
	cout << line3 << endl;
	area = sqrt((line1 + line2 + line3)*(line1 + line2 - line3)*(line1 + line3 - line2)*(line2 + line3 - line1))/4.0;
	return area;
}