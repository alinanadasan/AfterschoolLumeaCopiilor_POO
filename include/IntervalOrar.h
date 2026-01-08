//
// Created by Alina on 03/01/2026.
//

#ifndef OOP_INTERVALORAR_H
#define OOP_INTERVALORAR_H

#include <iostream>

class IntervalOrar {
    int oraStart, oraFinal;
public:
    // Folosim explicit pentru a preveni conversiile implicite de la int la obiect
    explicit IntervalOrar(int start = 0, int final = 0);
    int getStart() const;
    int getFinal() const;
    friend std::ostream& operator<<(std::ostream& os, const IntervalOrar& i);
};
#endif //OOP_INTERVALORAR_H