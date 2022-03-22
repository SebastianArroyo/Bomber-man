#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include <QGraphicsPixmapItem>

#include "campo.h"

enum direccion {
        Izquierda,
    Derecha,
    Abajo,
    Arriba
};

class Jugador : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Jugador(int x, int y, QObject *parent = nullptr);
    ~Jugador();
    int getX() const;
    int getY() const;
    void mover(direccion dir, std::vector<std::vector<Campo *>>& campos);
    void plantarBomba(std::vector<std::vector<Campo *>>& campos);
    void setX(int x);
    void setY(int y);
    void bajarVida(Campo * campo);
    int getVida();
    void agregarBomba();
    void increaseExplosionSize();
    void increaseHP();
signals:
    void jugadorMuerto();

private:
    Campo *getCampo(int x, int y, std::vector<std::vector<Campo *>>& campos) const;

    void conectarBomba(int x, int y, Bomba *bomba, std::vector<std::vector<Campo *> >& campos, bool& flag);

    int _x;
    int _y;
    int vida;
    int score;
    int bombas_maximas;
    int tamanio_explosion;

};

#endif // JUGADOR_H
