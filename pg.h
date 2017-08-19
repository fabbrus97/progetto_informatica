#ifndef PG_H
#define PG_H
#include "arma.h"
#include "personaggio.h"


class pg : public personaggio
{
    public:
        pg(arma x);
        void attacca();
    protected:
        arma armaInUso;
};

#endif // PG_H
