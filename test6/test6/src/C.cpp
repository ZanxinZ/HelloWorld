#include "C.h"
#include <iostream>
using namespace std;
C::C()
{
    ci=0;
    cj=0;
    ck=0;
}
C::C(int i,int j,int k){
    ci=i;
    cj=j;
    ck=k;
}
C::C(C &c){
    ci=c.ci;
    cj=c.cj;
    ck=c.ck;
}
C::~C()
{
    cout<<"C类型对象被回收"<<endl;
}
