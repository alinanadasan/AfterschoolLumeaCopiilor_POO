#include "InterfataUtilizator.h"
#include "ExceptiiAfterschool.h"
#include <iostream>
#include <fstream>
#include <limits>
#include "ActivitateFactory.h"

InterfataUtilizator::InterfataUtilizator() : centru(CentruAfterschool::getInstance()) {}

void InterfataUtilizator::curataInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void InterfataUtilizator::logAction(const std::string& msg) {
    std::cout << "\n[INFO InterfataUtilizator::logAction]: " << msg << std::endl;
}

int InterfataUtilizator::citesteInput() {
    int valoare;
    if (std::cin >> valoare) {
        istoricOptiuni.push_back(std::to_string(valoare));
        return valoare;
    }

    curataInput();
    return -1;
}

std::string InterfataUtilizator::citesteInputText() {
    std::string text;

    std::getline(std::cin, text);

    if (!text.empty()) {
        istoricOptiuni.push_back(text);
        return text;
    }

    return "";
}

// Meniu Principal
void InterfataUtilizator::afiseazaMeniuPrincipal() const {
    std::cout << "\n==============================================";
    std::cout << "\n   CENTRU AFTERSCHOOL - " <<  centru.getNumeCentru();
    std::cout << "\n             MENIU PRINCIPAL                  ";
    std::cout << "\n==============================================";
    std::cout << "\n1. Modul Administrare (Admin Copii/Catalog Activitati/Echipa Instructori)";
    std::cout << "\n2. Modul Inscrieri";
    std::cout << "\n3. Modul Rapoarte";
    std::cout << "\n0. Iesire Program";
    std::cout << "\n==============================================";
    std::cout << "\nOptiunea dvs: ";
}

// -----------------------------------------------------------
// MODUL ADMIN CENTRU
// -----------------------------------------------------------
void InterfataUtilizator::modulModificaInfoCentru() {
    while (true) {
        std::cout << "\n==============================================";
        std::cout << "\n       MODIFICA INFORMATII CENTRU             ";
        std::cout << "\n==============================================";

        centru.afiseazaDetalii();

        std::cout << "\nSelectati ce doriti sa modificati:";
        std::cout << "\n1. Numele Centrului";
        std::cout << "\n2. Taxa de Baza (Lunara)";
        std::cout << "\n3. Pretul Mesei (Zilnic)";
        std::cout << "\n0. Inapoi la meniul anterior";
        std::cout << "\n==============================================";
        std::cout << "\nOptiunea dvs: ";

        int optiune = citesteInput();

        if (optiune == 0) {
            std::cout << "Revenire la meniul anterior...\n";
            return;
        }

        bool modificareIncercata = false;

        try {
            switch (optiune) {
                case 1: {
                    std::cout << "\n[MODIFICARE NUME]";
                    std::cout << "\nIntrodu noul nume: ";

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::string numeNou = citesteInputText();

                    if (!numeNou.empty()) {
                        centru.setNumeCentru(numeNou);
                        logAction("Modificare nume centru in: " + numeNou);
                        modificareIncercata = true;
                    } else {
                        std::cout << "!! Nume invalid.\n";
                    }
                    break;
                }
                case 2: {
                    std::cout << "\n[MODIFICARE TAXA BAZA]";
                    std::cout << "\nIntrodu noua taxa (RON): ";
                    int taxaNoua = citesteInput();

                    if (taxaNoua != -1) {
                        centru.setTaxaBaza((double)taxaNoua);
                        logAction("Modificare taxa baza.");
                        modificareIncercata = true;
                    }
                    break;
                }
                case 3: {
                    std::cout << "\n[MODIFICARE PRET MASA]";
                    std::cout << "\nIntrodu noul pret masa (RON): ";
                    int pretNou = citesteInput();

                    if (pretNou != -1) {
                        centru.setPretMasaZilnic((double)pretNou);
                        logAction("Modificare pret masa.");
                        modificareIncercata = true;
                    }
                    break;
                }
                default:
                    std::cout << "!! Optiune invalida.\n";
                    continue;
            }
        } catch (const std::exception& e) {
            std::cerr << "[EROARE]: " << e.what() << "\n";
            modificareIncercata = true;
        }

        if (modificareIncercata) {
            std::cout << "\n----------------------------------------------";
            std::cout << "\n Doriti sa mai modificati ceva?";
            std::cout << "\n 1. DA";
            std::cout << "\n 0. NU (Revenire la meniul anterior)";
            std::cout << "\n----------------------------------------------";
            std::cout << "\nRaspunsul dvs: ";

            int raspuns = citesteInput();

            if (raspuns == 0) {
                std::cout << "Salvare si revenire...\n";
                return;
            }
        }
    }
}

void InterfataUtilizator::modulAdminCentru() {
    int opt = -1;
    bool ramaneInSubmeniu = true;

    while ( ramaneInSubmeniu ) {

        std::cout << "\n==============================================";
        std::cout << "\n       MODUL ADMIN CENTRU AFTERSCHOOL         ";
        std::cout << "\n==============================================";
        std::cout << "\n1. Afiseaza datele Afterschool-ului";
        std::cout << "\n2. Modifica datele centrului";
        std::cout << "\n0. Inapoi la modul ADMIN";
        std::cout << "\n==============================================";
        std::cout << "\nOptiunea dvs: ";

        opt = citesteInput();

        if (opt == -1) continue;

        if (opt == 0) {
            ramaneInSubmeniu = false;
            std::cout << "Revenire la Modul Admin...\n";
            continue;
        }

        switch (opt) {
            case 1:
                logAction("Ai ales optiunea 1: Afiseaza informatii Afterschool");
                centru.afiseazaDetalii();
                break;
            case 2:
                logAction("Ai ales optiunea 2: Modifica informatii Afterschool");
                modulModificaInfoCentru();
                break;

            default:
                std::cout << "!! Optiune inexistenta.\n";
        }
    }
}

// ---------------------------------------------------------
// MODUL COPII
// ---------------------------------------------------------
void InterfataUtilizator::modulModificaInfoCopil() {
    std::cout << "\n==============================================";
    std::cout << "\n       MODIFICA INFORMATII COPIL             ";
    std::cout << "\n==============================================";

    centru.genereazaRaportCopii();
    std::cout << "\nIntroduceti ID-ul copilului pe care doriti sa il modificati: ";
    const int idCopil = citesteInput();

    if (idCopil <= 0) {
        std::cout << "ID invalid sau anulare. Revenire...\n";
        return;
    }

    while (true) {
        std::cout << "\n==============================================";
        std::cout << "\n    MODIFICA INFORMATII COPIL (ID: " << idCopil << ")";
        std::cout << "\n==============================================";

        std::cout << "\nSelectati ce doriti sa modificati:";
        std::cout << "\n1. Nume Copil";
        std::cout << "\n2. Prenume Copil";
        std::cout << "\n3. CNP (Recalculeaza automat varsta)";
        std::cout << "\n4. Clasa";
        std::cout << "\n0. Inapoi la meniul anterior";
        std::cout << "\n==============================================";
        std::cout << "\nOptiunea dvs: ";

        const int optiune = citesteInput();

        if (optiune == 0) {
            std::cout << "Revenire la meniul anterior...\n";
            return;
        }

        bool afiseazaMeniuContinuare = false;

        try {
            switch (optiune) {
                case 1: { // NUME
                    std::cout << "\n[MODIFICARE NUME COPIL]";
                    std::cout << "\nIntrodu noul nume: ";

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::string numeNou = citesteInputText();

                    if (!numeNou.empty()) {
                        centru.modificaNumeCopil(idCopil, numeNou);
                        afiseazaMeniuContinuare = true;
                    } else {
                        throw std::runtime_error("Nume invalid (gol).");
                    }
                    break;
                }
                case 2: { // PRENUME
                    std::cout << "\n[MODIFICARE PRENUME COPIL]";
                    std::cout << "\nIntrodu noul prenume: ";

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::string prenumeNou = citesteInputText();

                    if (!prenumeNou.empty()) {
                        centru.modificaPrenumeCopil(idCopil, prenumeNou);
                        afiseazaMeniuContinuare = true;
                    } else {
                         throw std::runtime_error("Prenume invalid (gol).");
                    }
                    break;
                }
                case 3: { // CNP
                    std::cout << "\n[MODIFICARE CNP]";
                    std::cout << "\nIntrodu noul CNP: ";

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::string cnpNou = citesteInputText();

                    if (!cnpNou.empty()) {
                        centru.modificaCNPCopil(idCopil, cnpNou);
                        afiseazaMeniuContinuare = true;
                    }
                    break;
                }
                case 4: { // CLASA
                    std::cout << "\n[MODIFICARE CLASA]";
                    std::cout << "\nIntrodu noua clasa (0-8): ";
                    int clasaNoua = citesteInput();

                    /*if (clasaNoua < 0 || clasaNoua > 8) {
                        throw std::runtime_error("Clasa trebuie sa fie intre 0 si 8!");
                    }*/

                    if (clasaNoua != -1) {
                        centru.modificaClasaCopil(idCopil, clasaNoua);
                        afiseazaMeniuContinuare = true;
                    }
                    break;
                }
                default:
                    std::cout << "!! Optiune invalida.\n";
                    continue;
            }
        } catch (const std::exception& e) {
            std::cout << "\n[EROARE]: " << e.what() << "\n";
            afiseazaMeniuContinuare = true;
        }

        if (afiseazaMeniuContinuare) {
            std::cout << "\n----------------------------------------------";
            std::cout << "\n Doriti sa mai modificati si alte informatii la acest copil?";
            std::cout << "\n 1. DA";
            std::cout << "\n 0. NU (Revenire la meniul anterior)";
            std::cout << "\n----------------------------------------------";
            std::cout << "\nRaspunsul dvs: ";

            int raspuns = citesteInput();

            if (raspuns == 0) {
                std::cout << "Salvare si revenire...\n";
                return;
            }
        }
    }
}
void InterfataUtilizator::modulCopii()  {
    int opt = -1;
    bool ramaneInSubmeniu = true;

    while ( ramaneInSubmeniu ) {
        std::cout << "\n==============================================";
        std::cout << "\n             MODUL ADMIN COPII             ";
        std::cout << "\n==============================================";
        std::cout << "\n1. Afiseaza lista copii";
        std::cout << "\n2. Inregistrare manuala (via CNP)";
        std::cout << "\n3. Importa copii din 'copii.txt'";
        std::cout << "\n4. Modifica info copil";
        std::cout << "\n5. Sterge copil din centru";
        std::cout << "\n0. Inapoi la MODUL ADMIN";
        std::cout << "\n==============================================";
        std::cout << "\nOptiunea dvs: ";

        opt = citesteInput();

        if (opt == -1) continue;

        if (opt == 0) {
            ramaneInSubmeniu = false;
            std::cout << "Revenire la Modul Admin...\n";
            continue;
        }

        switch (opt) {
            case 1:
                logAction("Ai ales optiunea 1: Afisare lista copii.");
                centru.genereazaRaportCopii();
                break;
            case 2: {
                logAction("Ai ales optiunea 2: Inregistrare manuala (cu CNP).");
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Nume: ";
                std::string n = citesteInputText();

                std::cout << "Prenume: ";
                std::string p = citesteInputText();

                std::cout << "CNP: ";
                std::string cnp = citesteInputText();

                std::cout << "Clasa: ";
                const int cl = citesteInput();

                try {
                    centru.adaugaCopil(Copil(n, p, cnp, cl));
                    logAction("Copil adaugat cu succes.");
                } catch (const std::exception& e) {
                    std::cerr << "\n[EROARE]: " << e.what() << "\n";
                }
                break;
            }
            case 3: {
                logAction("Ai ales optiunea 3: Importa lista copii existenti din copii.txt...");
                centru.incarcaCopiiDinFisier("copii.txt");
                break;
            }
            case 4: {
                logAction("Ai ales optiunea 4: Modifica info copil...");
                modulModificaInfoCopil();
                break;
            }
            case 5: {
                logAction("Ai ales optiunea 5: Sterge copil din centru...");
                int id;
                std::cout << "ID pentru stergere: "; std::cin >> id;
                centru.stergeCopil(id);
                break;
            }
            default:
                std::cout << "!! Optiune inexistenta.\n";
        }
    }
}

// ---------------------------------------------------------
// MODUL ADMIN ACTIVITATI
// ---------------------------------------------------------
std::unique_ptr<Activitate> InterfataUtilizator::citesteSiCreeazaActivitate() {
    std::cout << "Tip Activitate (1-Sport, 2-Arta, 3-Edu, 4-Excursie): ";
    const int tip = citesteInput();

    std::cout << "Denumire: ";
    curataInput();
    const std::string den = citesteInputText();

    std::cout << "Pret de baza: ";
    double pret;
    if (!(std::cin >> pret)) { curataInput(); return nullptr; }

    std::cout << "Ora Start: ";
    const int hS = citesteInput();
    std::cout << "Ora Final: ";
    const int hF = citesteInput();

    const IntervalOrar interval(hS, hF);

    if (tip == 1) {
        std::cout << "Necesita echipament? (1-DA/0-NU): ";
        const int e = citesteInput();
        return ActivitateFactory::creareSport(den, pret, interval, e == 1);
    }
    if (tip == 2) {
        std::cout << "Nivel Creativitate (1-10): ";
        const int c = citesteInput();
        return ActivitateFactory::creareArta(den, pret, interval, c);
    }
    if (tip == 3) {
        std::cout << "Este simulare? (1-DA/0-NU): ";
        const int s = citesteInput();
        return ActivitateFactory::creareEducational(den, pret, interval, s == 1);
    }
    if (tip == 4) {
        std::cout << "Distanta (km): ";
        const int dist = citesteInput();
        return ActivitateFactory::creareExcursie(den, pret, interval, dist);
    }

    return nullptr;
}
void InterfataUtilizator::modulModificaActivitate() {
    centru.afiseazaListaActivitati();
    std::cout << "Introduceti Indexul activitatii pentru modificare: ";
    const int idx = citesteInput();

    try {
        Activitate* act = centru.getActivitateDinLista(idx);
        bool continua = true;

        while (continua) {
            std::cout << "\n--- MODIFICARE ACTIVITATE: " << act->getDenumire() << " ---\n";
            std::cout << "1. Modifica Denumire\n";
            std::cout << "2. Modifica Pret Baza\n";
            std::cout << "3. Modifica Interval Orar\n";
            std::cout << "0. Salvare si Iesire\n";
            std::cout << "Optiunea dvs: ";

            const int opt = citesteInput();
            if (opt == 0) break;

            switch (opt) {
                case 1: {
                    std::cout << "Denumire noua: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::string den = citesteInputText();
                    if (!den.empty()) act->setDenumire(den);
                    break;
                }
                case 2: {
                    std::cout << "Pret nou: ";
                    double p; std::cin >> p;
                    act->setPret(p);
                    break;
                }
                case 3: {
                    std::cout << "Ora Start noua: "; int hs = citesteInput();
                    std::cout << "Ora Final noua: "; int hf = citesteInput();
                    act->setInterval(IntervalOrar(hs, hf));
                    break;
                }
                default:
                    std::cout << "Optiune invalida.\n";
            }

            std::cout << "\nDoriti sa mai modificati ceva la aceasta activitate?\n1. DA\n0. NU\nOptiune: ";
            if (citesteInput() == 0) continua = false;
        }
    } catch (const std::exception& e) {
        std::cout << "[EROARE]: " << e.what() << "\n";
    }
}
void InterfataUtilizator::modulActivitati() {
    int opt = -1;
    bool ramaneInSubmeniu = true;

    while (ramaneInSubmeniu) {
        std::cout << "\n==============================================";
        std::cout << "\n            MODUL ADMIN ACTIVITATI             ";
        std::cout << "\n==============================================";
        std::cout << "\n1. Afiseaza lista activitati";
        std::cout << "\n2. Adauga activitate manual";
        std::cout << "\n3. Importa activitati din 'activitati.txt'";
        std::cout << "\n4. Modifica activitate";
        std::cout << "\n5. Sterge activitate din lista";
        std::cout << "\n0. Inapoi la MODUL ADMIN";
        std::cout << "\n==============================================";
        std::cout << "\nOptiunea dvs: ";

        opt = citesteInput();

        if (opt == -1) continue;
        if (opt == 0) {
            ramaneInSubmeniu = false;
            std::cout << "Revenire la Modul Admin...\n";
            continue;
        }

        switch (opt) {
            case 1:
                logAction("Afisare lista activitati disponibile.");
                centru.afiseazaListaActivitati();
                break;

            case 2: {
                logAction("Adaugare manuala activitate.");
                try {
                    std::unique_ptr<Activitate> noua = citesteSiCreeazaActivitate();
                    if (noua) {
                        centru.adaugaActivitateInLista(std::move(noua));
                        logAction("Activitate adaugata cu succes.");
                    } else {
                        std::cout << "!! Eroare la crearea activitatii (date invalide).\n";
                    }
                } catch (const std::exception& e) {
                    std::cout << "\n[EROARE]: " << e.what() << "\n";
                }
                break;
            }
            case 3:
                logAction("Import activitati din activitati.txt.");
                centru.incarcaActivitatiDinFisier("activitati.txt");
                break;

            case 4: {
                logAction("Modificare activitate din lista actvitati folosind ID.");
                modulModificaActivitate();
                break;
            }

            case 5: {
                logAction("Stergere activitate din lista.");
                centru.afiseazaListaActivitati();
                std::cout << "Introduceti Indexul activitatii pentru stergere: ";
                int idx = citesteInput();
                try {
                    centru.stergeActivitateDinLista(idx);
                } catch (const std::exception& e) {
                    std::cout << "\n[EROARE]: " << e.what() << "\n";
                }
                break;
            }

            default:
                std::cout << "!! Optiune inexistenta.\n";
        }
    }
}

// ---------------------------------------------------------
// MODUL ADMIN ECHIPA - INSTRUCTORI
// ---------------------------------------------------------
void InterfataUtilizator::modulAdaugaInstructor() {
    std::cout << "\n--- ADAUGARE INSTRUCTOR NOU ---";
    std::cout << "\nNume Instructor: ";
    curataInput();
    const std::string nume = citesteInputText();

    std::cout << "Specializare (Activitate existenta): ";
    std::string tipA = citesteInputText();

    if (nume.empty() || tipA.empty()) {
        std::cout << "!! Numele si specializarea nu pot fi goale.\n";
        return;
    }

    std::cout << "Salariu negociat (RON): ";
    double sal;
    if (!(std::cin >> sal) || sal < 0) {
        std::cout << "!! Suma invalida. Inregistrare anulata.\n";
        curataInput();
        return;
    }

    try {
        centru.adaugaInstructor(nume, tipA, sal);
        logAction("Instructorul " + nume + " a fost adaugat cu succes.");
    } catch (const std::exception& e) {
        std::cout << "[EROARE]: " << e.what() << "\n";
    }
}
void InterfataUtilizator::modulModificaSalariu() {
    centru.afiseazaSituatieEchipa();
    std::cout << "Introduceti Indexul instructorului: ";
    int idx = citesteInput();

    std::cout << "Suma Salariu (RON): ";
    if (double s; std::cin >> s && s >= 0) {
        try {
            centru.modificaSalariuInGrila(idx, s);
            logAction("Salariu actualizat cu succes.");
        } catch (const std::exception& e) {
            std::cout << "[EROARE]: " << e.what() << "\n";
        }
    } else {
        curataInput();
        std::cout << "!! Suma invalida.\n";
    }
}
void InterfataUtilizator::modulStergeInstructor() {
    centru.afiseazaSituatieEchipa();
    std::cout << "Introduceti Indexul instructorului pentru stergere: ";
    int idx = citesteInput();

    try {
        centru.stergeInstructorDinEchipa(idx);
        logAction("Instructor eliminat.");
    } catch (const std::exception& e) {
        std::cout << "[EROARE]: " << e.what() << "\n";
    }
}
void InterfataUtilizator::modulEchipa() {
    int opt = -1;
    bool ramaneInSubmeniu = true;

    while (ramaneInSubmeniu) {
        std::cout << "\n==============================================";
        std::cout << "\n            MODUL ADMIN ECHIPA             ";
        std::cout << "\n==============================================";
        std::cout << "\n1. Adauga Instructor (Manual)";
        std::cout << "\n2. Importa Instructori din 'instructori.txt'";
        std::cout << "\n3. Modifica/Inregistreaza Salariu";
        std::cout << "\n4. Afiseaza Situatie Echipa si Salarii";
        std::cout << "\n5. Sterge Instructor";
        std::cout << "\n0. Inapoi la Modul Admin";
        std::cout << "\n==============================================";
        std::cout << "\nOptiunea dvs: ";

        opt = citesteInput();

        if (opt == -1) continue;
        if (opt == 0) {
            ramaneInSubmeniu = false;
            std::cout << "Revenire la Modul Admin...\n";
            continue;
        }

        switch (opt) {
            case 1:
                logAction("Adaugare manuala instructor.");
                modulAdaugaInstructor();
                break;
            case 2:
                logAction("Import instructori din instructori.txt...");
                centru.incarcaInstructoriDinFisier("instructori.txt");
                break;
            case 3:
                logAction("Modificare salariu in grila.");
                modulModificaSalariu();
                break;
            case 4:
                logAction("Afisare raport echipa.");
                centru.afiseazaSituatieEchipa();
                break;
            case 5:
                logAction("Stergere instructor din echipa.");
                modulStergeInstructor();
                break;
            default:
                std::cout << "!! Optiune inexistenta.\n";
        }
    }
}

// -----------------------------------------------------------
// MODUL INSCRIERI
// -----------------------------------------------------------
void InterfataUtilizator::modulInscrieri() {
    int opt = -1;
    const bool ramaneInSubmeniu = true;

    while (ramaneInSubmeniu) {
        std::cout << "\n==============================================";
        std::cout << "\n               MODUL INSCRIERI                ";
        std::cout << "\n==============================================";
        std::cout << "\n1. Inscriere Copil la Activitate din Catalog";
        std::cout << "\n2. Inscriere Copil la Activitate Noua (Manuala)";
        std::cout << "\n3. Afiseaza Programul si Costurile unui Copil";
        std::cout << "\n0. Inapoi la MENIU PRINCIPAL";
        std::cout << "\n==============================================";
        std::cout << "\nOptiunea dvs: ";

        opt = citesteInput();
        if (opt == -1) continue;
        if (opt == 0) return;

        switch (opt) {
            case 1: {
                logAction("Inscriere din catalog.");
                centru.genereazaRaportCopii();
                centru.afiseazaListaActivitati();

                std::cout << "\nIntroduceti ID Copil: ";
                const int idC = citesteInput();
                std::cout << "Introduceti Index Activitate (IDX): ";
                const int idxA = citesteInput();

                try {
                    const Activitate* sablon = centru.getActivitateDinLista(idxA);
                    centru.inscrieCopilLaActivitate(idC, sablon->clone());
                } catch (const std::exception& e) {
                    std::cout << "[EROARE]: " << e.what() << "\n";
                }
                break;
            }

            case 2: {
                logAction("Inscriere manuala la activitate noua.");
                centru.genereazaRaportCopii();
                std::cout << "\nID Copil: ";
                const int idC = citesteInput();

                try {
                    std::unique_ptr<Activitate> noua = citesteSiCreeazaActivitate();
                    if (noua) {
                        centru.inscrieCopilLaActivitate(idC, std::move(noua));
                    }
                } catch (const std::exception& e) {
                    std::cout << "[EROARE]: " << e.what() << "\n";
                }
                break;
            }

            case 3: {
                logAction("Vizualizare program detaliat.");
                std::cout << "ID Copil: ";
                int idC = citesteInput();
                try {
                    centru.afiseazaProgramCopil(idC);
                } catch (const std::exception& e) {
                    std::cout << "[EROARE]: " << e.what() << "\n";
                }
                break;
            }

            default:
                std::cout << "!! Optiune inexistenta.\n";
        }
    }
}

// -----------------------------------------------------------
// MODUL ADMIN
// -----------------------------------------------------------
void InterfataUtilizator::modulAdmin() {
    int opt = -1;
    bool ramaneInSubmeniu = true;

    while (ramaneInSubmeniu) {
        std::cout << "\n==============================================";
        std::cout << "\n             MODUL ADMIN     ";
        std::cout << "\n==============================================";
        std::cout << "\n1. Modul Admin Centru Afterschool";
        std::cout << "\n2. Modul Admin Copii";
        std::cout << "\n3. Modul Admin Activitati";
        std::cout << "\n4. Modul Admin Echipa(Instructori/Salarii)";
        std::cout << "\n0. Inapoi la meniul principal";
        std::cout << "\n==============================================";
        std::cout << "\nOptiunea dvs: ";

        opt = citesteInput();

        if (opt == -1) continue;

        if (opt == 0) {
            ramaneInSubmeniu = false;
            continue;
        }

        switch (opt) {
            case 1: // Modul Admin Centru
                logAction("Ai ales optiunea 1: Modul Admin Centru Afterschool");
                modulAdminCentru();
                continue;

            case 2: { // Modul Admin Copii
                logAction("Ai ales optiunea 2: Modul Admin Copii");
                modulCopii();
                continue;
            }

            case 3: { // Modul Admin Activitati
                logAction("Ai ales optiunea 3: Modul Admin Activitati");
                modulActivitati();
                continue;
            }

            case 4: { // Modul Admin Echipa
                logAction("Ai ales optiunea 4: Modul Admin Echipa(Instructori/Salarii)");
                modulEchipa();
                continue;
            }

            default:
                std::cout << "!! Optiune inexistenta.\n";
                continue;
        }
    }
}

// -----------------------------------------------------------
// MODUL RAPOARTE
// -----------------------------------------------------------
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

void InterfataUtilizator::modulRapoarte() {
    int opt = -1;
    const bool ramaneInSubmeniu = true;

    while (ramaneInSubmeniu) {
        std::cout << "\n==============================================";
        std::cout << "\n              CENTRALIZATOR RAPOARTE          ";
        std::cout << "\n==============================================";
        std::cout << "\n1. Tabel Nominal Elevi (Situatie Financiara Detaliata)";
        std::cout << "\n2. Grad de Ocupare Activitati (Popularitate)";
        std::cout << "\n3. Catalog Activitati 'Orfane' (Fara copii inscrisi)";
        std::cout << "\n4. Bilant Echipa (Instructori si Sarcina de lucru)";
        std::cout << "\n5. Export Situatie Generala in 'raport_luna.txt'";
        std::cout << "\n0. Inapoi la MENIU PRINCIPAL";
        std::cout << "\n==============================================";
        std::cout << "\nOptiunea dvs: ";

        opt = citesteInput();
        if (opt == -1) continue;
        if (opt == 0) return;

        switch (opt) {
            case 1:
                logAction("Raport: Tabel Nominal Elevi.");
                centru.genereazaRaportCopii();
                break;
            case 2:
                logAction("Raport: Popularitate Activitati.");
                centru.raportPopularitateActivitati();
                break;
            case 3:
                logAction("Raport: Activitati fara inscrieri.");
                centru.raportActivitatiLibere();
                break;
            case 4:
                logAction("Raport: Bilant Echipa.");
                centru.afiseazaSituatieEchipa();
                break;
            case 5:
                logAction("Export date in fisier extern.");
                centru.exportRaportFisier("raport_luna.txt");
                break;
            default:
                std::cout << "!! Optiune inexistenta.\n";
        }
    }
}
// Sesiune Utilizator
void InterfataUtilizator::salveazaIstoric() const {
    std::ofstream fisier("tastatura.txt");

    if (fisier.is_open()) {
        for (const auto& opt : istoricOptiuni) {
            fisier << opt << "\n";
        }

        fisier.close();
        std::cout << "[INFO] Istoricul actiunilor a fost salvat in 'tastatura.txt'.\n";
    } else {
        std::cerr << "[ERROR] Nu s-a putut deschide fisierul pentru scriere.\n";
    }
}

void InterfataUtilizator::pornesteAplicatia() {
    int optiune = -1;

    istoricOptiuni.clear();

    while (true) {
        afiseazaMeniuPrincipal();

        optiune = citesteInput();

        if (optiune == -1) continue;

        if (optiune == 0) {
            salveazaIstoric();
            break;
        }

        try {
            switch (optiune) {
                case 1:
                    modulAdmin();
                    break;
                case 2:
                    modulInscrieri();
                    break;
                case 3:
                    modulRapoarte();
                    break;
                default:
                    std::cout << "Optiune invalida.\n";
            }
        } catch (const EroareAfterschool& e) {
            std::cerr << "\n[ERROR]: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "\n[ERROR]: " << e.what() << std::endl;
            curataInput();
        }
    }
}