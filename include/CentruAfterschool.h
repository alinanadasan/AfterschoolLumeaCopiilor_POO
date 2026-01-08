//
// Created by Alina on 03/01/2026.
//

#ifndef OOP_CENTRUAFTERSCHOOL_H
#define OOP_CENTRUAFTERSCHOOL_H

#include <vector>
#include <string>
#include <memory>
#include "Copil.h"

class CentruAfterschool {
    std::string numeCentru;
    std::vector<Copil> listaCopii;
    static int nrActivitatiProcesate;

public:
    explicit CentruAfterschool(std::string nume);
    static int getNrTotal();

    void adaugaCopil(const Copil& c);
    void inscrieCopilLaActivitate(int indexCopil, std::unique_ptr<Activitate> a);
    void genereazaRaport(double taxaBaza) const;
    void stergeCopil(int index);

    // REDENUMIRE AICI: Trebuie să se potrivească cu apelul din main.cpp
    void verificaPromotieSport(int idx) const;

    int getNrCopii() const;
    const Copil& getCopil(int index) const;
};

#endif //OOP_CENTRUAFTERSCHOOL_H