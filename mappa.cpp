//
// Created by simone on 14/03/17.
//

#include <sstream>
#include "mappa.hpp"
#include "includes/gameobjects.hpp"
#include "includes/item.hpp"
#include "includes/arma.hpp"
//contatore stanze

mappa::mappa(int n) {
    n_stanze = n>=1 ? n : 1;
    contatore_stanze = 1;

    i=1; j=2;

    while (i*j < n_stanze) {
        i = i + 1;
        j = j + 1;
    }

    p = new ptr_stanza*[i];

    //crea l'array bidimensionale
    for(int tmp = 0; tmp < i; tmp++) {
        p[tmp] = new ptr_stanza[j];
    }
    //inizializza l'array a NULL
    for (int y=i-1; y>=0; y--) {
        for (int x = j - 1; x >= 0; x--) {
            p[y][x] = NULL;
        }
    }

    entrata.x = entrata.y = entrata.xx = entrata.yy = -1;
    uscita.x = uscita.y = uscita.xx = uscita.yy = -1;
}

mappa::mappa(){}

int mappa::get_i(){
    return i;
}

int mappa::get_j(){
    return j;
}

bool mappa::check_room(int y, int x) {
    //ritorna true se una stanza esiste, false altrimenti
    return (y>=0 && y<i && x>=0 && x<j && p[y][x]!=NULL);
}

void mappa::generate_all_rooms() {

    //bisogna generare anzitutto la prima stanza e l'ultima
    //perché occupano posizioni privilegiate
    srand(time(0));
    //la prima stanza va nella prima riga
    int x, y;

    y = (rand() % i);
    x = 0;
    ptr_stanza prima_stanza = new stanza(x, y, 1);
    prima_stanza->setIs_emtpy(false);

    if (n_stanze == 1) {
        prima_stanza->posiziona(GameObjects::getNewLivSucc(),MAX_COLONNE-1, MAX_RIGHE/2);
        entrata.x = prima_stanza->getCoor_x();
        entrata.y = prima_stanza->getCoor_y();
        entrata.xx = 1;
        entrata.yy = 3;

        uscita.x = prima_stanza->getCoor_x();
        uscita.y = prima_stanza->getCoor_y();
        uscita.xx = MAX_COLONNE-2;
        uscita.yy = MAX_RIGHE/2;
    }

    p[y][x] = prima_stanza;
    contatore_stanze++;

    //se non siamo nel primo livello, generiamo l'ultima stanza (che va nell'ultima colonna);
    if (n_stanze != 1) {
        y = (rand() % i);
        x = j - 1;
        
        ptr_stanza ultima_stanza = new stanza(x, y, n_stanze);

        ultima_stanza->setIs_emtpy(false);
        ultima_stanza->posiziona(GameObjects::getNewLivSucc(),MAX_COLONNE-1, MAX_RIGHE/2);
        uscita.x = ultima_stanza->getCoor_x();
        uscita.y = ultima_stanza->getCoor_y();
        uscita.xx = MAX_COLONNE-2;
        uscita.yy = MAX_RIGHE/2;

        //aggiungiamo anche la porta per tornare al livello precedente;
        prima_stanza->posiziona(GameObjects::getNewLivPrec(),0,3);
        entrata.x = prima_stanza->getCoor_x();
        entrata.y = prima_stanza->getCoor_y();
        entrata.xx = 1;
        entrata.yy = 3;

        p[y][x] = ultima_stanza;
        contatore_stanze++;
    }
    //continuiamo a generare stanze finché non raggiungiamo il massimo consentito dal livello
    while (contatore_stanze <= n_stanze) {
        y = (rand() % i);
        x = (rand() % j);

        //controlliamo che la stanza sia presente o meno;
        if (!check_room(y, x)) {
            p[y][x] = new stanza(x, y, contatore_stanze);
            p[y][x]->setIs_emtpy(false);
            contatore_stanze++;
        }
    }
    //cerchiamo eventuali stanze rimaste vuote e stampiamo (?) una stanza vuota
    for (int tmp_i = 0; tmp_i < i; tmp_i++)
        for (int tmp_j = 0; tmp_j < j; tmp_j++)
            if (p[tmp_i][tmp_j] == NULL) {
                p[tmp_i][tmp_j] = new stanza(tmp_j,tmp_i);
                p[tmp_i][tmp_j]->setIs_emtpy(true);
            }
}

void mappa::add_doors(ptr_stanza room) {

    //stanza a destra
    if (check_room(room->getCoor_y(), room->getCoor_x()+1) && !p[room->getCoor_y()][room->getCoor_x()+1]->isIs_emtpy() && !room->has_connection(p[room->getCoor_y()][room->getCoor_x()+1])){
        room->posiziona(GameObjects::getNewPorta(), MAX_COLONNE-1, MAX_RIGHE/2);
        p[room->getCoor_y()][room->getCoor_x()+1]->posiziona(GameObjects::getNewPorta(),0,MAX_RIGHE/2);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->getCoor_y()][room->getCoor_x()+1]);
        p[room->getCoor_y()][room->getCoor_x()+1]->lista_connessioni=
                p[room->getCoor_y()][room->getCoor_x()+1]->aggiungi_stanza_a_lista_connessioni(p[room->getCoor_y()][room->getCoor_x()+1], room);

        room->lista_connessioni->porta=room->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1];
        p[room->getCoor_y()][room->getCoor_x()+1]->lista_connessioni->porta=
                p[room->getCoor_y()][room->getCoor_x()+1]->punti_stanza[MAX_RIGHE/2][0];
        room->lista_connessioni->x=1; room->lista_connessioni->y=(MAX_RIGHE/2); //ATTENZIONE sono coordinate cartesiane, non matriciali
        p[room->getCoor_y()][room->getCoor_x()+1]->lista_connessioni->x=MAX_COLONNE-2;
        p[room->getCoor_y()][room->getCoor_x()+1]->lista_connessioni->y=MAX_RIGHE/2;

        add_doors(p[room->getCoor_y()][room->getCoor_x()+1]);
    }

    //stanza sopra
    if (check_room(room->getCoor_y()-1, room->getCoor_x()) && !p[room->getCoor_y()-1][room->getCoor_x()]->isIs_emtpy() && !room->has_connection(p[room->getCoor_y()-1][room->getCoor_x()])){
        room->posiziona(GameObjects::getNewPorta(), MAX_COLONNE/2, 0);
        p[room->getCoor_y()-1][room->getCoor_x()]->posiziona(GameObjects::getNewPorta(),MAX_COLONNE/2,MAX_RIGHE-1);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->getCoor_y()-1][room->getCoor_x()]);
        p[room->getCoor_y()-1][room->getCoor_x()]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->getCoor_y()-1][room->getCoor_x()], room);

        room->lista_connessioni->porta=room->punti_stanza[0][MAX_COLONNE/2];
        p[room->getCoor_y()-1][room->getCoor_x()]->lista_connessioni->porta=
                p[room->getCoor_y()-1][room->getCoor_x()]->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2];
        room->lista_connessioni->x=MAX_COLONNE/2; room->lista_connessioni->y=(MAX_RIGHE-2); //ATTENZIONE sono coordinate cartesiane, non matriciali
        p[room->getCoor_y()-1][room->getCoor_x()]->lista_connessioni->x=MAX_COLONNE/2;
        p[room->getCoor_y()-1][room->getCoor_x()]->lista_connessioni->y=1;

        add_doors(p[room->getCoor_y()-1][room->getCoor_x()]);
    }

    //stanza sotto
    if (check_room(room->getCoor_y()+1, room->getCoor_x()) && !p[room->getCoor_y()+1][room->getCoor_x()]->isIs_emtpy() && !room->has_connection(p[room->getCoor_y()+1][room->getCoor_x()])){
        room->posiziona(GameObjects::getNewPorta(), MAX_COLONNE/2, MAX_RIGHE-1);
        p[room->getCoor_y()+1][room->getCoor_x()]->posiziona(GameObjects::getNewPorta(),MAX_COLONNE/2,0);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->getCoor_y()+1][room->getCoor_x()]);
        p[room->getCoor_y()+1][room->getCoor_x()]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->getCoor_y()+1][room->getCoor_x()], room);

        room->lista_connessioni->porta=room->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2];
        p[room->getCoor_y()+1][room->getCoor_x()]->lista_connessioni->porta=
                p[room->getCoor_y()+1][room->getCoor_x()]->punti_stanza[0][MAX_COLONNE/2];
        room->lista_connessioni->x=MAX_COLONNE/2; room->lista_connessioni->y=1; //ATTENZIONE sono coordinate cartesiane, non matriciali
        p[room->getCoor_y()+1][room->getCoor_x()]->lista_connessioni->x=MAX_COLONNE/2;
        p[room->getCoor_y()+1][room->getCoor_x()]->lista_connessioni->y=MAX_RIGHE-2;

        add_doors(p[room->getCoor_y()+1][room->getCoor_x()]);
    }

    //stanza a sinistra
    if (check_room(room->getCoor_y(), room->getCoor_x()-1) && !p[room->getCoor_y()][room->getCoor_x()-1]->isIs_emtpy() && !room->has_connection(p[room->getCoor_y()][room->getCoor_x()-1])){
        room->posiziona(GameObjects::getNewPorta(), 0, MAX_RIGHE/2);
        p[room->getCoor_y()][room->getCoor_x()-1]->posiziona(GameObjects::getNewPorta(),MAX_COLONNE-1,MAX_RIGHE/2);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->getCoor_y()][room->getCoor_x()-1]);
        p[room->getCoor_y()][room->getCoor_x()-1]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->getCoor_y()][room->getCoor_x()-1], room);

        room->lista_connessioni->porta=room->punti_stanza[MAX_RIGHE/2][0];
        p[room->getCoor_y()][room->getCoor_x()-1]->lista_connessioni->porta=p[room->getCoor_y()][room->getCoor_x()-1]->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1];
        room->lista_connessioni->x=MAX_COLONNE-2; room->lista_connessioni->y=MAX_RIGHE/2; //ATTENZIONE sono coordinate cartesiane, non matriciali
        p[room->getCoor_y()][room->getCoor_x()-1]->lista_connessioni->x=1;
        p[room->getCoor_y()][room->getCoor_x()-1]->lista_connessioni->y=MAX_RIGHE/2;

        add_doors(p[room->getCoor_y()][room->getCoor_x()-1]);
    }
}

ptr_stanza mappa::find_first(int row) {
    //trova la prima stanza in una riga
    int tmp_j=0;
    while (p[row][tmp_j]->isIs_emtpy()){
        //if (p[i][j]->is_emtpy)
        tmp_j++;
        if (tmp_j==j) { //se superi l'ultima colonna senza trovare nulla, la riga è vuota
            row++;
            tmp_j=0;
            if (row==i) //se superi l'ultima riga, devi arrenderti
                return NULL;
        }
    }
    return p[row][tmp_j];
}

void mappa::first_linking(ptr_stanza room, bool force_linking) {

    ptr_stanza tmp = NULL;

    if (room == NULL) {//condizione di arresto 1: room è NULL
        return;
    }

    if (room->getCoor_x() < j - 1) { //room->coor_y non può essere j-1, perché tmp sarebbe in una stanza inesistente
        tmp = p[room->getCoor_y()][room->getCoor_x() + 1];
    } else if (room->getCoor_x() == j - 1 && room->getCoor_y() < i - 1)
        return first_linking(find_first(room->getCoor_y() + 1),
                             false); //se siamo nell'ultima cella della riga, facciamo ripartire subito la funzione
    else return; //condizione di arresto due: raggiunta ultima cella della mappa

    while (tmp != NULL && tmp->getCoor_x() < j) {
        if (tmp->isIs_emtpy()) {
            if (tmp->getCoor_x() + 1 < j) {
                tmp = p[tmp->getCoor_y()][tmp->getCoor_x() + 1];
            } else return first_linking(tmp, false);
        } else {
            if (tmp->getCoor_x() == room->getCoor_x() + 1 && force_linking) {
                //forza la scrittura di porte
                room->posiziona(GameObjects::getNewPorta(), MAX_COLONNE-1, MAX_RIGHE/2);
                tmp->posiziona(GameObjects::getNewPorta(), 0, MAX_RIGHE/2);

                room->lista_connessioni->porta=room->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1];
                tmp->lista_connessioni->porta=tmp->punti_stanza[MAX_RIGHE/2][0];
                room->lista_connessioni->x=1; room->lista_connessioni->y=(MAX_RIGHE/2); //ATTENZIONE sono coordinate cartesiane, non matriciali
                tmp->lista_connessioni->x=MAX_COLONNE-2;
                tmp->lista_connessioni->y=MAX_RIGHE/2;

                return first_linking(tmp, true);

            } else if (tmp->getCoor_x() == room->getCoor_x() + 1 && !force_linking) {
                return first_linking(tmp, false);

            } else if (tmp->getCoor_x() > room->getCoor_x() + 1) {
                //costruisci il tunnel solo se la stanza non risulta già connessa
                if (!room->has_connection(tmp) || !room->has_connection(room)) {
                    for (int a = room->getCoor_x() + 1; a < tmp->getCoor_x(); a++)
                        for (int b = 0; b < MAX_COLONNE; b++) {
                            posiziona(GameObjects::getNewTunnel(), a, room->getCoor_y(), b, MAX_RIGHE/2 );
                        }
                    tmp->posiziona(GameObjects::getNewPorta(), 0, MAX_RIGHE/2);
                    room->posiziona(GameObjects::getNewPorta(), MAX_COLONNE-1, MAX_RIGHE/2);

                    room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, tmp);
                    tmp->lista_connessioni=tmp->aggiungi_stanza_a_lista_connessioni(tmp, room);

                    room->lista_connessioni->porta=room->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1];
                    tmp->lista_connessioni->porta=tmp->punti_stanza[MAX_RIGHE/2][0];
                    room->lista_connessioni->x=1; room->lista_connessioni->y=(MAX_RIGHE/2); //ATTENZIONE sono coordinate cartesiane, non matriciali
                    tmp->lista_connessioni->x=MAX_COLONNE-2; tmp->lista_connessioni->y=MAX_RIGHE/2;

                    add_doors(tmp);
                    add_doors(room);
                }
                return first_linking(tmp, false);
            }
        }
    }
    return;
}

bool mappa::check_row_connection(int row) {
    int h;
    ptr_stanza tmp=NULL;
    if (find_first(row)!=NULL) {
        tmp = find_first(row);
    }
    else return false;
    if ((tmp->getCoor_y()+1)<i && find_first(tmp->getCoor_y() + 1)!=NULL)
        h = find_first(tmp->getCoor_y() + 1)->getCoor_y();
    else return false;
    bool is_linked=false; //questo booleano dice se la riga data è collegata con la prima riga non vuota sottostante

    for (int scroll=tmp->getCoor_x(); scroll<j; scroll++){
        if (!p[row][scroll]->isIs_emtpy()){
            tmp=p[row][scroll];
            if (tmp->check_connection(tmp, p[h][scroll])) {
                is_linked = true;
            }
        }
    }
    return is_linked;
}

void mappa::second_linking(ptr_stanza room, ptr_stanza known_room) {

    if (room==NULL)
        return;

    if (room->getCoor_y()==i-1 || find_first(room->getCoor_y()+1)==NULL) {
        //se find_first restituisce NULL significa
        //che sotto la stanza room non ci sono altre
        //stanze, e la funzione termina.
        return;
    }

    if (check_row_connection(room->getCoor_y())){
        //tipo sono collegate con una porta, o con un tunnell...
        return second_linking(find_first(room->getCoor_y()+1), NULL);

    } else {
        //non sono collegate (magari sono attaccate eh, però non sono collegate
        ptr_stanza tmp=find_first(room->getCoor_y()+1);
        if (known_room!=NULL)
            tmp=known_room;

        //caso 1: le stanze sono attaccate
        //non si fa niente, si convoglia nel caso 2

        if (room->getCoor_x()==tmp->getCoor_x()) { //caso 2: le stanze sono nella stessa colonna
            //stampa il tunnel
            for (int altezza = room->getCoor_y() + 1; altezza < tmp->getCoor_y(); altezza++) {
                for (int a = 0; a < MAX_RIGHE; a++) {
                    posiziona(GameObjects::getNewTunnel(), room->getCoor_x(), altezza, MAX_COLONNE / 2, a);
                }
            }
            room->posiziona(GameObjects::getNewPorta(),MAX_COLONNE/2, MAX_RIGHE-1);
            tmp->posiziona(GameObjects::getNewPorta(),MAX_COLONNE/2, 0);

            room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, tmp);
            tmp->lista_connessioni=tmp->aggiungi_stanza_a_lista_connessioni(tmp, room);

            room->lista_connessioni->porta=room->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2];
            tmp->lista_connessioni->porta=tmp->punti_stanza[0][MAX_COLONNE/2];
            room->lista_connessioni->x=MAX_COLONNE/2; room->lista_connessioni->y=1; //ATTENZIONE sono coordinate cartesiane, non matriciali
            tmp->lista_connessioni->x=MAX_COLONNE/2; tmp->lista_connessioni->y=MAX_RIGHE-2;

            return second_linking(find_first(room->getCoor_y() + 1), NULL);
        } else { //caso 3: le stanze non sono nella stessa colonna, bisogna generare una nuova stanza
            //genera la nuova stanza

            ptr_stanza nuova_stanza = new stanza(room->getCoor_x(), tmp->getCoor_y(), contatore_stanze);
            //genero una nuova stanza nella stessa colonna di room e nella stessa riga di tmp
            nuova_stanza->setIs_emtpy(false);
            p[tmp->getCoor_y()][room->getCoor_x()] = nuova_stanza;//memory leak

            contatore_stanze++;
            //adesso c'è una stanza sotto room, posso rilanciare second_linking (dopo aver collegato le stanze della riga di tmp)
            first_linking(find_first(nuova_stanza->getCoor_y()), true);
            //room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[tmp->coor_x][room->coor_y]);
            //tmp->lista_connessioni=tmp->aggiungi_stanza_a_lista_connessioni(p[tmp->coor_x][room->coor_y], room);
            return second_linking(room, p[tmp->getCoor_y()][room->getCoor_x()]);
            //return second_linking(find_first(room->coor_x+1));
        }
    }
}

void mappa::generate_map() {
    generate_all_rooms();

    //ricerca la prima porta della mappa
    ptr_stanza first=NULL;
    //find first trova la prima stanza partendo da una riga in input, e restituisce un puntatore alla stanza.
    first = find_first(0);
    add_doors(first);

    first_linking(first, false);
    first=find_first(0);
    second_linking(first, NULL);
}

ptr_stanza mappa::find_room(int n_stanza) {
    //questa funzione prende in input un numero, e resistuisce un puntatore alla stanza con quel numero
    //se non esiste, ritorna null

    for (int y=0; y<i; y++)
        for (int x=0; x<j; x++){
            if (!p[y][x]->isIs_emtpy()){
                if (p[y][x]->getN_stanza()==n_stanza)
                    return p[y][x];
            }
        }

    return NULL;
}

/*
 * l'item nella stanza (xm,ym) in posizione (xs,ys) viene eleminato dalla memoria
 * e sostituito con l'item it
 */
void mappa::posiziona(ptr_item it, int xm, int ym, int xs, int ys) {
    p[ym][xm]->posiziona(it,xs,ys);
}

/*
 * Sposta l'item from al posto dell'item to e al posto di from ci mette un item Punto
 * Quindi libera la memoria dell'item to
 */
void mappa::sposta(ptr_item from, ptr_item to) {
    esci(from);
    posiziona(from, to->getPositionX(), to->getPositionY(), to->getPositionXX(), to->getPositionYY());
}

void mappa::esci(ptr_item it) {
    int xm = it->getPositionX();
    int ym = it->getPositionY();
    int xs = it->getPositionXX();
    int ys = it->getPositionYY();

    it->setPosition(-1,-1,-1,-1);

    p[ym][xm]->punti_stanza[ys][xs] = NULL;
    posiziona( GameObjects::getNewPunto(), xm, ym, xs, ys );
}

ptr_stanza mappa::get_stanza_random() {
    int rand_i = rand() % i;
    int rand_j = rand() % j;

    for(int tmp_i = rand_i; tmp_i < i; tmp_i++) {
        for(int tmp_j = rand_j; tmp_j < j; tmp_j++) {
            if(!p[tmp_i][tmp_j]->isIs_emtpy()) {
                return p[tmp_i][tmp_j];
            }
        }
    }

    for(int tmp_i = rand_i; tmp_i >= 0; tmp_i--) {
        for(int tmp_j = rand_j; tmp_j >= 0; tmp_j--) {
            if(!p[tmp_i][tmp_j]->isIs_emtpy()) {
                return p[tmp_i][tmp_j];
            }
        }
    }

    return NULL;
}