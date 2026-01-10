//
// Created by Alina on 03/01/2026.
//

#ifndef OOP_CENTRUAFTERSCHOOL_H
#define OOP_CENTRUAFTERSCHOOL_H

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "Copil.h"
#include "RegistruInstructori.h"
#include "Activitate.h"

class CentruAfterschool {

    std::string numeCentru;
    std::vector<Copil> listaCopii;
    double taxaBaza;
    double pretMasaZilnic;
    static int nrActivitatiCentru;

    // SINGLETON: Constructor
    explicit CentruAfterschool(std::string nume, const double taxa, const double pret);
    // Instantieri Template
    RegistruInstructori<std::string> echipaDidactica;
    RegistruInstructori<double> grilaSalarizare;
    // Vectorul pentru activitati
    std::vector<std::unique_ptr<Activitate>> listaActivitati;

public:

    CentruAfterschool(const CentruAfterschool&) = delete;
    CentruAfterschool& operator=(const CentruAfterschool&) = delete;

    void raportPopularitateActivitati() const;
    void raportActivitatiLibere() const;
    void exportRaportFisier(const std::string &numeFisier) const;

    static CentruAfterschool& getInstance();
    const std::string &getNumeCentru() const;
    void afiseazaDetalii() const;

    void setNumeCentru(const std::string &nume);
    void setTaxaBaza(double taxa);
    void setPretMasaZilnic(double pret);

    //Metode pentru gestiune copii
    void adaugaCopil(const Copil &c);
    void stergeCopil(int idDeSters);
    void modificaNumeCopil(int id, const std::string &numeNou);
    void modificaPrenumeCopil(int id, const std::string &prenumeNou);
    void modificaCNPCopil(int id, const std::string &cnpNou);
    void modificaClasaCopil(int id, int clasaNoua);
    void incarcaCopiiDinFisier(const std::string &numeFisier);

    void adaugaActivitateInLista(std::unique_ptr<Activitate> a);
    void afiseazaListaActivitati() const;
    void stergeActivitateDinLista(int index);
    void incarcaActivitatiDinFisier(const std::string &numeFisier);

    Activitate *getActivitateDinLista(int index) const;

    void adaugaInstructor(const std::string &nume, const std::string &specializare, double salariu);
    void incarcaInstructoriDinFisier(const std::string &numeFisier);
    void afiseazaSituatieEchipa() const;
    void modificaSalariuInGrila(int index, double sumaNoua);
    void stergeInstructorDinEchipa(int index);
    RegistruInstructori<std::string> &getEchipaDidactica();
    RegistruInstructori<double> &getGrilaSalarizare();

    void inscrieCopilLaActivitate(int idCopil, std::unique_ptr<Activitate> a);
    void afiseazaProgramCopil(int idCopil) const;

    //Metode STATISTICI
    void genereazaRaport() const;
    void genereazaRaportCopii() const;
};

#endif //OOP_CENTRUAFTERSCHOOL_H