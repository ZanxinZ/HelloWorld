#include<iostream>
using namespace std;
class Cpeople
{
public:
	Cpeople(){age=-1;weight=-1;money=-1;cout<<"Cpeople构造"<<endl;}
	Cpeople(int a,double b,double c){age=a;weight=b;money=c;cout<<"Cpeople构造"<<endl;}
	~Cpeople(){cout<<"Cpeople销毁"<<endl;}
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
	Cboss(){cout<<"Cboss构造"<<endl;}
	~Cboss(){cout<<"Cboss销毁"<<endl;}
	void goAboard(){}
};
class Cworker: virtual public Cpeople
{
public:
	Cworker(){cout<<"Cwork构造"<<endl;}
	~Cworker(){cout<<"Cwork销毁"<<endl;}
	void startWork(){}
	void endWork(){}
	int getActualAge(){return actualAge;}
private:
	int actualAge;
};
class Cemployer:public Cboss,public Cworker
{
public:
	Cemployer(){cout<<"Cemployer构造"<<endl;}
	Cemployer(int a,double b,double c):Cpeople(a,b,c){}
	~Cemployer(){cout<<"Cemployer销毁"<<endl;}
};


int main(){
	Cemployer em1(10,20,30);
	cout<<"age:"<<em1.showAge()<<endl;
	cout<<"money:"<<em1.showMoney()<<endl;

}