#include "arma.h"
#include "item.h"


arma::arma():item()
{
    arma::setAttraversabile(true);
    arma::setRaccoglibile(true);
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
