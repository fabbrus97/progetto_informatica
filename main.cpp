#include <iostream>
#include <math.h>
#include "mappa.hpp"
#include "includes/gameobjects.hpp"
#include "includes/personaggio.hpp"
#include "termcolor.hpp"

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
bool confermaRaccoltaArma(personaggio *giocatore, arma *it);
void getGiocatoreInputs(int *direzione, bool *attacca, bool *muovi);
void turnoDeiMob(personaggio *giocatore, livello *livelloCorrente);
void IAMob(personaggio *mob, personaggio *giocatore, livello *livelloCorrente);
void print_map(mappa *map);

void stampaSchedaPersonaggio(personaggio *giocatore);

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
    giocatore->setArmaInUso(GameObjects::getNewSpadaRotta());

    giocatore->setIcon(ICON_GIOCATORE);
}

void game_loop(personaggio *giocatore) {
    bool end = false;
    livello *primoLivello = getNewLivello(1);
    livello *livelloCorrente = primoLivello;

    // TODO : Posizionare il giocatore nel livello
    livelloCorrente->mappa->posiziona(
        giocatore,
        livelloCorrente->mappa->entrata.x,
        livelloCorrente->mappa->entrata.y,
        livelloCorrente->mappa->entrata.xx,
        livelloCorrente->mappa->entrata.yy
    );

    while(!end) {
        cout << "Mappa livello " << livelloCorrente->liv << "\n";
        print_map(livelloCorrente->mappa);
        stampaSchedaPersonaggio(giocatore);
        cout << "\n";

        int cambioLiv = turnoGiocatore(giocatore,livelloCorrente);

        if(cambioLiv == 0) {
            turnoDeiMob(giocatore,livelloCorrente);
        } else if(cambioLiv > 0) {
            livelloCorrente->mappa->esci(giocatore);
            if(livelloCorrente->next == NULL) {
                livello *nuovoLivello = getNewLivello( 1 + livelloCorrente->liv );
                livelloCorrente->next = nuovoLivello;
                nuovoLivello->prev = livelloCorrente;
            }
            livelloCorrente = livelloCorrente->next;
            livelloCorrente->mappa->posiziona(
                giocatore,
                livelloCorrente->mappa->entrata.x,
                livelloCorrente->mappa->entrata.y,
                livelloCorrente->mappa->entrata.xx,
                livelloCorrente->mappa->entrata.yy
            );
            cout << "Sei salito al livello " << livelloCorrente->liv << "\n";
        } else {
            if(livelloCorrente->prev != NULL) {
                livelloCorrente->mappa->esci(giocatore);
                livelloCorrente = livelloCorrente->prev;
                livelloCorrente->mappa->posiziona(
                    giocatore,
                    livelloCorrente->mappa->uscita.x,
                    livelloCorrente->mappa->uscita.y,
                    livelloCorrente->mappa->uscita.xx,
                    livelloCorrente->mappa->uscita.yy
                );
                cout << "Sei sceso al livello " << livelloCorrente->liv << "\n";
            }
        }
        cout << "\n";
    }
}

livello *getNewLivello(int l) {
    livello *liv;

    liv = new livello;
    liv->prev = NULL;
    liv->next = NULL;
    liv->liv = l;

    liv->mappa = new mappa( 2.8*log(1+l) );
    liv->mappa->generate_map();

    liv->n_mobs = MIN( 6*log(1+l), MAX_MOBS_X_LIV);

    for(int i=0; i<liv->n_mobs; i++) {
        liv->mobs[i] = GameObjects::getNewMob();
        liv->mappa->get_stanza_random()->posiziona_casualmente(liv->mobs[i]);
    }

    liv->mappa->get_stanza_random()->posiziona_casualmente(
        GameObjects::getNewArmaAnduril()
    );

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
            cout << "Prima di attaccare dovresti raccogliere un'arma\n";
        } else {
            report_attacco ra = giocatore->attacca(livelloCorrente->mappa,direzione);
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
        report_movimento rm = giocatore->muovi(livelloCorrente->mappa,direzione);
        if(rm.riuscito == true) {
            cout << "Ti sei mosso\n";
        } else {
            if(rm.itemScontrato != NULL) {
                if(rm.itemScontrato->getRaccoglibile()) {
                    if( rm.itemScontrato->getIcon() == ICON_ARMA
                    &&  confermaRaccoltaArma(giocatore, (arma *)rm.itemScontrato)
                    &&  giocatore->raccogliArma(livelloCorrente->mappa, (arma *) rm.itemScontrato)
                    ){
                        giocatore->muovi(livelloCorrente->mappa,direzione);
                        // TODO : mettere a posto il report di raccolta
                        char nomeItemScontrato[MAX_NOME_COMPLETO_LENGTH];
                        rm.itemScontrato->getNomeCompleto(nomeItemScontrato);
                        cout << "Hai raccolto '" << nomeItemScontrato << "'\n";
                    } else {
                        cout << "Non sei riuscito a raccogliere l'oggetto..\n";
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
            } else {
                cout << "Oggetto a NULL\n";
            }
        }
    }
    return 0;
}

bool confermaRaccoltaArma(personaggio *giocatore, arma *armaDaRacc) {
    char inConferma;
    bool input_error;
    bool conferma;

    arma *armaInUso = giocatore->getArmaInUso();

    char nomeArmaInUso[MAX_NOME_COMPLETO_LENGTH];
    char nomeArmaDaRacc[MAX_NOME_COMPLETO_LENGTH];

    if(armaInUso != NULL){
        armaInUso->getNomeCompleto(nomeArmaInUso);
        armaDaRacc->getNomeCompleto(nomeArmaDaRacc);
    } else {
        return true;
    }
    cout << "Arma in uso : '" << nomeArmaInUso << "' (" << armaInUso->getDanniArma() << "d / " << armaInUso->getRange() << "r)\n";
    cout << "Arma trovata: '" << nomeArmaDaRacc << "' (" << armaDaRacc->getDanniArma() << "d / " << armaDaRacc->getRange() << "r)\n";
    do {
        input_error = false;
        cout << "Sei sicuro di volere raccogliere questa arma? L'attuale in uso verrà persa.(y/n): ";
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
            case 'W':
                *direzione = DIREZIONE_SU;
                break;
            case 'a':
            case 'A':
                *direzione = DIREZIONE_SINISTRA;
                break;
            case 's':
            case 'S':
                *direzione = DIREZIONE_GIU;
                break;
            case 'd':
            case 'D':
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
            IAMob(livelloCorrente->mobs[t], giocatore,livelloCorrente);
        }
    }
}

void IAMob(personaggio *m, personaggio *g, livello *livelloCorrente) {
    int dxx = g->getPositionXX() - m->getPositionXX();
    int dyy = g->getPositionYY() - m->getPositionYY();
    int absDxx = abs(dxx);
    int absDyy = abs(dyy);
    // Se il giocatore é nel range di attacco del mob, allora il mob lo attacca
    if( m->getArmaInUso() != NULL
    &&  m->getPositionXX() == g->getPositionXX() && m->getArmaInUso()->getRange() >= absDyy
    &&  m->getPositionYY() == g->getPositionYY() && m->getArmaInUso()->getRange() >= absDxx
    ) {
        report_attacco ra;
        if (dxx < 0)
            ra = m->attacca(livelloCorrente->mappa,DIREZIONE_SINISTRA);
        else if (dxx > 0)
            ra = m->attacca(livelloCorrente->mappa,DIREZIONE_DESTRA);
        else if (dyy < 0)
            ra = m->attacca(livelloCorrente->mappa,DIREZIONE_SU);
        else if(dyy > 0)
            ra = m->attacca(livelloCorrente->mappa,DIREZIONE_GIU);

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
            if (dxx < 0) {
                rm = m->muovi(livelloCorrente->mappa, DIREZIONE_SINISTRA);
            } else {
                rm = m->muovi(livelloCorrente->mappa, DIREZIONE_DESTRA);
            }
        } else {
            if (dyy < 0) {
                rm = m->muovi(livelloCorrente->mappa, DIREZIONE_SU);
            } else {
                rm = m->muovi(livelloCorrente->mappa,DIREZIONE_GIU);
            }
        }
    }
}

void stampaSchedaPersonaggio(personaggio *giocatore) {
    char nomeCompleto[MAX_NOME_COMPLETO_LENGTH];
    char armaNomeCompleto[MAX_NOME_COMPLETO_LENGTH];

    giocatore->getNomeCompleto(nomeCompleto);
    if(giocatore->getArmaInUso()) {
        giocatore->getArmaInUso()->getNomeCompleto(armaNomeCompleto);
    }

    cout << "> " << nomeCompleto << "\n";
    cout << "Vita: " << giocatore->getPuntiVita() << "\n";
    cout << "Exp: " << giocatore->getPuntiEsperienza() << "\n";
    if(giocatore->getArmaInUso() != NULL ) {
        cout << "Arma: " << armaNomeCompleto << "\n";
        cout << "- Danni: " << giocatore->getArmaInUso()->getDanniArma() << "d\n";
        cout << "- Range: " << giocatore->getArmaInUso()->getRange() << "r\n";
    } else {
        cout << "Arma: <a mani vuote>\n";
    }
}

void print_map(mappa *map) {
    for (int i = 0; i < map->get_i(); i++) {
        for (int y = 0; y < MAX_RIGHE; y++) {
            for (int j = 0; j < map->get_j(); j++) {
                ptr_stanza tmp = map->p[i][j];

                for (int x = 0; x < MAX_COLONNE; x++) {
                    char icon = tmp->punti_stanza[y][x]->getIcon();

                    cout << termcolor::on_grey;
                    switch(icon) {
                        case ICON_LIV_PREC:
                        case ICON_LIV_SUCC:
                        case ICON_PORTA:
                            cout << termcolor::cyan;
                            break;
                        case ICON_GIOCATORE:
                            cout << termcolor::green;
                            break;
                        case ICON_MOB:
                            cout << termcolor::red;
                            break;
                        case ICON_ARMA:
                            cout << termcolor::yellow;
                            break;
                        default:
                            cout << termcolor::white;
                            break;
                    }
                    cout << icon << termcolor::reset;
                }
            }
            cout << endl;
        }
    }
}