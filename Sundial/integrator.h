//---------------------------------------------------------------------------

#ifndef integratorH
#define integratorH


//подключение заголовочного файла библиотеки векторных и матричных операций
#include <armadillo>

using namespace arma;

// опережающие декларации
class TModel;

class TIntegrator
{
    protected:
        // макисмальная погрешность на шаге
        long double Eps;

    public:
        // базовый конструктор
        TIntegrator() : Eps( 1e-8 ) {}
        inline void setPrecision( long double Eps ) { this->Eps = Eps; }
        inline long double getPrecision() const { return Eps; }
        /* абстрактный метод, реализующий процедуру численного интегрирования вовзращающий глобальную
        погрешность вычислений */
        virtual long double Run(TModel* Model) = 0;
        virtual ~TIntegrator(){}
};

class TDormandPrinceIntegrator : public TIntegrator
{
    private:
        // Коэффициенты a,b,c
        static const long double c[7], a[7][6], b1[7], b2[7];
        // Коэффициенты K[i]
        vec K[7];
        // Машинный нуль
        long double u;
    public:
        TDormandPrinceIntegrator();
        virtual long double Run(TModel* Model);
        ~TDormandPrinceIntegrator(){}
};


#endif
