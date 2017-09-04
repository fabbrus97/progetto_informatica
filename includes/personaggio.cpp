#include "personaggio.h"
#include "item.h"
#include "coltello.h"
#define CONST_LENGTH 100

personaggio::personaggio():item()
{
    char nomePersonaggio[CONST_LENGTH] = {'U', 'T', 'E', 'N', 'T', 'E', '\0'};
    personaggio::setNomeCompleto(nomePersonaggio);
    coltello armaDiPartenza = coltello();
    personaggio::setArmaInUso(armaDiPartenza);
    personaggio::setIcon('@');
    personaggio::setPuntiVita(300);
    personaggio::setPuntiEsperienza(0);
    personaggio::setAttraversabile(false);
    personaggio::setRaccoglibile(false);
}

int personaggio::getPuntiVita()
{
    return puntiVita;
}

void personaggio::setPuntiVita(int new_puntiVita)
{
    puntiVita = new_puntiVita;
}

int personaggio::getPuntiEsperienza()
{
    return puntiEsperienza;
}

void personaggio::setPuntiEsperienza(int new_puntiEsperienza)
{
    puntiEsperienza = new_puntiEsperienza;
}

arma personaggio::getArmaInUso()
{
    return armaInUso;
}

void personaggio::setArmaInUso(arma new_armaInUso)
{
    armaInUso = new_armaInUso;
}

