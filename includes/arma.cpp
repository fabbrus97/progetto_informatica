#include "arma.hpp"
#include "item.hpp"
#include "gameobjects.hpp"

arma::arma(){}

arma::arma(char nome[], int ra, int dam):
    item(ICON_ARMA, false, true, 7, nome,  -1, -1, -1, -1)
{
    range = ra;
    danniArma = dam;
}

int arma::getRange()
{
    return range;
}

int arma::getDanniArma()
{
    return danniArma;
}

void arma::setDanniArma(int damage)
{
    danniArma = damage;
}

void arma::setRange(int ra)
{
    range = ra;
}
