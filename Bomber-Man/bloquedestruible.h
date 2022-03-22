#ifndef BLOQUEDESTRUIBLE_H
#define BLOQUEDESTRUIBLE_H

#include "bloque.h"

class BloqueDestruible : public Bloque {
public:
    BloqueDestruible() = default;
    ~BloqueDestruible();
};

#endif // BLOQUEDESTRUIBLE_H
