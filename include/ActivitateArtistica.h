#ifndef OOP_ACTIVITATEARTISTICA_H
#define OOP_ACTIVITATEARTISTICA_H

#include "Activitate.h"

class ActivitateArtistica : public Activitate {
    int nivelCreativitate;
protected:
    void print(std::ostream& os) const override;
public:
    ActivitateArtistica(std::string nume, double pret, IntervalOrar inter, int nivel);
    double getPretCalculat() const override;
    std::unique_ptr<Activitate> clone() const override;
};

#endif //OOP_ACTIVITATEARTISTICA_H