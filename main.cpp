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
    mappa* mappa;
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
bool confermaRaccoltaItem(item *it);
void getGiocatoreInputs(int *direzione, bool *attacca, bool *muovi);
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

    // TODO : Posizionare il giocatore nel livello
    //livelloCorrente->mappa->find_first(0)->;

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
            // TODO : Posizionare il giocatore nel livello
        } else {
            if(livelloCorrente->prev != NULL) {
                livelloCorrente = livelloCorrente->prev;
                // TODO : Posizionare il giocatore nel livello
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
    int direzione;
    bool attacca;
    bool muovi;

    cout << "É il tuo turno.\n";

    getGiocatoreInputs(&direzione,&attacca,&muovi);

    if(attacca) {
        if(giocatore->getArmaInUso() == NULL){
            cout << "Prima di attaccare dovrei raccogliere un'arma\n";
        } else {
            report_attacco ra = giocatore->attacca(direzione);
            if(ra.pgColpito == NULL) {
                cout << "Hai attaccato a vuoto\n";
            } else {
                char nomeAttaccato[MAX_NOME_COMPLETO_LENGTH];
                ra.pgColpito->getNomeCompleto(nomeAttaccato);
                cout << "Hai inflitto'" << ra.danniInflitti << " danni a '" << nomeAttaccato << "'\n";
            }
        }

        // TODO : report di attacco
    } else if(muovi) {
        report_movimento rm = giocatore->muovi(direzione);
        if(rm.riuscito == true) {
            cout << "Ti sei mosso\n";
        } else {
            if(rm.itemScontrato != NULL) {
                if(rm.itemScontrato->getRaccoglibile()) {
                    if( confermaRaccoltaItem(rm.itemScontrato)
                    &&  giocatore->raccogli(rm.itemScontrato)
                    ){
                        giocatore->muovi(direzione);
                        // TODO : mettere a posto il report di raccolta
                        cout << "Hai raccolto...stocazzo\n";
                    } else {
                        cout << "Non sei riuscito a raccogliere l'oggetto\n";
                    }
                } else {
                    switch (rm.itemScontrato->getIcon()) {
                        case ICON_LIV_SUCC:
                            return 1;
                        case ICON_LIV_PREC:
                            return -1;
                        case ICON_PORTA:
                            // TODO : Segui la porta
                            break;
                    }
                }
            }
        }
    }
    return 0;
}

bool confermaRaccoltaItem(item *it) {
    char inConferma;
    bool input_error;
    bool conferma;
    do {
        input_error = false;
        cout<< "Sei sicuro di volere raccogliere questo oggetto?(y/n): ";
        cin >> inConferma;
        switch(inConferma) {
            case 'y':
            case 'Y':
                conferma = true;
                break;
            case 'n':
            case 'N':
                conferma = false;
                break;
            default:
                input_error=true;
                cout << "Comando sconosciuto\n";
        }
    } while(input_error);
    return conferma;
}

void getGiocatoreInputs(int *direzione, bool *attacca, bool *muovi) {
    char inAzione, inDirezione;
    bool input_error;

    do {
        *attacca = false;
        *muovi = false;
        input_error = false;

        cout << "(a) per attaccare (m) per muoverti: ";
        cin >> inAzione;

        switch (inAzione) {
            case 'a':
            case 'A':
                *attacca = true;
                break;
            case 'm':
            case 'M':
                *muovi = true;
                break;
            default:
                input_error = true;
                cout << "Azione non consentita\n";
        }
    } while(input_error);

    do {
        input_error = false;
        cout << "Direzione (wasd): ";
        cin >> inDirezione;

        switch (inDirezione) {
            case 'w':
                *direzione = DIREZIONE_SU;
                break;
            case 'a':
                *direzione = DIREZIONE_SINISTRA;
                break;
            case 's':
                *direzione = DIREZIONE_GIU;
                break;
            case 'd':
                *direzione = DIREZIONE_DESTRA;
                break;
            default:
                input_error = true;
                cout << "Direzione inesistente\n";
        }
    } while(input_error);
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
        report_attacco ra;
        if (dxx < 0)
            ra = m->attacca(DIREZIONE_SINISTRA);
        else if (dxx > 0)
            ra = m->attacca(DIREZIONE_DESTRA);
        else if (dyy < 0)
            ra = m->attacca(DIREZIONE_SU);
        else if(dyy > 0)
            ra = m->attacca(DIREZIONE_GIU);

        if(ra.colpito == true && ra.pgColpito == g) {
            char nomeAttaccato[MAX_NOME_COMPLETO_LENGTH];
            m->getNomeCompleto(nomeAttaccato);
            cout << "'" << nomeAttaccato << "' ti ha inflitto" << ra.danniInflitti << " danni\n";
        }

    // Altrimenti si muove verso di lui
    } else {
        report_movimento rm;
        //in questo modo si muove a "zig zag" verso il giocatore
        //NB il mob non sa cambiare stanza/livello e nemmeno attraversare gli ostacoli
        if(absDxx > absDyy) {
            if (dxx < 0)
                rm = m->muovi(DIREZIONE_SINISTRA);
            else
                rm = m->muovi(DIREZIONE_DESTRA);
        } else {
            if (dyy < 0)
                rm = m->muovi(DIREZIONE_SU);
            else
                rm = m->muovi(DIREZIONE_GIU);
        }
    }
}