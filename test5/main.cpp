#include <iostream>
#include "A.h"
#include "B1.h"
#include "B2.h"
#include "B3.h"
using namespace std;

//实验5
int main() {
	B1 b1;
	B2 b2;
	B3 b3;
	//公有继承
	b1.seta(1,2,3);//设置来自父类的
	b1.setb1(4,5,6);//设置本身的
	cout<<b1.ai<<endl;//可以访问
	cout << "b1a i:" << b1.getAi()<< " j:" << b1.getAj() << " k:" << b1.getAk() << endl;
	cout << "b1  i:" << b1.getBi() << " j:" << b1.getBj() << " k:" << b1.getBk() << endl;

	//私有继承
	//b2.seta(7, 8, 9);//不可访问，已是private 性质
	b2.setAi(7);
	b2.setAj(8);
	b2.setAk(9);
	b2.setb2(10,11,12);
	cout<<"b2a i:"<<b2.getAi()<<" j:"<<b2.getAj()<<" k:"<<b2.getAk()<<endl;
	cout<<"b2  i:"<<b2.getBi()<<" j:"<<b2.getBj()<<" k:"<<b2.getBk()<<endl;
	//保护继承
	//b3.seta(13,14,15);//不可访问，已是protected 类型
	b3.setAi(13);
	b3.setAj(14);
	b3.setAk(15);
	b3.setb3(16, 17, 18);
	cout << "b3a i:" << b3.getAi() << " j:" << b3.getAj() << " k:" << b3.getAk() << endl;
	cout << "b3  i:" << b3.getBi() << " j:" << b3.getBj() << " k:" << b3.getBk() << endl;
}
