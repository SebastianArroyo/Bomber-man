#ifndef BOMBA_H
#define BOMBA_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Bomba : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Bomba() = default;
    Bomba(int * bombasMaximas);
    ~Bomba();
    void emitExplode();

signals:
    void explode();

private:
    int * _bombasMaximas;
};

#endif // BOMBA_H
