//
// Created by Alina on 08/01/2026.
//
#include "ActivitateArtistica.h"

// constructor
ActivitateArtistica::ActivitateArtistica(std::string nume, double pret, IntervalOrar intrv, int nivel)
    : Activitate(std::move(nume), pret, intrv, "") {

    this->nivelCreativitate = nivel;
    std::cout << ">> [LOG] Activitate artistica creata: " << this->getDenumire() << "\n";
}

double ActivitateArtistica::getPretCalculat() const {
    // calcul diferit pret in functie de nivelCreativitate
    return this->pretExtra + (static_cast<double>(this->nivelCreativitate) * 10.5);
}

std::unique_ptr<Activitate> ActivitateArtistica::clone() const {

    return std::make_unique<ActivitateArtistica>(*this);
}

void ActivitateArtistica::print(std::ostream& os) const {
    Activitate::print(os);
    os << " [Tip: ARTA | Nivel Creativitate: " << this->nivelCreativitate << "/10]";
}