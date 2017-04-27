//
// Created by simone on 14/03/17.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

const int max_righe=10;
const int max_colonne=20;
const double alfa=1.5;

/*
 * struttura stanza
 */

class stanza;

typedef stanza* ptr_stanza;

struct connessioni{
    ptr_stanza stanza_puntata;
    connessioni *next;
};

typedef connessioni * ptr_connessioni;

class stanza {
protected:
    int n_stanza;
    bool is_link=false;
public:
    bool is_emtpy=true;
    int coor_x;
    int coor_y;
    char punti_stanza[max_righe][max_colonne];
    ptr_connessioni lista_connessioni=NULL;

    stanza(int x, int y, int n_room);
    stanza(int x, int y);

    ptr_connessioni aggiungi_stanza_a_lista_connessioni(ptr_stanza stanza_di_cui_modificare_lista, ptr_stanza stanza_da_aggiungere);
    bool check_connection(ptr_stanza stanza_di_partenza, ptr_stanza stanza_da_controllare);
    bool has_connection(ptr_stanza room);
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
    ptr_stanza** p =new ptr_stanza*[i];
public:
    mappa(int n);
    bool check_room(int x, int y);
    /*DA MODIFICARE...? */
    /********************/
    //void save_room(ptr_stanza);
    //stanza initialize_room(int n_stanza);
    //void add_empty_rooms();
    void generate_all_rooms();
    ptr_stanza find_first(int row);
    ptr_stanza find_place(int posizione, ptr_stanza prima_stanza);
    void first_linking(ptr_stanza room);
    void second_linking(ptr_stanza room);
    void add_doors(ptr_stanza room);
    void generate_map();
    void print_map();
};
