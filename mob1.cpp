#include "mob1.h"
#include "coltello.h"
#define CONST_LENGTH 100

mob1::mob1():personaggio()
{
    char nomeMob1[CONST_LENGTH] = {'M', 'O', 'B', '1', '\0'};
    mob1::setNomeCompleto(nomeMob1);
    mob1::setIcon('m');
    mob1::setPuntiVita(120);
    coltello knife = coltello();
    mob1::setArmaInUso(knife);
}


