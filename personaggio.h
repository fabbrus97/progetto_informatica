#ifndef PERSONAGGIO_H
#define PERSONAGGIO_H
#include "item.h"
#include "arma.h"

class personaggio : public item
{
protected:
    int puntiEsperienza;
    int puntiVita;
    arma armaInUso;

public:
    personaggio(int pExp, int pVita, arma inUso);
    int getPuntiVita();
    void setPuntiVita (int new_puntiVita);
    int getPuntiEsperienza();
    void setPuntiEsperienza(int new_puntiEsperienza);
    arma getArmaInUso();
    void setArmaInUso(arma new_armaInUso);
    personaggio attacca(); //da fare
    arma raccogli(); //da fare
};

#endif // PERSONAGGIO_H
