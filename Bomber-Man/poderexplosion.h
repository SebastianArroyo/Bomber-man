#ifndef PODEREXPLOSION_H
#define PODEREXPLOSION_H

#include "poder.h"

class Jugador;

class PoderExplosion : public Poder {
public:
    PoderExplosion(int x, int y);
    void usarPoder(Jugador * jugador);
};

#endif // PODEREXPLOSION_H
