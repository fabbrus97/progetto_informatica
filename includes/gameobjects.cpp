//
// Created by Mirko Lancerotto on 05/09/17.
//

#include "gameobjects.hpp"
#include "item.hpp"
#include "arma.hpp"
#include "personaggio.hpp"

//PUNTI MAPPA
ptr_item GameObjects::getNewMuro() {
    return new item(ICON_MURO,false,false,0,"Muro");
}
ptr_item GameObjects::getNewSpazio() {
    return new item(ICON_SPAZIO,false,false,0,"Vuoto");
}
ptr_item GameObjects::getNewPunto() {
    return new item(ICON_PUNTO,true,false,0,"Punto");
}
ptr_item GameObjects::getNewPorta() {
    return new item(ICON_PORTA,false,false,0,"Porta");
}
ptr_item GameObjects::getNewTunnel() {
    return new item(ICON_TUNNEL,false,false,0,"Tunnel");
}
ptr_item GameObjects::getNewLivSucc() {
    return new item(ICON_LIV_SUCC,false,false,0,"Scale Livello Successivo");
}
ptr_item GameObjects::getNewLivPrec() {
    return new item(ICON_LIV_PREC,false,false,0,"Scale Livello Precedente");
}

// ARMI
ptr_arma GameObjects::getNewArmaAnduril() {
    return new arma("Spada di Aragorn",1,5,0); //spada di Aragorn
}
ptr_arma GameObjects::getNewArmaGlamdring() {
    return new arma("Glamdring",1,2,3);
}
ptr_arma GameObjects::getNewArmaPugnaleMorgul() {
    return new arma("Pugnale Morgul",4,5,6);
}

// PERSONAGGI
ptr_personaggio GameObjects::getNewMob() {
    return new personaggio();
}