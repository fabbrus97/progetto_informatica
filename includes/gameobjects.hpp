//
// Created by Mirko Lancerotto on 05/09/17.
//

#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "item.hpp"
#include "arma.hpp"
#include "personaggio.hpp"

#define ICON_MURO '#'
#define ICON_SPAZIO ' '
#define ICON_PUNTO '.'
#define ICON_PORTA '+'
#define ICON_TUNNEL 'x'
#define ICON_LIV_SUCC '>'
#define ICON_LIV_PREC '<'

#define ICON_GIOCATORE 'G'
#define ICON_MOB 'm'

#define ICON_ARMA 'w'

class GameObjects {
public:
    static ptr_item getNewMuro();
    static ptr_item getNewSpazio();
    static ptr_item getNewPunto();
    static ptr_item getNewPorta();
    static ptr_item getNewTunnel();
    static ptr_item getNewLivSucc();
    static ptr_item getNewLivPrec();

    static ptr_arma getNewArcoDiOssa();
    static ptr_arma getNewCatene();
    static ptr_arma getNewSpadaScaltra();
    static ptr_arma getNewAsciaGigante();

    static ptr_arma getNewSpadaRotta();
    static ptr_arma getNewSpadaAnduril();
    static ptr_arma getNewSpadaGlamdring();
    static ptr_arma getNewArmaPugnaleMorgul();
    static ptr_arma getNewArcoDorato();

    static ptr_personaggio getNewMaialeZombie();
    static ptr_personaggio getNewScheletroDiZurgul();
    static ptr_personaggio getNewZurgulIncatenato();
    static ptr_personaggio getNewDemoneSpadaccino();
    static ptr_personaggio getNewGiganteDelleAnde();
};
#endif
