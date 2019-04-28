//6-8
int *a = new int[10];
//6-14
double *a;
	cout << sizeof(a) << endl;//在X86里4，在X64里8
	cout << sizeof(*a) << endl;//8
//6-15
//一个是指向常类型整型数的指针，一个是指向整型数的常指针
//第一个所指向的内容不可变，第二个一旦被定义指向谁之后本身就不能变
//6-16
int a=2;
	int *p;
	int &r=a;
	p = &a;
	*p = 10;
	r = 5;
//6-20
include <iostream>
using namespace std;
class SimpleCircle
{
public:
	SimpleCircle();
	
	int getRadius() { return *itsRadius; }
	void setRadius(int r) { *itsRadius = r; }
private:
	int *itsRadius;
	int	radius;
};

SimpleCircle::SimpleCircle()
{
	itsRadius = &radius;
	*itsRadius = 0;
}
int main() {
	SimpleCircle circle;
	circle.setRadius(20);
	cout << circle.getRadius() << endl;
}	
