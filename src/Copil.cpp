//
// Created by Alina on 03/01/2026.
//

#include "Copil.h"
#include "ExceptiiAfterschool.h"
#include <algorithm>

Copil::Copil(std::string n, int v) : nume(std::move(n)), varsta(v), nrLuni(1) {
    if (v < 5 || v > 18) throw EroareVarsta();
    istoricPlati = new double[1]{0.0};
}

Copil::Copil(const Copil& altul) : nume(altul.nume), varsta(altul.varsta), nrLuni(altul.nrLuni) {
    istoricPlati = new double[nrLuni];
    for(int i=0; i<nrLuni; ++i) istoricPlati[i] = altul.istoricPlati[i];
    for(const auto& a : altul.activitati) activitati.push_back(a->clone());
}

void swap(Copil& primu, Copil& aldoilea) noexcept {
    using std::swap;
    swap(primu.nume, aldoilea.nume);
    swap(primu.varsta, aldoilea.varsta);
    swap(primu.istoricPlati, aldoilea.istoricPlati);
    swap(primu.nrLuni, aldoilea.nrLuni);
    swap(primu.activitati, aldoilea.activitati);
}

Copil& Copil::operator=(Copil altul) {
    swap(*this, altul);
    return *this;
}

Copil::~Copil() { delete[] istoricPlati; }

void Copil::adaugaActivitate(std::unique_ptr<Activitate> a) { activitati.push_back(std::move(a)); }

bool Copil::areConflictOrar(const Activitate& noua) const {
    for(const auto& a : activitati)
        if(a->getInterval().getStart() < noua.getInterval().getFinal() && a->getInterval().getFinal() > noua.getInterval().getStart()) return true;
    return false;
}

double Copil::calculTaxa(double b) const {
    double t = b;
    for(const auto& a : activitati) t += a->getPretCalculat();
    return (activitati.size() >= 2) ? t * 0.9 : t;
}

std::ostream& operator<<(std::ostream& os, const Copil& c) {
    os << "Copil: " << c.nume << " (" << c.varsta << " ani)";
    return os;
}