//
// Created by simone on 14/03/17.
//

#include "mappa.hpp"

//contatore stanze
int contatore_stanze=1;

//oggetti stanza
item muro('#',false);
item punto_stanza('.',true);
item tunnel('x',true);
item porta_liv_succ('S',true);
item porta_liv_prec('B',true);
item spazio(' ',false);
item porta('+', true);

//prova armi
sword pungolo(5, 's', false);
bow arcoBase(3, 'a', true);

//personaggi
item personaggio('@',false);

stanza::stanza(int x, int y, int n_room){
    coor_x=x;
    coor_y=y;
    n_stanza=n_room;

    //crea l'array bidimensionale
    for(int tmp = 0; tmp < max_righe; tmp++) {
        punti_stanza[tmp] = new ptr_item[max_colonne];
    }

    //costruiamo i muri
    for (int i=0; i<max_righe; i++){
        punti_stanza[i][0]=&muro;
        punti_stanza[i][max_colonne-1]=&muro;
    }
    for (int j=0; j<max_colonne; j++){
        punti_stanza[0][j]=&muro;
        punti_stanza[max_righe-1][j]=&muro;
    }

    //costruiamo l'interno della stanza
    for (int i=1; i<max_righe-1; i++)
        for (int j=1; j<max_colonne-1; j++)
            punti_stanza[i][j]=&punto_stanza;

    //spawn character
    if (n_stanza==1)
        punti_stanza[1][1]=&personaggio;
}

stanza::stanza(int x, int y) {
    coor_x = x;
    coor_y = y;

    //crea l'array bidimensionale
    for(int tmp = 0; tmp < max_righe; tmp++) {
        punti_stanza[tmp] = new ptr_item[max_colonne];
    }
    //inizializza l'array a NULL
    for (int x=max_righe-1; x>=0; x--)
        for (int y=max_colonne-1; y>=0; y--) {
            punti_stanza[x][y] = &spazio;
        }

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

bool stanza::check_connection(ptr_stanza stanza_di_partenza, ptr_stanza stanza_da_controllare)

{
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
    //se la stanza ha almeno una connessione, la funzione restituisce true
    return (room->lista_connessioni!=NULL);
}

bool mappa::check_room(int x, int y) {
    //ritorna true se una stanza esiste, false altrimenti
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
        prima_stanza.punti_stanza[max_righe / 2][max_colonne - 1] = &porta_liv_succ;
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
        ultima_stanza.punti_stanza[max_righe / 2][max_colonne - 1] = &porta_liv_succ;
        //aggiungiamo anche la porta per tornare al livello precedente;
        p[prima_stanza.coor_x][prima_stanza.coor_y]->punti_stanza[3][0]= &porta_liv_prec;
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

    //funzione da togliere: impostazione corretta delle coordinate
    for (int a=0; a<i; a++)
        for (int b=0; b<j; b++){
            p[a][b]->coor_x=a;
            p[a][b]->coor_y=b;
        }
}

void mappa::add_doors(ptr_stanza room) {

    //stanza a destra
    if (check_room(room->coor_x, room->coor_y+1) && !p[room->coor_x][room->coor_y+1]->is_emtpy && !room->has_connection(p[room->coor_x][room->coor_y+1])){
        room->punti_stanza[max_righe/2][max_colonne-1]=&porta;
        p[room->coor_x][room->coor_y+1]->punti_stanza[max_righe/2][0]=&porta;
        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->coor_x][room->coor_y+1]);
        p[room->coor_x][room->coor_y+1]->aggiungi_stanza_a_lista_connessioni(p[room->coor_x][room->coor_y+1], room);

        add_doors(p[room->coor_x][room->coor_y+1]);
    }

    //stanza sopra
    if (check_room(room->coor_x-1, room->coor_y) && !p[room->coor_x-1][room->coor_y]->is_emtpy && !room->has_connection(p[room->coor_x-1][room->coor_y])){
        room->punti_stanza[0][max_colonne/2]=&porta;
        p[room->coor_x-1][room->coor_y]->punti_stanza[max_righe-1][max_colonne/2]=&porta;

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->coor_x-1][room->coor_y]);
        p[room->coor_x-1][room->coor_y]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->coor_x-1][room->coor_y], room);

        add_doors(p[room->coor_x-1][room->coor_y]);
    }

    //stanza sotto
    if (check_room(room->coor_x+1, room->coor_y) && !p[room->coor_x+1][room->coor_y]->is_emtpy && !room->has_connection(p[room->coor_x+1][room->coor_y])){
        room->punti_stanza[max_righe-1][max_colonne/2]=&porta;
        p[room->coor_x+1][room->coor_y]->punti_stanza[0][max_colonne/2]=&porta;

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->coor_x+1][room->coor_y]);
        p[room->coor_x+1][room->coor_y]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->coor_x+1][room->coor_y], room);

        add_doors(p[room->coor_x+1][room->coor_y]);
    }

    //stanza a sinistra
    if (check_room(room->coor_x, room->coor_y-1) && !p[room->coor_x][room->coor_y-1]->is_emtpy && !room->has_connection(p[room->coor_x][room->coor_y-1])){
        room->punti_stanza[max_righe/2][0]=&porta;
        p[room->coor_x][room->coor_y-1]->punti_stanza[max_righe/2][max_colonne-1]=&porta;

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
                    cout << tmp.punti_stanza[x][y]->carattere;
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
    cout << "sono in first_linking" << endl;
    ptr_stanza tmp = NULL;

    if (room == NULL) {//condizione di arresto 1: room è NULL
        cout << "la stanza in input è NULL" << endl;
        return;
    }

    //if (force_linking && room->coor_y==j-1) return; //con questa condizione, non si riesegue su tutte le righe F_L ma sono su quella interessata

    if (room->coor_y < j - 1) { //room->coor_y non può essere j-1, perché tmp sarebbe in una stanza inesistente
        tmp = p[room->coor_x][room->coor_y + 1];
        cout << "ora tmp è diverso da NULL con coordinate " << room->coor_x << ", " << room->coor_y + 1 << "( "
             << tmp->coor_x << ", " <<
             tmp->coor_y << ")" << endl;
    } else if (room->coor_y == j - 1 && room->coor_x < i - 1)
        return first_linking(find_first(room->coor_x + 1),
                             false); //se siamo nell'ultima cella della riga, facciamo ripartire subito la funzione
    else return; //condizione di arresto due: raggiunta ultima cella della mappa

    while (tmp != NULL && tmp->coor_y < j) {
        cout << "sono nel while" << endl;
        cout << "le coordinate di tmp sono " << tmp->coor_x << ", " << tmp->coor_y << endl;
        if (tmp->is_emtpy) {
            if (tmp->coor_y + 1 < j) {
                tmp = p[tmp->coor_x][tmp->coor_y + 1];
                cout << "la stanza " << tmp->coor_x << ", " << tmp->coor_y << " è vuota; faccio scorrere tmp avanti"
                     << endl;
            } else return first_linking(tmp, false);
        } else {
            cout << "la stanza " << tmp->coor_x << ", " << tmp->coor_y << " è piena; devo fare qualcosa" << endl;
            if (tmp->coor_y == room->coor_y + 1 && force_linking) {
                cout << "poiché room è nella posizione " << room->coor_x << ", " << room->coor_y
                     << " forzo la costruzione di porte" << endl;
                //forza la scrittura di porte
                room->punti_stanza[max_righe / 2][max_colonne - 1] = &porta;
                tmp->punti_stanza[max_righe / 2][0] = &porta;
                return first_linking(tmp, true);
            } else if (tmp->coor_y == room->coor_y + 1 && !force_linking) {
                return first_linking(tmp, false);
            } else if (tmp->coor_y > room->coor_y + 1) {
                cout << "poiché room è nella posizione " << room->coor_x << ", " << room->coor_y
                     << " costruisco un tunnel" << endl;
                //costruisci il tunnel solo se la stanza non risulta già connessa
                if (!room->has_connection(tmp) || !room->has_connection(room)) {
                    for (int a = room->coor_y + 1; a < tmp->coor_y; a++)
                        for (int b = 0; b < max_colonne; b++)
                            p[room->coor_x][a]->punti_stanza[max_righe / 2][b] = &tunnel;
                    tmp->punti_stanza[max_righe / 2][0] = &porta;
                    room->punti_stanza[max_righe / 2][max_colonne - 1] = &porta;
                    room->aggiungi_stanza_a_lista_connessioni(room, tmp);
                    tmp->aggiungi_stanza_a_lista_connessioni(tmp, room);

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
            if (tmp->check_connection(tmp, p[h][scroll]))
                is_linked = true;
        }
    }
    return is_linked;

}

void mappa::second_linking(ptr_stanza room) {
    cout << "sono in second linking" << endl;
    if (room==NULL)
        return;

    if (room->coor_x==i-1 || find_first(room->coor_x+1)==NULL) {
        //se find_first restituisce NULL significa
        //che sotto la stanza room non ci sono altre
        //stanze, e la funzione termina.
        cout << "find_first(room->coor_x+1)==NULL; faccio il return" << endl;
        return;
    }

    if (check_row_connection(room->coor_x)){
        cout << "la riga in esame è connessa con quella sottostanze; rilancio second_linking" << endl;
        return second_linking(find_first(room->coor_x+1));
    } else {
        ptr_stanza tmp=find_first(room->coor_x+1);

        //caso 1)
        //non si fa niente, si convoglia nel caso 2
        if (room->coor_y==tmp->coor_y) { //caso 2: le stanze sono nella stessa colonna
            cout << "le stanze " << room->coor_x << "," << room->coor_y << " e " << tmp->coor_x << "," << tmp->coor_y
                 << " sono nella stessa colonna" << endl;
            //stampa il tunnel
            for (int altezza = room->coor_x + 1; altezza < tmp->coor_x; altezza++)
                for (int a = 0; a < max_righe; a++)
                    p[altezza][room->coor_y]->punti_stanza[a][max_colonne / 2] = &tunnel;
            room->punti_stanza[max_righe - 1][max_colonne / 2] = &porta;
            cout << "aggiungo una porta in fondo alla stanza " << room->coor_x << "," << room->coor_y << endl;
            tmp->punti_stanza[0][max_colonne / 2] = &porta;
            cout << "aggiungo una porta in cima alla stanza " << tmp->coor_x << "," << tmp->coor_y << endl;
            room->aggiungi_stanza_a_lista_connessioni(room, tmp);
            tmp->aggiungi_stanza_a_lista_connessioni(tmp, room);

            return second_linking(find_first(room->coor_x + 1));
        } else { //caso 3: le stanze non sono nella stessa colonna, bisogna generare una nuova stanza
            cout << "le stanze " << room->coor_x << "," << room->coor_y << " e " << tmp->coor_x << "," << tmp->coor_y << " non sono nella stessa colonna" << endl;
            //genera la nuova stanza
            cout << "genero una nuova stanza " << tmp->coor_x << "," << room->coor_y << " che è vuota (" << p[tmp->coor_x][room->coor_y]->is_emtpy << ")" << endl;
            stanza nuova_stanza(tmp->coor_x, room->coor_y, contatore_stanze); //genero una nuova stanza nella stessa colonna di room e nella stessa riga di tmp
            nuova_stanza.is_emtpy = false;
            p[tmp->coor_x][room->coor_y] = new stanza(tmp->coor_x, room->coor_y);
            *p[tmp->coor_x][room->coor_y] = nuova_stanza;
            contatore_stanze++;
            //adesso c'è una stanza sotto room, posso rilanciare second_linking (dopo aver collegato le stanze della riga di tmp)
            first_linking(find_first(nuova_stanza.coor_x), true);
            room->aggiungi_stanza_a_lista_connessioni(room, p[tmp->coor_x][room->coor_y]);
            tmp->aggiungi_stanza_a_lista_connessioni(p[tmp->coor_x][room->coor_y], room);
            return second_linking(room);
            //return second_linking(find_first(room->coor_x+1));
        }
    }
}

void mappa::generate_map() {
    generate_all_rooms();

    /*contatore_stanze--;

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
    p[2][3]->is_emtpy=false;
    */

    //ricerca la prima porta della mappa
    ptr_stanza first=NULL;
    //find first trova la prima stanza partendo da una riga in input, e restituisce un puntatore alla stanza.
    first = find_first(0);
    add_doors(first);

    /*for (int a=0; a<i; a++)
        for (int b=0; b<j; b++){
            ptr_stanza stanza=p[a][b];
            cout << "a,b: " << a << "," << b << endl;
            cout << "coordinate p[a][b]: " << p[a][b]->coor_x << "," << p[a][b]->coor_y << endl;
            cout << "coordinate stanza: " << stanza->coor_x << "," << stanza->coor_y << endl;
        }
    */

    first_linking(first, false);
    second_linking(first);

    //ESEMPIO DI USO DI ARMI

    //cerchiamo la prima stanza e
    // salviamola nel puntatore
    // chiamato "first" e piazziamoci
    // delle armi

    first=find_first(0);

    first->punti_stanza[3][3]=&pungolo;
    first->punti_stanza[3][4]=&arcoBase;

    first->punti_stanza[3][3]->damage();
    first->punti_stanza[3][4]->damage();

    first->punti_stanza[3][2]->damage();
}