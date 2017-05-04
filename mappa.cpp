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

void mappa::first_linking(ptr_stanza room){
    if (room==NULL)
        return;
    //il check_room per la stanza successiva è analogo al p->next!=NULL;
    if (check_room(room->coor_x, room->coor_y+1) && !p[room->coor_x][room->coor_y+1]->is_emtpy) {
        return first_linking(p[room->coor_x][room->coor_y + 1]);
    } else if (!check_room(room->coor_x, room->coor_y+1)) {
        if (!check_room(room->coor_x + 1, room->coor_y)) {
            return; //non ci sono altre celle sottostanti, la mappa è finita
        }
        else {
            ptr_stanza first = find_first(room->coor_x + 1);
            if (first!=NULL) {
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

bool mappa::check_row_connection(int row) {

    ptr_stanza tmp=NULL;
    tmp=find_first(row);
    bool is_linked=false; //questo booleano dice se la riga data è linked con la riga sottostante
    for (int scroll=tmp->coor_y; scroll<j; scroll++){
        if (!p[row][scroll]->is_emtpy){
            tmp=p[row][scroll];
            if (tmp->check_connection(tmp, p[row+1][scroll]))
                is_linked = true;
        }
    }
    return is_linked;

}

void mappa::second_linking(ptr_stanza room) {

    if (room==NULL || room->coor_x==i-1) {
        return;
    } else {
        cout << "analisi in corso della stanza " << room->coor_x << "," << room->coor_y << endl;
    }

    if (check_row_connection(room->coor_x)){
        cout << "verifichiamo che la riga " << room->coor_x << " sia collegata con la riga successiva" << endl;
        return second_linking(find_first(room->coor_x+1));
    } else if (find_first(room->coor_x+1)==NULL){
        cout << "le righe non sono collegate" << endl;
        int x=2; bool flag=false;
        while (!flag) {
            if (room->coor_x + x >= i) {
                cout << "non ci sono altre righe da collegare, fine funzione" << endl;
                return;
            } else if (!p[room->coor_x+x][room->coor_y]->is_emtpy){
                cout << "trovata una stanza, stampo un tunnel per collegare le righe" << endl;
                for (int altezza=room->coor_x+1; altezza < room->coor_x+x; altezza++){
                    for (int a=0; a<max_righe; a++)
                        p[altezza][room->coor_y]->punti_stanza[a][max_colonne/2]='x';
                    room->punti_stanza[max_righe-1][max_colonne/2]='+';
                    p[room->coor_x+x][room->coor_y]->punti_stanza[0][max_colonne/2]='+';
                }
                return second_linking(p[room->coor_x+x][room->coor_y]);
            } else if (room->coor_x+x < i) {
                cout << "controllo la riga sotto (aumento la variabile x)" << endl;
                x++;
            } else {
                cout << "siamo arrivati alla fine, verifichiamo che ci siano delle stanze di fianco" << endl;
                for (int scroll = room->coor_y; scroll < j; scroll++){

                    if (!p[room->coor_x][scroll]->is_emtpy) {
                        cout << "fortunatamente ne ho trovata una" << endl;
                        return second_linking(p[room->coor_x][scroll]);
                    }
                }

                cout << "nessuna stanza trovata, generazione nuova stanza e tunnel" << endl;

                room=find_first(room->coor_x);
                stanza nuova_stanza(room->coor_x+x, room->coor_y, contatore_stanze);
                nuova_stanza.is_emtpy = false;
                p[room->coor_x + x][room->coor_y] = new stanza(room->coor_x + x, room->coor_y);
                *p[room->coor_x + x][room->coor_y] = nuova_stanza;
                contatore_stanze++;

                add_doors(room);
                first_linking(find_first(room->coor_x + x)); //first_linking va da sx a dx, quindi bisogna dargli la prima stanza come input

                cout << "rilancio second_linking sulla stessa stanza per creare tunnel" << endl;
                return second_linking(room);
            }
            x++;
        }
    } else {
        cout << "la riga sotto non è vuota, ma non ci sono stanze a cui collegarsi" << endl;
        for (int scroll=room->coor_y; scroll<j; scroll++) {
            if (p[room->coor_x + 1][scroll]->is_emtpy) {
                cout << "quindi creo una stanza" << endl;
                stanza nuova_stanza(room->coor_x + 1, room->coor_y, contatore_stanze);
                nuova_stanza.is_emtpy = false;
                p[room->coor_x + 1][room->coor_y] = new stanza(room->coor_x + 1, room->coor_y);
                *p[room->coor_x + 1][room->coor_y] = nuova_stanza;
                contatore_stanze++;

                add_doors(room);
                first_linking(find_first(room->coor_x+1)); //first_linking va da sx a dx, quindi bisogna dargli la prima stanza come input
                cout << "rilancio second_linking sulla stanza appena creata" << endl;
                return second_linking(p[room->coor_x + 1][room->coor_y]);
            }
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

    first_linking(first);
    second_linking(first);

    /*for (int tmp_x=0; tmp_x<i; tmp_x++) {

        //first_linking(first);
        add_doors(first);
    }*/
}