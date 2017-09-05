//#include <iostream>
#include "mappa.hpp"
#include "includes/gameobjects.hpp"
#include "includes/personaggio.hpp"

using namespace std;

struct lista_mappe{
    mappa* map;
    lista_mappe * next;
};

void init_giocatore(personaggio *);
void game_loop(personaggio *);

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
    lista_mappe *head=NULL;

    mappa nuova_mappa(1);
    nuova_mappa.generate_map();

    head = new lista_mappe;
    head->map = new mappa;
    head->map = &nuova_mappa;

    while(!end) {
        head->map->print_map();
        //turno del giocatore
        //choose what to do (a=>attacca m=>move)

        //se il giocatore si é mosso ed é sopra una porta:
        //
        /*
        for(int t=0; t<..; t++){
            //turno del mob t del livello corrente
            //choose what to do (a=>attacca m=>move)
        }
        */
    }
}