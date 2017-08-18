#include "coltello.h"
#define CONST_LENGTH 100

coltello::coltello():arma()
{
    char nomeColtello[CONST_LENGTH] = {'C', 'O', 'L', 'T', 'E', 'L', 'L', 'O', '\0'};
    coltello::setNomeCompleto(nomeColtello);
    coltello::setIcon('C');
    coltello::setDanniArma(40);
    coltello::setExpRichiesti(0);
    coltello::setRange(1);
}

