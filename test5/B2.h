#pragma once
#include "a.h"

class B2 :
	private A
{
public:
	B2(void);
	~B2(void);
	int b2i;
	void setb2(int my_b2i,int my_b2j,int my_b2k);
	int getBi();//操作自身成员
	int getBj();
	int getBk();
	void setBi(int i);
	void setBj(int j);
	void setBk(int k);
	
	int getAi();//操作父类成员
	int getAj();
	int getAk();
	void setAi(int i);
	void setAj(int j);
	void setAk(int k);
protected:
	int b2j;
private:
	int b2k;
};

