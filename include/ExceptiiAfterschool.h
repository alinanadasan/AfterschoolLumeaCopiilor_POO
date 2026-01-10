// Created by Alina on 08/01/2026.
//

#ifndef OOP_EXCEPTIIAFTERSCHOOL_H
#define OOP_EXCEPTIIAFTERSCHOOL_H

#include <exception>
#include <string>
#include <utility>

class EroareAfterschool : public std::exception {
protected:
    std::string mesaj;

public:
    explicit EroareAfterschool(std::string m) {
        this->mesaj = std::move(m);
    }

    const char* what() const noexcept override {
        return this->mesaj.c_str();
    }
};


class EroareVarsta final : public EroareAfterschool {
public:
    explicit EroareVarsta()
        : EroareAfterschool("Eroare: Varsta trebuie sa fie intre 6 si 15 ani!") {
    }
};

class EroareID final : public EroareAfterschool {
public:
    explicit EroareID()
        : EroareAfterschool("Eroare: Indexul introdus este invalid!") {
    }
};

class EroareConflictOrar final : public EroareAfterschool {
public:
    explicit EroareConflictOrar(const std::string& numeActivitate)
        : EroareAfterschool("Conflict orar detectat pentru activitatea: " + numeActivitate) {
    }
};

class EroareClasa final : public EroareAfterschool {
public:
    EroareClasa() : EroareAfterschool("Clasa trebuie sa fie intre 0 si 8!") {}
};

class EroareCNP final : public EroareAfterschool {
public:
    explicit EroareCNP(const std::string& msg) : EroareAfterschool("CNP Invalid: " + msg) {}
};

#endif //OOP_EXCEPTIIAFTERSCHOOL_H