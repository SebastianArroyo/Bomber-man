#ifndef PODER_H
#define PODER_H

#include <QGraphicsPixmapItem>

class Jugador;

class Poder : public QGraphicsPixmapItem {
public:
    Poder() = default;
    virtual ~Poder() = default;
    virtual void usarPoder(Jugador * jugador) = 0;
};

#endif // PODER_H
