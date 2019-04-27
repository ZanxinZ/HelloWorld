#ifndef B_H
#define B_H


class B
{
    public:
        B();
        B(int i,int j,int k);
        B(B  &b);
         ~B();

        int Getbi() { return bi; }

        int bi;

    protected:
        int bj;

    private:
        int bk;
};

#endif // B_H
