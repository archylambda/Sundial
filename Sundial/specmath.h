#ifndef SPECMATH_H
#define SPECMATH_H
#include <armadillo>

using namespace arma;

class SpecMath
{

public:
    SpecMath();

    static long double gradToRad(const int &grad, const int &min);
    //получени матрицы поворота орбитальной СК к инерциальной геоцентрической
    static mat getMatfromOrbToInert(const long double &incl, const long double &longAsc,
                                        const long double &argPer, const long double &trueAnom);
    //перевод из географической СК в Гринвическую СК
    static vec fromGeographToGrinvich(const long double &R, const long double &h,
                                          const long double &lambda, const long double &phi);
    static mat getMatFromInertToGrinvich(const long double &omega, const long double &t);

    static mat getMatFromInertToTopocentric(const long double &s, const long double &phi);
     //возвращает угол гринвического меридиана на передаваемую юлианскую дату
    static long double getSiderealTime(const long double &JD);
};

#endif // SPECMATH_H
