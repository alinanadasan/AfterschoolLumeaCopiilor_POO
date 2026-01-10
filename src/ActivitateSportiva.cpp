//
// Created by Alina on 08/01/2026.
//
#include "ActivitateSportiva.h"

ActivitateSportiva::ActivitateSportiva(std::string nume, double pret, IntervalOrar interv, bool echip)
    : Activitate(std::move(nume), pret, interv, ""), necesitaEchipament(echip) {

    std::cout << ">> [LOG] Activitate Sportiva creata: " << this->getDenumire()
              << " | Necesita echipament: " << (this->areEchipament() ? "DA" : "NU") << "\n";
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

    os << " | Echipament special: " << (areEchipament() ? "Inclus/Necesar" : "Nu este cazul");
}