//
// Created by Alina on 03/01/2026.
//
#include "CentruAfterschool.h"
#include "ActivitateSportiva.h"
#include "ExceptiiAfterschool.h"
#include "ActivitateFactory.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <utility>
#include <iomanip> // Necesar pentru std::setw, std::left
#include <sstream>

int CentruAfterschool::nrActivitatiCentru = 0;

// ---------------------------------------------------------
// METODE ADMIN CENTRU AFTERSCHOOL
// ---------------------------------------------------------

// Constructor SINGLETON, initializeaza si registrele template pentru echipa si grila salarii
CentruAfterschool::CentruAfterschool(std::string nume, const double taxa, const double pret){

    this->numeCentru = std::move(nume);
    this->echipaDidactica = RegistruInstructori<std::string>("Echipa Didactica (Nume)");
    this->grilaSalarizare = RegistruInstructori<double>("Grila Salarizare (RON)");
    this->taxaBaza = taxa;
    this->pretMasaZilnic = pret;
    std::cout << "[INFO CentruAfterschool]: Centrul '" << numeCentru << "' a fost configurat.\n";

}
CentruAfterschool& CentruAfterschool::getInstance() {
    static CentruAfterschool instance("Lumea Copiilor", 400.0, 30.0);
    return instance;
}
const std::string& CentruAfterschool::getNumeCentru() const {
    return this->numeCentru;
}

// ---------------------------------------------------------
// METODE ADMIN CENTRU AFTERSCHOOL
// ---------------------------------------------------------
void CentruAfterschool::afiseazaDetalii() const {
    std::cout << "\n==============================================";
    std::cout << "\n       DETALII CENTRU: " << this->numeCentru;
    std::cout << "\n==============================================";

    // Formatare preturi
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n Taxa Baza (lunara): " << this->taxaBaza << " RON";
    std::cout << "\n Pret Masa (zilnic): " << this->pretMasaZilnic << " RON";
    // Resetare formatare
    std::cout.unsetf(std::ios_base::floatfield);

    std::cout << "\n----------------------------------------------";

    // Statistici
    std::cout << "\n Nr. Copii Inscrisi: " << this->listaCopii.size();
    std::cout << "\n Nr. Activitati:     " << this->listaActivitati.size();
    std::cout << "\n Nr. Instructori:    " << this->echipaDidactica.getInregistrari().size();

    std::cout << "\n==============================================\n";
}
void CentruAfterschool::setNumeCentru(const std::string& nume) {
    this->numeCentru = nume;
    std::cout << "[INFO] Numele centrului a fost actualizat: " << this->numeCentru << "\n";
}
void CentruAfterschool::setTaxaBaza(double taxa) {
    if(taxa < 0) throw EroareAfterschool("Taxa nu poate fi negativa!");
    this->taxaBaza = taxa;
    std::cout << "[INFO] Taxa de baza a fost actualizata: "
    << std::fixed << std::setprecision(2) << this->taxaBaza << " RON\n";
    std::cout.unsetf(std::ios_base::floatfield);
}
void CentruAfterschool::setPretMasaZilnic(double pret) {
    if(pret < 0) throw EroareAfterschool("Pretul nu poate fi negativ!");
    this->pretMasaZilnic = pret;
    std::cout << "[INFO] Pretul mesei a fost actualizat: "
    << std::fixed << std::setprecision(2) << this->pretMasaZilnic << " RON\n";
    std::cout.unsetf(std::ios_base::floatfield);
}


// ---------------------------------------------------------
// METODE ADMIN COPII
// ---------------------------------------------------------

void CentruAfterschool::adaugaCopil(const Copil& c) {
    this->listaCopii.push_back(c);
    std::sort(this->listaCopii.begin(), this->listaCopii.end());
    std::cout << "[INFO CentruAfterschool::adaugaCopil]: Copilul " << c.getNume() <<" "<< c.getPrenume() << " a fost adaugat.\n";
}
void CentruAfterschool::stergeCopil(const int idDeSters) {

    bool gasit = false;

    for ( auto it = this->listaCopii.begin(); it != this->listaCopii.end(); ++it ) {
        if ( it->getId() == idDeSters ) {
            std::cout << "[INFO CentruAfterschool::stergeCopil]: Elevul " << it->getNume() << " a fost sters.\n";
            this->listaCopii.erase(it);
            gasit = true;
            break;
        }
    }

    if (!gasit) {
        throw EroareID();
    }
}
void CentruAfterschool::modificaNumeCopil(const int id, const std::string& numeNou) {
    bool gasit = false;
    for (auto& c : this->listaCopii) {
        if (c.getId() == id) {
            c.setNume(numeNou);
            gasit = true;
            std::cout << "[INFO CentruAfterschool::modificaNumeCopil]: Numele copilului cu ID = " << id
            << " a fost modificat in: " << numeNou << "\n";
            break;
        }
    }
    if (!gasit) throw EroareID();

    // aplicam sortarea
    std::sort(this->listaCopii.begin(), this->listaCopii.end());
}
void CentruAfterschool::modificaPrenumeCopil(const int id, const std::string& prenumeNou) {
    bool gasit = false;
    for (auto& c : this->listaCopii) {
        if (c.getId() == id) {
            c.setPrenume(prenumeNou);
            gasit = true;
            std::cout << "[INFO CentruAfterschool::modificaPrenumeCopil]: Prenumele copilului cu ID = " << id
            << " a fost modificat in: " << prenumeNou << "\n";
            break;
        }
    }
    if (!gasit) throw EroareID();

    // aplicam sortarea
    std::sort(this->listaCopii.begin(), this->listaCopii.end());
}
void CentruAfterschool::modificaCNPCopil(const int id, const std::string& cnpNou) {
    bool gasit = false;

    for (auto& c : this->listaCopii) {
        if (c.getId() == id) {
            c.setCNP(cnpNou);

            std::cout << "[INFO CentruAfterschool::modificaCNPCopil]: CNP-ul copilului (ID: " << id
                      << ") a fost actualizat.\n"
                      << "       >> Noua varsta calculata: " << c.getVarsta() << " ani.\n";

            gasit = true;
            break;
        }
    }

    if (!gasit) {
        throw EroareID();
    }
    std::sort(this->listaCopii.begin(), this->listaCopii.end());
}
void CentruAfterschool::modificaClasaCopil(const int id, const int clasaNoua) {
    bool gasit = false;
    for (auto& c : this->listaCopii) {
        if (c.getId() == id) {
            c.setClasa(clasaNoua);
            gasit = true;
            std::cout << "[INFO CentruAfterschool::modificaClasaCopil]: Clasa in care se afla copilul cu ID = " << id
            << " a fost modificata cu " << clasaNoua << ".\n";
            break;
        }
    }
    if (!gasit) throw EroareID();

}
void CentruAfterschool::incarcaCopiiDinFisier(const std::string& numeFisier) {
    std::ifstream f(numeFisier);
    if (!f.is_open()) {
        std::cerr << "[EROARE CentruAfterschool::incarcaCopiiDinFisier]: Fisierul " << numeFisier << " nu a putut fi deschis!\n";
        return;
    }

    std::string linie;
    int indexLinie = 0;
    int copiiAdaugati = 0;

    while (std::getline(f, linie)) {
        indexLinie++;
        if (linie.empty()) continue;

        std::stringstream ss(linie);
        std::string nume, prenume, dateIdentificare, clasa_str;

        if (std::getline(ss, nume, '|') &&
            std::getline(ss, prenume, '|') &&
            std::getline(ss, dateIdentificare, '|') &&
            std::getline(ss, clasa_str, '|')) {

            try {
                int clasa = std::stoi(clasa_str);
                if (dateIdentificare.length() == 13) {
                    // Constructor CNP
                    Copil c(nume, prenume, dateIdentificare, clasa);
                    this->listaCopii.push_back(c);
                    copiiAdaugati++;

                    std::cout << "[INFO Import]: Linia " << indexLinie << "- Inserat " << nume << " " << prenume
                              << " | CNP: " << dateIdentificare
                              << " | Clasa: " << clasa
                              << " | Varsta: " << c.getVarsta() << " ani.\n";
                }
                else if (dateIdentificare.length() <= 3) {
                    // Constructor Varsta
                    int varstaFisier = std::stoi(dateIdentificare);
                    Copil c(nume, prenume, clasa, varstaFisier);
                    this->listaCopii.push_back(c);
                    copiiAdaugati++;

                    std::cout << "[INFO Import]: Linia " << indexLinie << "- Inserat " << nume << " " << prenume
                              << " (LIPSA CNP) | Clasa: " << clasa
                              << " | Varsta: " << varstaFisier << " ani.\n";
                }
                else {
                    throw std::runtime_error("Format invalid: Lungimea nu corespunde nici unui CNP (13), nici unei varste (1-3 cifre).");
                }
            } catch (const std::exception& e) {
                std::cout << "[EROARE Import]: Linia "  << indexLinie << " - " << nume << " " << prenume
                          << " (" << dateIdentificare << ") RESPINS.\n"
                          << "                 Motiv: " << e.what() << "\n";
            }
        }
    }
    f.close();

    if (copiiAdaugati > 0) {
        std::sort(listaCopii.begin(), listaCopii.end());
        std::cout << ">> [INFO] Import finalizat. " << copiiAdaugati << " copii adaugati si lista sortata.\n";
    }
}

// ---------------------------------------------------------
// METODE ADMIN ACTIVITATI
// ---------------------------------------------------------
void CentruAfterschool::adaugaActivitateInLista(std::unique_ptr<Activitate> a) {
    if (a) {
        this->listaActivitati.push_back(std::move(a));
        std::cout << "[INFO CentruAfterschool] Activitate adaugata in lista de activitati a centrului.\n";
    }
}
void CentruAfterschool::afiseazaListaActivitati() const {
    if (listaActivitati.empty()) {
        std::cout << "[INFO] Lista de activitati este goala. Introdu activitati noi din meniu\n";
        return;
    }

    std::cout << "\n====================================================================================================\n";
    std::cout << "                                LISTA ACTIVITATI DISPONIBILE                                      ";
    std::cout << "\n====================================================================================================\n";

    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(25) << "Denumire Activitate"
              << std::setw(15) << "Tip"
              << std::setw(25) << "Interval Orar"
              << std::setw(15) << "Pret Final"
              << "\n";

    std::cout << "----------------------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < listaActivitati.size(); ++i) {
        const auto& act = listaActivitati[i];

        std::string tipAfisat = "Generic";
        if (dynamic_cast<ActivitateSportiva*>(act.get())) tipAfisat = "SPORT";
        else if (dynamic_cast<ActivitateArtistica*>(act.get())) tipAfisat = "ARTA";
        else if (dynamic_cast<ActivitateEducationala*>(act.get())) tipAfisat = "EDU";
        else if (dynamic_cast<ActivitateExcursie*>(act.get())) tipAfisat = "EXCURSIE";

        std::stringstream ss;
        ss << act->getInterval();
        std::string intervalStr = ss.str();

        std::cout << std::left
                  << std::setw(5)  << i
                  << std::setw(25) << act->getDenumire()
                  << std::setw(15) << tipAfisat
                  << std::setw(25) << intervalStr
                  << std::fixed << std::setprecision(2)
                  << std::setw(15) << act->getPretCalculat()
                  << " RON\n";
    }
    std::cout << "====================================================================================================\n";
}
void CentruAfterschool::stergeActivitateDinLista(const int index) {
    if (index >= 0 && index < static_cast<int>(listaActivitati.size())) {
        std::cout << "[INFO] S-a sters din lista activitatea: ";
        listaActivitati[index]->afiseazaDetalii(std::cout);

        listaActivitati.erase(listaActivitati.begin() + index);
    } else {
        std::cerr << "[EROARE]: Index invalid pentru stergere din lista!\n";
    }
}
void CentruAfterschool::incarcaActivitatiDinFisier(const std::string& numeFisier) {
    std::ifstream f(numeFisier);
    if (!f.is_open()) {
        std::cout << "[EROARE CentruAfterschool::incarcaActivitatiDinFisier]: Fisierul " << numeFisier << " nu a putut fi deschis!\n";
        return;
    }

    std::string linie;
    int indexLinie = 0;
    int adaugate = 0;

    while (std::getline(f, linie)) {
        indexLinie++;
        if (linie.empty()) continue;

        std::stringstream ss(linie);
        std::string tip_str, denumire, pret_str, hs_str, hf_str, extra_str;

        // Format fisier: TIP|Denumire|Pret|OraStart|OraFinal|Extra
        if (std::getline(ss, tip_str, '|') &&
            std::getline(ss, denumire, '|') &&
            std::getline(ss, pret_str, '|') &&
            std::getline(ss, hs_str, '|') &&
            std::getline(ss, hf_str, '|') &&
            std::getline(ss, extra_str, '|')) {

            try {
                if (!extra_str.empty() && extra_str.back() == '\r') extra_str.pop_back();

                double pret = std::stod(pret_str);
                int hS = std::stoi(hs_str);
                int hF = std::stoi(hf_str);
                IntervalOrar interval(hS, hF);

                std::unique_ptr<Activitate> activitateNoua = nullptr;

                if (tip_str == "SPORT") {
                    bool echipament = (std::stoi(extra_str) == 1);
                    activitateNoua = ActivitateFactory::creareSport(denumire, pret, interval, echipament);
                }
                else if (tip_str == "ARTA") {
                    int nivel = std::stoi(extra_str);
                    activitateNoua = ActivitateFactory::creareArta(denumire, pret, interval, nivel);
                }
                else if (tip_str == "EDU") {
                    bool simulare = (std::stoi(extra_str) == 1);
                    activitateNoua = ActivitateFactory::creareEducational(denumire, pret, interval, simulare);
                }
                else if (tip_str == "EXCURSIE") {
                    int distanta = std::stoi(extra_str);
                    activitateNoua = ActivitateFactory::creareExcursie(denumire, pret, interval, distanta);
                }

                if (activitateNoua) {
                    this->listaActivitati.push_back(std::move(activitateNoua));
                    adaugate++;

                    std::cout << "[INFO Import]: Linia " << indexLinie << " - Inserat " << tip_str
                              << " | " << denumire << " | Pret: " << pret << " RON\n";
                }
            } catch (const std::exception& e) {
                std::cout << "[EROARE Import]: Linia " << indexLinie << " - " << denumire << " RESPINS.\n"
                          << "                 Motiv: " << e.what() << "\n";
            }
        }
    }

    f.close();
    std::cout << ">> [INFO] Import activitati finalizat. " << adaugate << " activitati adaugate in catalog.\n";
}
Activitate* CentruAfterschool::getActivitateDinLista(const int index) const {
    if (index >= 0 && index < static_cast<int>(listaActivitati.size())) {
        return listaActivitati[index].get();
    }
    throw std::out_of_range("Index activitate invalid!");
}

// ---------------------------------------------------------
// METODE ADMIN ECHIPA
// ---------------------------------------------------------
void CentruAfterschool::adaugaInstructor(const std::string& nume, const std::string& specializare, const double salariu) {
    int indexUltimulGasit = -1;

    for (size_t i = 0; i < this->listaActivitati.size(); ++i) {
        if (this->listaActivitati[i]->getDenumire() == specializare) {
            indexUltimulGasit = static_cast<int>(i);

            if (!this->listaActivitati[i]->areInstructor()) {
                this->listaActivitati[i]->setInstructor(nume);

                this->echipaDidactica.adauga(nume + " (" + specializare + ")");
                this->grilaSalarizare.adauga(salariu);

                std::cout << "[LOG] " << nume << " a preluat grupa existenta de '" << specializare << "'.\n";
                return;
            }
        }
    }

    if (indexUltimulGasit != -1) {
        std::unique_ptr<Activitate> activitateNoua = this->listaActivitati[indexUltimulGasit]->clone();
        activitateNoua->setInterval(activitateNoua->getInterval().decaleaza(0));
        activitateNoua->setInstructor(nume);

        this->listaActivitati.push_back(std::move(activitateNoua));

       this->echipaDidactica.adauga(nume + " (" + specializare + " - Gr. Noua)");
        this->grilaSalarizare.adauga(salariu);

        std::cout << "[INFO] Grupa noua creata pentru " << nume << ".\n";
    } else {
        this->echipaDidactica.adauga(nume + " (" + specializare + " - FARA GRUPA)");
        this->grilaSalarizare.adauga(salariu);
        std::cout << "[ATENTIE] Instructor in asteptare (specializarea nu exista in catalog).\n";
    }
}
void CentruAfterschool::incarcaInstructoriDinFisier(const std::string& numeFisier) {
    std::ifstream f(numeFisier);
    if (!f.is_open()) {
        std::cout << "[EROARE CentruAfterschool]: Fisierul " << numeFisier << " nu a putut fi deschis!\n";
        return;
    }

    std::string linie;
    int indexLinie = 0;
    int instructoriAdaugati = 0;

    while (std::getline(f, linie)) {
        indexLinie++;
        if (linie.empty()) continue;

        std::stringstream ss(linie);
        std::string nume, specializare, sal_str;

        // Format: Nume|Specializare|Salariu
        if (std::getline(ss, nume, '|') &&
            std::getline(ss, specializare, '|') &&
            std::getline(ss, sal_str, '|')) {

            try {
                if (!sal_str.empty() && sal_str.back() == '\r') sal_str.pop_back();

                double sal = std::stod(sal_str);

                this->adaugaInstructor(nume, specializare, sal);
                instructoriAdaugati++;

                std::cout << "[INFO Import]: Linia " << indexLinie << " - Inserat " << nume
                          << " | Spec: " << specializare << " | Salariu: " << sal << " RON\n";

            } catch (const std::exception& e) {
                std::cout << "[EROARE Import]: Linia " << indexLinie << " - " << nume << " RESPINS.\n"
                          << "                 Motiv: " << e.what() << "\n";
            }
            }
    }
    f.close();
    std::cout << ">> [INFO] Import finalizat. " << instructoriAdaugati << " instructori noi in echipa.\n";
}
void CentruAfterschool::afiseazaSituatieEchipa() const {
    const auto& numeInstructori = echipaDidactica.getInregistrari();
    const auto& salarii = grilaSalarizare.getInregistrari();

    if (numeInstructori.empty()) {
        std::cout << "\n[INFO] Nu exista instructori inregistrati in echipa.\n";
        return;
    }

    std::cout << "\n====================================================================================================\n";
    std::cout << "                                   SITUATIE ECHIPA SI SALARIZARE                                    ";
    std::cout << "\n====================================================================================================\n";

    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(40) << "Nume Instructor (si Specializare)"
              << std::setw(20) << "Salariu Baza"
              << "\n";

    std::cout << "----------------------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < numeInstructori.size(); ++i) {
        std::cout << std::left
                  << std::setw(5)  << i
                  << std::setw(40) << numeInstructori[i];

        if (i < salarii.size()) {
            std::cout << std::fixed << std::setprecision(2)
                      << std::right << std::setw(12) << salarii[i] << " RON";
        } else {
            std::cout << std::right << std::setw(16) << "NESETAT";
        }
        std::cout << std::left << "\n";
    }
    std::cout << "====================================================================================================\n";
}
void CentruAfterschool::modificaSalariuInGrila(const int index, const double sumaNoua) {
    if (sumaNoua < 0) {
        throw EroareAfterschool("Salariul nu poate fi negativ!");
    }
    this->grilaSalarizare.modifica(index, sumaNoua);
}
void CentruAfterschool::stergeInstructorDinEchipa(int index) {
    this->echipaDidactica.sterge(index);
    this->grilaSalarizare.sterge(index);
}

void CentruAfterschool::inscrieCopilLaActivitate(const int idCopil, std::unique_ptr<Activitate> a) {
    bool gasit = false;
    for (auto& copil : this->listaCopii) {
        if (copil.getId() == idCopil) {
            if (copil.areConflictOrar(*a)) {
                throw EroareConflictOrar(a->getDenumire());
            }

            const std::string numeAct = a->getDenumire();
            copil.adaugaActivitate(std::move(a));
            nrActivitatiCentru++;
            gasit = true;

            std::cout << "[INFO Inscriere]: Copilul " << copil.getNume() << " " << copil.getPrenume()
                      << " a fost inscris cu succes la: " << numeAct << "\n";
            break;
        }
    }
    if (!gasit) throw EroareID();
}
void CentruAfterschool::afiseazaProgramCopil(const int idCopil) const {
    const Copil* c = nullptr;
    for (const auto& copil : listaCopii) {
        if (copil.getId() == idCopil) {
            c = &copil;
            break;
        }
    }

    if (!c) throw EroareID();

    std::cout << "\n================================================================================\n";
    std::cout << " PROGRAM ACTIVITATI: " << c->getNume() << " " << c->getPrenume();
    std::cout << "\n================================================================================\n";

    const auto& acte = c->getActivitati();
    if (acte.empty()) {
        std::cout << "  [!] Copilul nu este inscris la nicio activitate.\n";
    } else {
        std::cout << std::left << std::setw(25) << "Activitate" << std::setw(20) << "Orar" << "Pret\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        for (const auto& a : acte) {
            if (a) {
                std::cout << std::left << std::setw(25) << a->getDenumire()
                          << std::setw(20) << a->getInterval()
                          << std::fixed << std::setprecision(2) << a->getPretCalculat() << " RON\n";
            }
        }
    }

    double total = c->calculTaxa(this->taxaBaza, this->pretMasaZilnic);

    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << " Detalii Calcul:\n";
    std::cout << "   - Taxa Baza: " << this->taxaBaza << " RON\n";
    std::cout << "   - Cost Masa (" << c->getZilePrezente() << " zile): "
              << (c->getZilePrezente() * this->pretMasaZilnic) << " RON\n";
    std::cout << " TOTAL ESTIMAT LUNA CURENTA: " << total << " RON\n";
    std::cout << "================================================================================\n";
}
// ---------------------------------------------------------
// METODE STATISTICI
// ---------------------------------------------------------
void CentruAfterschool::genereazaRaportCopii() const {
    if (listaCopii.empty()) {
        std::cout << "[INFO CentruAfterschool::genereazaRaportCopii] Nu exista copii inscrisi in centru.\n";
        return;
    }

    std::cout << "\n====================================================================================================\n";
    std::cout << "                                  LISTA COPII SI SITUATIE FINANCIARA                                ";
    std::cout << "\n====================================================================================================\n";

    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(20) << "Nume"
              << std::setw(20) << "Prenume"
              << std::setw(15) << "CNP"
              << std::setw(8)  << "Varsta"
              << std::setw(8)  << "Clasa"
              << std::setw(10) << "Activit."
              << std::setw(12) << "Cost Total"
              << "\n";

    std::cout << "----------------------------------------------------------------------------------------------------\n";

    double totalCentru = 0.0;
    for (const auto& c : listaCopii) {
        const double costCurent = c.calculTaxa(this->taxaBaza, this->pretMasaZilnic);
        totalCentru += costCurent;

        std::cout << std::left
                  << std::setw(5)  << c.getId()
                  << std::setw(20) << c.getNume()
                  << std::setw(20) << c.getPrenume();

        std::string cnpAfisat = c.getCNP();
        if(cnpAfisat.length() > 13) {
            cnpAfisat.resize(13);
        }

        std::cout << std::setw(15) << cnpAfisat
                  << std::setw(8)  << c.getVarsta()
                  << std::setw(8)  << c.getClasa()
                  << std::setw(10) << c.getActivitati().size()
                  << std::fixed << std::setprecision(2)
                  << std::right << std::setw(8) << costCurent << " RON"
                  << std::left << "\n";
    }
    std::cout << "====================================================================================================\n";
    std::cout << "TOTAL ESTIMAT INCASARI CENTRU: " << std::fixed << std::setprecision(2) << totalCentru << " RON\n";
    std::cout << "====================================================================================================\n";
}
void CentruAfterschool::raportPopularitateActivitati() const {
    std::cout << "\n--- GRAD DE OCUPARE ACTIVITATI ---\n";
    std::cout << std::left << std::setw(25) << "Activitate" << "Nr. Elevi Inscriși\n";
    std::cout << "------------------------------------------\n";

    for (const auto& act : listaActivitati) {
        int count = 0;
        for (const auto& copil : listaCopii) {
            for (const auto& a_copil : copil.getActivitati()) {
                if (a_copil->getDenumire() == act->getDenumire()) {
                    count++;
                }
            }
        }
        std::cout << std::left << std::setw(25) << act->getDenumire() << count << " elevi\n";
    }
}
void CentruAfterschool::raportActivitatiLibere() const {
    std::cout << "\n--- ACTIVITATI FARA NICIUN COPIL INSCRIȘ ---\n";
    bool exista = false;

    for (const auto& act : listaActivitati) {
        int count = 0;
        for (const auto& copil : listaCopii) {
            for (const auto& a_copil : copil.getActivitati()) {
                if (a_copil->getDenumire() == act->getDenumire()) count++;
            }
        }
        if (count == 0) {
            std::cout << " [!] " << act->getDenumire() << " (" << act->getInterval() << ")\n";
            exista = true;
        }
    }
    if (!exista) std::cout << "Toate activitatile au cel putin un elev.\n";
}
void CentruAfterschool::exportRaportFisier(const std::string& numeFisier) const {
    std::ofstream g(numeFisier);
    if (!g.is_open()) return;

    g << "RAPORT LUNAR - " << this->numeCentru << "\n";
    g << "==========================================\n\n";

    for (const auto& c : listaCopii) {
        g << c.getId() << ". " << c.getNume() << " " << c.getPrenume() << "\n";
        g << "   Total de plata: " << c.calculTaxa(this->taxaBaza, this->pretMasaZilnic) << " RON\n";
        g << "------------------------------------------\n";
    }

    g.close();
    std::cout << "[SUCCESS] Raportul a fost salvat in " << numeFisier << "\n";
}

