#include <cstdio>
#include "personaggio.hpp"
#include "gameobjects.hpp"
#include "../mappa.hpp" //questo inclune forse è da spostare
#define CONST_LENGTH 100

personaggio::personaggio()
    :item(ICON_MOB, false, false)
{
    setNomeCompleto("Mob");
    maxPuntiVita = 100;
    setPuntiVita(maxPuntiVita);
    armaInUso = NULL;

    setDifesa(0);
    setAttacco(0);
}

personaggio::personaggio(char icon, char nome[], int pExp, int pVita, arma *inUso)
        :item(icon, false, false, 7, nome, -1, -1, -1, -1) {
    setPuntiVita(pVita);
    armaInUso = inUso;

    setDifesa(0);
    setAttacco(0);
}

personaggio::~personaggio() {
    if(armaInUso != NULL)
        delete armaInUso;
}

int personaggio::getPuntiVita() {
    return puntiVita;
}

void personaggio::setPuntiVita(int new_puntiVita) {
    if(new_puntiVita > maxPuntiVita)
        puntiVita = maxPuntiVita;
    else if(new_puntiVita < 0)
        puntiVita = 0;
    else
        puntiVita = new_puntiVita;
}

int personaggio::getMaxPuntiVita() {
    return maxPuntiVita;
}
void personaggio::setMaxPuntiVita (int new_maxPuntiVita) {
    maxPuntiVita = new_maxPuntiVita;
    setPuntiVita(maxPuntiVita);
}

int personaggio::getAttacco() {
    return attacco;
}
void personaggio::setAttacco(int a) {
    attacco = a;
}
void personaggio::incAttacco() {
    attacco++;
}
int personaggio::getDifesa() {
    return difesa;
}
void personaggio::setDifesa(int d) {
    difesa = d;
}
void personaggio::incDifesa() {
    difesa++;
}

arma *personaggio::getArmaInUso() {
    return armaInUso;
}

void personaggio::setArmaInUso(arma *new_armaInUso) {
    if(armaInUso != NULL) {
        delete armaInUso;
    }
    armaInUso = new_armaInUso;
}

/*
 * Il personaggio prova a muoversi di una casella nella direzione scelta:
 * Se l'item presente nella casella in cui il personaggio sta tentando di
 * spostarsi é attraversabile allora l'item verrá eliminato dalla memoria
 * mentre il personaggio assumerá la sua posizione grazie a mappa::sposta(this, item nella posizione)
 * ed il report sará:
 * {
 *  itemScontrato = NULL
 *  riuscito = true
 * }
 * Se l'item non é attraversabile il personaggio rimarrá dov'é ed il report sará:
 * {
 *  itemScontrato = oggettoItem
 *  riuscito = false
 * }
 *
 * Il chiamante si preoccuperá di capire se l'item é raccoglibile o meno, e nel caso raccoglierlo e quindi
 * riprovare di spostarsi nella stessa direzione.
 */
report_movimento personaggio::muovi(mappa *map, int direzione) {
    report_movimento rm;
    rm.itemScontrato = NULL;
    rm.riuscito = false;

    int x=getPositionX();
    int y=getPositionY();
    int xx=getPositionXX();
    int yy=getPositionYY();

    switch(direzione){
        case DIREZIONE_SU:
            if (map->p[y][x]->punti_stanza[yy-1][xx]->getAttraversabile()) {
                map->sposta(this, map->p[y][x]->punti_stanza[yy - 1][xx]);
                rm.riuscito = true;
            }
            else {
                rm.itemScontrato = map->p[y][x]->punti_stanza[yy-1][xx];
            }
            break;
        case DIREZIONE_GIU:
            if (map->p[y][x]->punti_stanza[yy+1][xx]->getAttraversabile()) {
                map->sposta(this, map->p[y][x]->punti_stanza[yy + 1][xx]);
                rm.riuscito = true;
            }
            else {
                rm.itemScontrato = map->p[y][x]->punti_stanza[yy+1][xx];
            }
            break;
        case DIREZIONE_SINISTRA:
            if (map->p[y][x]->punti_stanza[yy][xx-1]->getAttraversabile()) {
                map->sposta(this, map->p[y][x]->punti_stanza[yy][xx-1]);
                rm.riuscito = true;
            }
            else {
                rm.itemScontrato = map->p[y][x]->punti_stanza[yy][xx-1];
            }
            break;
        case DIREZIONE_DESTRA:
            if (map->p[y][x]->punti_stanza[yy][xx+1]->getAttraversabile()) {
                map->sposta(this, map->p[y][x]->punti_stanza[yy][xx+1]);
                rm.riuscito = true;
            }
            else {
                rm.itemScontrato = map->p[y][x]->punti_stanza[yy][xx+1];
            }
            break;
    }

    return rm;
}

/*
 * Data la gittata dell'arma attualmente in uso il personaggio tenta di attaccare nella scelta
 * colpendo solo il personaggio piú vicino che rientra nella gittata.
 * Quindi evoca il metodo personaggio::infliggi(int danno) del personaggio colpito
 *
 */

report_attacco personaggio::attacca(mappa *map, int direzione) {
    int coorXX = getPositionXX();
    int coorYY = getPositionYY();
    int coorX = getPositionX();
    int coorY = getPositionY();
    int currentYY = coorYY;
    int currentXX = coorXX;
    report_attacco ra;

    ptr_item puntatore = this;

    ra.colpito = false;
    ra.pgColpito = NULL;
    ra.danniInflitti = 0;

    if(getArmaInUso() == NULL)
        return ra;

    int dannoTotale = getArmaInUso()->getDanniArma() + attacco;
    dannoTotale = dannoTotale + dannoTotale*(rand()%20)/100;

    if (direzione == DIREZIONE_GIU)
    {
        while (!ra.colpito && currentYY < (MAX_RIGHE - 2 ))
        {
            if (puntatore != this && (puntatore->getIcon() == ICON_MOB || puntatore->getIcon() == ICON_GIOCATORE))
            {
                if (fabs(getPositionYY() - puntatore->getPositionYY()) <= getArmaInUso()->getRange())
                {
                    ra.pgColpito = (personaggio *)puntatore;
                    ra.colpito = true;
                    ra.danniInflitti = ra.pgColpito->infliggi(dannoTotale);
                } else {
                    return ra;
                }
            }
            else
            {
                currentYY = currentYY + 1;
                puntatore = map->p[coorY][coorX]->punti_stanza[currentYY][coorXX];
            }
        }
    }
    else if (direzione == DIREZIONE_DESTRA)
    {
        while (!ra.colpito && currentXX < (MAX_COLONNE - 2))
        {
            if (puntatore != this && (puntatore->getIcon() == ICON_MOB || puntatore->getIcon() == ICON_GIOCATORE))
            {
                if (fabs(getPositionXX() - puntatore->getPositionXX()) <= getArmaInUso()->getRange())
                {
                    ra.pgColpito = (personaggio *) puntatore;
                    ra.colpito = true;
                    ra.danniInflitti = ra.pgColpito->infliggi(dannoTotale);
                } else {
                    return ra;
                }
            }
            else
            {
                currentXX = currentXX + 1;
                puntatore = map->p[coorY][coorX]->punti_stanza[coorYY][currentXX];
            }
        }
    }
    else if (direzione == DIREZIONE_SU)
    {
        while (!ra.colpito && currentYY > 0)
        {
            if (puntatore != this && (puntatore->getIcon() == ICON_MOB || puntatore->getIcon() == ICON_GIOCATORE))
            {
                if (fabs(getPositionYY() - puntatore->getPositionYY()) <= getArmaInUso()->getRange())
                {
                    ra.pgColpito = (personaggio *)puntatore;
                    ra.colpito = true;
                    ra.danniInflitti = ra.pgColpito->infliggi(dannoTotale);
                } else {
                    return ra;
                }
            }
            else
            {
                currentYY = currentYY - 1;
                puntatore = map->p[coorY][coorX]->punti_stanza[currentYY][coorXX];
            }
        }
    }
    else if (direzione == DIREZIONE_SINISTRA)
    {
        while (!ra.colpito && currentXX > 0)
        {
            if (puntatore != this && (puntatore->getIcon() == ICON_MOB || puntatore->getIcon() == ICON_GIOCATORE))
            {
                if (fabs(getPositionXX() - puntatore->getPositionXX()) <= getArmaInUso()->getRange())
                {
                    ra.pgColpito = (personaggio *) puntatore;
                    ra.colpito = true;
                    ra.danniInflitti = ra.pgColpito->infliggi(dannoTotale);
                } else {
                    return ra;
                }
            }
            else
            {
                currentXX = currentXX - 1;
                puntatore = map->p[coorY][coorX]->punti_stanza[coorYY][currentXX];
            }
        }
    }
    return ra;
}

/*
 * raccoglie l'arma 'daRaccogliere' che si trova posizionata nella mappa 'map'
 * quindi la sostituisce a quella correntemente usata dal personaggio
 *
 * ritorna true o false nel caso sia rispettivamente riuscito o meno
 * a raccogliere l'oggetto
 */
bool personaggio::raccogliArma(mappa *map, arma *daRaccogliere) {
    if( daRaccogliere == NULL
    ||  map == NULL
    ) {
        return false;
    }

    int x = daRaccogliere->getPositionX();
    int y = daRaccogliere->getPositionY();
    int xx = daRaccogliere->getPositionXX();
    int yy = daRaccogliere->getPositionYY();

    if(map->p[y][x]->punti_stanza[yy][xx] == daRaccogliere) {
        map->esci(daRaccogliere);
        setArmaInUso(daRaccogliere);
        return true;
    }

    return false;
}

/*
 * Questo metodo viene invocato per infliggere danno al personaggio corrente.
 * L'uso di un metodo apposito per questa funzione rende possibile l'eventuale implementazione
 * di metodi per diminuire il danno subito secondo caratteristiche specifiche del personaggio.
 * Per esempio, ponendo il caso che tutti i personaggi abbiano un valore di 'difesa', e che il danno
 * effettivamente inflitto sia pari a ('puntiVitaMax'*'Danno')/('PuntiVitaMax'+'Difesa')
 * Allora un personaggio con
 * PuntiVitaMax = 100
 * Difesa = 10
 * nel caso venisse attaccato con 25 danni, al posto di 25 ne subirebbe effettivamente:
 * 100*25 / (100+10) = 2500 / 110 = 22
 *
 * La funzione ritorna il danno effettivamente inflitto (al momento pari a 'danno')
 */
int personaggio::infliggi(int danno) {
    int dannoEffettivo = maxPuntiVita * danno / (maxPuntiVita + difesa);
    setPuntiVita(
        getPuntiVita() - dannoEffettivo
    );

    return dannoEffettivo;
}