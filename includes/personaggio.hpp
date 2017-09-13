#ifndef PERSONAGGIO_H
#define PERSONAGGIO_H
#include "item.hpp"
#include "arma.hpp"
#include "../mappa.hpp"

#define DIREZIONE_SU 0
#define DIREZIONE_SINISTRA 1
#define DIREZIONE_DESTRA 3
#define DIREZIONE_GIU 4

#define MAX_PUNTI_VITA 100

class personaggio;

struct report_attacco {
    bool colpito;
    personaggio *pgColpito;
    int danniInflitti;
};

struct report_movimento {
    bool riuscito;
    item *itemScontrato;
};

class personaggio : public item {
protected:
    int puntiEsperienza;
    int puntiVita;
    int difesa;
    int attacco;
    arma *armaInUso;

public:
    personaggio();
    personaggio(char icon, char nome[], int pExp, int pVita, arma *inUso);
    ~personaggio();
    int getPuntiVita();
    void setPuntiVita (int new_puntiVita);
    int getPuntiEsperienza();
    void setPuntiEsperienza(int new_puntiEsperienza);
    int getAttacco();
    void setAttacco(int a);
    void incAttacco();
    int getDifesa();
    void setDifesa(int d);
    void incDifesa();
    arma *getArmaInUso();
    void setArmaInUso(arma *new_armaInUso);
    report_attacco attacca(mappa *map, int direzione); //da fare
    report_movimento muovi(mappa *map, int direzione);
    bool raccogliArma(mappa *map, arma *daRaccogliere);
    int infliggi(int danno); //da fare
};

typedef personaggio* ptr_personaggio;
#endif // PERSONAGGIO_H
