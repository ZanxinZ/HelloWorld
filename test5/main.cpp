#include <iostream>
#include "A.h"
#include "B1.h"
#include "B2.h"
#include "B3.h"
using namespace std;

//ʵ��5
int main() {
	B1 b1;
	B2 b2;
	B3 b3;
	//���м̳�
	b1.seta(1,2,3);//�������Ը����
	b1.setb1(4,5,6);//���ñ����
	cout<<b1.ai<<endl;//���Է���
	cout << "b1a i:" << b1.getAi()<< " j:" << b1.getAj() << " k:" << b1.getAk() << endl;
	cout << "b1  i:" << b1.getBi() << " j:" << b1.getBj() << " k:" << b1.getBk() << endl;

	//˽�м̳�
	//b2.seta(7, 8, 9);//���ɷ��ʣ�����private ����
	b2.setAi(7);
	b2.setAj(8);
	b2.setAk(9);
	b2.setb2(10,11,12);
	cout<<"b2a i:"<<b2.getAi()<<" j:"<<b2.getAj()<<" k:"<<b2.getAk()<<endl;
	cout<<"b2  i:"<<b2.getBi()<<" j:"<<b2.getBj()<<" k:"<<b2.getBk()<<endl;
	//�����̳�
	//b3.seta(13,14,15);//���ɷ��ʣ�����protected ����
	b3.setAi(13);
	b3.setAj(14);
	b3.setAk(15);
	b3.setb3(16, 17, 18);
	cout << "b3a i:" << b3.getAi() << " j:" << b3.getAj() << " k:" << b3.getAk() << endl;
	cout << "b3  i:" << b3.getBi() << " j:" << b3.getBj() << " k:" << b3.getBk() << endl;
}
