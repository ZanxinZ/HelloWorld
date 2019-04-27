#ifndef A_H
#define A_H


class A
{
    public:
        A();
         A(int i,int j,int k);
         ~A();

        int Getai() { return ai; }
        A(A &a);
        void Setaj(int val) { ai = val; }

        int ai;

    protected:
        int aj;

    private:
    int ak;
};

#endif // A_H
