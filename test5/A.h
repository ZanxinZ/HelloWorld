#pragma once
#ifndef _A_H
class A
{
public:
	A(void);
	~A(void);
	int ai;
	void seta(int my_ai,int my_aj,int my_ak);
	int getAi();
	int getAj();
	int getAk();
	void setAi(int i);
	void setAj(int j);
	void setAk(int k);
protected:
	int aj;
private:
	int ak;
};

#endif