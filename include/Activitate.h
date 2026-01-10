#ifndef OOP_ACTIVITATE_H
#define OOP_ACTIVITATE_H

#include <string>
#include <memory>
#include <iostream>
#include "IntervalOrar.h"

class Activitate {
    friend class CentruAfterschool;
    std::string numeInstructor;
protected:
    std::string denumire;
    double pretExtra;
    IntervalOrar interval;
    virtual void print(std::ostream& os) const;

public:
    //constructor
    Activitate(std::string nume, const double pret, IntervalOrar intrv, std::string instructor);

    //destructor
    virtual ~Activitate() = default;
    //folosita de Copil
    virtual std::unique_ptr<Activitate> clone() const = 0;

    //supraincarcare operator afisare
    friend std::ostream& operator<<(std::ostream& os, const Activitate& a);

    //metode de logica
    virtual double getPretCalculat() const;
    void afiseazaDetalii(std::ostream& os) const;

    //getters
    const std::string& getDenumire() const;
    IntervalOrar getInterval() const;
    std::string getInstructor() const;

    bool areInstructor() const;
    void setDenumire(const std::string &nume);
    void setPret(double pret);
    void setInterval(const IntervalOrar &nou);
    void setInstructor(const std::string &nume);

};
#endif //OOP_ACTIVITATE_H