#include <iostream>
#include <limits>
#include <string>
#include "CentruAfterschool.h"

void afiseazaMeniu() {
    std::cout << "\n--- SISTEM GESTIUNE AFTERSCHOOL ---";
    std::cout << "\n1. Adauga un copil nou";
    std::cout << "\n2. Inscrie un copil la o activitate";
    std::cout << "\n3. Afiseaza raportul financiar";
    // Am adaugat optiunea 4 aici:
    std::cout << "\n4. Sterge un copil din sistem";
    std::cout << "\n0. Iesire";
    std::cout << "\nOptiunea dvs: ";
}

int main() {
    CentruAfterschool centrulMeu("Lumea Copiilor");
    int optiune = -1;

    while (true) {
        afiseazaMeniu();

        if (!(std::cin >> std::ws >> optiune)) break;
        std::cout << optiune << "\n";

        if (optiune == 0) break;

        if (optiune == 1) {
            std::string nume;
            int varsta;
            std::cout << "Nume: ";
            std::cin >> std::ws;
            std::getline(std::cin, nume);
            std::cout << "[" << nume << "]\n";
            std::cout << "Varsta: ";
            std::cin >> varsta;
            std::cout << "[" << varsta << "]\n";
            centrulMeu.adaugaCopil(Copil(nume, varsta));
            std::cout << ">>> Succes: Copil adaugat.\n";

        } else if (optiune == 2) {
            int idx, start, final;
            double pret;
            std::string numAct;

            std::cout << "Index copil: ";
            std::cin >> idx;

            std::cout << "Denumire activitate: ";
            std::cin >> std::ws;
            std::getline(std::cin, numAct);

            std::cout << "Pret: ";
            std::cin >> pret;

            std::cout << "Ora start: ";
            std::cin >> start;

            std::cout << "Ora final: ";
            std::cin >> final;

            // Creăm obiectul activitate separat pentru a-i putea apela metodele
            Activitate nouaAct(numAct, pret, IntervalOrar(start, final));

            // Înscriem copilul în centru
            centrulMeu.inscrieCopilLaActivitate(idx, nouaAct);

            // FOLOSIRE METODE: Utilizăm getDenumire() și getNume() pentru confirmare.
            // Aceasta elimină avertismentul "style: The function is never used".
            std::cout << ">>> Confirmare: " << centrulMeu.getCopil(idx).getNume()
                      << " a fost procesat pentru activitatea: " << nouaAct.getDenumire() << "\n";
        } else if (optiune == 3) {
            centrulMeu.genereazaRaport(1000.0);

        } else if (optiune == 4) { // Logica pentru stergere
            if (centrulMeu.getNrCopii() == 0) {
                std::cout << "!!! Eroare: Nu exista copii de sters.\n";
                continue;
            }
            std::cout << "Index copil de sters (0-" << centrulMeu.getNrCopii() - 1 << "): ";
            int idx;
            std::cin >> idx;
            std::cout << idx << "\n";
            centrulMeu.stergeCopil(idx);
        }
    }

    std::cout << "\n--- Executie finalizata cu succes ---\n";
    return 0;
}