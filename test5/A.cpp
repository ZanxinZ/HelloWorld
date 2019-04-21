#include "A.h"
A::A(void){}
A::~A(void){}
void A::seta(int my_ai,int my_aj,int my_ak){
	ai=my_ai;
	aj=my_aj;
	ak=my_ak;
}
int A::getAi(){
	return ai;
}
int A::getAj(){
	return aj;
}
int A::getAk(){
	return ak;
}
void A::setAi(int i){
	ai=i;
}
void A::setAj(int j){
	aj=j;
}
void A::setAk(int k){
	ak=k;
}