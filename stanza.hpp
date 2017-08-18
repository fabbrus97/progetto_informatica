#ifndef STANZA_HPP
#define STANZA_HPP

#include <iostream>
#include "oggetti_mappa.hpp"

#define MAX_RIGHE 10
#define MAX_COLONNE 20

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
    bool is_emtpy; //la stanza contiene solo spazi (o eventualmente tunnel)
    int coor_x; //coordinate della stanza all'interno della mappa
    int coor_y; //coordinate della stanza all'interno della mappa
    //item punti_stanza[MAX_RIGHE][MAX_COLONNE];
    ptr_item** punti_stanza;
    ptr_connessioni lista_connessioni;

    stanza(int x, int y, int n_room);
    stanza(int x, int y);

    ptr_connessioni aggiungi_stanza_a_lista_connessioni(ptr_stanza stanza_di_cui_modificare_lista, ptr_stanza stanza_da_aggiungere);
    bool check_connection(ptr_stanza stanza_di_partenza, ptr_stanza stanza_da_controllare);
    bool has_connection(ptr_stanza room);

    bool posiziona_casualmente(ptr_stanza stanza, ptr_item oggetto, int tentativo);
};

#endif
