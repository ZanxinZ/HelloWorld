#include "B3.h"
B3::B3(void){}
B3::~B3(void){}
void B3::setb3(int my_b3i,int my_b3j,int my_b3k){
	b3i=my_b3i;
	b3j=my_b3j;
	b3k=my_b3k;
}
//���������Ա
int B3::getBi(){
	return b3i;
}
int B3::getBj(){
	return b3j;
}
int B3::getBk(){
	return b3k;
}
//�������Ը���ĳ�Ա
int B3::getAi() {
	return A::getAi();
}
int B3::getAj() {

	return A::getAj();
}
int B3::getAk() {
	return A::getAk();
}
void B3::setAi(int i) {
	A::ai = i;//���๫��
}
void B3::setAj(int j) {
	A::aj = j;//���ౣ��
}
void B3::setAk(int k) {
	A::setAk(k);//����˽��ֻ��ͨ�����෽��
}