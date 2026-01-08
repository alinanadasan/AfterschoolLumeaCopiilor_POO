//
// Created by Alina on 03/01/2026.
//

#include "CentruAfterschool.h"
#include <iostream>

CentruAfterschool::CentruAfterschool(std::string nume) : numeCentru(std::move(nume)) {}
void CentruAfterschool::adaugaCopil(const Copil& c) { listaCopii.push_back(c); }
void CentruAfterschool::inscrieCopilLaActivitate(int indexCopil, const Activitate& a) {
    if (indexCopil >= 0 && indexCopil < (int)listaCopii.size()) {
        if (listaCopii[indexCopil].areConflictOrar(a)) {
            std::cout << "EROARE: Conflict de program!\n";
        } else {
            listaCopii[indexCopil].adaugaActivitate(a);
            std::cout << "Inscriere reusita.\n";
        }
    }
}
void CentruAfterschool::genereazaRaport(double taxaBaza) const {
    std::cout << "\n--- RAPORT FINANCIAR ---\n";
    for (const auto& c : listaCopii)
        std::cout << c << " | Taxa: " << c.calculTaxa(taxaBaza) << " RON\n";
}
int CentruAfterschool::getNrCopii() const { return (int)listaCopii.size(); }
const Copil& CentruAfterschool::getCopil(int index) const { return listaCopii[index]; }
void CentruAfterschool::stergeCopil(int index) {
    if (index >= 0 && index < (int)listaCopii.size()) {
        std::cout << ">>> Se sterge copilul: " << listaCopii[index].getNume() << "\n";
        listaCopii.erase(listaCopii.begin() + index);
        std::cout << ">>> Stergere reusita.\n";
    } else {
        std::cout << "!!! Eroare: Index invalid.\n";
    }
}