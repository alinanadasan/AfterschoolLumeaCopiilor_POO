#ifndef OOP_ACTIVITATEFACTORY_H
#define OOP_ACTIVITATEFACTORY_H

#include <memory>
#include <string>
#include "Activitate.h"
#include "ActivitateSportiva.h"
#include "ActivitateArtistica.h"
#include "ActivitateEducationala.h"
#include "ActivitateExcursie.h"

class ActivitateFactory {
public:

    static std::unique_ptr<Activitate> creareSport(const std::string& nume, double pret, IntervalOrar interv, bool echip) {
        return std::make_unique<ActivitateSportiva>(nume, pret, interv, echip);
    }

    static std::unique_ptr<Activitate> creareArta(const std::string& nume, double pret, IntervalOrar interv, int nivel) {
        return std::make_unique<ActivitateArtistica>(nume, pret, interv, nivel);
    }

    static std::unique_ptr<Activitate> creareEducational(const std::string& nume, double pret, IntervalOrar interv, bool simulare) {
        return std::make_unique<ActivitateEducationala>(nume, pret, interv, simulare);
    }

    static std::unique_ptr<Activitate> creareExcursie(const std::string& nume, double pret, IntervalOrar interv, int distanta) {
        return std::make_unique<ActivitateExcursie>(nume, pret, interv, distanta);
    }
};

#endif //OOP_ACTIVITATEFACTORY_H