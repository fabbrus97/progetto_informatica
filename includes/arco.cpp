#include "arco.h"
#define CONST_LENGTH 100


arco::arco():arma()
{
    char nomeArco[CONST_LENGTH] = {'A', 'R', 'C', 'O', '\0'};
    arco::setNomeCompleto(nomeArco);
    arco::setIcon('[');
    arco::setRange(4);
    arco::setDanniArma(70);
    arco::setExpRichiesti(200);
}

