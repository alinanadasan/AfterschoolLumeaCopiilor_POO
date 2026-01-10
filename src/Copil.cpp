//
// Created by Alina on 03/01/2026.
//

#include "Copil.h"
#include "ExceptiiAfterschool.h"
#include <algorithm>
#include <utility>
#include <limits>
#include <sstream>

int Copil::nrCopii = 0;

//constructor de initializare: e nevoie de nume, prenume, cnp si clasaScoala
Copil::Copil(const std::string& nume, const std::string& prenume, const std::string& cnp, const int clasaScoala){

    id = ++nrCopii;

    this->nume = nume;
    this->prenume = prenume;
    this->cnp = cnp;
    this->clasaScoala = clasaScoala;
    this->dataNasterii = std::chrono::year_month_day{};
    this->varsta = 0;
    this->istoricPlati = nullptr;
    this->nrLuni = 0;
    this->zilePrezente = 0;

    try {
        this->extrageDataNastereDinCNP();
        this->calculeazaVarsta();

        if (varsta < 6 || varsta > 15) {
            throw EroareVarsta();
        }
        if (clasaScoala < 0 || clasaScoala > 8) {
            throw EroareClasa();
        }

        istoricPlati = new double[1]{0.0};

    } catch (...) {
        nrCopii--;
        throw;
    }
}

//Constructor supraincarcat - nume, prenume, clasa, varsta, restul default
Copil::Copil(const std::string& nume, const std::string& prenume, const int clasaScoala, const int varsta) {
    this->id = ++nrCopii;
    this->nume = nume;
    this->prenume = prenume;
    this->clasaScoala = clasaScoala;
    this->varsta = varsta;

    // Verificare Varsta
    if (this->varsta < 6 || this->varsta > 15) {
        nrCopii--;
        throw EroareVarsta();
    }

    // Verificare Clasa
    if (clasaScoala < 0 || clasaScoala > 8) {
        nrCopii--;
        throw EroareClasa();
    }

    this->cnp = "LIPSA";
    this->dataNasterii = std::chrono::year_month_day{};
    this->nrLuni = 1;
    this->istoricPlati = new double[1]{0.0};
    this->zilePrezente = 0;
}
// Constructor de copiere
Copil::Copil(const Copil& alt_copil) {

    this->id = alt_copil.id;
    this->nume = alt_copil.nume;
    this->prenume = alt_copil.prenume;
    this->clasaScoala = alt_copil.clasaScoala;
    this->varsta = alt_copil.varsta;
    this->cnp = alt_copil.cnp;
    this->dataNasterii = alt_copil.dataNasterii;
    this->nrLuni = alt_copil.nrLuni;
    this->zilePrezente = alt_copil.zilePrezente;

    if (alt_copil.istoricPlati != nullptr && alt_copil.nrLuni > 0) {
        this->istoricPlati = new double[this->nrLuni];
        for (int i = 0; i < this->nrLuni; ++i) {
            this->istoricPlati[i] = alt_copil.istoricPlati[i];
        }
    } else {
        this->istoricPlati = nullptr;
    }

    this->activitati.clear();
    for (const auto & i : alt_copil.activitati) {
        if (i != nullptr) {
            this->activitati.push_back(i->clone());
        }
    }
}

// Destructor
Copil::~Copil() {

    if (this->istoricPlati != nullptr) {
        delete[] this->istoricPlati;
        this->istoricPlati = nullptr;
    }

    //std::cout << "Destructor apelat pentru copilul cu ID: " << this->id << "\n";
}

//operator de asignare
Copil& Copil::operator=(const Copil& alt_copil) {
    if (this == &alt_copil) {
        return *this;
    }

    double* tempPlati = nullptr;
    if (alt_copil.istoricPlati != nullptr && alt_copil.nrLuni > 0) {
        tempPlati = new double[alt_copil.nrLuni];
        for (int i = 0; i < alt_copil.nrLuni; ++i) {
            tempPlati[i] = alt_copil.istoricPlati[i];
        }
    }

    delete[] this->istoricPlati;
    this->activitati.clear();

    this->id = alt_copil.id;
    this->nume = alt_copil.nume;
    this->prenume = alt_copil.prenume;
    this->clasaScoala = alt_copil.clasaScoala;
    this->varsta = alt_copil.varsta;
    this->cnp = alt_copil.cnp;
    this->dataNasterii = alt_copil.dataNasterii;
    this->nrLuni = alt_copil.nrLuni;
    this->zilePrezente = alt_copil.zilePrezente;

    this->istoricPlati = tempPlati;

    for (const auto & i : alt_copil.activitati) {
        if (i != nullptr) {
            this->activitati.push_back(i->clone());
        }
    }

    return *this;
}

//operator afisare
std::ostream& operator<<(std::ostream& os, const Copil& c) {
    os << "=========== DETALII ELEV (ID: " << c.id << ") ===========\n";
    os << "Nume: " << c.nume << " " << c.prenume << "\n";
    os << "CNP: " << c.cnp << "\n";
    os << "Clasa: " << c.clasaScoala << " | Varsta: " << c.varsta << " ani\n";

    os << "Prezenta luna curenta: " << c.zilePrezente << " zile\n";

    os << "Data Nasterii: ";
    if (c.dataNasterii.ok()) {
        os << static_cast<unsigned>(c.dataNasterii.day()) << "."
           << static_cast<unsigned>(c.dataNasterii.month()) << "."
           << static_cast<int>(c.dataNasterii.year());
    } else {
        os << "Necunoscuta / Invalida";
    }
    os << "\n";

    os << "Activitati inscrise (" << c.activitati.size() << "):\n";
    if (c.activitati.empty()) {
        os << "   - Nici o activitate.\n";
    } else {
        for (const auto& act_ptr : c.activitati) {
            if (act_ptr) {
                os << "   - " << *act_ptr << "\n";
            }
        }
    }

    os << "Istoric Plati: ";
    if (c.istoricPlati != nullptr && c.nrLuni > 0) {
        os << "[ ";
        for (int i = 0; i < c.nrLuni; ++i) {
            os << c.istoricPlati[i] << " lei";
            if (i < c.nrLuni - 1) os << ", ";
        }
        os << " ]";
    } else {
        os << "Fara istoric de plata.";
    }

    os << "\n==============================================\n";
    return os;
}

//operator citire
std::istream& operator>>(std::istream& is, Copil& c) {
    std::cout << "\n--- Introducere Date Elev ---\n";

    std::cout << "Nume: ";
    is >> c.nume;

    std::cout << "Prenume: ";
    is >> c.prenume;

    std::cout << "CNP (introdu '0' sau 'LIPSA' daca nu are): ";
    std::string tempCNP;
    is >> tempCNP;

    if ( tempCNP == "0" ) {
        c.cnp = "LIPSA";
        c.dataNasterii = std::chrono::year_month_day{};
        std::cout << ">> Atentie: Nu ati introdus CNP. Introduceti varsta manual: ";
        is >> c.varsta;
    } else {
        c.cnp = tempCNP;
        c.extrageDataNastereDinCNP();
        c.calculeazaVarsta();
        std::cout << ">> Varsta calculata automat din CNP: " << c.varsta << " ani.\n";
    }

    int clasaIntrodusa;
    bool clasaValida = false;

    while (!clasaValida) {
        std::cout << "Clasa (0-8): ";

        if (is >> clasaIntrodusa) {
            if (clasaIntrodusa >= 0 && clasaIntrodusa <= 12) {
                c.clasaScoala = clasaIntrodusa;
                clasaValida = true;
            } else {
                std::cout << "Eroare: Numarul clasei trebuie sa fie intre 0 si 8.\n";
            }
        } else {
            std::cout << "Eroare: Introdu un numar (cifre).\n";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    c.zilePrezente = 0;

    if (c.istoricPlati != nullptr) {
        delete[] c.istoricPlati;
        c.istoricPlati = nullptr;
        c.nrLuni = 0;
    }

    c.activitati.clear();

    return is;
}

//operator +=
Copil& Copil::operator+=(const double plata) {
    double* temp = new double[this->nrLuni + 1];

    if (this->istoricPlati != nullptr) {
        for (int i = 0; i < this->nrLuni; ++i) {
            temp[i] = this->istoricPlati[i];
        }
        delete[] this->istoricPlati;
    }

    temp[this->nrLuni] = plata;

    this->istoricPlati = temp;
    this->nrLuni++;

    return *this;
}

//operator <
bool operator<(const Copil& c1, const Copil& c2) {
    // Ordonare dupa varsta, nume, apoi, prenume
    if (c1.varsta != c2.varsta) {
        return c1.varsta < c2.varsta;
    }

    if (c1.nume != c2.nume) {
        return c1.nume < c2.nume;
    }

    return c1.prenume < c2.prenume;
}

//metode de logica
bool Copil::areConflictOrar(const Activitate& activitate_noua) const {
    for (const auto& a : activitati) {
        if (a && a->getInterval().seSuprapune(activitate_noua.getInterval())) {
            return true;
        }
    }
    return false;
}

void Copil::adaugaActivitate(std::unique_ptr<Activitate> a) {
    if (!a) return;

    if (this->areConflictOrar(*a)) {
        std::cout << ">> [EROARE] Conflict orar pentru " << nume << " " << prenume << "!\n";
        return;
    }

    const std::string denumireSalvata = a->getDenumire();

    activitati.push_back(std::move(a));

    std::cout << ">> [LOG] " << denumireSalvata << " adaugata in orarul lui " << prenume << ".\n";
}

double Copil::calculTaxa(const double taxaAdmin, const double pretMasaZi) const {

    const int zileDeCalcul = (zilePrezente > 0) ? zilePrezente : 0;
    const double costMasa = pretMasaZi * static_cast<double>(zileDeCalcul);

    double totalActivitati = 0.0;
    for (const auto& a : activitati) {
        if (a) {
            totalActivitati += a->getPretCalculat();
        }
    }

    if (activitati.size() >= 4) {
        totalActivitati *= 0.9;
    }

    return taxaAdmin + costMasa + totalActivitati;
}

// Getters/setters
int Copil::getId() const {
    return id;
}
const std::string& Copil::getNume() const {
    return this->nume;
}
const std::string& Copil::getPrenume() const {
    return this->prenume;
}
int Copil::getClasa() const {
    return clasaScoala;
}
int Copil::getZilePrezente() const {
    return zilePrezente;
}

const std::vector<std::unique_ptr<Activitate>>& Copil::getActivitati() const {
    return activitati;
}

// Setters
void Copil::setNume(const std::string& n) {
    this->nume = n;
}
void Copil::setPrenume(const std::string& p) {
    this->prenume = p;
}
void Copil::setCNP(const std::string& cnpNou) {
    const std::string cnpVechi = this->cnp;
    const std::chrono::year_month_day dataVeche = this->dataNasterii;
    const int varstaVeche = this->varsta;

    try {
        this->cnp = cnpNou;

        this->extrageDataNastereDinCNP();
        this->calculeazaVarsta();

        if (this->varsta < 6 || this->varsta > 15) {
            throw EroareVarsta();
        }

    } catch (...) {
        this->cnp = cnpVechi;
        this->dataNasterii = dataVeche;
        this->varsta = varstaVeche;

        throw;
    }
}
void Copil::setClasa(const int c) {

    if (c < 0 || c > 8) {
        throw EroareClasa();
    }

    this->clasaScoala = c;
}

// HELPERS
// Converteste string "ZZ.LL.AAAA" in std::chrono::year_month_day
std::chrono::year_month_day Copil::stringToChrono(const std::string& dataNasteriiStr) {

    if ( dataNasteriiStr.length() != 10 ) {
        throw std::invalid_argument("Data nasterii introdusa nu este in formatul dd.mm.yyyy !");
    }
    const int zi = std::stoi(dataNasteriiStr.substr(0, 2));
    const int luna = std::stoi(dataNasteriiStr.substr(3,2));
    const int an = std::stoi(dataNasteriiStr.substr(6,4));

    return std::chrono::year(an) / std::chrono::month(luna) / std::chrono::day(zi);

}

void Copil::extrageDataNastereDinCNP() {

    if (cnp == "LIPSA" || cnp.length() < 13) return;

    const int s = cnp[0] - '0';
    const int zi = std::stoi(cnp.substr(5, 2));
    const int luna = std::stoi(cnp.substr(3,2));
    const int an = std::stoi(cnp.substr(1,2));
    if (s != 5 && s != 6) {
          throw EroareCNP("CNP-ul nu corespunde unei persoane nascute dupa anul 2000!");
    }
    const int anNastere = 2000 + an;
    dataNasterii = std::chrono::year(anNastere) / std::chrono::month(luna) / std::chrono::day(zi);
}

void Copil::calculeazaVarsta() {

    if ( !dataNasterii.ok() ) return;

    const auto now = std::chrono::system_clock::now();
    const std::chrono::year_month_day azi = std::chrono::floor<std::chrono::days>(now);
    varsta = static_cast<int>(azi.year()) - static_cast<int>(dataNasterii.year());

    if ( azi.month() < dataNasterii.month() || (azi.month() == dataNasterii.month() && azi.day() < dataNasterii.day() ) ) {
        varsta--;
    }

}

int Copil::getVarsta() const {
    return this->varsta;
}

std::string Copil::getDataNasterii() const {
    // Verificam daca data este valida
    if (!this->dataNasterii.ok()) {
        return "Nedeterminata";
    }

    // pentru formatul "ZZ.LL.AAAA"
    std::stringstream ss;
    ss << static_cast<unsigned>(this->dataNasterii.day()) << "."
       << static_cast<unsigned>(this->dataNasterii.month()) << "."
       << static_cast<int>(this->dataNasterii.year());

    return ss.str();
}

const std::string& Copil::getCNP() const {
    return this->cnp;
}