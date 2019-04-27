#include "B.h"
#include <iostream>
using namespace std;
B::B()
{
    bi=0;
    bj=0;
    bk=0;
}
B::B(int i,int j,int k){
    bi=i;
    bj=j;
    bk=k;
}
B::B(B &b){
    bi=b.bi;
    bj=b.bj;
    bk=b.bk;
}
B::~B()
{
   cout <<"B类型对象被回收"<<endl;
}
