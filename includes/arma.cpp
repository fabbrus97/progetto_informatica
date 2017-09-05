#include "arma.hpp"
#include "item.hpp"
#include "gameobjects.hpp"

arma::arma(){}

arma::arma(char nome[], int ra, int dam, int exp):
    item(ICON_ARMA, true, true, 7, nome,  -1, -1, -1, -1)
{
    range = ra;
    danniArma = dam;
    exp_richiesti = exp;
}

int arma::getRange()
{
    return range;
}

int arma::getDanniArma()
{
    return danniArma;
}

int arma::getExpRichiesti()
{
    return exp_richiesti;
}

void arma::setDanniArma(int damage)
{
    danniArma = damage;
}

void arma::setExpRichiesti(int exp)
{
    exp_richiesti = exp;
}

void arma::setRange(int ra)
{
    range = ra;
}
