#ifndef CAMPO_H
#define CAMPO_H

#include <QGraphicsPixmapItem>
#include <QObject>

#include "bloquedestruible.h"
#include "bloqueindestruible.h"
#include "explosion.h"
#include "bomba.h"
#include "configuracion.h"
#include "podervida.h"
#include "poderbomba.h"
#include "poderexplosion.h"
#include "puntaje.h"

enum blockType {
    Destruible,
    Indestruible,
    Vacio
};

class Jugador;
class Enemigo;

class Campo : public QObject, public QGraphicsPixmapItem {

    Q_OBJECT

public:
    Campo(int x, int y, QObject *parent = nullptr);
    ~Campo();
    blockType hayBloqueEnCampo() const;
    void ubiBloqueIndestruible(BloqueIndestruible * bloqueIndestruible);
    void ubiBloqueDestruible(BloqueDestruible * bloqueDestruible);
    void ponerBomba(Bomba * bomba);
    void playerOn(Jugador * jugador);
    void enemigoOn(Enemigo *enemigo);
    void playerOut(Jugador * jugador);
    void enemigoOut(Enemigo *enemigo);
    void conseguirPoder(Jugador * jugador);
    bool esBomba() const;
    bool esBloqueIndestructible() const;
    bool esBloqueDestruible() const;
    bool esVacio() const;

public slots:
    void explosion();

private:
    void createPixmapItem(QGraphicsPixmapItem *item, QString path) const;
    void crearExplosion();
    void poderRandom();

    int _x;
    int _y;
    bool _isPlayerOn;
    bool _isEnemigoOn;
    BloqueDestruible * _bloqueDestruible = nullptr;
    BloqueIndestruible * _bloqueIndestruible = nullptr;
    Explosion * _explosion = nullptr;
    Bomba * _bomba = nullptr;
    Jugador * _jugadores[tamanios::Jugadores];
    Puntaje *_puntaje;
    Enemigo *_enemigos[tamanios::Enemigos];
    Poder * _poder = nullptr;
};

#endif // CAMPO_H
