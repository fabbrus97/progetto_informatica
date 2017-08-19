#include "mob2.h"
#include "spada.h"
#define CONST_LENGTH 100

mob2::mob2():mob1()
{
    char nomeMob2[CONST_LENGTH] = {'M', 'O', 'B', '2', '\0'};
    mob1::setNomeCompleto(nomeMob2);
    mob2::setIcon('o');
    mob2::setPuntiVita(220);
    spada sword = spada();
    mob2::setArmaInUso(sword);
}

