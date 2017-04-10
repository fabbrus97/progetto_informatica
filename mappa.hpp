//
// Created by simone on 14/03/17.
//

#ifndef ADD_ROOM
#define ADD_ROOM stanza nuova_stanza = initialize_room(contatore_stanze + 1); if (stanza_isolata->i+1 < i && !check_room(stanza_isolata ->i+1, stanza_isolata->j)) { cout << "ok, sono nella stanza sotto" << endl; p[stanza_isolata->i + 1][stanza_isolata->j] = nuova_stanza; save_room(stanza_isolata ->i+1, stanza_isolata->j); } else if (stanza_isolata->i-1 > 0 && ! check_room(stanza_isolata ->i-1, stanza_isolata->j)) { cout << "ok, sono nella stanza sopra" << endl; p[stanza_isolata->i - 1][stanza_isolata->j] = nuova_stanza; save_room(stanza_isolata ->i-1, stanza_isolata->j); } else if (stanza_isolata->j+1 < j && !check_room(tmp ->i, tmp->j+1)) {cout << "ok, sono nella stanza a destra" << endl; p[stanza_isolata->i][stanza_isolata->j + 1] = nuova_stanza; save_room(stanza_isolata ->i, stanza_isolata->j+1); } else if (stanza_isolata->j-1 > 0 && !check_room(tmp ->i, tmp->j-1)) { cout << "ok, sono nella stanza a sinistra" << endl; p[stanza_isolata->i][stanza_isolata->j - 1] = nuova_stanza; save_room(stanza_isolata ->i, stanza_isolata->j-1); }
#endif

#ifndef RIGHT_TO_LEFT_TUNNEL
#define RIGHT_TO_LEFT_TUNNEL
#endif
#ifndef LEFT_TO_RIGHT_TUNNEL
#define LEFT_TO_RIGHT_TUNNEL
#endif
#ifndef TOP_TO_BOTTOM_TUNNEL
#define TOP_TO_BOTTOM_TUNNEL
#endif
#ifndef BOTTOM_TO_TOP_TUNNEL
#define BOTTOM_TO_TOP_TUNNEL for (int riga = x - 1, n = 0; n < x - tmp->i - 1; n++, riga--) for (int b = 0; b < 10; b++) if (!check_room(riga, y)){ p[riga][y].punti_stanza[b][10] = 'x'; p[x][y].punti_stanza[0][10] = '+'; p[tmp->i][tmp->j].punti_stanza[9][10] = '+'; } else { n++; p[riga][y].punti_stanza[9][10] = '+'; }
#endif


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
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
    bool is_link=false;
    //stanza* child=NULL;
    //stanza* sibling=NULL;
    //stanza* father=NULL;
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
    bool check_room(int x, int y);
    void save_room(int x, int y);
    stanza initialize_room(int n_stanza);
    void add_empty_rooms();
    void fill_room();
    void generate_all_rooms();
    void add_tunnel(ptr_stanze_occupate stanza_isolata, bool escludi_valore);
    void add_doors(int i, int j);
    void generate_map();
    void print_map();
    void print_list();
};

