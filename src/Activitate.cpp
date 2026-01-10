//
// Created by Alina on 03/01/2026.
//

#include "Activitate.h"

//constructor de initializare
Activitate::Activitate(std::string nume, const double pret, IntervalOrar intrv, std::string instructor) {

    this->denumire = std::move(nume);
    this->pretExtra = pret;
    this->interval = intrv;
    this->numeInstructor = std::move(instructor);
}

//operator afisare
std::ostream& operator<<(std::ostream& os, const Activitate& a) {

    a.afiseazaDetalii(os);
    return os;
}

void Activitate::print(std::ostream& os) const {

    os << "Activitate: " << this->denumire
       << " | Pret: " << this->getPretCalculat() << " RON"
       << " | Interval: " << this->interval;
}
//metode de logica
double Activitate::getPretCalculat() const {
    return this->pretExtra;
}

void Activitate::afiseazaDetalii(std::ostream& os) const {
    os << "Activitate: " << denumire << " | Pret: " << pretExtra << " RON | " << interval;
    if (areInstructor()) {
        os << " | Instructor: " << numeInstructor;
    } else {
        os << " | [LIPSA]";
    }
}
const std::string& Activitate::getDenumire() const {

    return this->denumire;
}
IntervalOrar Activitate::getInterval() const {
    return this->interval;
}
std::string Activitate::getInstructor() const {
    return this->numeInstructor;
}

void Activitate::setInterval(const IntervalOrar& nou) {
    this->interval = nou;
}
void Activitate::setInstructor(const std::string& nume) {
    this->numeInstructor = nume;
}
bool Activitate::areInstructor() const {
    return !this->numeInstructor.empty();
}

void Activitate::setDenumire(const std::string& nume) {
    this->denumire = nume;
}

void Activitate::setPret(double pret) {
    this->pretExtra = pret;
}