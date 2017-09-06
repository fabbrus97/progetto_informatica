#include <iostream>
#include <math.h>
#include "mappa.hpp"
#include "includes/gameobjects.hpp"
#include "includes/personaggio.hpp"

//
#define MAX_MOBS_X_LIV 70
#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)

using namespace std;

struct livello{
    mappa *mappa;
    ptr_personaggio mobs[MAX_MOBS_X_LIV];
    int n_mobs; //numero di mob presenti nel livello
    int liv; //numero del livello da 1 a +inf
    livello *prev;
    livello * next;
};

void init_giocatore(personaggio *);
void game_loop(personaggio *);
livello *getNewLivello(int l);
int turnoGiocatore(personaggio *giocatore, livello *livelloCorrente);
void turnoDeiMob(personaggio *giocatore, livello *livelloCorrente);
void IAMob(personaggio *mob, personaggio *giocatore);

int main() {
    personaggio giocatore;
    init_giocatore(&giocatore);
    game_loop(&giocatore);


    return 0;
}

void init_giocatore(personaggio *giocatore) {

    char nome[64];
    cout << "Come ti chiami?\n";
    cin >> nome;
    giocatore->setNomeCompleto(nome);

    giocatore->setIcon(ICON_GIOCATORE);
}

void game_loop(personaggio *giocatore) {
    bool end = false;
    livello *primoLivello = getNewLivello(1);
    livello *livelloCorrente = primoLivello;

    while(!end) {
        livelloCorrente->mappa->print_map();
        int cambioLiv = turnoGiocatore(giocatore,livelloCorrente);

        if(cambioLiv == 0) {
            turnoDeiMob(giocatore,livelloCorrente);
        } else if(cambioLiv > 0) {
            if(livelloCorrente->next == NULL) {
                livello *nuovoLivello = getNewLivello( 1 + livelloCorrente->liv );
                livelloCorrente->next = nuovoLivello;
                nuovoLivello->prev = livelloCorrente;
            }
            livelloCorrente = livelloCorrente->next;
        } else {
            if(livelloCorrente->prev != NULL) {
                livelloCorrente = livelloCorrente->prev;
            }
        }

    }
}

livello *getNewLivello(int l) {
    livello *liv;

    liv = new livello;
    liv->prev = NULL;
    liv->next = NULL;

    liv->mappa = new mappa(l);
    liv->mappa->generate_map();

    liv->n_mobs = MIN( 10*log(1+l), MAX_MOBS_X_LIV);

    for(int i=0; i<liv->n_mobs; i++) {
        liv->mobs[i] = GameObjects::getNewMob();
    }

    //TODO: posiziona i mob

    return liv;
}

// se <0 scendo di 1 livello
// se == 0 mantendo il livello corrente
// se >0 salgo di 1 livello
int turnoGiocatore(personaggio *giocatore, livello *livelloCorrente) {
    char in;
    cout << "É il tuo turno.\n";
    cin >> in;
    //turno del giocatore
    //choose what to do (a=>attacca m=>move)
}

void turnoDeiMob(personaggio *giocatore, livello *livelloCorrente) {
    for(int t=0; t<livelloCorrente->n_mobs; t++){
        if( livelloCorrente->mobs[t]->getPositionX() == giocatore->getPositionX()
        &&  livelloCorrente->mobs[t]->getPositionY() == giocatore->getPositionY()
        ) {
            //Muove il Mob solo se é nella stessa stanza del giocatore
            IAMob(livelloCorrente->mobs[t], giocatore);
        }
    }
}

void IAMob(personaggio *m, personaggio *g) {
    int dxx = g->getPositionXX() - m->getPositionXX();
    int dyy = g->getPositionYY() - m->getPositionYY();
    int absDxx = abs(dxx);
    int absDyy = abs(dyy);

    if(m->getArmaInUso() == NULL)
        return;

    // Se il giocatore é nel range di attacco del mob, allora il mob lo attacca
    if( m->getPositionXX() == g->getPositionXX() && m->getArmaInUso()->getRange() >= absDyy
    &&  m->getPositionYY() == g->getPositionYY() && m->getArmaInUso()->getRange() >= absDxx
    ) {
        if (dxx < 0)
            m->attacca(DIREZIONE_SINISTRA);
        else if (dxx > 0)
            m->attacca(DIREZIONE_DESTRA);
        else if (dyy < 0)
            m->attacca(DIREZIONE_SU);
        else if(dyy > 0)
            m->attacca(DIREZIONE_GIU);

    // Altrimenti si muove verso di lui
    } else {

    }
}