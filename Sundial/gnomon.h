#ifndef GNOMON_H
#define GNOMON_H
#include "dateandtime.h"
#include <armadillo>
#include "specmath.h"
#include <math.h>
#include <stdexcept>
using namespace arma;

struct Location {
    long double lambda; // долгота
    long double phi;    // широта

    Location(int lambda_i, int lambda_m, int phi_i, int phi_m){
        if (abs(lambda_i) <= 180 && abs(phi_i) <= 90 && lambda_m < 60 && phi_m < 60){
            lambda = SpecMath::gradToRad(lambda_i, lambda_m);
            phi = SpecMath::gradToRad(phi_i, phi_m);
        } else {
            throw std::invalid_argument("Incorrect argument");
        }
    }
    Location(){
        lambda = SpecMath::gradToRad(0,0);
        phi = SpecMath::gradToRad(0,0);
    }
};


class Gnomon
{
private:
    long double height_; //высота гномона
    long double S_; // угол место

    Location location_;


    //вектор тени
    vec Shadow_;

    bool isDay_;
    bool isDayLast_;
    long double maxShadowLen_;
public:

    Gnomon(const Location &loc, long double SG,  long double height, long double maxShadowLen);


    void setLoc(const Location &loc);
    void setS(const long double SG);

    inline long double getS() const { return S_;}
    inline Location getLoc() const { return location_; }
    inline vec getShadow() const { return Shadow_; }
    inline bool isDay()const {return isDay_; }
    inline void setDayLast(bool a) {isDayLast_ = a;}
    inline long double maxShadowLen()const {return maxShadowLen_; }
    bool isNightDayChanged();

    void updateShadow(const vec& EarthVec, const long double EarthR);
};

#endif // GNOMON_H
