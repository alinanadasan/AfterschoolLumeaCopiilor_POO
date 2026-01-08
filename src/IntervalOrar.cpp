//
// Created by Alina on 03/01/2026.
//

#include "IntervalOrar.h"
IntervalOrar::IntervalOrar(int start, int final) : oraStart(start), oraFinal(final) {}
int IntervalOrar::getStart() const { return oraStart; }
int IntervalOrar::getFinal() const { return oraFinal; }
std::ostream& operator<<(std::ostream& os, const IntervalOrar& i) {
    os << i.oraStart << ":00 - " << i.oraFinal << ":00";
    return os;
}