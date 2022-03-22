#ifndef BLOQUEINDESTRUIBLE_H
#define BLOQUEINDESTRUIBLE_H

#include "bloque.h"

class BloqueIndestruible : public Bloque {
public:
    BloqueIndestruible() = default;
    ~BloqueIndestruible();
};

#endif // BLOQUEINDESTRUIBLE_H
