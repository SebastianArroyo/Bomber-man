#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include "campo.h"

enum direccion2 {
        Izquierda2,
    Derecha2,
};

class QTimer;

class Enemigo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Enemigo(int x, int y, QObject *parent = nullptr);
    ~Enemigo();
    int getX() const;
    int getY() const;
    void mover(direccion2 dir,std::vector<std::vector<Campo *>>& campos);
    void setX(int x);
    void setY(int y);
    int getVida2();
    void bajarVida2(Campo * campo);

signals:
    void enemigoMuerto();

private:
    QTimer *timer2;
    Campo *getCampo(int x, int y, std::vector<std::vector<Campo *>>& campos) const;
    int _x;
    int _y;
    int vida2;
    bool ubicado;
};

#endif // ENEMIGO_H
