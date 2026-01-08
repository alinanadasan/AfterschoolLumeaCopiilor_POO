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

                // CONSTRUCȚIE SIGURĂ:
                // Cream obiectul separat. Daca varsta e 4, constructorul arunca exceptia AICI.
                // Programul sare direct la block-ul catch de jos si NU mai intra in adaugaCopil.
                Copil copilNou(nume, varsta);

                // Daca am ajuns aici, inseamna ca obiectul e valid
                centrulMeu.adaugaCopil(copilNou);

                std::cout << ">>> Succes: " << copilNou.getNume() << " a fost adaugat. In sistem sunt acum "
                          << centrulMeu.getNrCopii() << " copii." << std::endl;
            } else if (optiune == 2) {
                int idx, tip;
                std::cout << "Index copil: "; std::cin >> idx; std::cout << idx << std::endl;

                // Verificăm indexul înainte de a cere restul datelor
                if (idx < 0 || idx >= centrulMeu.getNrCopii()) {
                    throw EroareIndex();
                }

                std::cout << "Tip (1-Sport, 2-Arta, 3-Edu): "; std::cin >> tip; std::cout << tip << std::endl;

                std::string numAct; double pret; int start, final;
                std::cout << "Denumire: "; std::cin >> std::ws; std::getline(std::cin, numAct);
                std::cout << "[" << numAct << "]" << std::endl;
                std::cout << "Pret/Start/Final: "; std::cin >> pret >> start >> final;
                std::cout << pret << " " << start << " " << final << std::endl;

                // Creăm pointerul SMART separat
                std::unique_ptr<Activitate> noua;
                if (tip == 1) {
                    int echip;
                    std::cout << "Echipament (1-Da, 0-Nu): "; std::cin >> echip; std::cout << echip << std::endl;
                    noua = std::make_unique<ActivitateSportiva>(numAct, pret, IntervalOrar(start, final), echip == 1);
                } else if (tip == 2) {
                    int creativ;
                    std::cout << "Creativitate: "; std::cin >> creativ; std::cout << creativ << std::endl;
                    noua = std::make_unique<ActivitateArtistica>(numAct, pret, IntervalOrar(start, final), creativ);
                } else if (tip == 3) {
                    int mat;
                    std::cout << "Materiale: "; std::cin >> mat; std::cout << mat << std::endl;
                    noua = std::make_unique<ActivitateEducationala>(numAct, pret, IntervalOrar(start, final), mat);
                } else {
                    throw EroareAfterschool("Tip activitate invalid!");
                }

                // Abia acum trimitem obiectul către centru
                centrulMeu.inscrieCopilLaActivitate(idx, std::move(noua));

                // Confirmare folosind getterele pentru a curăța Cppcheck
                std::cout << ">>> Confirmare: " << centrulMeu.getCopil(idx).getNume() << " a fost inscris." << std::endl;

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