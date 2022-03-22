#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "enemigo.h"
#include "configuracion.h"
#include "campo.h"

Enemigo::Enemigo(int x, int y, QObject *parent)  : QObject (parent) {
//    timer2 = new QTimer(this);
//    connect(timer2, SIGNAL(timeout()), this, SLOT(mover(Derecha2,campos)));
    _x = x;
    _y = y;
    vida2 = tamanios::Vida2;
    setPos(x * tamanios::TamanioCampo, y * tamanios::TamanioCampo);
    setPixmap(QPixmap(":/img/img/ghost.png"));
//    timer2->start(2000);
}

Enemigo::~Enemigo(){
    scene()->removeItem(this);
}

void Enemigo::mover(direccion2 dir, std::vector<std::vector<Campo *>>& campos) {
    while (dir==Derecha2){
        if (_x < tamanios::Columnas - 1 && getCampo(_x + 1, _y, campos)->esVacio()) {
            getCampo(_x, _y, campos)->enemigoOut(this);
            getCampo(_x + 1, _y, campos)->enemigoOn(this);
            ++_x;
            setPos(_x * tamanios::TamanioCampo, _y * tamanios::TamanioCampo);
        }
        else{
            dir=Izquierda2;
        }
    }
    while(dir==Izquierda2){
        if (_x > 0 && getCampo(_x - 1, _y, campos)->esVacio()) {
            getCampo(_x, _y, campos)->enemigoOut(this);
            getCampo(_x - 1, _y, campos)->enemigoOn(this);
            --_x;
            setPos(_x * tamanios::TamanioCampo, _y * tamanios::TamanioCampo);
        }
        else{
            dir=Derecha2;
        }
    }
}

int Enemigo::getX() const
{
    return _x;
}

int Enemigo::getY() const
{
    return _y;
}

int Enemigo::getVida2()
{
    return vida2;
}

void Enemigo::setX(int x)
{
    _x=x;
}

void Enemigo::setY(int y)
{
    _y=y;
}

void Enemigo::bajarVida2(Campo *campo)
{
    vida2--;
    if(vida2 == 0) {
        campo->enemigoOut(this);
        emit enemigoMuerto();
        delete this;
    }
}

Campo *Enemigo::getCampo(int x, int y, std::vector<std::vector<Campo *> > &campos) const {
    return campos[static_cast<size_t>(y)][static_cast<size_t>(x)];
}
