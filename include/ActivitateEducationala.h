//
// Created by Alina on 08/01/2026.
//

#ifndef OOP_ACTIVITATEEDUCATIONALA_H
#define OOP_ACTIVITATEEDUCATIONALA_H

#include "Activitate.h"

class ActivitateEducationala : public Activitate {
    bool esteSimulare;

protected:
    void print(std::ostream& os) const override;

public:
    ActivitateEducationala(std::string nume, double pret, IntervalOrar inter, bool simulare);

    ~ActivitateEducationala() override = default;

    double getPretCalculat() const override;

    std::unique_ptr<Activitate> clone() const override;

    bool getEsteSimulare() const;
};

#endif //OOP_ACTIVITATEEDUCATIONALA_H