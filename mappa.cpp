//
// Created by simone on 14/03/17.
//

#include "mappa.hpp"
#include "spada.h"
#include "coltello.h"

//contatore stanze
int contatore_stanze=1;

mappa::mappa(int n) {
    n_livello=n;

    i=1; j=2;

    int n_stanze=(int)(n_livello*alfa);

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
    for (int x=i-1; x>=0; x--)
        for (int y=j-1; y>=0; y--) {
            p[x][y] = NULL;
        }
}

mappa::mappa(){}

bool mappa::check_room(int x, int y) {
    //ritorna true se una stanza esiste, false altrimenti
    return (x>=0 && x<i && y>=0 && y<j && p[x][y]!=NULL);
}

void mappa::generate_all_rooms() {
    item porta_liv_succ('S',true);
    item porta_liv_prec('B',true);

    //bisogna generare anzitutto la prima stanza e l'ultima
    //perché occupano posizioni privilegiate
    srand(time(0));
    //la prima stanza va nella prima riga
    int x, y;
    x = (rand() % i);
    y = 0;
    stanza prima_stanza(x, y, 1);
    prima_stanza.is_emtpy = false;
    if (n_livello == 1) {
        prima_stanza.punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1] = new item;
        *prima_stanza.punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1] = porta_liv_succ;
        prima_stanza.punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1]->get_position(prima_stanza.coor_x, prima_stanza.coor_y, MAX_RIGHE/2, MAX_COLONNE-1);
    }
    p[x][y] = new stanza(x, y);
    *p[x][y] = prima_stanza;
    contatore_stanze++;
    //se non siamo nel primo livello, generiamo l'ultima stanza (che va nell'ultima colonna);
    if (n_livello != 1) {
        x = (rand() % i);
        y = j - 1;
        stanza ultima_stanza(x, y, (int) (n_livello * alfa));

        ultima_stanza.is_emtpy = false;
        ultima_stanza.punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1] = new item;
        *ultima_stanza.punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1] = porta_liv_succ;
        ultima_stanza.punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1]->get_position(ultima_stanza.coor_x, ultima_stanza.coor_y, MAX_RIGHE/2, MAX_COLONNE-1);

        //aggiungiamo anche la porta per tornare al livello precedente;
        prima_stanza.punti_stanza[3][0]= new item;
        *prima_stanza.punti_stanza[3][0]= porta_liv_prec;
        prima_stanza.punti_stanza[3][0]->get_position(prima_stanza.coor_x, prima_stanza.coor_y, 3, 0);


        p[x][y] = new stanza(x, y);
        *p[x][y] = ultima_stanza;
        contatore_stanze++;
    }
    //continuiamo a generare stanze finché non raggiungiamo il massimo consentito dal livello
    while (contatore_stanze <= (int) (n_livello * alfa)) {
        x = (rand() % i);
        y = (rand() % j);
        stanza nuova_stanza(x, y, contatore_stanze);
        nuova_stanza.is_emtpy = false;
        //controlliamo che la stanza sia presente o meno;
        if (!check_room(x, y)) {
            p[x][y] = new stanza(x, y);
            *p[x][y] = nuova_stanza;
            contatore_stanze++;
        }
    }
    //cerchiamo eventuali stanze rimaste vuote e stampiamo (?) una stanza vuota
    for (int tmp_i = 0; tmp_i < i; tmp_i++)
        for (int tmp_j = 0; tmp_j < j; tmp_j++)
            if (p[tmp_i][tmp_j] == NULL) {
                p[tmp_i][tmp_j] = new stanza(tmp_i, tmp_j);
                //p[tmp_i][tmp_j]->is_emtpy=true;
            }
}

void mappa::add_doors(ptr_stanza room) {
    item porta('+', true);

    //stanza a destra
    if (check_room(room->coor_x, room->coor_y+1) && !p[room->coor_x][room->coor_y+1]->is_emtpy && !room->has_connection(p[room->coor_x][room->coor_y+1])){
        room->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1]=new item;
        *room->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1]=porta;
        room->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1]->get_position(room->coor_x, room->coor_y, MAX_RIGHE/2, MAX_COLONNE-1);

        p[room->coor_x][room->coor_y+1]->punti_stanza[MAX_RIGHE/2][0]=new item;
        *p[room->coor_x][room->coor_y+1]->punti_stanza[MAX_RIGHE/2][0]=porta;
        p[room->coor_x][room->coor_y+1]->punti_stanza[MAX_RIGHE/2][0]->get_position(room->coor_x, room->coor_y, room->coor_x, room->coor_y+1);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->coor_x][room->coor_y+1]);
        p[room->coor_x][room->coor_y+1]->aggiungi_stanza_a_lista_connessioni(p[room->coor_x][room->coor_y+1], room);

        add_doors(p[room->coor_x][room->coor_y+1]);
    }

    //stanza sopra
    if (check_room(room->coor_x-1, room->coor_y) && !p[room->coor_x-1][room->coor_y]->is_emtpy && !room->has_connection(p[room->coor_x-1][room->coor_y])){
        room->punti_stanza[0][MAX_COLONNE/2]=new item;
        *room->punti_stanza[0][MAX_COLONNE/2]=porta;
        room->punti_stanza[0][MAX_COLONNE/2]->get_position(room->coor_x, room->coor_y, 0, MAX_COLONNE/2);

        p[room->coor_x-1][room->coor_y]->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2]=new item;
        *p[room->coor_x-1][room->coor_y]->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2]=porta;
        p[room->coor_x-1][room->coor_y]->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2]->get_position(room->coor_x-1, room->coor_y, MAX_RIGHE-1, MAX_COLONNE/2);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->coor_x-1][room->coor_y]);
        p[room->coor_x-1][room->coor_y]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->coor_x-1][room->coor_y], room);

        add_doors(p[room->coor_x-1][room->coor_y]);
    }

    //stanza sotto
    if (check_room(room->coor_x+1, room->coor_y) && !p[room->coor_x+1][room->coor_y]->is_emtpy && !room->has_connection(p[room->coor_x+1][room->coor_y])){
        room->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2]=new item;
        *room->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2]=porta;
        room->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2]->get_position(room->coor_x, room->coor_y, MAX_RIGHE-1, MAX_COLONNE/2);

        p[room->coor_x+1][room->coor_y]->punti_stanza[0][MAX_COLONNE/2]=new item;
        *p[room->coor_x+1][room->coor_y]->punti_stanza[0][MAX_COLONNE/2]=porta;
        p[room->coor_x+1][room->coor_y]->punti_stanza[0][MAX_COLONNE/2]->get_position(room->coor_x+1, room->coor_y, 0, MAX_COLONNE/2);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->coor_x+1][room->coor_y]);
        p[room->coor_x+1][room->coor_y]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->coor_x+1][room->coor_y], room);

        add_doors(p[room->coor_x+1][room->coor_y]);
    }

    //stanza a sinistra
    if (check_room(room->coor_x, room->coor_y-1) && !p[room->coor_x][room->coor_y-1]->is_emtpy && !room->has_connection(p[room->coor_x][room->coor_y-1])){
        room->punti_stanza[MAX_RIGHE/2][0]=new item;
        *room->punti_stanza[MAX_RIGHE/2][0]=porta;
        room->punti_stanza[MAX_RIGHE/2][0]->get_position(room->coor_x, room->coor_y, MAX_RIGHE/2, 0);

        p[room->coor_x][room->coor_y-1]->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1]=new item;
        *p[room->coor_x][room->coor_y-1]->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1]=porta;
        p[room->coor_x][room->coor_y-1]->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1]->get_position(room->coor_x, room->coor_y-1, MAX_RIGHE/2, MAX_COLONNE-1);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->coor_x][room->coor_y-1]);
        p[room->coor_x][room->coor_y-1]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->coor_x][room->coor_y-1], room);

        add_doors(p[room->coor_x][room->coor_y-1]);
    }
}

void mappa::print_map() {
    for (int tmp_i = 0; tmp_i < i; tmp_i++) {
        for (int x = 0; x < MAX_RIGHE; x++) {
            for (int tmp_j = 0; tmp_j < j; tmp_j++) {
                stanza tmp = *p[tmp_i][tmp_j];

                for (int y = 0; y < MAX_COLONNE; y++) {
                    cout << tmp.punti_stanza[x][y]->icon;
                }
            }
            cout << endl;
        }
    }
}

ptr_stanza mappa::find_first(int row) {
    //trova la prima stanza in una riga
    int tmp_j=0;
    while (p[row][tmp_j]->is_emtpy){
        //if (p[i][j]->is_emtpy)
        tmp_j++;
        if (tmp_j==j) { //se arrivi in fondo alla riga senza trovare nulla, la riga è vuota
            row++;
            tmp_j=0;
            if (row==i)
                return NULL;
        }
    }
    return p[row][tmp_j];
}

void mappa::first_linking(ptr_stanza room, bool force_linking) {
    item tunnel('x',true);
    item porta('+', true);
    ptr_stanza tmp = NULL;

    if (room == NULL) {//condizione di arresto 1: room è NULL
        return;
    }

    //if (force_linking && room->coor_y==j-1) return; //con questa condizione, non si riesegue su tutte le righe F_L ma sono su quella interessata

    if (room->coor_y < j - 1) { //room->coor_y non può essere j-1, perché tmp sarebbe in una stanza inesistente
        tmp = p[room->coor_x][room->coor_y + 1];
    } else if (room->coor_y == j - 1 && room->coor_x < i - 1)
        return first_linking(find_first(room->coor_x + 1),
                             false); //se siamo nell'ultima cella della riga, facciamo ripartire subito la funzione
    else return; //condizione di arresto due: raggiunta ultima cella della mappa

    while (tmp != NULL && tmp->coor_y < j) {
        //if (force_linking && tmp->coor_y==j-1) return; //questa riga evita di rieseguire first_linking su tutta la mappa, ma lo esegue solo sulla riga interessata
        if (tmp->is_emtpy) {
            if (tmp->coor_y + 1 < j) {
                tmp = p[tmp->coor_x][tmp->coor_y + 1];
            } else return first_linking(tmp, false);
        } else {
            if (tmp->coor_y == room->coor_y + 1 && force_linking) {
                //forza la scrittura di porte
                room->punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1] = new item;
                *room->punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1] = porta;
                room->punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1]->get_position(room->coor_x, room->coor_y, MAX_RIGHE/2, MAX_COLONNE-1);

                tmp->punti_stanza[MAX_RIGHE / 2][0] = new item;
                *tmp->punti_stanza[MAX_RIGHE / 2][0] = porta;
                tmp->punti_stanza[MAX_RIGHE/2][0]->get_position(room->coor_x, room->coor_y, MAX_RIGHE/2, 0);

                return first_linking(tmp, true);

            } else if (tmp->coor_y == room->coor_y + 1 && !force_linking) {
                return first_linking(tmp, false);
            } else if (tmp->coor_y > room->coor_y + 1) {
                //costruisci il tunnel solo se la stanza non risulta già connessa
                if (!room->has_connection(tmp) || !room->has_connection(room)) {
                    for (int a = room->coor_y + 1; a < tmp->coor_y; a++)
                        for (int b = 0; b < MAX_COLONNE; b++) {
                            p[room->coor_x][a]->punti_stanza[MAX_RIGHE / 2][b] = new item;
                            *p[room->coor_x][a]->punti_stanza[MAX_RIGHE / 2][b] = tunnel;
                            p[room->coor_x][a]->punti_stanza[MAX_RIGHE / 2][b]->get_position(room->coor_x, a, MAX_RIGHE/2, b);
                        }
                    tmp->punti_stanza[MAX_RIGHE / 2][0] = new item;
                    *tmp->punti_stanza[MAX_RIGHE / 2][0] = porta;
                    tmp->punti_stanza[MAX_RIGHE / 2][0]->get_position(tmp->coor_x, tmp->coor_y, MAX_RIGHE/2, 0);

                    room->punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1] = new item;
                    *room->punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1] = porta;
                    room->punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1]->get_position(room->coor_x, room->coor_y, MAX_RIGHE/2, MAX_COLONNE-1);

                    room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, tmp);
                    tmp->lista_connessioni=tmp->aggiungi_stanza_a_lista_connessioni(tmp, room);

                    add_doors(tmp); add_doors(room);
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
    if ((tmp->coor_x+1)<i && find_first(tmp->coor_x + 1)!=NULL)
        h = find_first(tmp->coor_x + 1)->coor_x;
    else return false;
    bool is_linked=false; //questo booleano dice se la riga data è collegata con la prima riga non vuota sottostante
    for (int scroll=tmp->coor_y; scroll<j; scroll++){
        if (!p[row][scroll]->is_emtpy){
            tmp=p[row][scroll];
            if (tmp->check_connection(tmp, p[h][scroll])) {
                is_linked = true;
            }
        }
    }
    return is_linked;
}

void mappa::second_linking(ptr_stanza room, ptr_stanza known_room) {
    item tunnel('x',true);
    item porta('+', true);
    if (room==NULL)
        return;

    if (room->coor_x==i-1 || find_first(room->coor_x+1)==NULL) {
        //se find_first restituisce NULL significa
        //che sotto la stanza room non ci sono altre
        //stanze, e la funzione termina.
        return;
    }

    if (check_row_connection(room->coor_x)){
        second_linking(find_first(room->coor_x+1), NULL);
        return;
    } else {
        ptr_stanza tmp=find_first(room->coor_x+1);
        if (known_room!=NULL)
            tmp=known_room;

        //caso 1)
        //non si fa niente, si convoglia nel caso 2
        if (room->coor_y==tmp->coor_y) { //caso 2: le stanze sono nella stessa colonna
            //stampa il tunnel
            for (int altezza = room->coor_x + 1; altezza < tmp->coor_x; altezza++)
                for (int a = 0; a < MAX_RIGHE; a++) {
                    p[altezza][room->coor_y]->punti_stanza[a][MAX_COLONNE / 2] = new item;
                    *p[altezza][room->coor_y]->punti_stanza[a][MAX_COLONNE / 2] = tunnel;
                    p[altezza][room->coor_y]->punti_stanza[a][MAX_COLONNE / 2]->get_position(altezza, room->coor_y, a, MAX_COLONNE/2);
                }
            room->punti_stanza[MAX_RIGHE - 1][MAX_COLONNE / 2] = new item;
            *room->punti_stanza[MAX_RIGHE - 1][MAX_COLONNE / 2] = porta;
            room->punti_stanza[MAX_RIGHE - 1][MAX_COLONNE / 2]->get_position(room->coor_x, room->coor_y, MAX_RIGHE-1, MAX_COLONNE/2);

            tmp->punti_stanza[0][MAX_COLONNE / 2] = new item;
            *tmp->punti_stanza[0][MAX_COLONNE / 2] = porta;
            tmp->punti_stanza[0][MAX_COLONNE / 2]->get_position(tmp->coor_x, tmp->coor_y, 0, MAX_COLONNE/2);

            room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, tmp);
            tmp->lista_connessioni=tmp->aggiungi_stanza_a_lista_connessioni(tmp, room);

            return second_linking(find_first(room->coor_x + 1), NULL);
        } else { //caso 3: le stanze non sono nella stessa colonna, bisogna generare una nuova stanza
            //genera la nuova stanza
            stanza nuova_stanza(tmp->coor_x, room->coor_y, contatore_stanze); //genero una nuova stanza nella stessa colonna di room e nella stessa riga di tmp
            nuova_stanza.is_emtpy = false;
            p[tmp->coor_x][room->coor_y] = new stanza(tmp->coor_x, room->coor_y);
            *p[tmp->coor_x][room->coor_y] = nuova_stanza;
            contatore_stanze++;
            //adesso c'è una stanza sotto room, posso rilanciare second_linking (dopo aver collegato le stanze della riga di tmp)
            first_linking(find_first(nuova_stanza.coor_x), true);
            //room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[tmp->coor_x][room->coor_y]);
            //tmp->lista_connessioni=tmp->aggiungi_stanza_a_lista_connessioni(p[tmp->coor_x][room->coor_y], room);
            return second_linking(room, p[tmp->coor_x][room->coor_y]);
            //return second_linking(find_first(room->coor_x+1));
        }
    }
}

void mappa::generate_map() {
    generate_all_rooms();

    //contatore_stanze--;

    /*
    p[0][0]=new stanza(0,0,0);
    p[0][0]->is_emtpy=false;
    p[0][1]=new stanza(0,1);
    p[0][1]->is_emtpy=true;
    p[0][2]=new stanza(0,2);
    p[0][2]->is_emtpy=true;
    p[0][3]=new stanza(0,3,1);
    p[0][3]->is_emtpy=false;

    p[1][0]=new stanza(1,0);
    p[1][0]->is_emtpy=true;
    p[1][1]=new stanza(1,1,2);
    p[1][1]->is_emtpy=false;
    p[1][2]=new stanza(1,2,3);
    p[1][2]->is_emtpy=false;
    p[1][3]=new stanza(1,3);
    p[1][3]->is_emtpy=true;

    p[2][0]=new stanza(2,0,4);
    p[2][0]->is_emtpy=false;
    p[2][1]=new stanza(2,1,5);
    p[2][1]->is_emtpy=false;
    p[2][2]=new stanza(2,2);
    p[2][2]->is_emtpy=true;
    p[2][3]=new stanza(2,3,6);
    p[2][3]->is_emtpy=false;*/

    //ricerca la prima porta della mappa
    ptr_stanza first=NULL;
    //find first trova la prima stanza partendo da una riga in input, e restituisce un puntatore alla stanza.
    first = find_first(0);
    add_doors(first);

   /* for (int a=0; a<i; a++)
        for (int b=0; b<j; b++){
            ptr_stanza stanza=p[a][b];
            cout << "a,b: " << a << "," << b << endl;
            cout << "coordinate p[a][b]: " << p[a][b]->coor_x << "," << p[a][b]->coor_y << endl;
            cout << "coordinate stanza: " << stanza->coor_x << "," << stanza->coor_y << endl;
        }
    */

    first_linking(first, false);
    second_linking(first, NULL);

    spada anduril; //spada di Aragorn
    *first->punti_stanza[3][4]=anduril;


    spada glamdring; //spada di Ganjalf
    ptr_connessioni tmp=first->lista_connessioni;
    while(first->lista_connessioni->next!=NULL)
        tmp=first->lista_connessioni->next;
    *tmp->stanza_puntata->punti_stanza[2][max_colonne-3]=glamdring;

    //un modo per scoprire se una stanza esiste (cioè è formata da muri, punti etc e non da soli spazi) è tramite il booleano
    //is_empty:

    coltello pugnale_morgul;

    if (!p[0][2]->is_emtpy)
        *p[0][2]->punti_stanza[5][6]=pugnale_morgul;
}
