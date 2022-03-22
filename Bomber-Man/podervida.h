#ifndef PODERVIDA_H
#define PODERVIDA_H

#include "poder.h"

class Jugador;

class PoderVida : public Poder {
public:
    PoderVida(int x, int y);
    void usarPoder(Jugador * jugador);
};

#endif // PODERVIDA_H
