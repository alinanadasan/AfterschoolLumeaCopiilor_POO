//
// Created by Alina on 08/01/2026.
//
#include "ActivitateExcursie.h"

ActivitateExcursie::ActivitateExcursie(std::string n, double p, IntervalOrar i, int distanta)
    : Activitate(std::move(n), p, i), distantaKm(distanta) {}

double ActivitateExcursie::getPretCalculat() const {
    // Pretul biletului (pretExtra) + costul transportului (2.5 RON per km)
    return pretExtra + (distantaKm * 2.5);
}

std::unique_ptr<Activitate> ActivitateExcursie::clone() const {
    return std::make_unique<ActivitateExcursie>(*this);
}

void ActivitateExcursie::print(std::ostream& os) const {
    Activitate::print(os);
    os << " [Tip: EXCURSIE | Distanta: " << distantaKm << " km]";
}