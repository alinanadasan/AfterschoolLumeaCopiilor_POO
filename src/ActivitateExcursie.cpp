//
// Created by Alina on 08/01/2026.
//
#include "ActivitateExcursie.h"

ActivitateExcursie::ActivitateExcursie(std::string nume, double pret, IntervalOrar interv, int distanta)
    : Activitate(std::move(nume), pret, interv, "") {

    this->distantaKm = distanta;
    std::cout << ">> [LOG] Activitate Excursie creata: " << this->getDenumire()
              << " | Distanta: " << this->getDistantaKm() << " km\n";
}

double ActivitateExcursie::getPretCalculat() const {
    // Pretul biletului (pretExtra) + costul transportului (2.5 RON/km)
    return pretExtra + getDistantaKm() * 2.5;
}

std::unique_ptr<Activitate> ActivitateExcursie::clone() const {
    return std::make_unique<ActivitateExcursie>(*this);
}

void ActivitateExcursie::print(std::ostream& os) const {
    Activitate::print(os);
    os << " [Tip: EXCURSIE | Distanta: " << getDistantaKm() << " km]";
}

int ActivitateExcursie::getDistantaKm() const {
    return this->distantaKm;
}