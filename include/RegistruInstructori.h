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
};
#endif //OOP_REGISTRUINSTRUCTORI_H