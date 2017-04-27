//
// Created by simone on 14/03/17.
//

#include "mappa.hpp"

//contatore stanze
int contatore_stanze=1;

stanza::stanza(int x, int y, int n_room){
    coor_x=x;
    coor_y=y;
    n_stanza=n_room;

    //costruiamo i muri
    for (int i=0; i<max_righe; i++){
        punti_stanza[i][0]='#';
        punti_stanza[i][max_colonne-1]='#';
    }
    for (int j=0; j<max_colonne; j++){
        punti_stanza[0][j]='#';
        punti_stanza[max_righe-1][j]='#';
    }

    //costruiamo l'interno della stanza
    for (int i=1; i<max_righe-1; i++)
        for (int j=1; j<max_colonne-1; j++)
            punti_stanza[i][j]='.';

    //spawn character
    if (n_stanza==1)
        punti_stanza[1][1]='@';
}

stanza::stanza(int x, int y) {
    coor_x = x;
    coor_y = y;
    for (int i = 0; i < max_righe; i++)
        for (int j = 0; j < max_colonne; j++)
            punti_stanza[i][j] = ' ';

}

mappa::mappa(int n) {
    n_livello=n;

    i=1; j=2;

    int n_stanze=(int)(n_livello*alfa);

    while (i*j < n_stanze) {
        i = i + 1;
        j = j + 1;
    }

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

ptr_connessioni stanza::aggiungi_stanza_a_lista_connessioni(ptr_stanza stanza_di_cui_modificare_lista, ptr_stanza stanza_da_aggiungere){
    ptr_connessioni tmp = new connessioni;
    tmp->stanza_puntata = stanza_da_aggiungere;
    tmp->next = stanza_di_cui_modificare_lista->lista_connessioni;
    return tmp;
}

bool stanza::check_connection(ptr_stanza stanza_di_partenza, ptr_stanza stanza_da_controllare){
    ptr_connessioni tmp=stanza_di_partenza->lista_connessioni;
    while (tmp!=NULL){
        /* Se il ptr alla stanza in lista_connessioni della stanza_di_partenza è uguale al ptr stanza_da_controllare,
         * la funzione ritorna "true", che significa: la stanza è già presente nella lista, ovvero le stanze sono già connesse
         */
        if (tmp->stanza_puntata == stanza_da_controllare)
            return true;
        tmp=tmp->next;
    }
    return false;
}

bool stanza::has_connection(ptr_stanza room){
    return (room->lista_connessioni!=NULL);
}

bool mappa::check_room(int x, int y) {
    return (x>=0 && x<i && y>=0 && y<j && p[x][y]!=NULL);
}

ptr_stanza mappa::find_place(int posizione, ptr_stanza prima_stanza){
    int x = prima_stanza->coor_x, y = prima_stanza->coor_y;
    if (y+1<j && p[x][y+1]==NULL){ //destra
        p[x][y+1] = new stanza(x, y+1);
        return p[x][y+1];
    }
    else if (x+1<i && p[x+1][y]==NULL){ //sotto
        p[x+1][y] = new stanza(x+1, y);
        return p[x+1][y];
    }
    else if (y-1>=0 && p[x][y-1]==NULL){ //sinistra
        p[x][y-1] = new stanza(x, y-1);
        return p[x][y-1];
    }
    else if (x-1>=0 && p[x-1][y]==NULL){ //sopra
        p[x-1][y] = new stanza(x-1, y);
        return p[x-1][y];
    } else {
        srand(time(0));
        int posizione = (rand() % 4);

        if (check_room(x+1, y)) {
            return find_place(posizione, p[x + 1][y]);
        }
        else if (check_room(x-1, y)) {
            return find_place(posizione, p[x - 1][y]);
        }
        else if (check_room(x, y+1)) {
            return find_place(posizione, p[x][y + 1]);
        }
        else if (check_room(x, y-1)) {
            return find_place(posizione, p[x][y - 1]);
        }
    }
}

void mappa::generate_all_rooms() {
    //bisogna generare anzitutto la prima stanza e l'ultima
    //perché occupano posizioni privilegiate
    srand(time(0));
    //la prima stanza va nella prima riga
    int x, y;
    x = (rand() % i);
    y = 0;
    cout << "prima stanza " << x << "," << y << endl;
    stanza prima_stanza(x, y, 1);
    prima_stanza.is_emtpy = false;
    if (n_livello == 1)
        prima_stanza.punti_stanza[max_righe / 2][max_colonne - 1] = 'S';
    p[x][y] = new stanza(x, y);
    *p[x][y] = prima_stanza;
    contatore_stanze++;
    //se non siamo nel primo livello, generiamo l'ultima stanza (che va nell'ultima colonna);
    if (n_livello != 1) {
        x = (rand() % i);
        y = j - 1;
        cout << "ultima stanza " << x << "," << y << endl;
        stanza ultima_stanza(x, y, (int) (n_livello * alfa));
        ultima_stanza.is_emtpy = false;
        ultima_stanza.punti_stanza[max_righe / 2][max_colonne - 1] = 'S';
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
            cout << "stanza " << x << "," << y << endl;
            p[x][y] = new stanza(x, y);
            *p[x][y] = nuova_stanza;
            contatore_stanze++;
        }
    }
    //cerchiamo eventuali stanze rimaste vuote e stampiamo una stanza vuota
    for (int tmp_i = 0; tmp_i < i; tmp_i++)
        for (int tmp_j = 0; tmp_j < j; tmp_j++)
            if (p[tmp_i][tmp_j] == NULL) {
                p[tmp_i][tmp_j] = new stanza(x, y);
                //p[tmp_i][tmp_j]->is_emtpy=true;
            }
}

void mappa::add_doors(ptr_stanza room) {

    //stanza a destra
    if (check_room(room->coor_x, room->coor_y+1) && !p[room->coor_x][room->coor_y+1]->is_emtpy && !room->has_connection(p[room->coor_x][room->coor_y+1])){
        room->punti_stanza[max_righe/2][max_colonne-1]='+';
        p[room->coor_x][room->coor_y+1]->punti_stanza[max_righe/2][0]='+';
        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->coor_x][room->coor_y+1]);
        p[room->coor_x][room->coor_y+1]->aggiungi_stanza_a_lista_connessioni(p[room->coor_x][room->coor_y+1], room);

        add_doors(p[room->coor_x][room->coor_y+1]);
    }

    //stanza sopra
    if (check_room(room->coor_x-1, room->coor_y) && !p[room->coor_x-1][room->coor_y]->is_emtpy && !room->has_connection(p[room->coor_x-1][room->coor_y])){
        room->punti_stanza[0][max_colonne/2]='+';
        p[room->coor_x-1][room->coor_y]->punti_stanza[max_righe-1][max_colonne/2]='+';

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->coor_x-1][room->coor_y]);
        p[room->coor_x-1][room->coor_y]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->coor_x-1][room->coor_y], room);

        add_doors(p[room->coor_x-1][room->coor_y]);
    }

    //stanza sotto
    if (check_room(room->coor_x+1, room->coor_y) && !p[room->coor_x+1][room->coor_y]->is_emtpy && !room->has_connection(p[room->coor_x+1][room->coor_y])){
        room->punti_stanza[max_righe-1][max_colonne/2]='+';
        p[room->coor_x+1][room->coor_y]->punti_stanza[0][max_colonne/2]='+';

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->coor_x+1][room->coor_y]);
        p[room->coor_x+1][room->coor_y]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->coor_x+1][room->coor_y], room);

        add_doors(p[room->coor_x+1][room->coor_y]);
    }

    //stanza a sinistra
    if (check_room(room->coor_x, room->coor_y-1) && !p[room->coor_x][room->coor_y-1]->is_emtpy && !room->has_connection(p[room->coor_x][room->coor_y-1])){
        room->punti_stanza[max_righe/2][0]='+';
        p[room->coor_x][room->coor_y-1]->punti_stanza[max_righe/2][max_colonne-1]='+';

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->coor_x][room->coor_y-1]);
        p[room->coor_x][room->coor_y-1]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->coor_x][room->coor_y-1], room);

        add_doors(p[room->coor_x][room->coor_y-1]);
    }
}

void mappa::print_map() {
    for (int tmp_i = 0; tmp_i < i; tmp_i++) {
        for (int x = 0; x < max_righe; x++) {
            for (int tmp_j = 0; tmp_j < j; tmp_j++) {
                stanza tmp = *p[tmp_i][tmp_j];
                for (int y = 0; y < max_colonne; y++) {
                    cout << tmp.punti_stanza[x][y];
                }
            }
            cout << endl;
        }
    }
}

ptr_stanza mappa::find_first(int row) {
    //trova la prima stanza in una riga
    int tmp_j=0;
    cout << "Cerchiamo stanze piene, queste sono vuote: " << endl;
    while (p[row][tmp_j]->is_emtpy){
        cout << row << "," << tmp_j << ": " << p[row][tmp_j]->is_emtpy << endl;
        //if (p[i][j]->is_emtpy)
        tmp_j++;
        if (tmp_j==j) { //se arrivi in fondo alla riga senza trovare nulla, la riga è vuota
            row++;
            tmp_j=0;
            if (row==i)
                return NULL;
        }
    }
    cout << "Ritorno la stanza " << row << "," << tmp_j << " di coordinate " << p[row][tmp_j]->coor_x << "," << p[row][tmp_j]->coor_y << endl;
    return p[row][tmp_j];
}

void mappa::first_linking(ptr_stanza room){
    //il check_room per la stanza successiva è analogo al p->next!=NULL;
    cout << "analizzo la stanza " << room << ", di coordinate " << room->coor_x << "," << room->coor_y << endl;
    if (check_room(room->coor_x, room->coor_y+1))
        cout << "la stanza a destra è " << p[room->coor_x][room->coor_y+1] << endl;
    if (check_room(room->coor_x, room->coor_y+1) && !p[room->coor_x][room->coor_y+1]->is_emtpy) {
        return first_linking(p[room->coor_x][room->coor_y + 1]);
    } else if (!check_room(room->coor_x, room->coor_y+1)) {
        if (!check_room(room->coor_x + 1, room->coor_y)) {
            cout << "ultima cella della riga; fine funzione" << endl;
            return; //non ci sono altre celle sottostanti, la mappa è finita
        }
        else {
            ptr_stanza first = find_first(room->coor_x + 1);
            if (first!=NULL) {
                cout << "la prima stanza trovata ha coordinate " << first->coor_x << "," << room->coor_y << endl;
                cout << "È la stanza " << p[first->coor_x][first->coor_y]->coor_x << "," << p[first->coor_x][first->coor_y]->coor_y << endl;
                //return first_linking(first);
                return first_linking(p[first->coor_x][first->coor_y]);
            } else
                return;
        }
    }
    else if (p[room->coor_x][room->coor_y+1]->is_emtpy){
        for (int scroll=room->coor_y+1; scroll<j; scroll++){
            if (!p[room->coor_x][scroll]->is_emtpy)
                if (room->has_connection(p[room->coor_x][scroll]) && room->has_connection(room))
                    return first_linking(p[room->coor_x][scroll]);
                else {
                    for (int a=room->coor_y+1; a<scroll; a++)
                        for (int b=0; b<max_colonne; b++)
                            p[room->coor_x][a]->punti_stanza[max_righe/2][b]='x';
                    p[room->coor_x][scroll]->punti_stanza[max_righe/2][0]='+';
                    p[room->coor_x][room->coor_y]->punti_stanza[max_righe/2][max_colonne-1]='+';

                    room->aggiungi_stanza_a_lista_connessioni(room, p[room->coor_x][scroll]);
                    room->aggiungi_stanza_a_lista_connessioni(p[room->coor_x][scroll], room);

                    add_doors(p[room->coor_x][scroll]);
                    add_doors(room);

                    return first_linking(p[room->coor_x][scroll]);
                }

            if (!check_room(room->coor_x, scroll+1)){
                if (!check_room(room->coor_x+1, room->coor_y))
                    return; //non ci sono altre celle sottostanti, la mappa è finita
                else {
                    ptr_stanza first=find_first(room->coor_x+1);
                    return first_linking(first);
                }
            }
        }
    }
}

void mappa::second_linking(ptr_stanza room) {}

void mappa::generate_map() {
    generate_all_rooms();
    //ricerca la prima porta della mappa

    ptr_stanza first=NULL;
    //find first trova la prima stanza partendo da una riga in input, e restituisce un puntatore alla stanza.
    first = find_first(0);
    add_doors(first);

    first_linking(first);

    /*for (int tmp_x=0; tmp_x<i; tmp_x++) {

        //first_linking(first);
        add_doors(first);
    }*/
}