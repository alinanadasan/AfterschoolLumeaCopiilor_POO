#ifndef OOP_ACTIVITATEARTISTICA_H
#define OOP_ACTIVITATEARTISTICA_H

#include "Activitate.h"

class ActivitateArtistica : public Activitate {
    int nivelCreativitate; //folosit pentru a calcula pretul diferit

protected:
    //suprascriere metoda print
    void print(std::ostream& os) const override;

public:
    //constructorul aceste clase(derivata din Activitate)
    ActivitateArtistica(std::string nume, double pret, IntervalOrar intrv, int nivel);
    // Destructor virtual implicit
    ~ActivitateArtistica() override = default;

    //suprascriere metoda getPretCalculat
    double getPretCalculat() const override;
    // implementarea metoda clone pentru constructorul de copiere din Copil
    std::unique_ptr<Activitate> clone() const override;
};

#endif //OOP_ACTIVITATEARTISTICA_H