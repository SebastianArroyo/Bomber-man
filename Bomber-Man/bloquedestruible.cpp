#include <QGraphicsScene>

#include "bloquedestruible.h"

BloqueDestruible::~BloqueDestruible() {
    scene()->removeItem(this);
}
