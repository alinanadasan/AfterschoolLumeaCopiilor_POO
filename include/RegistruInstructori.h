#ifndef OOP_REGISTRUINSTRUCTORI_H
#define OOP_REGISTRUINSTRUCTORI_H

#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>

// Clasa Template pentru gestiunea diverselor registre din Afterschool
template <typename T>
class RegistruInstructori {
private:
    std::vector<T> inregistrari;
    std::string denumire;

public:
    // Constructor default
    RegistruInstructori() : denumire("Departament Necunoscut") {}

    // Constructor cu parametru
    explicit RegistruInstructori(std::string dep) : denumire(std::move(dep)) {
        std::cout << "[LOG RegistruInstructori]: Registru nou creat pentru: " << this->denumire << "\n";
    }

    void adauga(const T& element) {
        this->inregistrari.push_back(element);
    }

    void sterge(int index) {
        if (index >= 0 && index < static_cast<int>(inregistrari.size())) {
            inregistrari.erase(inregistrari.begin() + index);
        } else {
            throw std::out_of_range("Index registru invalid pentru stergere!");
        }
    }

    void modifica(int index, const T& elementNou) {
        if (index >= 0 && index < static_cast<int>(inregistrari.size())) {
            inregistrari[index] = elementNou;
        } else {
            throw std::out_of_range("Index registru invalid pentru modificare!");
        }
    }

    // Getters
    const std::vector<T>& getInregistrari() const {
        return this->inregistrari;
    }
    const std::string& getDepartament() const {
        return this->denumire;
    }
};

template <typename T>
void afiseazaRegistru(const RegistruInstructori<T>& registru) {
    std::cout << "\n=====================================";
    std::cout << "\n--- REGISTRU: " << registru.getDepartament() << " ---";
    std::cout << "\n=====================================\n";

    const auto& lista = registru.getInregistrari();

    if (lista.empty()) {
        std::cout << " [!] Momentan nu exista date inregistrate.\n";
    } else {
        for (size_t i = 0; i < lista.size(); ++i) {
            std::cout << " [" << i << "] " << lista[i] << "\n";
        }
    }
    std::cout << "-------------------------------------\n";
}

#endif //OOP_REGISTRUINSTRUCTORI_H