//
// Created by Alina on 08/01/2026.
//
#include "ActivitateSportiva.h"

ActivitateSportiva::ActivitateSportiva(std::string n, double p, IntervalOrar i, bool e)
    : Activitate(std::move(n), p, i), necesitaEchipament(e) {}

double ActivitateSportiva::getPretCalculat() const {
    return pretExtra + (necesitaEchipament ? 50.0 : 0.0);
}

std::unique_ptr<Activitate> ActivitateSportiva::clone() const {
    return std::make_unique<ActivitateSportiva>(*this);
}

void ActivitateSportiva::print(std::ostream& os) const {
    Activitate::print(os);
    os << " [Tip: SPORT | Echipament: " << (necesitaEchipament ? "DA" : "NU") << "]";
}