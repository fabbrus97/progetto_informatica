//
// Created by simone on 14/03/17.
//
#ifndef MAPPA_HPP
#define MAPPA_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

#include "stanza.hpp"
#include "includes/item.hpp"

using namespace std;

const double alfa=1.5;

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
    ptr_stanza** p;

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
    ptr_stanza find_room(int n_stanza);
    int getN_livello();

    void posiziona(ptr_item it, int xm, int ym, int xs, int ys);
    void sposta(ptr_item from, ptr_item to);
    void esci(ptr_item it);

    ptr_stanza get_stanza_random();
};

#endif
