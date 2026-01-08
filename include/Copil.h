//
// Created by Alina on 03/01/2026.
//

#ifndef OOP_COPIL_H
#define OOP_COPIL_H

#include <string>
#include <vector>
#include "Activitate.h"

class Copil {
    std::string nume;
    int varsta;
    std::vector<Activitate> activitati;
    double* istoricPlati;
    int nrLuni;
public:
    Copil(std::string nume, int varsta);
    Copil(const Copil& altul);
    Copil& operator=(const Copil& altul);
    ~Copil();

    void adaugaActivitate(const Activitate& a);
    bool areConflictOrar(const Activitate& noua) const;
    double calculTaxa(double taxaBaza) const;
    std::string getNume() const;
    friend std::ostream& operator<<(std::ostream& os, const Copil& c);
};

#endif //OOP_COPIL_H