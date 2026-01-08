//
// Created by Alina on 08/01/2026.
//

#ifndef OOP_ACTIVITATEEXCURSIE_H
#define OOP_ACTIVITATEEXCURSIE_H

#include "Activitate.h"

class ActivitateExcursie : public Activitate {
    int distantaKm; // Distanta pana la destinatie
protected:
    void print(std::ostream& os) const override;
public:
    ActivitateExcursie(std::string nume, double pret, IntervalOrar inter, int distanta);

    // Pretul se calculeaza in functie de distanta parcursa (transport)
    double getPretCalculat() const override;

    std::unique_ptr<Activitate> clone() const override;
};

#endif //OOP_ACTIVITATEEXCURSIE_H