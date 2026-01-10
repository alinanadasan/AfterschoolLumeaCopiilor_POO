//
// Created by Alina on 09/01/2026.
//

#ifndef OOP_INTERFATAUTILIZATOR_H
#define OOP_INTERFATAUTILIZATOR_H

#include "CentruAfterschool.h"
#include <string>
#include <vector>

class InterfataUtilizator {
    CentruAfterschool& centru;
    std::vector<std::string> istoricOptiuni;

    // Metode pentru log si istoric optiuni(pt generare tastatura.txt)
    static void curataInput();
    static void logAction(const std::string& msg);

    int citesteInput();
    std::string citesteInputText();
    void salveazaIstoric() const;

    // Meniu principal si submeniuri
    void afiseazaMeniuPrincipal() const;

    void modulModificaInfoCentru();
    void modulAdminCentru();

    void modulModificaInfoCopil();
    void modulCopii();

    std::unique_ptr<Activitate> citesteSiCreeazaActivitate();
    void modulModificaActivitate();
    void modulActivitati();

    void modulAdaugaInstructor();
    void modulModificaSalariu();
    void modulStergeInstructor();
    void modulEchipa();

    void modulInscrieri();
    void modulAdmin();

    void modulRapoarte();

public:
    InterfataUtilizator();
    void pornesteAplicatia();
};

#endif //OOP_INTERFATAUTILIZATOR_H