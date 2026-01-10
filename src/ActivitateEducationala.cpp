//
// Created by Alina on 08/01/2026.
//

#include "ActivitateEducationala.h"
#include <iostream>

ActivitateEducationala::ActivitateEducationala(std::string nume, double pret, IntervalOrar interv, bool simulare)
    : Activitate(std::move(nume), pret, interv,"") {
    this->esteSimulare = simulare;
    std::cout << ">> [LOG] Activitate EDU configurata: " << this->getDenumire()
                  << " | Tip: " << (this->getEsteSimulare() ? "Simulare" : "Standard") << "\n";
}

double ActivitateEducationala::getPretCalculat() const {
    //adaugam 100 ron la pretul de baza
    return this->pretExtra + (this->getEsteSimulare() ? 100.0 : 0.0);
}

std::unique_ptr<Activitate> ActivitateEducationala::clone() const {
    return std::make_unique<ActivitateEducationala>(*this);
}

bool ActivitateEducationala::getEsteSimulare() const {
    return this->esteSimulare;
}

void ActivitateEducationala::print(std::ostream& os) const {
    Activitate::print(os);
    os << " [Tip: EDU | " << (this->getEsteSimulare() ? "SIMULARE" : "CURS") << "]";
}