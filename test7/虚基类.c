#include<iostream>
using namespace std;
class Cpeople
{
public:
	Cpeople(){age=-1;weight=-1;money=-1;cout<<"Cpeople����"<<endl;}
	Cpeople(int a,double b,double c){age=a;weight=b;money=c;cout<<"Cpeople����"<<endl;}
	~Cpeople(){cout<<"Cpeople����"<<endl;}
	int showAge(){return age;}
	double showMoney(){return money;}
private:
	int age;
	double weight;
	double money;
};
class Cboss: virtual public Cpeople
{
public:
	Cboss(){cout<<"Cboss����"<<endl;}
	~Cboss(){cout<<"Cboss����"<<endl;}
	void goAboard(){}
};
class Cworker: virtual public Cpeople
{
public:
	Cworker(){cout<<"Cwork����"<<endl;}
	~Cworker(){cout<<"Cwork����"<<endl;}
	void startWork(){}
	void endWork(){}
	int getActualAge(){return actualAge;}
private:
	int actualAge;
};
class Cemployer:public Cboss,public Cworker
{
public:
	Cemployer(){cout<<"Cemployer����"<<endl;}
	Cemployer(int a,double b,double c):Cpeople(a,b,c){}
	~Cemployer(){cout<<"Cemployer����"<<endl;}
};


int main(){
	Cemployer em1(10,20,30);
	cout<<"age:"<<em1.showAge()<<endl;
	cout<<"money:"<<em1.showMoney()<<endl;

}