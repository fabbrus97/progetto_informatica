#include "stanza.hpp"
using namespace std;

stanza::stanza(int x, int y, int n_room){
    item punto_stanza('.',true,false);
    item muro('#',false,false);
    coor_x=x;
    coor_y=y;
    n_stanza=n_room;
    lista_connessioni = NULL;

    punti_stanza = new ptr_item*[MAX_RIGHE];
    //crea l'array bidimensionale
    for(int tmp = 0; tmp < MAX_RIGHE; tmp++) {
        punti_stanza[tmp] = new ptr_item[MAX_COLONNE];
    }

    //costruiamo i muri
    for (int i=0; i<MAX_RIGHE; i++){
        punti_stanza[i][0]=new item;
        *punti_stanza[i][0]=muro;
        punti_stanza[i][0]->get_position(x, y, i, 0);

        punti_stanza[i][MAX_COLONNE-1]=new item;
        *punti_stanza[i][MAX_COLONNE-1]=muro;
        punti_stanza[i][MAX_COLONNE-1]->get_position(x, y, i, MAX_COLONNE-1);
    }
    for (int j=0; j<MAX_COLONNE; j++){
        punti_stanza[0][j]=new item;
        *punti_stanza[0][j]=muro;
        punti_stanza[0][j]->get_position(x, y, 0, j);

        punti_stanza[MAX_RIGHE-1][j]=new item;
        *punti_stanza[MAX_RIGHE-1][j]=muro;
        punti_stanza[MAX_RIGHE-1][j]->get_position(x, y, MAX_RIGHE-1, j);
    }

    //costruiamo l'interno della stanza
    for (int i=1; i<MAX_RIGHE-1; i++)
        for (int j=1; j<MAX_COLONNE-1; j++) {
            punti_stanza[i][j] = new item;
            *punti_stanza[i][j] = punto_stanza;
            punti_stanza[i][j]->get_position(x, y, i, j);
        }

}

stanza::stanza(int x, int y) {
    item spazio(' ',false,false);
    is_emtpy = true;
    punti_stanza = new ptr_item*[MAX_RIGHE];
    lista_connessioni = NULL;
    coor_x = x;
    coor_y = y;

    //crea l'array bidimensionale
    for(int tmp = 0; tmp < MAX_RIGHE; tmp++) {
        punti_stanza[tmp] = new ptr_item[MAX_COLONNE];
    }
    //inizializza l'array a NULL
    for (int x=MAX_RIGHE-1; x>=0; x--)
        for (int y=MAX_COLONNE-1; y>=0; y--) {
            punti_stanza[x][y] = new item;
            *punti_stanza[x][y] = spazio;
            //in realtà inizializzare le posizioni di questi punti è inutile
            punti_stanza[x][y]->get_position(coor_x, coor_y, x, y);
        }

}


ptr_connessioni stanza::aggiungi_stanza_a_lista_connessioni(ptr_stanza stanza_di_cui_modificare_lista, ptr_stanza stanza_da_aggiungere){
    ptr_connessioni tmp = new connessioni;
    tmp->stanza_puntata = stanza_da_aggiungere;
    tmp->next = stanza_di_cui_modificare_lista->lista_connessioni;
    return tmp;
}

bool stanza::check_connection(ptr_stanza stanza_di_partenza, ptr_stanza stanza_da_controllare) {
    ptr_connessioni tmp = stanza_di_partenza->lista_connessioni;
    while (tmp != NULL) {
        /* Se il ptr alla stanza in lista_connessioni della stanza_di_partenza è uguale al ptr stanza_da_controllare,
         * la funzione ritorna "true", che significa: la stanza è già presente nella lista, ovvero le stanze sono già connesse
         */
        if (tmp->stanza_puntata == stanza_da_controllare) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

bool stanza::has_connection(ptr_stanza room){
    //se la stanza ha almeno una connessione, la funzione restituisce true
    return (room->lista_connessioni!=NULL);
}

bool stanza::posiziona_casualmente(ptr_stanza stanza, ptr_item oggetto, int tentativo) {
    if (tentativo==(MAX_RIGHE-2)*(MAX_COLONNE-2))
        return false;

    srand(time(0));
    int x, y;
    //x e y sono inizializzati in modo che siano un numero tra 1 e MAX_RIGHE-1 o MAX_COLONNE-1
    x = (rand() % (MAX_RIGHE-1))+1;
    y = (rand() % (MAX_COLONNE-1))+1;

    if (stanza->punti_stanza[x][y]->icon=='.'){
        stanza->punti_stanza[x][y]=oggetto;
        return true;
    } else
        return posiziona_casualmente(stanza, oggetto, tentativo+1);

}
