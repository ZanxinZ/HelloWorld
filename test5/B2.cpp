#include "B2.h"
B2::B2(void){}
B2::~B2(void){}
//初始化
void B2::setb2(int my_b2i,int my_b2j,int my_b2k){
	b2i=my_b2i;
	b2j=my_b2j;
	b2k=my_b2k;
}
int B2::getBi(){
	return b2i;
}
int B2::getBj(){
	return b2j;
}
int B2::getBk(){
	return b2k;
}
void B2::setBi(int i) {
	b2i = i;
}
void B2::setBj(int j) {
	b2j = j;
}
void B2::setBk(int k) {
	b2k = k;
}


int B2::getAi(){
	return A::getAi();
}
int B2::getAj(){
	
	return A::getAj();
}
int B2::getAk(){
	return A::getAk();
}
void B2::setAi(int i){
	A::ai=i;//父类公共
}
void B2::setAj(int j){
	A::aj=j;//父类保护
}
void B2::setAk(int k){
	A::setAk(k);//父类私有只能通过父类方法
}