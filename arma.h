#ifndef ARMA_H
#define ARMA_H
#include <item.h>


class arma : public item
{
protected:
    int range;
    int danniArma;
    int exp_richiesti;
public:
    arma();
    int getRange();
    int getDanniArma();
    int getExpRichiesti();
    void setDanniArma(int damage);
    void setExpRichiesti(int exp);
    void setRange(int ra);
};

#endif // ARMA_H
