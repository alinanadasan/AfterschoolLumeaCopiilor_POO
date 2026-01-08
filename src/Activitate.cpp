//
// Created by Alina on 03/01/2026.
//

#include "Activitate.h"
Activitate::Activitate(std::string nume, double pret, IntervalOrar inter)
    : denumire(nume), pretExtra(pret), interval(inter) {}
std::string Activitate::getDenumire() const { return denumire; }
double Activitate::getPret() const { return pretExtra; }
IntervalOrar Activitate::getInterval() const { return interval; }
std::ostream& operator<<(std::ostream& os, const Activitate& a) {
    os << "Activitate: " << a.denumire << " | Pret: " << a.pretExtra << " RON | " << a.interval;
    return os;
}