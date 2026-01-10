//
// Created by Alina on 08/01/2026.
//
#include "ActivitateSportiva.h"

ActivitateSportiva::ActivitateSportiva(std::string nume, const double pret, IntervalOrar interv, bool echip)
: Activitate(std::move(nume), pret, interv,"") {

    this->necesitaEchipament = echip;
    std::cout << ">> [LOG] Activitate sportiva creata: " << this->getDenumire() << "\n";
}

double ActivitateSportiva::getPretCalculat() const {
    //adaugam 50 ron la pretul de baza
    return this->pretExtra + (this->necesitaEchipament ? 50.0 : 0.0);
}

std::unique_ptr<Activitate> ActivitateSportiva::clone() const {

    return std::make_unique<ActivitateSportiva>(*this);
}

bool ActivitateSportiva::areEchipament() const {

    return this->necesitaEchipament;
}

void ActivitateSportiva::print(std::ostream& os) const {

    Activitate::print(os);
    os << " [Tip: SPORT | Echipament necesar: " << (this->necesitaEchipament ? "DA" : "NU") << "]";
}