#include "poderbomba.h"
#include "jugador.h"

PoderBomba::PoderBomba(int x, int y) {
    setPos(x, y);
    setPixmap(QPixmap(":/img/img/bombPowerUp.png"));
}

void PoderBomba::usarPoder(Jugador * jugador) {
    jugador->agregarBomba();
}
