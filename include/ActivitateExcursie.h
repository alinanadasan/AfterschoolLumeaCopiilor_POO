#ifndef OOP_ACTIVITATEEXCURSIE_H
#define OOP_ACTIVITATEEXCURSIE_H

#include "Activitate.h"

class ActivitateExcursie : public Activitate {
    int distantaKm; // Distanta pana la destinatie pentru calculul transportului

protected:
    // Suprascriere metoda print pentru detalii specifice excursiei
    void print(std::ostream& os) const override;

public:
    // Constructorul clasei derivate
    ActivitateExcursie(std::string nume, double pret, IntervalOrar inter, int distanta);

    // Destructor virtual implicit
    ~ActivitateExcursie() override = default;

    // Pretul se calculeaza in functie de distanta parcursa (2.5 RON/km)
    double getPretCalculat() const override;

    // Implementarea metodei clone
    std::unique_ptr<Activitate> clone() const override;

    // Getters
    int getDistantaKm() const;
};

#endif //OOP_ACTIVITATEEXCURSIE_H