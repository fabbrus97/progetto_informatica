#include "spada.h"
#define CONST_LENGTH 100

spada::spada():arma()
{
    char nomeSpada[CONST_LENGTH] = {'S', 'P', 'A', 'D', 'A', '\0'};
    spada::setNomeCompleto(nomeSpada);
    spada::setIcon('S');
    spada::setRange(2);
    spada::setDanniArma(90);
    spada::setExpRichiesti(100);
}
