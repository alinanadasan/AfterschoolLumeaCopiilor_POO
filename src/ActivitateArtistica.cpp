//
// Created by Alina on 08/01/2026.
//
#include "ActivitateArtistica.h"

ActivitateArtistica::ActivitateArtistica(std::string n, double p, IntervalOrar i, int nivel)
    : Activitate(std::move(n), p, i), nivelCreativitate(nivel) {}

double ActivitateArtistica::getPretCalculat() const {
    // Arta adaugă o taxă de materiale bazată pe nivelul de creativitate
    return pretExtra + (nivelCreativitate * 10.5);
}

std::unique_ptr<Activitate> ActivitateArtistica::clone() const {
    return std::make_unique<ActivitateArtistica>(*this);
}

void ActivitateArtistica::print(std::ostream& os) const {
    Activitate::print(os);
    os << " [Tip: ARTA | Nivel Creativitate: " << nivelCreativitate << "/10]";
}