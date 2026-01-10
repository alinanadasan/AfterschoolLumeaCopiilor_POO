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
#include <chrono>

class Copil {

    static int nrCopii;
    //info copil
    int id;
    std::string nume;
    std::string prenume;
    std::string cnp;
    int clasaScoala;
    std::chrono::year_month_day dataNasterii{};
    int varsta;
    int zilePrezente;

    std::vector<std::unique_ptr<Activitate>> activitati;
    double* istoricPlati = nullptr;
    int nrLuni = 0;

    //helpers
    void extrageDataNastereDinCNP();
    static std::chrono::year_month_day stringToChrono(const std::string& dataNasteriiStr) ;
    void calculeazaVarsta();

public:
    //constructor de initializare: e nevoie de nume, prenume, cnp si clasaScoala
    Copil(const std::string &nume, const std::string &prenume, const std::string &cnp, int clasaScoala);
    //Constructor supraincarcat, avem nevoie doar de nume, prenume, clasa, varsta, restul default
    Copil(const std::string &nume, const std::string &prenume, int clasaScoala, int varsta);
    //constructor de copiere
    Copil(const Copil& alt_copil);

    //destructor
    ~Copil();

    //Operatori
    //operator de asignare
    Copil &operator=(const Copil &alt_copil);

    //operator de citire/afisare
    friend std::ostream& operator<<(std::ostream& os, const Copil& c);
    friend std::istream& operator>>(std::istream& is, Copil& c);
    Copil& operator+=(double plata);
    friend bool operator<(const Copil& c1, const Copil& c2);

    //metode de logica
    [[nodiscard]] bool areConflictOrar(const Activitate& activitate_noua) const;
    void adaugaActivitate(std::unique_ptr<Activitate> a);
    [[nodiscard]] double calculTaxa(double taxaAdmin, double pretMasaZi) const;

    // Getters
    int getId() const;
    const std::string& getNume() const;
    const std::string& getPrenume() const;
    int getClasa() const;
    int getVarsta() const;
    std::string getDataNasterii() const;
    const std::string &getCNP() const;

    int getZilePrezente() const;
    const std::vector<std::unique_ptr<Activitate>>& getActivitati() const;

    void setNume(const std::string &n);
    void setPrenume(const std::string &p);
    void setCNP(const std::string &cnpNou);
    void setClasa(int c);


};

#endif //OOP_COPIL_H