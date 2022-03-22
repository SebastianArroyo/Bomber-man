#include "podervida.h"
#include "jugador.h"

PoderVida::PoderVida(int x, int y) {
    setPos(x, y);
    setPixmap(QPixmap(":/img/img/healthPowerUp.png"));
}

void PoderVida::usarPoder(Jugador * jugador) {
    jugador->increaseHP();
}
