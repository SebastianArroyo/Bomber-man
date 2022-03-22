#ifndef PUNTAJE_H
#define PUNTAJE_H


class Puntaje
{
public:
    Puntaje();
    ~Puntaje();
    int getScore();
    void subirPuntos();
    void bajarPuntos();

private:
    int score;
};

#endif // PUNTAJE_H
