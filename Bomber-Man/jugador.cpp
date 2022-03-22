#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include "jugador.h"
#include "bomba.h"
#include "configuracion.h"
#include "enemigo.h"

Jugador::Jugador(int x, int y, QObject *parent)  : QObject (parent) {
    _x = x;
    _y = y;
    vida = tamanios::Vida;
    bombas_maximas = tamanios::Bombas;
    tamanio_explosion = tamanios::RangoExplosion;
    setPos(x * tamanios::TamanioCampo, y * tamanios::TamanioCampo);
    setPixmap(QPixmap(":/img/img/player_front.png"));
}

Jugador::~Jugador() {
    scene()->removeItem(this);
}

void Jugador::mover(direccion dir, std::vector<std::vector<Campo *> > &campos) {
    if(dir == Izquierda) {
        if (_x > 0 && getCampo(_x - 1, _y, campos)->esVacio()) {
            getCampo(_x, _y, campos)->playerOut(this);
            getCampo(_x - 1, _y, campos)->playerOn(this);
            --_x;
            setPos(_x * tamanios::TamanioCampo, _y * tamanios::TamanioCampo);
            getCampo(_x, _y, campos)->conseguirPoder(this);
        }
    }
    else if (dir == Derecha) {
        if (_x < tamanios::Columnas - 1 && getCampo(_x + 1, _y, campos)->esVacio()) {
            getCampo(_x, _y, campos)->playerOut(this);
            getCampo(_x + 1, _y, campos)->playerOn(this);
            ++_x;
            setPos(_x * tamanios::TamanioCampo, _y * tamanios::TamanioCampo);
            getCampo(_x, _y, campos)->conseguirPoder(this);
        }
    }
    else if (dir == Abajo) {
        if (_y < tamanios::Filas - 1 && getCampo(_x, _y + 1, campos)->esVacio()) {
            getCampo(_x, _y, campos)->playerOut(this);
            getCampo(_x, _y + 1, campos)->playerOn(this);
            ++_y;
            setPos(_x * tamanios::TamanioCampo, _y * tamanios::TamanioCampo);
            getCampo(_x, _y, campos)->conseguirPoder(this);
        }
    }
    else if (dir == Arriba) {
        if (_y > 0 && getCampo(_x, _y - 1, campos)->esVacio()) {
            getCampo(_x, _y, campos)->playerOut(this);
            getCampo(_x, _y - 1, campos)->playerOn(this);
            --_y;
            setPos(_x * tamanios::TamanioCampo, _y * tamanios::TamanioCampo);
            getCampo(_x, _y, campos)->conseguirPoder(this);
        }
    }
}

void Jugador::plantarBomba(std::vector<std::vector<Campo *> >& campos) {
    if(bombas_maximas > 0) {
        if(getCampo(_x, _y, campos)->esBomba() == false) {
            Bomba *bomb = new Bomba(&bombas_maximas);
            getCampo(_x, _y, campos)->ponerBomba(bomb);

            connect(bomb, SIGNAL(explode()), getCampo(_x, _y, campos), SLOT(explosion())); //connect always
            bool flagLeft = true, flagRight = true, flagUp = true, flagDown = true;
            for(int i = 1; i <= tamanio_explosion; i++) {
                if (flagRight && _x + i < tamanios::Columnas) {
                    conectarBomba(_x + i, _y, bomb, campos, flagRight);
                }

                if (flagLeft && _x - i >= 0) {
                    conectarBomba(_x - i, _y, bomb, campos, flagLeft);
                }

                if (flagUp && _y - i >= 0) {
                    conectarBomba(_x, _y - i, bomb, campos, flagUp);
                }

                if (flagDown && _y + i < tamanios::Filas) {
                    conectarBomba(_x, _y + i, bomb, campos, flagDown);
                }
            }

            bombas_maximas--;

            QTimer::singleShot(2000, bomb, &Bomba::emitExplode);
        }
    }
}

int Jugador::getX() const {
    return _x;
}

int Jugador::getY() const {
    return _y;
}

int Jugador::getVida()
{
    return vida;
}

void Jugador::setX(int x) {
    _x = x;
}

void Jugador::setY(int y) {
    _y = y;
}

void Jugador::bajarVida(Campo * campo)
{
    vida--;
    if(vida == 0) {
        campo->playerOut(this);
        emit jugadorMuerto();
        delete this;
    }
}

void Jugador::agregarBomba() {
    bombas_maximas++;
}

void Jugador::increaseExplosionSize() {
    tamanio_explosion++;
}

void Jugador::increaseHP() {
    vida++;
}

Campo *Jugador::getCampo(int x, int y, std::vector<std::vector<Campo *> > &campos) const {
    return campos[static_cast<size_t>(y)][static_cast<size_t>(x)];
}

void Jugador::conectarBomba(int x, int y, Bomba *bomba, std::vector<std::vector<Campo *> >& campos, bool& flag) {
    if (getCampo(x, y, campos)->hayBloqueEnCampo() != Indestruible){
        connect(bomba, SIGNAL(explode()), getCampo(x, y, campos), SLOT(explosion()));
    }
    else
        flag = false;
    if (getCampo(x, y, campos)->hayBloqueEnCampo() == Destruible)
        flag = false;
}
