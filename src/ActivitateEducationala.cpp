//
// Created by Alina on 08/01/2026.
//
#include "ActivitateEducationala.h"

ActivitateEducationala::ActivitateEducationala(std::string n, double p, IntervalOrar i, int m)
    : Activitate(std::move(n), p, i), nrMaterialeCurs(m) {}

double ActivitateEducationala::getPretCalculat() const {
    // Educația oferă o reducere de 5% la prețul de bază, dar adaugă 15 RON per manual/curs
    return (pretExtra * 0.95) + (nrMaterialeCurs * 15.0);
}

std::unique_ptr<Activitate> ActivitateEducationala::clone() const {
    return std::make_unique<ActivitateEducationala>(*this);
}

void ActivitateEducationala::print(std::ostream& os) const {
    Activitate::print(os);
    os << " [Tip: EDU | Materiale: " << nrMaterialeCurs << "]";
}