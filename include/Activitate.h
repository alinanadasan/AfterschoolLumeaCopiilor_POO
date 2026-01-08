//
// Created by Alina on 03/01/2026.
//

#ifndef OOP_ACTIVITATE_H
#define OOP_ACTIVITATE_H

#include <string>
#include "IntervalOrar.h"

class Activitate {
    std::string denumire;
    double pretExtra;
    IntervalOrar interval;
public:
    Activitate(std::string nume, double pret, IntervalOrar inter);
    std::string getDenumire() const;
    double getPret() const;
    IntervalOrar getInterval() const;
    friend std::ostream& operator<<(std::ostream& os, const Activitate& a);
};
#endif //OOP_ACTIVITATE_H