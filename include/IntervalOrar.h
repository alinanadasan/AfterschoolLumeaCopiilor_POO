#ifndef OOP_INTERVALORAR_H
#define OOP_INTERVALORAR_H

#include <iostream>

class IntervalOrar {
    int oraStart, oraFinal;

public:
    // Constructor cu valori implicite
    explicit IntervalOrar(int start = 0, int final = 0);

    // Getters
    int getStart() const;
    int getFinal() const;

    // Operator de afisare (friend)
    friend std::ostream& operator<<(std::ostream& os, const IntervalOrar& i);

    // Logica pentru detectarea conflictelor orare
    bool seSuprapune(const IntervalOrar& altul) const;

    IntervalOrar decaleaza(int pauza = 0) const;
};
#endif //OOP_INTERVALORAR_H