#include <QGraphicsScene>

#include "bomba.h"

Bomba::Bomba(int *bombasMaximas) : _bombasMaximas(bombasMaximas){ }

Bomba::~Bomba() {
    scene()->removeItem(this);
}

void Bomba::emitExplode() {
    emit explode();
    (*_bombasMaximas)++;
    delete this;
}
