#include "IntervalOrar.h"

IntervalOrar::IntervalOrar(const int start, const int final) {
    if (start >= 0 && start < final && final <= 24) {
        this->oraStart = start;
        this->oraFinal = final;
    } else {
        this->oraStart = 8;
        this->oraFinal = 9;
    }
}

int IntervalOrar::getStart() const {
    return this->oraStart;
}

int IntervalOrar::getFinal() const {
    return this->oraFinal;
}

std::ostream& operator<<(std::ostream& os, const IntervalOrar& i) {
    os << (i.oraStart < 10 ? "0" : "") << i.oraStart << ":00 - "
       << (i.oraFinal < 10 ? "0" : "") << i.oraFinal << ":00";
    return os;
}

bool IntervalOrar::seSuprapune(const IntervalOrar& altul) const {
    // Doua intervale [A, B] si [C, D] se suprapun daca A < D si C < B
    return (this->oraStart < altul.oraFinal) && (altul.oraStart < this->oraFinal);
}

IntervalOrar IntervalOrar::decaleaza(int pauza) const {
    // Calculam durata activitatii curente (ex: 16-14 = 2 ore)
    const int durata = this->oraFinal - this->oraStart;

    // Noul start este finalul celei vechi + eventuala pauza
    const int nouStart = this->oraFinal + pauza;

    // Noul final este noul start + durata aceleiasi activitati
    const int nouFinal = nouStart + durata;

    return IntervalOrar(nouStart, nouFinal);
}