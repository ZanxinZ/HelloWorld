#include<iostream>
using namespace std;
class Cpeople
{
public:
	Cpeople(){age=0;weight=0;money=0;cout<<"Cpeople����"<<endl;}
	Cpeople(int a,double b,double c){age=a;weight=b;money=c;cout<<"Cpeople����"<<endl;}
	~Cpeople(){cout<<"Cpeople����"<<endl;}
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
	Cboss(){cout<<"Cboss����"<<endl;}
	Cboss(int a,double b,double c):Cpeople(a,b,c){cout<<"Cboss����"<<endl;}
	~Cboss(){cout<<"Cboss����"<<endl;}
};
class Cworker: public Cpeople
{
public:
	Cworker(){cout<<"Cwork����"<<endl;}
	Cworker(int a,double b,double c):Cpeople(a,b,c){cout<<"Cwork����"<<endl;}
	~Cworker(){cout<<"Cwork����"<<endl;}
};
class Cemployer:public Cboss,public Cworker
{
public:
	Cemployer(){cout<<"Cemployer����"<<endl;}
	Cemployer(int a,double b,double c):Cworker(a,b,c),Cboss(a,b,c){cout<<"Cemployer����"<<endl;}
	~Cemployer(){cout<<"Cemployer����"<<endl;}
};


int main(){
	Cemployer em1(10,20,30);
	cout<<"age:"<<em1.Cworker::showAge()<<endl;
	cout<<"money:"<<em1.CworkershowMoney()<<endl;

}