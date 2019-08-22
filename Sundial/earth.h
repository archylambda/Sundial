#ifndef EARTH_H
#define EARTH_H
#include "model.h"
#include "dateandtime.h"
#include "gnomon.h"
#include <fstream>
#include <string>
#include <dateandtime.h>
#include <map>
using namespace std;

class Earth : public TModel
{
private:
    //вектор состояния Земли
    vec curX_;
    //угловая скорость вращения земли
    const long double Omega = 7.292115e-5; //рад/сек
    //радис земли
    const long double R = 6371.3; // km
    //начальная дата
    const Date startDate{1,1,2019};
    //реальная дата и время
    Date date_;
    // звёздное время на нчало моделирования
    long double InitSG_;
    //звёздное время текущее
    long double SG_;
    //модель солнечных часов
    Gnomon* gnomon_;
    //вывод в файл
    fstream outfile_;

    // режим работы модели
    // 1 - "прыжок"
    int workMode_;

    //моделирование вращения земли
    void earthRotate(long double t);

    vec dayStart_;
    vec nightStart_;
public:

    Earth(const Location &loc, const string &outFileName);

    virtual void getRight( const vec& X, long  double t, vec& Y );

    virtual void addResult(const vec& X, long double t );

    virtual void prepareResult();

    virtual void ActionAfterStep(const vec& X, long double t);

    void jumpModeOn(const Date& reqDate);
    void simModeOn(const Date& reqDate, long double simDuration, const vec &initX);
    void timeAnalysisModeOn();

    inline vec getLastX(){ return curX_;}
    inline vec getDayStart(){ return dayStart_;}
    inline vec getNightStart(){ return nightStart_;}


    ~Earth();
};

#endif // EARTH_H
