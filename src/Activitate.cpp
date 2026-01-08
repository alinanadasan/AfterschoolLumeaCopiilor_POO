//
// Created by Alina on 03/01/2026.
//

#include "Activitate.h"
Activitate::Activitate(std::string nume, double pret, IntervalOrar inter)
    : denumire(std::move(nume)), pretExtra(pret), interval(inter) {}

void Activitate::afiseazaDetalii(std::ostream& os) const { print(os); }

void Activitate::print(std::ostream& os) const {
    os << "Activitate: " << denumire << " | Pret: " << getPretCalculat() << " RON | " << interval;
}

std::ostream& operator<<(std::ostream& os, const Activitate& a) {
    a.afiseazaDetalii(os);
    return os;
}
const std::string& Activitate::getDenumire() const { return denumire; }
IntervalOrar Activitate::getInterval() const { return interval; }
