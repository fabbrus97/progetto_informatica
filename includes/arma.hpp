#ifndef ARMA_H
#define ARMA_H
#include "item.hpp"


class arma : public item
{
protected:
    int range;
    int danniArma;
    int exp_richiesti;
public:
    arma();
    arma(char nome[], int ra, int dam, int exp);
    int getRange();
    int getDanniArma();
    int getExpRichiesti();
    void setDanniArma(int damage);
    void setExpRichiesti(int exp);
    void setRange(int ra);
};

typedef arma* ptr_arma;

#endif // ARMA_H
