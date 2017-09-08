#ifndef STANZA_HPP
#define STANZA_HPP

#include <iostream>
#include "includes/item.hpp"

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
    static bool posiziona_casualmente(ptr_stanza stanza, ptr_item oggetto, int tentativo);
};

#endif
