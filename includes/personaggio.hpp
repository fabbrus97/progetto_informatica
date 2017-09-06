#ifndef PERSONAGGIO_H
#define PERSONAGGIO_H
#include "item.hpp"
#include "arma.hpp"

class personaggio : public item
{
protected:
    int puntiEsperienza;
    int puntiVita;
    arma *armaInUso;

public:
    personaggio();
    personaggio(char icon, char nome[], int pExp, int pVita, arma *inUso);
    int getPuntiVita();
    void setPuntiVita (int new_puntiVita);
    int getPuntiEsperienza();
    void setPuntiEsperienza(int new_puntiEsperienza);
    arma *getArmaInUso();
    void setArmaInUso(arma new_armaInUso);
    personaggio attacca(); //da fare
    arma *raccogli(); //da fare
};

typedef personaggio* ptr_personaggio;
#endif // PERSONAGGIO_H
