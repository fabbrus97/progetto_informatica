//
// Created by Mirko Lancerotto on 05/09/17.
//

#include "gameobjects.hpp"
#include "item.hpp"
#include "arma.hpp"
#include "personaggio.hpp"

//PUNTI MAPPA
ptr_item GameObjects::getNewMuro() {
    return new item(ICON_MURO,false,false);
}
ptr_item GameObjects::getNewSpazio() {
    return new item(ICON_SPAZIO,false,false);
}
ptr_item GameObjects::getNewPunto() {
    return new item(ICON_PUNTO,true,false);
}
ptr_item GameObjects::getNewPorta() {
    return new item(ICON_PORTA,true,false);
}
ptr_item GameObjects::getNewTunnel() {
    return new item(ICON_TUNNEL,false,false);
}
ptr_item GameObjects::getNewLivSucc() {
    return new item(ICON_LIV_SUCC,true,false);
}
ptr_item GameObjects::getNewLivPrec() {
    return new item(ICON_LIV_PREC,true,false);
}

// ARMI
ptr_arma GameObjects::getNewArmaAnduril() {
    return new arma(1,5,0); //spada di Aragorn
}
ptr_arma GameObjects::getNewArmaGlamdring() {
    return new arma(1,2,3);
}
ptr_arma GameObjects::getNewArmaPugnaleMorgul() {
    return new arma(4,5,6);
}

// PERSONAGGI