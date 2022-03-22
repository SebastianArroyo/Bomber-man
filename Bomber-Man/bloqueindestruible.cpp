#include <QGraphicsScene>

#include "bloqueindestruible.h"

BloqueIndestruible::~BloqueIndestruible() {
    scene()->removeItem(this);
}
