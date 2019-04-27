#include "A.h"
#include <iostream>
using namespace std;
A::A()
{
    ai=0;
    aj=0;
    ak=0;
}
A::A(int i,int j,int k){
    ai=i;
    aj=j;
    ak=k;
}
A::A(A &a){
    ai=a.ai;
    aj=a.aj;
    ak=a.ak;
}
A::~A()
{

    cout<<"A类型对象被回收"<<endl;
}
