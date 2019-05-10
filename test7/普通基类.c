#include<iostream>
using namespace std;
class Cpeople
{
public:
	Cpeople(){age=0;weight=0;money=0;cout<<"Cpeople构造"<<endl;}
	Cpeople(int a,double b,double c){age=a;weight=b;money=c;cout<<"Cpeople构造"<<endl;}
	~Cpeople(){cout<<"Cpeople销毁"<<endl;}
	int showAge(){return age;}
	double showMoney(){return money;}
private:
	int age;
	double weight;
	double money;
};
class Cboss: public Cpeople
{
public:
	Cboss(){cout<<"Cboss构造"<<endl;}
	Cboss(int a,double b,double c):Cpeople(a,b,c){cout<<"Cboss构造"<<endl;}
	~Cboss(){cout<<"Cboss销毁"<<endl;}
};
class Cworker: public Cpeople
{
public:
	Cworker(){cout<<"Cwork构造"<<endl;}
	Cworker(int a,double b,double c):Cpeople(a,b,c){cout<<"Cwork构造"<<endl;}
	~Cworker(){cout<<"Cwork销毁"<<endl;}
};
class Cemployer:public Cboss,public Cworker
{
public:
	Cemployer(){cout<<"Cemployer构造"<<endl;}
	Cemployer(int a,double b,double c):Cworker(a,b,c),Cboss(a,b,c){cout<<"Cemployer构造"<<endl;}
	~Cemployer(){cout<<"Cemployer销毁"<<endl;}
};


int main(){
	Cemployer em1(10,20,30);
	cout<<"age:"<<em1.Cworker::showAge()<<endl;
	cout<<"money:"<<em1.CworkershowMoney()<<endl;

}