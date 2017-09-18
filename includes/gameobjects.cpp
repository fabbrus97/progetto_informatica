//
// Created by Mirko Lancerotto on 05/09/17.
//

#include "gameobjects.hpp"
#include "item.hpp"
#include "arma.hpp"
#include "personaggio.hpp"

//PUNTI MAPPA
ptr_item GameObjects::getNewMuro() {
    return new item(ICON_MURO,false,false,"Muro");
}
ptr_item GameObjects::getNewSpazio() {
    return new item(ICON_SPAZIO,false,false,"Vuoto");
}
ptr_item GameObjects::getNewPunto() {
    return new item(ICON_PUNTO,true,false,"Punto");
}
ptr_item GameObjects::getNewPorta() {
    return new item(ICON_PORTA,false,false,"Porta");
}
ptr_item GameObjects::getNewTunnel() {
    return new item(ICON_TUNNEL,false,false,"Tunnel");
}
ptr_item GameObjects::getNewLivSucc() {
    return new item(ICON_LIV_SUCC,false,false,"Scale Livello Successivo");
}
ptr_item GameObjects::getNewLivPrec() {
    return new item(ICON_LIV_PREC,false,false,"Scale Livello Precedente");
}

// ARMI
ptr_arma GameObjects::getNewArcoDiOssa() {
    return new arma("Arco di Ossa",5,3);
}
ptr_arma GameObjects::getNewCatene() {
    return new arma("Catene",3,5);
}
ptr_arma GameObjects::getNewSpadaScaltra() {
    return new arma("Spada Scaltra",1,8);
}
ptr_arma GameObjects::getNewAsciaGigante() {
    return new arma("Ascia Gigante",2,11);
}


ptr_arma GameObjects::getNewSpadaRotta() {
    return new arma("Spada rotta",1,6);
}
ptr_arma GameObjects::getNewSpadaAnduril() {
    return new arma("Spada Anduril",1,13);
}
ptr_arma GameObjects::getNewSpadaGlamdring() {
    return new arma("Spada Glamdring",2,17);
}
ptr_arma GameObjects::getNewArmaPugnaleMorgul(){
    return new arma("Spada Anduril",1,22);
}
ptr_arma GameObjects::getNewArcoDorato() {
    return new arma("Spada Anduril",7,31);
}


// PERSONAGGI

ptr_personaggio GameObjects::getNewMaialeZombie() {
    ptr_personaggio mob = new personaggio();
    mob->setNomeCompleto("Maiale zombie");
    mob->setArmaInUso(GameObjects::getNewSpadaRotta());
    mob->setAttacco(rand()%3);
    mob->setDifesa(rand()%3);
    mob->setMaxPuntiVita(15);
    return mob;
}
ptr_personaggio GameObjects::getNewScheletroDiZurgul() {
    ptr_personaggio mob = new personaggio();
    mob->setNomeCompleto("Scheletro di Zurgul");
    mob->setArmaInUso(GameObjects::getNewArcoDiOssa());
    mob->setAttacco(1+ rand()%5);
    mob->setDifesa(1+ rand()%5);
    mob->setMaxPuntiVita(23);
    return mob;
}
ptr_personaggio GameObjects::getNewZurgulIncatenato() {
    ptr_personaggio mob = new personaggio();
    mob->setNomeCompleto("Zurgul incatenato");
    mob->setArmaInUso(GameObjects::getNewCatene());
    mob->setAttacco(3+ (rand()%6));
    mob->setDifesa(3+ (rand()%6));
    mob->setMaxPuntiVita(35);
    return mob;
}
ptr_personaggio GameObjects::getNewDemoneSpadaccino() {
    ptr_personaggio mob = new personaggio();
    mob->setNomeCompleto("Demone spadaccino");
    mob->setArmaInUso(GameObjects::getNewSpadaScaltra());
    mob->setAttacco(5+ (rand()%8));
    mob->setDifesa(5+ (rand()%8));
    mob->setMaxPuntiVita(42);
    return mob;
}
ptr_personaggio GameObjects::getNewGiganteDelleAnde() {
    ptr_personaggio mob = new personaggio();
    mob->setNomeCompleto("Gigante delle Ande");
    mob->setArmaInUso(GameObjects::getNewAsciaGigante());
    mob->setAttacco(8 + (rand() % 10));
    mob->setDifesa(8 + (rand() % 10));
    mob->setMaxPuntiVita(57);
    return mob;
}