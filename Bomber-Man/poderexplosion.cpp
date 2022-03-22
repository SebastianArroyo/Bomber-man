#include "poderexplosion.h"
#include "jugador.h"

PoderExplosion::PoderExplosion(int x, int y) {
    setPos(x, y);
    setPixmap(QPixmap(":/img/img/explosionPowerUp.png"));
}


void PoderExplosion::usarPoder(Jugador * jugador) {
    jugador->increaseExplosionSize();
}
