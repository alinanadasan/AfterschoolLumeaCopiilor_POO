//
// Created by Alina on 03/01/2026.
//

#ifndef OOP_CENTRUAFTERSCHOOL_H
#define OOP_CENTRUAFTERSCHOOL_H

#include <vector>
#include <string>
#include "Copil.h"

class CentruAfterschool {
    std::string numeCentru;
    std::vector<Copil> listaCopii;
public:
    explicit CentruAfterschool(std::string nume);
    void adaugaCopil(const Copil& c);
    void inscrieCopilLaActivitate(int indexCopil, const Activitate& a);
    void genereazaRaport(double taxaBaza) const;
    int getNrCopii() const;
    const Copil& getCopil(int index) const;
    void stergeCopil(int index);
};

#endif //OOP_CENTRUAFTERSCHOOL_H