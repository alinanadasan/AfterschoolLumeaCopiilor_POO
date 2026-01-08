#ifndef OOP_ACTIVITATE_H
#define OOP_ACTIVITATE_H

#include <string>
#include <memory>
#include <iostream>
#include "IntervalOrar.h"

class Activitate {
protected:
    std::string denumire;
    double pretExtra;
    IntervalOrar interval;
    virtual void print(std::ostream& os) const; // Partea virtuala a NVI
public:
    Activitate(std::string nume, double pret, IntervalOrar inter);
    virtual ~Activitate() = default;
    virtual std::unique_ptr<Activitate> clone() const = 0; // Constructor virtual
    virtual double getPretCalculat() const { return pretExtra; }
    void afiseazaDetalii(std::ostream& os) const; // Interfata Non-Virtuala (NVI)
    const std::string& getDenumire() const;
    IntervalOrar getInterval() const;
    friend std::ostream& operator<<(std::ostream& os, const Activitate& a);
};

#endif //OOP_ACTIVITATE_H