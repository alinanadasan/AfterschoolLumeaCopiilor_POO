//
// Created by Alina on 08/01/2026.
//

#ifndef OOP_EXCEPTIIAFTERSCHOOL_H
#define OOP_EXCEPTIIAFTERSCHOOL_H
#include <exception>
#include <string>

class EroareAfterschool : public std::exception {
protected:
    std::string mesaj;
public:
    explicit EroareAfterschool(std::string m) : mesaj(std::move(m)) {}
    const char* what() const noexcept override { return mesaj.c_str(); }
};

class EroareVarsta : public EroareAfterschool {
public:
    explicit EroareVarsta() : EroareAfterschool("Eroare: Varsta trebuie sa fie intre 5 si 18 ani!") {}
};

class EroareIndex : public EroareAfterschool {
public:
    explicit EroareIndex() : EroareAfterschool("Eroare: Indexul introdus este invalid!") {}
};

class EroareConflictOrar : public EroareAfterschool {
public:
    explicit EroareConflictOrar(const std::string& nume)
        : EroareAfterschool("Conflict detectat pentru activitatea: " + nume) {}
};
#endif //OOP_EXCEPTIIAFTERSCHOOL_H