#pragma once
#include "a.h"
class B3 :
	protected A
{
public:
	B3(void);
	~B3(void);
	int  b3i;
	void setb3(int my_b3i,int my_b3j,int my_b3k);
	int getBi();
	int getBj();
	int getBk();

	int getAi();//操作父类成员
	int getAj();
	int getAk();
	void setAi(int i);
	void setAj(int j);
	void setAk(int k);
protected:
	int b3j;
private:
	int b3k;
};

