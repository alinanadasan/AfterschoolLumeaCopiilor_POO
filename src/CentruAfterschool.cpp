//
// Created by Alina on 03/01/2026.
//
#include "CentruAfterschool.h"
#include "ActivitateSportiva.h"
#include "ExceptiiAfterschool.h"
#include <iostream>

int CentruAfterschool::nrActivitatiProcesate = 0;

CentruAfterschool::CentruAfterschool(std::string nume) : numeCentru(std::move(nume)) {}

int CentruAfterschool::getNrTotal() { return nrActivitatiProcesate; }

void CentruAfterschool::adaugaCopil(const Copil& c) { listaCopii.push_back(c); }

void CentruAfterschool::inscrieCopilLaActivitate(int indexCopil, std::unique_ptr<Activitate> a) {
    if (indexCopil < 0 || indexCopil >= (int)listaCopii.size()) throw EroareIndex();
    if (listaCopii[indexCopil].areConflictOrar(*a)) throw EroareConflictOrar(a->getDenumire());

    listaCopii[indexCopil].adaugaActivitate(std::move(a));
    nrActivitatiProcesate++;
}

void CentruAfterschool::stergeCopil(int index) {
    if (index < 0 || index >= (int)listaCopii.size()) throw EroareIndex();
    listaCopii.erase(listaCopii.begin() + index);
}

// REDENUMIRE ȘI AICI:
void CentruAfterschool::verificaPromotieSport(int idx) const {
    if (idx < 0 || idx >= (int)listaCopii.size()) return;

    for (const auto& a : listaCopii[idx].getActivitati()) {
        auto const* sport = dynamic_cast<ActivitateSportiva*>(a.get());
        if (sport && sport->areEchipament()) {
            std::cout << "[DYNAMIC CAST] Voucher acordat pentru " << sport->getDenumire() << "\n";
        }
    }
}

void CentruAfterschool::genereazaRaport(double taxaBaza) const {
    std::cout << "\n--- RAPORT FINANCIAR ---\n";
    for (const auto& c : listaCopii) {
        std::cout << c << " | Taxa: " << c.calculTaxa(taxaBaza) << " RON\n";
    }
}

int CentruAfterschool::getNrCopii() const { return (int)listaCopii.size(); }
const Copil& CentruAfterschool::getCopil(int index) const { return listaCopii[index]; }