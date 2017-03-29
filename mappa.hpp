//
// Created by simone on 14/03/17.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

/*
 * Costanti e altri elementi globali
 */

//questa costante determina il numero di stanze per ogni livello
const double alfa=1.5;

//dimensione delle stanze
const int m=10;
const int n=20;

//occorre una lista per salvare gli indici delle stanze occupate nella mappa
//per non sovrascriverle
struct stanze_occupate{
    int i;
    int j;
    stanze_occupate *next;
};

typedef stanze_occupate *ptr_stanze_occupate;

/*
 * struttura stanza
 */

struct stanza {
    int n_stanza;
    char punti_stanza[m][n];
    bool is_isolated=true;
};

/*
 * classe mappa
 */

class mappa {
protected:
    int n_livello;
    int i;
    int j;
    stanza nuova_stanza;
    stanza** p =new stanza*[i];
public:
    mappa(int n);
    stanza initialize_room(int n_stanza);
    bool check_room(int x, int y);
    void save_room(int x, int y);
    void add_empty_rooms();
    void fill_room();
    void generate_all_rooms();
    void print_all_rooms();
    bool is_isolated(ptr_stanze_occupate room);
    void print_list();
    void generate_tunnel();
};

