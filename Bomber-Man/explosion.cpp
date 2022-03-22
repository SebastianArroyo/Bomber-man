#include <QGraphicsScene>

#include "explosion.h"


Explosion::~Explosion() {
    scene()->removeItem(this);
}

void Explosion::quitarExplosion() {
    delete this;
}
