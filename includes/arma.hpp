#ifndef ARMA_H
#define ARMA_H
#include "item.hpp"


class arma : public item
{
protected:
    int range;
    int danniArma;
public:
    arma();
    arma(char nome[], int ra, int dam);
    int getRange();
    int getDanniArma();
    void setDanniArma(int damage);
    void setRange(int ra);
};

typedef arma* ptr_arma;

#endif // ARMA_H
