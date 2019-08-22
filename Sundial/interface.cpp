#include "interface.h"
#include "const.h"

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

Interface::Interface()
{
    dWinter.resize(365);
    nWinter.resize(365);

    dSummer.resize(365);
    nSummer.resize(365);

    dWinSum.resize(365);
    nWinSum.resize(365);
}

void Interface::timeAnalSim(const Location &loc, vec &rDays, vec &rNights){
    TIntegrator* Integrator = new TDormandPrinceIntegrator();
    Integrator->setPrecision(1e-10);

    string outpath = "";
    Earth* earth = new Earth(loc, outpath);

    earth->timeAnalysisModeOn();

    Integrator->Run(earth);

    rDays = earth->getDayStart();
    rNights = earth->getNightStart();

    delete earth;
    delete Integrator;
}

void Interface::getLocalTime(const vec &days, const vec &nights, vec &rDays,
                        vec &rNights, int diffUTC){
    for (int i = 0; i != days.n_elem; i++){
        rDays[i] = days[i] + diffUTC*SEC_IN_HOUR;
        rNights[i] = nights[i] + diffUTC*SEC_IN_HOUR;
    }

}

void Interface::getMixedTime(const vec &days, const vec &nights, vec &rDays, vec &rNights){

    for (int i = 0; i != SUMMER_CHANGED_DAY; i++){
        rDays[i] = days[i];
        rNights[i] = nights[i];
    }

    if(days[SUMMER_CHANGED_DAY] < 2*SEC_IN_HOUR){
        rDays[SUMMER_CHANGED_DAY] = days[SUMMER_CHANGED_DAY];
    } else {
        rDays[SUMMER_CHANGED_DAY] = days[SUMMER_CHANGED_DAY] + SEC_IN_HOUR;
    }

    rNights[SUMMER_CHANGED_DAY] = nights[SUMMER_CHANGED_DAY];

    for(int i = SUMMER_CHANGED_DAY + 1; i != WINTER_CHANGED_DAY; i++){
        rDays[i] = days[i] + SEC_IN_HOUR;
        rNights[i] = nights[i] + SEC_IN_HOUR;
    }

    if(days[WINTER_CHANGED_DAY]+SEC_IN_HOUR < 3*SEC_IN_HOUR){
        rDays[WINTER_CHANGED_DAY] = days[WINTER_CHANGED_DAY] + SEC_IN_HOUR;
    } else {
        rDays[WINTER_CHANGED_DAY] = days[WINTER_CHANGED_DAY];
    }

    rNights[WINTER_CHANGED_DAY] = nights[WINTER_CHANGED_DAY];

    for(int i = WINTER_CHANGED_DAY + 1; i < days.n_elem; i++){
        rDays[i] = days[i];
        rNights[i] = nights[i];
    }
}

void Interface::getTrulyResult(const vec &days, const vec &nights, const string &outfile){
    fstream file;

    file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try{
        file.open(outfile, ios::out);
    } catch (fstream::failure e){
        cerr << "Exception opening file\n";
    }

    vec trulySunDur(days.n_elem);

    for(int i = 0; i != days.size(); i++){
        trulySunDur[i] = (nights[i] - days[i]) / SEC_IN_HOUR;
    }

    for(int i = 0; i != trulySunDur.size(); i++){
        file << i + 1 << ' ' << trulySunDur[i] << endl;
    }

    file.close();
}

void Interface::getResult(const vec &days, const vec &nights, const string &outfile){
    fstream file;

    file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try{
        file.open(outfile, ios::out);
    } catch (fstream::failure e){
        cerr << "Exception opening file\n";
    }

    vec sunDur(days.size());

    for (int i = 0; i != days.n_elem; i++){
        sunDur[i] = (MIN(18 * SEC_IN_HOUR, nights[i]) - MAX(6 * SEC_IN_HOUR, days[i])) / SEC_IN_HOUR;
    }

    for(int i = 0; i != sunDur.n_elem; i++){
        file << i + 1 << ' ' << sunDur[i] << endl;
    }

    file.close();

}

void Interface::oneDayAnalysis(const Date &data, const Location &loc) const{

    TIntegrator* Integrator = new TDormandPrinceIntegrator();
    Integrator->setPrecision(1e-10);

    string outpath = "oneDayAnalysis.txt";
    Earth* earth = new Earth(loc, outpath);

    earth->jumpModeOn(data);
    Integrator->Run(earth);

    earth->simModeOn(data, 24*3600, earth->getLastX());

    Integrator->Run(earth);

    delete earth;
    delete Integrator;
}

void Interface::timeAnalysis(const Location &loc, const int timezone) {

    timeAnalSim(loc, days, nights);

    //зимнее время
    getLocalTime(days, nights, dWinter, nWinter, timezone);
    //летнее время
    getLocalTime(days, nights, dSummer, nSummer, timezone+1);
    //с переходом
    getMixedTime(dWinter, nWinter, dWinSum, nWinSum);

    string trulyF = "/home/artem/MAII/Programming/OPRS/5laba/trulyTimeAnalysis";
    getTrulyResult(dWinter, nWinter, trulyF);
    string winF = "/home/artem/MAII/Programming/OPRS/5laba/WinTimeAnalysis";
    getResult(dWinter, nWinter, winF);
    string sumF = "/home/artem/MAII/Programming/OPRS/5laba/SumTimeAnalysis";
    getResult(dSummer, nSummer, sumF);
    string mixF = "/home/artem/MAII/Programming/OPRS/5laba/MixTimeAnalysis";
    getResult(dWinSum, nWinSum, mixF);

}


