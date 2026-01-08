#ifndef OOP_ACTIVITATESPORTIVA_H
#define OOP_ACTIVITATESPORTIVA_H

#include "Activitate.h"

class ActivitateSportiva : public Activitate {
    bool necesitaEchipament;
protected:
    void print(std::ostream& os) const override;
public:
    ActivitateSportiva(std::string nume, double pret, IntervalOrar inter, bool echip);
    double getPretCalculat() const override; // Specific temei
    std::unique_ptr<Activitate> clone() const override; // Constructor virtual
    bool areEchipament() const { return necesitaEchipament; }
};

#endif //OOP_ACTIVITATESPORTIVA_H