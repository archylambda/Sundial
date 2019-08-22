#ifndef INTERFACE_H
#define INTERFACE_H
#include "dateandtime.h"
#include "earth.h"
#include "integrator.h"

class Interface
{
private:

    vec days;
    vec nights;

    vec dWinter;
    vec nWinter;

    vec dSummer;
    vec nSummer;

    vec dWinSum;
    vec nWinSum;

    void timeAnalSim(const Location &loc, vec& rDays, vec& rNights);
    void getLocalTime(const vec &days, const vec &nights, vec &rDays,
                             vec &rNights, int diffUTC);
    void getMixedTime(const vec &days, const vec &nights, vec &rDays,
                      vec &rNights);
    void getTrulyResult(const vec& days, const vec &nights, const string& outfile);
    void getResult(const vec& days, const vec& nights ,const string& outfile);
public:
    Interface();
    void oneDayAnalysis(const Date &data, const Location &loc) const;
    void timeAnalysis(const Location &loc, const int timezone);

};

#endif // INTERFACE_H
