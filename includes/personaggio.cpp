#include <cstdio>
#include "personaggio.hpp"
#include "gameobjects.hpp"
#define CONST_LENGTH 100

personaggio::personaggio() {
    icon = ICON_MOB;
    setNomeCompleto("Mob");
    puntiEsperienza = 0;
    puntiVita = 100;
    armaInUso = NULL;
}

personaggio::personaggio(char icon, char nome[], int pExp, int pVita, arma *inUso)
        :item(icon, false, false, 7, nome, -1, -1, -1, -1) {
    puntiEsperienza = pExp;
    puntiVita = pVita;
    armaInUso = inUso;
}

personaggio::~personaggio() {
    delete armaInUso;
}

int personaggio::getPuntiVita() {
    return puntiVita;
}

void personaggio::setPuntiVita(int new_puntiVita) {
    puntiVita = new_puntiVita;
}

int personaggio::getPuntiEsperienza() {
    return puntiEsperienza;
}

void personaggio::setPuntiEsperienza(int new_puntiEsperienza) {
    puntiEsperienza = new_puntiEsperienza;
}

arma *personaggio::getArmaInUso() {
    return armaInUso;
}

void personaggio::setArmaInUso(arma *new_armaInUso) {
    armaInUso = new_armaInUso;
}

// TODO
report_movimento personaggio::muovi(int direzione) {
    report_movimento rm;
    rm.itemScontrato = NULL;
    rm.riuscito = false;
    return rm;
}

// TODO
report_attacco personaggio::attacca(int direzione) {
    report_attacco ra;
    ra.colpito = false;
    ra.pgColpito = NULL;
    ra.danniInflitti = 0;
    return ra;
}
