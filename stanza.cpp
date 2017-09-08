#include "stanza.hpp"
#include "includes/gameobjects.hpp"
using namespace std;

stanza::stanza(int x, int y, int n_room){
    //item punto_stanza('.',true,false);
    //item muro('#',false,false);
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
        punti_stanza[i][0]=new item(ICON_MURO,false,false);
        punti_stanza[i][0]->setPositionX(x, y, 0, i);

        punti_stanza[i][MAX_COLONNE-1]=new item(ICON_MURO,false,false);
        punti_stanza[i][MAX_COLONNE-1]->setPositionX(x, y, MAX_COLONNE-1, i);
    }
    for (int j=1; j<MAX_COLONNE-1; j++){
        punti_stanza[0][j]=new item(ICON_MURO,false,false);
        punti_stanza[0][j]->setPositionX(x, y, j, 0);

        punti_stanza[MAX_RIGHE-1][j]=new item(ICON_MURO,false,false);
        punti_stanza[MAX_RIGHE-1][j]->setPositionX(x, y, j, MAX_RIGHE-1);
    }

    //costruiamo l'interno della stanza
    for (int i=1; i<MAX_RIGHE-1; i++)
        for (int j=1; j<MAX_COLONNE-1; j++) {
            punti_stanza[i][j] = new item(ICON_PUNTO,true,false);
            punti_stanza[i][j]->setPositionX(x, y, j, i);
        }

}

stanza::stanza(int x, int y) {
    //item spazio(' ',false,false);
    is_emtpy = true;
    coor_x = x;
    coor_y = y;

    lista_connessioni = NULL;
    punti_stanza = new ptr_item *[MAX_RIGHE];

    //crea l'array bidimensionale
    for (int tmp = 0; tmp < MAX_RIGHE; tmp++) {
        punti_stanza[tmp] = new ptr_item[MAX_COLONNE];
    }
    //inizializza l'array a NULL
    for (int i = 0; i < MAX_RIGHE; i++)
        for (int j = 0; j < MAX_COLONNE; j++) {
            punti_stanza[i][j] = new item(ICON_SPAZIO, false, false, 0, "Vuoto", coor_x, coor_y, j, i);
        }
}

int stanza::getN_stanza() const {
    return n_stanza;
}

void stanza::setN_stanza(int n_stanza) {
    stanza::n_stanza = n_stanza;
}

bool stanza::isIs_emtpy() const {
    return is_emtpy;
}

void stanza::setIs_emtpy(bool is_emtpy) {
    stanza::is_emtpy = is_emtpy;
}

int stanza::getCoor_x() const {
    return coor_x;
}

void stanza::setCoor_x(int coor_x) {
    stanza::coor_x = coor_x;
}

int stanza::getCoor_y() const {
    return coor_y;
}

void stanza::setCoor_y(int coor_y) {
    stanza::coor_y = coor_y;
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
    y = (rand() % (MAX_RIGHE-1))+1;
    x = (rand() % (MAX_COLONNE-1))+1;

    if (stanza->punti_stanza[y][x]->getIcon()==ICON_PUNTO){
        posiziona(oggetto,x,y);
        return true;
    } else
        return posiziona_casualmente(stanza, oggetto, tentativo+1);

}

void stanza::posiziona(ptr_item it, int x, int y) {
    ptr_item oldItem = punti_stanza[y][x];
    punti_stanza[y][x] = it;
    it->setPositionX(getCoor_x(),getCoor_y(),x,y);
    if(oldItem != NULL)
        delete oldItem;
}