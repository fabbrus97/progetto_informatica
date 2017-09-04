#include "mob3.h"
#include "arco.h"
#define CONST_LENGTH 100

mob3::mob3():mob1()
{
    char nomeMob3[CONST_LENGTH] = {'M', 'O', 'B', '3', '\0'};
    mob1::setNomeCompleto(nomeMob3);
    mob3::setIcon('b');
    mob3::setPuntiVita(320);
    arco bow = arco();
    mob3::setArmaInUso(bow);
}


