//6-8
int *a = new int[10];
//6-14
double *a;
	cout << sizeof(a) << endl;//��X86��4����X64��8
	cout << sizeof(*a) << endl;//8
//6-15
//һ����ָ��������������ָ�룬һ����ָ���������ĳ�ָ��
//��һ����ָ������ݲ��ɱ䣬�ڶ���һ��������ָ��˭֮����Ͳ��ܱ�
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
