#include "gnomon.h"
#include "math.h"
#include "const.h"
#include "specmath.h"

Gnomon::Gnomon(const Location &loc, long double SG, long double height, long double maxShadowLen){
    location_ = loc;
    height_ = height;
    setS(SG);

    Shadow_.resize(3);

    maxShadowLen_ = maxShadowLen;

    isDayLast_ = false;
}

void Gnomon::setLoc(const Location &loc){
    location_ = loc;

}

void Gnomon::setS(const long double SG){

    S_ = SG + location_.lambda;
}

void Gnomon::updateShadow(const vec& EarthVec, const long double EarthR){
    // проверить является ли вектором конечной длины
    // вектор гномона
    vec rGnmn = normalise(SpecMath::fromGeographToGrinvich(0, height_, S_, location_.phi));

    //радиус вектор Земли, считаем коллинеарным вектору луча
    vec rEarth(3);
    rEarth[0] = EarthVec[0]; rEarth[1] = EarthVec[1]; rEarth[2] = EarthVec[2];
    rEarth = normalise(rEarth);

    long double skalEarthGnmn = dot(rEarth, rGnmn);
    long double dayAngle = acosl(dot(rEarth, rGnmn));
    if ( dayAngle > M_PI_2l){
        isDay_ = true;
        // вектор части луча от конца гномона до земли
        vec rBeam = (-height_/skalEarthGnmn) * rEarth;

        Shadow_ = rGnmn + rBeam;
    } else {
        isDay_ = false;
    }


}

bool Gnomon::isNightDayChanged(){
    if(isDay_ != isDayLast_){
        isDayLast_ = isDay_;
        return true;
    } else {
        return false;
    }
}
