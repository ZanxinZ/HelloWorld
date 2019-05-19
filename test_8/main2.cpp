#include <iostream>
#include <math.h>
using namespace std;
class baseFly{
public :
    virtual void Fly(){
        cout<<"\n---Class BaseFly::Fly()---\n";
    }

};
class birdFly:public baseFly{
    void Fly(){
           cout<<"\n---Class birdFly::Fly()---\n";
    }
};
class dragonFly:public baseFly{
    void Fly(){
           cout<<"\n---Class dragonFly::Fly()---\n";
    }
};
class planeFly:public baseFly{
    void Fly(){
           cout<<"\n---Class planeFly::Fly()---\n";
    }
};
int main(){
    cout<<"\n测试继承中的多态性（Virtual）"<<endl;
    baseFly *pBase;
    birdFly *pBird=new birdFly();
    pBase=pBird;
    cout<<"\nbirdFly->\n";
    pBase->Fly();

    dragonFly *pDragon=new dragonFly();
    pBase=pDragon;
    cout<<"\dragonFly->\n";
    pBase->Fly();

    planeFly *pPlane=new planeFly();
    pBase=pPlane;//基类指针指向派生类
    cout<<"\planeFly->\n";
    pBase->Fly();
    baseFly bs;

	delete pBase;
	delete pBird;
	delete pDragon;
	delete pPlane;
	return 0;
}
// 运行结果
//继承中的多态性
//birFlyd->

//---Class birdFly::Fly()---
//dragonFly->

//---Class dragonFly::Fly()---
//planeFly->

//---Class planeFly::Fly()---

