#include <QGraphicsScene>
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

#include "campo.h"
#include "jugador.h"
#include "enemigo.h"

Campo::Campo(int x, int y, QObject *parent) : QObject(parent), _x(x), _y(y), _isPlayerOn(false), _isEnemigoOn(false) {
    setPos(x, y);
    setPixmap(QPixmap(":/img/img/field.png"));
    for (int i = 0; i < tamanios::Jugadores; i++) {
        _jugadores[i] = nullptr;
    }
    for (int i = 0; i < tamanios::Enemigos; i++) {
        _enemigos[i] = nullptr;
    }
}

Campo::~Campo() {
    if(_bloqueDestruible)
        delete _bloqueDestruible;
    if(_bloqueIndestruible)
        delete _bloqueIndestruible;
    if(_explosion)
        delete _explosion;
    if(_bomba)
        delete _bomba;
}

void Campo::ubiBloqueIndestruible(BloqueIndestruible *bloqueIndestruible) {
    createPixmapItem(bloqueIndestruible, ":/img/img/unDestroyableBlock.png");
    _bloqueIndestruible = bloqueIndestruible;
}

void Campo::ubiBloqueDestruible(BloqueDestruible *bloqueDestruible) {
    createPixmapItem(bloqueDestruible, ":/img/img/destroyableBlock.png");
    _bloqueDestruible = bloqueDestruible;
}

void Campo::ponerBomba(Bomba *bomba) {
    createPixmapItem(bomba, ":/img/img/bomb.png");
    _bomba = bomba;
}

void Campo::playerOn(Jugador * jugador) {
    for (int i = 0; i < tamanios::Jugadores; i++) {
        if(!_jugadores[i]) {
            _jugadores[i] = jugador;
            break;
        }
    }
    _isPlayerOn = true;
}

void Campo::enemigoOn(Enemigo *enemigo) {
    for (int i = 0; i < tamanios::Enemigos; i++) {
        if(!_enemigos[i]) {
            _enemigos[i] = enemigo;
            break;
        }
    }
    _isEnemigoOn = true;
}


void Campo::playerOut(Jugador * jugador) {
    for (int i = 0; i < tamanios::Jugadores; i++) {
        if(_jugadores[i] == jugador)
            _jugadores[i] = nullptr;
        else if(_jugadores[i])
            _isPlayerOn = false;
    }
}

void Campo::enemigoOut(Enemigo * enemigo) {
    for (int i = 0; i < tamanios::Enemigos; i++) {
        if(_enemigos[i] == enemigo)
            _enemigos[i] = nullptr;
        else if(_enemigos[i])
            _isEnemigoOn = false;
    }
}

bool Campo::esBomba() const {
    if(_bomba == nullptr)
        return false;
    return true;
}

bool Campo::esBloqueIndestructible() const {
    if(_bloqueIndestruible == nullptr)
        return false;
    return true;
}

bool Campo::esBloqueDestruible() const
{
    if(_bloqueDestruible == nullptr)
        return false;
    return true;
}

blockType Campo::hayBloqueEnCampo() const
{
    if (_bloqueDestruible)
        return Destruible;
    else if (_bloqueIndestruible)
        return Indestruible;
    else
        return Vacio;
}

bool Campo::esVacio() const {
    if(_bloqueIndestruible == nullptr && _bloqueDestruible == nullptr && _bomba == nullptr)
        return true;
    return false;
}

void Campo::conseguirPoder(Jugador * jugador)  {
    if(_poder != nullptr) {
        _poder->usarPoder(jugador);
        scene()->removeItem(_poder);
        delete _poder;
        _poder = nullptr;
    }
}

void Campo::explosion() {
    _bomba = nullptr;
    if (_bloqueDestruible) {
        delete _bloqueDestruible;
        _bloqueDestruible = nullptr;
        poderRandom();
        crearExplosion();
    }
    else if (!_bloqueDestruible && !_bloqueIndestruible) {
        crearExplosion();
    }
}

void Campo::createPixmapItem(QGraphicsPixmapItem *item, QString path) const {
    item->setPos(_x, _y);
    item->setPixmap(QPixmap(path));
    scene()->addItem(item);
}

void Campo::crearExplosion() {
    _explosion = new Explosion();
    createPixmapItem(_explosion, ":/img/img/fire.png");
    if (_isEnemigoOn == true) {
        for (int i = 0; i < tamanios::Enemigos; i++) {
            if(_enemigos[i]){
                _enemigos[i]->bajarVida2(this);
//                _puntaje->subirPuntos();
            }
        }
    }
    if(_isPlayerOn == true) {
        for (int i = 0; i < tamanios::Jugadores; i++) {
            if(_jugadores[i]) {
                _jugadores[i]->bajarVida(this);
//                _puntaje->bajarPuntos();
            }
        }
    }

    QTimer::singleShot(300, _explosion, &Explosion::quitarExplosion);
    _explosion = nullptr;
}

void Campo::poderRandom() {
    int randomNumber = QRandomGenerator::global()->bounded(20);
    if(randomNumber == 0 ) {
        PoderVida * newPowerUp = new PoderVida(_x, _y);
        _poder = newPowerUp;
        scene()->addItem(newPowerUp);
     }
    else if(randomNumber == 1 || randomNumber == 10) {
        PoderExplosion * newPowerUp = new PoderExplosion(_x, _y);
        _poder = newPowerUp;
        scene()->addItem(newPowerUp);
    }
    else if(randomNumber == 2 || randomNumber == 20) {
        PoderBomba * newPowerUp = new PoderBomba(_x, _y);
        _poder = newPowerUp;
        scene()->addItem(newPowerUp);
    }
}
