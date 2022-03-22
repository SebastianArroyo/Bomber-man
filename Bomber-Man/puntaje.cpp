#include "puntaje.h"
#include "configuracion.h"

Puntaje::Puntaje()
{
    score = 0;
}

int Puntaje::getScore()
{
    return score;
}

void Puntaje::subirPuntos()
{
    score++;
}

void Puntaje::bajarPuntos()
{
    score--;
}
