#include <iostream>

using namespace std;
template<class T>
class Cpoint {
public:
	Cpoint() {}
	Cpoint(double x, double y) { _x = x; _y = y; }
	double getX() { return _x; }
	double getY() { return _y; }

	Cpoint<T>  operator+(const Cpoint<T> &a);
	Cpoint<T> operator-(const Cpoint<T> &a);
	Cpoint operator++(int);
	Cpoint operator--(int);
	Cpoint& operator++();
	Cpoint& operator--();
private:
	T _x, _y;
};
template<class T>
Cpoint<T> Cpoint<T>:: operator +(const Cpoint<T> &b) {
	Cpoint<T> c;
	c._x = _x + b._x;
	c._y = _y + b._y;
	return c;
}
template<class T>
Cpoint<T >Cpoint<T>::operator-(const Cpoint<T> &b) {
	Cpoint<T> c;
	c._x = _x - b._x;
	c._y = _y - b._y;
	return c;
}
template<class T>
Cpoint<T> Cpoint<T>::operator++(int) {
	Cpoint<T> b(_x, _y);
	_x++;
	_y++;
	return  b;
}
template<class T>
Cpoint<T> Cpoint<T>::operator--(int) {
	Cpoint<T> b(_x, _y);
	_x--;
	_y--;
	return  b;
}
template<class T>
Cpoint<T>& Cpoint<T>::operator++() {
	_x++;
	_y++;
	return *this;

}
template<class T>
Cpoint<T>& Cpoint<T>::operator--() {
	_x--;
	_y--;
	return *this;

}
int main()
{
	Cpoint<int> a(1, 1);
	Cpoint<int> b(2, 2);

	cout << "At first ";
	cout << "a=(" << a.getX() << "," << a.getY() << ") ";
	cout << "b=(" << b.getX() << "," << b.getY() << ")" << endl;
	Cpoint<int> c = a + b;
	cout << "a+b=(" << c.getX() << "," << c.getY() << ")" << endl;
	Cpoint<int> d = a - b;
	cout << "a-b=(" << d.getX() << "," << d.getY() << ")" << endl;
	Cpoint<int> e = a++;
	cout << "e=a++ then ";
	cout << "e=(" << e.getX() << "," << e.getY() << ") ";
	cout << "a=(" << a.getX() << "," << a.getY() << ")" << endl;
	Cpoint<int> f = a--;
	cout << "f=a-- then ";
	cout << "f=(" << f.getX() << "," << f.getY() << ") ";
	cout << "a=(" << a.getX() << "," << a.getY() << ")" << endl;
	Cpoint<int> g = ++a;
	cout << "g=++a then ";
	cout << "g=(" << g.getX() << "," << g.getY() << ") ";
	cout << "a=(" << a.getX() << "," << a.getY() << ")" << endl;
	Cpoint<int> h = --a;
	cout << "h=++a then ";
	cout << "h=(" << h.getX() << "," << h.getY() << ") ";
	cout << "a=(" << a.getX() << "," << a.getY() << ")" << endl;
	return 0;
}
//运行结果：
//At first a = (1, 1) b = (2, 2)
//a + b = (3, 3)
//a - b = (-1, -1)
//e = a++ then e = (1, 1) a = (2, 2)
//f = a-- then f = (2, 2) a = (1, 1)
//g = ++a then g = (2, 2) a = (2, 2)
//h = ++a then h = (1, 1) a = (1, 1)