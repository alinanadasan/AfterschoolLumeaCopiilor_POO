//
// Created by Alina on 03/01/2026.
//

#ifndef OOP_COPIL_H
#define OOP_COPIL_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "Activitate.h"

class Copil {
    std::string nume;
    int varsta;
    std::vector<std::unique_ptr<Activitate>> activitati;

    // FIX MSAN: Initializare implicita pentru a evita garbage value la constructie esuata
    double* istoricPlati = nullptr;
    int nrLuni = 0;

public:
    Copil(std::string nume, int varsta);
    Copil(const Copil& altul);
    Copil& operator=(Copil altul); // Copy-and-swap
    ~Copil();
    friend void swap(Copil& primu, Copil& aldoilea) noexcept;

    void adaugaActivitate(std::unique_ptr<Activitate> a);
    bool areConflictOrar(const Activitate& noua) const;
    double calculTaxa(double taxaBaza) const;
    const std::string& getNume() const { return nume; }
    const std::vector<std::unique_ptr<Activitate>>& getActivitati() const { return activitati; }
    friend std::ostream& operator<<(std::ostream& os, const Copil& c);
};

#endif //OOP_COPIL_H