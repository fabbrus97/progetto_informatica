#include "personaggio.hpp"
#define CONST_LENGTH 100

personaggio::personaggio(char icon, char nome[], int pExp, int pVita, arma inUso)
        :item(icon, false, false, 7, nome, -1, -1, -1, -1){
    puntiEsperienza = pExp;
    puntiVita = pVita;
    armaInUso = inUso;
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

