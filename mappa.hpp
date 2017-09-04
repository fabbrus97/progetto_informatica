//
// Created by simone on 14/03/17.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "item.hpp"
using namespace std;

/*
 * variabili globali
 */

const int max_righe=10; //indica il numero di righe in una stanza
const int max_colonne=20; //indica il numero di colonne in una stanza
const double alfa=1.5; //valore usato per calcolare il numero di stanze in un livello o mappa

/*
 * stanza
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
    int n_stanza; //l'ordine con cui viene generata la stanza
    bool is_emtpy=true; //la stanza contiene solo spazi (o eventualmente tunnel)
    int coor_x; //coordinate della stanza all'interno della mappa
    int coor_y; //coordinate della stanza all'interno della mappa
public:
    ptr_item** punti_stanza;
    ptr_connessioni lista_connessioni; //la lista di puntatori a stanze a cui la stanza è connessa

    stanza(int x, int y, int n_room);
    stanza(int x, int y);

    int getN_stanza() const;
    void setN_stanza(int n_stanza);
    bool isIs_emtpy() const;
    void setIs_emtpy(bool is_emtpy);
    int getCoor_x() const;
    void setCoor_x(int coor_x);
    int getCoor_y() const;
    void setCoor_y(int coor_y);

    ptr_connessioni aggiungi_stanza_a_lista_connessioni(ptr_stanza stanza_di_cui_modificare_lista, ptr_stanza stanza_da_aggiungere);
    bool check_connection(ptr_stanza stanza_di_partenza, ptr_stanza stanza_da_controllare);
    bool has_connection(ptr_stanza room);
    bool posiziona_casualmente(ptr_stanza stanza, ptr_item oggetto, int tentativo);
};

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
