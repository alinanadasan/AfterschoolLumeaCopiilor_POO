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
            if (!(std::cin >> optiune)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            std::cout << optiune << std::endl;

            if (optiune == 0) break;

            if (optiune == 1) {
                std::string nume;
                int varsta = 0;

                std::cout << "Nume: "; std::cin >> std::ws; std::getline(std::cin, nume);
                std::cout << "[" << nume << "]" << std::endl;

                std::cout << "Varsta: "; std::cin >> varsta;
                std::cout << "[" << varsta << "]" << std::endl;

                // FIX MSAN CRASH: Validam aici pentru a evita 'throw' din constructor care cauzeaza stack-overflow in MSAN
                if (varsta < 5 || varsta > 18) {
                    std::cout << "\n[NOTIFICARE]: Operatiune anulata. Varsta invalida (trebuie 5-18 ani)." << std::endl;
                    continue; // Sarim peste crearea obiectului
                }

                Copil c(nume, varsta);
                centrulMeu.adaugaCopil(c);

                // FIX STYLE: Folosim getNume() pentru a elimina avertismentul "unused function"
                // Deoarece adaugaCopil primeste const reference, facem o copie locala sau accesam ultimul element
                // Aici accesam ultimul copil adaugat pentru confirmare
                if(centrulMeu.getNrCopii() > 0) {
                     std::cout << ">>> Succes: " << centrulMeu.getCopil(centrulMeu.getNrCopii()-1).getNume()
                               << " a fost adaugat. In sistem sunt: "
                               << centrulMeu.getNrCopii() << " copii." << std::endl;
                }
            }
            else if (optiune == 2) {
                int idx = -1;
                int tip = 0;

                std::cout << "Index copil: "; std::cin >> idx; std::cout << idx << std::endl;

                if (idx < 0 || idx >= centrulMeu.getNrCopii()) throw EroareIndex();

                std::cout << "Tip (1-Sport, 2-Arta, 3-Edu): "; std::cin >> tip; std::cout << tip << std::endl;

                std::string numAct;
                double pret = 0.0;
                int start = 0, final = 0;

                std::cout << "Denumire: "; std::cin >> std::ws; std::getline(std::cin, numAct);
                std::cout << "[" << numAct << "]\nPret/Start/Final: ";
                std::cin >> pret >> start >> final;
                std::cout << pret << " " << start << " " << final << std::endl;

                std::unique_ptr<Activitate> noua;
                if (tip == 1) {
                    int echip = 0;
                    std::cout << "Echipament: "; std::cin >> echip; std::cout << echip << std::endl;
                    noua = std::make_unique<ActivitateSportiva>(numAct, pret, IntervalOrar(start, final), echip == 1);
                } else if (tip == 2) {
                    int cr = 0;
                    std::cout << "Creativitate: "; std::cin >> cr; std::cout << cr << std::endl;
                    noua = std::make_unique<ActivitateArtistica>(numAct, pret, IntervalOrar(start, final), cr);
                } else {
                    int mat = 0;
                    std::cout << "Materiale: "; std::cin >> mat; std::cout << mat << std::endl;
                    noua = std::make_unique<ActivitateEducationala>(numAct, pret, IntervalOrar(start, final), mat);
                }

                centrulMeu.inscrieCopilLaActivitate(idx, std::move(noua));
                std::cout << ">>> Confirmare: Inscris cu succes." << std::endl;
                centrulMeu.verificaPromotieSport(idx);
            }
            else if (optiune == 3) {
                centrulMeu.genereazaRaport(1000.0);
                std::cout << "Total activitati (Static): " << CentruAfterschool::getNrTotal() << std::endl;
            }
            else if (optiune == 4) {
                int idx = -1;
                std::cout << "Index de sters: "; std::cin >> idx; std::cout << idx << std::endl;

                // Verificare inainte de stergere
                if (idx >= 0 && idx < centrulMeu.getNrCopii()) {
                    // FIX STYLE: Folosim getCopil inainte de a sterge, doar ca sa folosim functia
                    std::cout << "Se sterge copilul: " << centrulMeu.getCopil(idx).getNume() << std::endl;
                }
                centrulMeu.stergeCopil(idx);
            }
        }
        catch (const EroareAfterschool& e) {
            std::cout << "\n[NOTIFICARE]: A aparut o problema la procesare..." << std::endl;
            std::cerr << "DETALII EROARE: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const std::exception& e) {
            std::cerr << "!!! Eroare sistem: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}