//
// Created by simone on 14/03/17.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "item.h"

using namespace std;

const int max_righe=10;
const int max_colonne=20;
const double alfa=1.5;

// struttura stanza

class stanza;

typedef stanza* ptr_stanza;

struct connessioni{
    ptr_stanza stanza_puntata;
    connessioni *next;
};

typedef connessioni * ptr_connessioni;

class stanza {
public:
    int n_stanza; //l'ordine con cui viene generata la stanza
    //bool is_link=false; //la stanza è isolata dalle altre
    bool is_emtpy=true; //la stanza contiene solo spazi (o eventualmente tunnel)
    int coor_x; //coordinate della stanza all'interno della mappa
    int coor_y; //coordinate della stanza all'interno della mappa
    //item punti_stanza[max_righe][max_colonne];
    ptr_item** punti_stanza; // = new ptr_item*[max_righe];
    ptr_connessioni lista_connessioni;//=NULL;

    stanza(int x, int y, int n_room);
    stanza(int x, int y);

    ptr_connessioni aggiungi_stanza_a_lista_connessioni(ptr_stanza stanza_di_cui_modificare_lista, ptr_stanza stanza_da_aggiungere);
    bool check_connection(ptr_stanza stanza_di_partenza, ptr_stanza stanza_da_controllare);
    bool has_connection(ptr_stanza room);

    bool posiziona_casualmente(ptr_stanza stanza, ptr_item oggetto, int tentativo);
    };

//void aggiungi_stanza_a_lista_connessioni(ptr_stanza stanza_di_cui_modificare_lista, ptr_stanza stanza_da_aggiungere);

/*
 * classe mappa
 */

class mappa {
protected:
    int n_livello;
    int i;
    int j;
    //stanza nuova_stanza;
    public:
    ptr_stanza** p = new ptr_stanza*[i];

    mappa(int n);
    mappa();
    bool check_room(int x, int y);
    /********************/
    void generate_all_rooms();
    ptr_stanza find_first(int row);
    bool check_row_connection(int row);
    void first_linking(ptr_stanza room, bool force_linking);
    void second_linking(ptr_stanza room, ptr_stanza known_room);
    void add_doors(ptr_stanza room);
    void generate_map();
    void print_map();
};
