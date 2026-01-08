//
// Created by Alina on 03/01/2026.
//

#include "Copil.h"
#include <iostream>

Copil::Copil(std::string nume, int varsta) : nume(nume), varsta(varsta), nrLuni(1) {
    istoricPlati = new double[1]{0.0};
}
Copil::Copil(const Copil& altul) : nume(altul.nume), varsta(altul.varsta),
                                   activitati(altul.activitati), nrLuni(altul.nrLuni) {
    istoricPlati = new double[nrLuni];
    for(int i=0; i<nrLuni; ++i) istoricPlati[i] = altul.istoricPlati[i];
}
Copil& Copil::operator=(const Copil& altul) {
    if(this != &altul) {
        delete[] istoricPlati;
        nume = altul.nume; varsta = altul.varsta; activitati = altul.activitati; nrLuni = altul.nrLuni;
        istoricPlati = new double[nrLuni];
        for(int i=0; i<nrLuni; ++i) istoricPlati[i] = altul.istoricPlati[i];
    }
    return *this;
}
Copil::~Copil() { delete[] istoricPlati; }
void Copil::adaugaActivitate(const Activitate& a) { activitati.push_back(a); }
bool Copil::areConflictOrar(const Activitate& noua) const {
    for(const auto& act : activitati)
        if(act.getInterval().getStart() < noua.getInterval().getFinal() &&
           act.getInterval().getFinal() > noua.getInterval().getStart()) return true;
    return false;
}
double Copil::calculTaxa(double taxaBaza) const {
    double total = taxaBaza;
    for(const auto& act : activitati) total += act.getPret();
    return (activitati.size() >= 2) ? total * 0.9 : total;
}
const std::string& Copil::getNume() const {
    return nume;
}
std::ostream& operator<<(std::ostream& os, const Copil& c) {
    os << "Copil: " << c.nume << " (" << c.varsta << " ani)";
    return os;
}