#ifndef C_H
#define C_H

#include <A.h>
#include <B.h>

class C : public A ,private B
{
    public:
        C();
        C(int i,int j,int k);
        C(C &c);

         ~C();

        int Getci() { return ci; }

        int ci;

    protected:
        int cj;

    private:
        int ck;
        B bb;
        A aa;
};

#endif // C_H
