#ifndef OOP_ACTIVITATESPORTIVA_H
#define OOP_ACTIVITATESPORTIVA_H

#include "Activitate.h"

class ActivitateSportiva : public Activitate {
    bool necesitaEchipament;

protected:
    // Suprascriere metoda print
    void print(std::ostream& os) const override;

public:
    //constructorul aceste clase(derivata din Activitate)
    ActivitateSportiva(std::string nume, double pret, IntervalOrar interv, bool echip);

    // Destructor virtual implicit
    ~ActivitateSportiva() override = default;

    //suprascriere metoda getPretCalculat
    double getPretCalculat() const override;

    // implementarea metoda clone pentru constructorul de copiere din Copil
    std::unique_ptr<Activitate> clone() const override;

    bool areEchipament() const;
};

#endif //OOP_ACTIVITATESPORTIVA_H