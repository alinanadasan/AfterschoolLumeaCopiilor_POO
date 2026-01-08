#include <iostream>
#include <limits>
#include <string>
#include <memory>
#include "CentruAfterschool.h"
#include "ActivitateSportiva.h"
#include "ActivitateArtistica.h"
#include "ActivitateEducationala.h"
#include "ExceptiiAfterschool.h"

void afiseazaMeniu() {
    std::cout << "\n--- SISTEM GESTIUNE AFTERSCHOOL (TEMA 2) ---";
    std::cout << "\n1. Adauga un copil nou";
    std::cout << "\n2. Inscrie un copil la o activitate";
    std::cout << "\n3. Afiseaza raportul financiar";
    std::cout << "\n4. Sterge un copil din sistem";
    std::cout << "\n0. Iesire";
    std::cout << "\nOptiunea dvs: ";
}

int main() {
    CentruAfterschool centrulMeu("Lumea Copiilor");
    int optiune = -1;

    while (true) {
        try {
            afiseazaMeniu();
            if (!(std::cin >> optiune)) break;
            std::cout << optiune << std::endl;

            if (optiune == 0) break;

            if (optiune == 1) {
                std::string nume; int varsta;
                std::cout << "Nume: "; std::cin >> std::ws; std::getline(std::cin, nume);
                std::cout << "[" << nume << "]" << std::endl;

                std::cout << "Varsta: ";
                if (!(std::cin >> varsta)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                std::cout << "[" << varsta << "]" << std::endl;

                // Aceasta linie arunca EroareVarsta daca varsta nu e intre 5-18
                centrulMeu.adaugaCopil(Copil(nume, varsta));
                std::cout << ">>> Succes: Copil adaugat. In sistem sunt acum "
                << centrulMeu.getNrCopii() << " copii." << std::endl;

            } else if (optiune == 2) {
                int idx, tip;
                std::cout << "Index copil: "; std::cin >> idx; std::cout << idx << std::endl;
                std::cout << "Tip (1-Sport, 2-Arta, 3-Edu): "; std::cin >> tip; std::cout << tip << std::endl;

                std::string numAct; double pret; int start, final;
                std::cout << "Denumire: "; std::cin >> std::ws; std::getline(std::cin, numAct);
                std::cout << "[" << numAct << "]" << std::endl;

                std::cout << "Pret: "; std::cin >> pret; std::cout << pret << std::endl;
                std::cout << "Ora start: "; std::cin >> start; std::cout << start << std::endl;
                std::cout << "Ora final: "; std::cin >> final; std::cout << final << std::endl;

                std::unique_ptr<Activitate> noua;
                if (tip == 1) {
                    int echip;
                    std::cout << "Echipament (1-Da, 0-Nu): "; std::cin >> echip; std::cout << echip << std::endl;
                    noua = std::make_unique<ActivitateSportiva>(numAct, pret, IntervalOrar(start, final), echip == 1);
                } else if (tip == 2) {
                    int creativ;
                    std::cout << "Nivel creativitate: "; std::cin >> creativ; std::cout << creativ << std::endl;
                    noua = std::make_unique<ActivitateArtistica>(numAct, pret, IntervalOrar(start, final), creativ);
                } else if (tip == 3) {
                    int materiale;
                    std::cout << "Nr materiale: "; std::cin >> materiale; std::cout << materiale << std::endl;
                    noua = std::make_unique<ActivitateEducationala>(numAct, pret, IntervalOrar(start, final), materiale);
                } else {
                    std::cout << "!!! Tip invalid!" << std::endl;
                    continue;
                }

                // Poate arunca EroareIndex sau EroareConflictOrar
                centrulMeu.inscrieCopilLaActivitate(idx, std::move(noua));
                // FOLOSIM getCopil si getNume pentru confirmare
                std::cout << ">>> Confirmare: Copilul " << centrulMeu.getCopil(idx).getNume()
                          << " a fost inscris cu succes." << std::endl;

                // Testare dynamic_cast (downcast cu sens)
                centrulMeu.verificaPromotieSport(idx);

            } else if (optiune == 3) {
                centrulMeu.genereazaRaport(1000.0);
                std::cout << "Total activitati procesate (Static): " << CentruAfterschool::getNrTotal() << std::endl;

            } else if (optiune == 4) {
                int idx;
                std::cout << "Index de sters: "; std::cin >> idx; std::cout << idx << std::endl;
                centrulMeu.stergeCopil(idx);
            }
        }
        catch (const EroareAfterschool& e) {
            // 1. Mesaj pe cout (apare imediat în fluxul alb de text)
            std::cout << "\n[NOTIFICARE]: A aparut o problema la procesare..." << std::endl;

            // 2. Mesaj pe cerr (apare cu rosu, tehnic e fluxul de eroare)
            std::cerr << "DETALII EROARE: " << e.what() << std::endl;

            // 3. Sincronizam fluxul de citire (ignoram restul datelor invalide)
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const std::exception& e) {
            std::cout << "\n[SISTEM]: Eroare critica de sistem!" << std::endl;
            std::cerr << "MESAJ: " << e.what() << std::endl;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cout << "--- Executie finalizata ---" << std::endl;
    return 0;
}