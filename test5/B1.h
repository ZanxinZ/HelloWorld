#pragma once
#include "a.h"
class B1 :
	public A
{
public:

	B1(void);
	~B1(void);
	int  b1i;
	void setb1(int my_b1i,int my_b1j,int my_b1k);
	int getBi();
	int getBj();
	int getBk();
	
	

protected:
	int b1j;
private:
	int b1k;
};

