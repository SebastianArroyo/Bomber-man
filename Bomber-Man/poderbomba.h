#ifndef PODERBOMBA_H
#define PODERBOMBA_H

#include "poder.h"

class Jugador;

class PoderBomba : public Poder {
public:
    PoderBomba(int x, int y);
    void usarPoder(Jugador * jugador);
};

#endif // PODERBOMBA_H
