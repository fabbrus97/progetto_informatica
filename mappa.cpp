//
// Created by simone on 14/03/17.
//

#include "mappa.hpp"
#include "arma.hpp"

//contatore stanze
int contatore_stanze=1;

//oggetti stanza
item muro('#',false, false);
item punto_stanza('.',true, false);
item tunnel('x',true, false);
item porta_liv_succ('S',true, false);
item porta_liv_prec('B',true, false);
item spazio(' ',false, false);
item porta('+', true, false);

stanza::stanza(int x, int y, int n_room){
    coor_x=x;
    coor_y=y;
    n_stanza=n_room;

    lista_connessioni=NULL;
    punti_stanza=new ptr_item*[max_righe];

    //crea l'array bidimensionale
    for(int tmp = 0; tmp < max_righe; tmp++) {
        punti_stanza[tmp] = new ptr_item[max_colonne];
    }

    //costruiamo i muri
    for (int i=0; i<max_righe; i++){
        punti_stanza[i][0]=new item;
        *punti_stanza[i][0]=muro;
        punti_stanza[i][0]->setPositionX(x, y, i, 0);

        punti_stanza[i][max_colonne-1]=new item;
        *punti_stanza[i][max_colonne-1]=muro;
        punti_stanza[i][max_colonne-1]->setPositionX(x, y, i, max_colonne-1);
    }
    for (int j=0; j<max_colonne; j++){
        punti_stanza[0][j]=new item;
        *punti_stanza[0][j]=muro;
        punti_stanza[0][j]->setPositionX(x, y, 0, j);

        punti_stanza[max_righe-1][j]=new item;
        *punti_stanza[max_righe-1][j]=muro;
        punti_stanza[max_righe-1][j]->setPositionX(x, y, max_righe-1, j);
    }

    //costruiamo l'interno della stanza
    for (int i=1; i<max_righe-1; i++)
        for (int j=1; j<max_colonne-1; j++) {
            punti_stanza[i][j] = new item;
            *punti_stanza[i][j] = punto_stanza;
            punti_stanza[i][j]->setPositionX(x, y, i, j);
        }

}

stanza::stanza(int x, int y) {
    coor_x = x;
    coor_y = y;

    lista_connessioni=NULL;
    punti_stanza=new ptr_item*[max_righe];

    //crea l'array bidimensionale
    for(int tmp = 0; tmp < max_righe; tmp++) {
        punti_stanza[tmp] = new ptr_item[max_colonne];
    }
    //inizializza l'array a NULL
    for (int x=max_righe-1; x>=0; x--)
        for (int y=max_colonne-1; y>=0; y--) {
            punti_stanza[x][y] = new item;
            *punti_stanza[x][y] = spazio;
            //in realtà inizializzare le posizioni di questi punti è inutile
            punti_stanza[x][y]->setPositionX(coor_x, coor_y, x, y);
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

mappa::mappa(){}

ptr_connessioni stanza::aggiungi_stanza_a_lista_connessioni(ptr_stanza stanza_di_cui_modificare_lista, ptr_stanza stanza_da_aggiungere){
    ptr_connessioni tmp = new connessioni;
    tmp->stanza_puntata = stanza_da_aggiungere;
    tmp->next = stanza_di_cui_modificare_lista->lista_connessioni;
    return tmp;
}

bool stanza::check_connection(ptr_stanza stanza_di_partenza, ptr_stanza stanza_da_controllare) {
    //cout << "sono in check_connection" << endl;
    ptr_connessioni tmp = stanza_di_partenza->lista_connessioni;
    //cout << "la stanza di partenza è " << stanza_di_partenza->coor_x << "," << stanza_di_partenza->coor_y << "; tmp è "
    //     << tmp << endl;
    while (tmp != NULL) {

        //cout << "sto controllando la stanza " << stanza_da_controllare->coor_x << "," << stanza_da_controllare->coor_y
        //     << endl;

        /* Se il ptr alla stanza in lista_connessioni della stanza_di_partenza è uguale al ptr stanza_da_controllare,
         * la funzione ritorna "true", che significa: la stanza è già presente nella lista, ovvero le stanze sono già connesse
         */
        if (tmp->stanza_puntata == stanza_da_controllare) {
            //cout << "le stanze sono collegate " << endl;
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
    if (tentativo==(max_righe-2)*(max_colonne-2))
        return false;

    srand(time(0));
    int x, y;
    //x e y sono inizializzati in modo che siano un numero tra 1 e max_righe-1 o max_colonne-1
    x = (rand() % (max_righe-1))+1;
    y = (rand() % (max_colonne-1))+1;

    if (stanza->punti_stanza[x][y]->getIcon()=='.'){
        stanza->punti_stanza[x][y]=oggetto;
        return true;
    } else
        return posiziona_casualmente(stanza, oggetto, tentativo+1);

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
    //cout << "prima stanza " << x << "," << y << endl;
    //cout << "sto per allocare la prima stanza" << endl;
    stanza prima_stanza(x, y, 1);
    //cout << "ho allocato la prima stanza" << endl;
    prima_stanza.setIs_emtpy(false);
    if (n_livello == 1) {
        prima_stanza.punti_stanza[max_righe / 2][max_colonne - 1] = new item;
        *prima_stanza.punti_stanza[max_righe / 2][max_colonne - 1] = porta_liv_succ;
        prima_stanza.punti_stanza[max_righe / 2][max_colonne - 1]->setPositionX(prima_stanza.getCoor_x(), prima_stanza.getCoor_y(), max_righe/2, max_colonne-1);
    }
    //cout << "inseriamo la prima stanza nella mappa" << endl;
    p[x][y] = new stanza(x, y);
    //cout << "ho allocato una stanza vuota" << endl;
    *p[x][y] = prima_stanza;
    contatore_stanze++;
    //se non siamo nel primo livello, generiamo l'ultima stanza (che va nell'ultima colonna);
    //cout << "adesso ci occupiamo dell'ultima stanza" << endl;
    if (n_livello != 1) {
        x = (rand() % i);
        y = j - 1;
        //cout << "ultima stanza " << x << "," << y << endl;
        stanza ultima_stanza(x, y, (int) (n_livello * alfa));
        ultima_stanza.setIs_emtpy(false);
        ultima_stanza.punti_stanza[max_righe / 2][max_colonne - 1] = new item;
        *ultima_stanza.punti_stanza[max_righe / 2][max_colonne - 1] = porta_liv_succ;
        ultima_stanza.punti_stanza[max_righe / 2][max_colonne - 1]->setPositionX(ultima_stanza.getCoor_x(), ultima_stanza.getCoor_y(), max_righe/2, max_colonne-1);

        //aggiungiamo anche la porta per tornare al livello precedente;
        prima_stanza.punti_stanza[3][0]= new item;
        *prima_stanza.punti_stanza[3][0]= porta_liv_prec;
        prima_stanza.punti_stanza[3][0]->setPositionX(prima_stanza.getCoor_x(), prima_stanza.getCoor_y(), 3, 0);

        p[x][y] = new stanza(x, y);
        *p[x][y] = ultima_stanza;
        contatore_stanze++;
    }
    //continuiamo a generare stanze finché non raggiungiamo il massimo consentito dal livello
    while (contatore_stanze <= (int) (n_livello * alfa)) {
        x = (rand() % i);
        y = (rand() % j);
        stanza nuova_stanza(x, y, contatore_stanze);
        nuova_stanza.setIs_emtpy(false);
        //controlliamo che la stanza sia presente o meno;
        if (!check_room(x, y)) {
            //cout << "stanza " << x << "," << y << endl;
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

    //stanza a destra
    if (check_room(room->getCoor_x(), room->getCoor_y()+1) && !p[room->getCoor_x()][room->getCoor_y()+1]->isIs_emtpy() && !room->has_connection(p[room->getCoor_x()][room->getCoor_y()+1])){
        //se esiste la stanza xy, non è vuota e non ha alcuna connessione
        room->punti_stanza[max_righe/2][max_colonne-1]=new item;
        *room->punti_stanza[max_righe/2][max_colonne-1]=porta;
        room->punti_stanza[max_righe/2][max_colonne-1]->setPositionX(room->getCoor_x(), room->getCoor_y(), max_righe/2, max_colonne-1);

        p[room->getCoor_x()][room->getCoor_y()+1]->punti_stanza[max_righe/2][0]=new item;
        *p[room->getCoor_x()][room->getCoor_y()+1]->punti_stanza[max_righe/2][0]=porta;
        p[room->getCoor_x()][room->getCoor_y()+1]->punti_stanza[max_righe/2][0]->setPositionX(room->getCoor_x(), room->getCoor_y()+1, max_righe/2, 0);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->getCoor_x()][room->getCoor_y()+1]);
        p[room->getCoor_x()][room->getCoor_y()+1]->aggiungi_stanza_a_lista_connessioni(p[room->getCoor_x()][room->getCoor_y()+1], room);

        add_doors(p[room->getCoor_x()][room->getCoor_y()+1]);
    }

    //stanza sopra
    if (check_room(room->getCoor_x()-1, room->getCoor_y()) && !p[room->getCoor_x()-1][room->getCoor_y()]->isIs_emtpy() && !room->has_connection(p[room->getCoor_x()-1][room->getCoor_y()])){
        room->punti_stanza[0][max_colonne/2]=new item;
        *room->punti_stanza[0][max_colonne/2]=porta;
        room->punti_stanza[0][max_colonne/2]->setPositionX(room->getCoor_x(), room->getCoor_y(), 0, max_colonne/2);

        p[room->getCoor_x()-1][room->getCoor_y()]->punti_stanza[max_righe-1][max_colonne/2]=new item;
        *p[room->getCoor_x()-1][room->getCoor_y()]->punti_stanza[max_righe-1][max_colonne/2]=porta;
        p[room->getCoor_x()-1][room->getCoor_y()]->punti_stanza[max_righe-1][max_colonne/2]->setPositionX(room->getCoor_x()-1, room->getCoor_y(), max_righe-1, max_colonne/2);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->getCoor_x()-1][room->getCoor_y()]);
        p[room->getCoor_x()-1][room->getCoor_y()]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->getCoor_x()-1][room->getCoor_y()], room);

        add_doors(p[room->getCoor_x()-1][room->getCoor_y()]);
    }

    //stanza sotto
    if (check_room(room->getCoor_x()+1, room->getCoor_y()) && !p[room->getCoor_x()+1][room->getCoor_y()]->isIs_emtpy() && !room->has_connection(p[room->getCoor_x()+1][room->getCoor_y()])){
        room->punti_stanza[max_righe-1][max_colonne/2]=new item;
        *room->punti_stanza[max_righe-1][max_colonne/2]=porta;
        room->punti_stanza[max_righe-1][max_colonne/2]->setPositionX(room->getCoor_x(), room->getCoor_y(), max_righe-1, max_colonne/2);

        p[room->getCoor_x()+1][room->getCoor_y()]->punti_stanza[0][max_colonne/2]=new item;
        *p[room->getCoor_x()+1][room->getCoor_y()]->punti_stanza[0][max_colonne/2]=porta;
        p[room->getCoor_x()+1][room->getCoor_y()]->punti_stanza[0][max_colonne/2]->setPositionX(room->getCoor_x()+1, room->getCoor_y(), 0, max_colonne/2);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->getCoor_x()+1][room->getCoor_y()]);
        p[room->getCoor_x()+1][room->getCoor_y()]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->getCoor_x()+1][room->getCoor_y()], room);

        add_doors(p[room->getCoor_x()+1][room->getCoor_y()]);
    }

    //stanza a sinistra
    if (check_room(room->getCoor_x(), room->getCoor_y()-1) && !p[room->getCoor_x()][room->getCoor_y()-1]->isIs_emtpy() && !room->has_connection(p[room->getCoor_x()][room->getCoor_y()-1])){
        room->punti_stanza[max_righe/2][0]=new item;
        *room->punti_stanza[max_righe/2][0]=porta;
        room->punti_stanza[max_righe/2][0]->setPositionX(room->getCoor_x(), room->getCoor_y(), max_righe/2, 0);

        p[room->getCoor_x()][room->getCoor_y()-1]->punti_stanza[max_righe/2][max_colonne-1]=new item;
        *p[room->getCoor_x()][room->getCoor_y()-1]->punti_stanza[max_righe/2][max_colonne-1]=porta;
        p[room->getCoor_x()][room->getCoor_y()-1]->punti_stanza[max_righe/2][max_colonne-1]->setPositionX(room->getCoor_x(), room->getCoor_y()-1, max_righe/2, max_colonne-1);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->getCoor_x()][room->getCoor_y()-1]);
        p[room->getCoor_x()][room->getCoor_y()-1]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->getCoor_x()][room->getCoor_y()-1], room);

        add_doors(p[room->getCoor_x()][room->getCoor_y()-1]);
    }
}

void mappa::print_map() {
    for (int tmp_i = 0; tmp_i < i; tmp_i++) {
        for (int x = 0; x < max_righe; x++) {
            for (int tmp_j = 0; tmp_j < j; tmp_j++) {
                stanza tmp = *p[tmp_i][tmp_j];
                for (int y = 0; y < max_colonne; y++) {
                    cout << tmp.punti_stanza[x][y]->getIcon();
                }
            }
            cout << endl;
        }
    }
}

ptr_stanza mappa::find_first(int row) {
    //trova la prima stanza in una riga
    int tmp_j=0;
    while (p[row][tmp_j]->isIs_emtpy()){
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
    //cout << "sono in first_linking" << endl;
    ptr_stanza tmp = NULL;

    if (room == NULL) {//condizione di arresto 1: room è NULL
        //cout << "la stanza in input è NULL" << endl;
        return;
    }

    //if (force_linking && room->coor_y==j-1) return; //con questa condizione, non si riesegue su tutte le righe F_L ma sono su quella interessata

    if (room->getCoor_y() < j - 1) { //room->coor_y non può essere j-1, perché tmp sarebbe in una stanza inesistente
        tmp = p[room->getCoor_x()][room->getCoor_y() + 1];
    } else if (room->getCoor_y() == j - 1 && room->getCoor_x() < i - 1)
        return first_linking(find_first(room->getCoor_x() + 1),
                             false); //se siamo nell'ultima cella della riga, facciamo ripartire subito la funzione
    else return; //condizione di arresto due: raggiunta ultima cella della mappa

    while (tmp != NULL && tmp->getCoor_y() < j) {
        //cout << "sono nel while" << endl;
        //if (force_linking && tmp->coor_y==j-1) return; //questa riga evita di rieseguire first_linking su tutta la mappa, ma lo esegue solo sulla riga interessata
        if (tmp->isIs_emtpy()) {
            if (tmp->getCoor_y() + 1 < j) {
                tmp = p[tmp->getCoor_x()][tmp->getCoor_y() + 1];
            } else return first_linking(tmp, false);
        } else {
            if (tmp->getCoor_y() == room->getCoor_y() + 1 && force_linking) {
                //forza la scrittura di porte
                room->punti_stanza[max_righe / 2][max_colonne - 1] = new item;
                *room->punti_stanza[max_righe / 2][max_colonne - 1] = porta;
                room->punti_stanza[max_righe / 2][max_colonne - 1]->setPositionX(room->getCoor_x(), room->getCoor_y(), max_righe/2, max_colonne-1);

                tmp->punti_stanza[max_righe / 2][0] = new item;
                *tmp->punti_stanza[max_righe / 2][0] = porta;
                tmp->punti_stanza[max_righe/2][0]->setPositionX(room->getCoor_x(), room->getCoor_y(), max_righe/2, 0);

                return first_linking(tmp, true);

            } else if (tmp->getCoor_y() == room->getCoor_y() + 1 && !force_linking) {
                return first_linking(tmp, false);
            } else if (tmp->getCoor_y() > room->getCoor_y() + 1) {
                //costruisci il tunnel solo se la stanza non risulta già connessa
                if (!room->has_connection(tmp) || !room->has_connection(room)) {
                    for (int a = room->getCoor_y() + 1; a < tmp->getCoor_y(); a++)
                        for (int b = 0; b < max_colonne; b++) {
                            p[room->getCoor_x()][a]->punti_stanza[max_righe / 2][b] = new item;
                            *p[room->getCoor_x()][a]->punti_stanza[max_righe / 2][b] = tunnel;
                            p[room->getCoor_x()][a]->punti_stanza[max_righe / 2][b]->setPositionX(room->getCoor_x(), a, max_righe/2, b);
                        }
                    tmp->punti_stanza[max_righe / 2][0] = new item;
                    *tmp->punti_stanza[max_righe / 2][0] = porta;
                    tmp->punti_stanza[max_righe / 2][0]->setPositionX(tmp->getCoor_x(), tmp->getCoor_y(), max_righe/2, 0);

                    room->punti_stanza[max_righe / 2][max_colonne - 1] = new item;
                    *room->punti_stanza[max_righe / 2][max_colonne - 1] = porta;
                    room->punti_stanza[max_righe / 2][max_colonne - 1]->setPositionX(room->getCoor_x(), room->getCoor_y(), max_righe/2, max_colonne-1);

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
    //cout << "sono in check_row_connection" << endl;
    int h;
    ptr_stanza tmp=NULL;
    if (find_first(row)!=NULL) {
        tmp = find_first(row);
    }
    else return false;
    if ((tmp->getCoor_x()+1)<i && find_first(tmp->getCoor_x() + 1)!=NULL)
        h = find_first(tmp->getCoor_x() + 1)->getCoor_x();
    else return false;
    bool is_linked=false; //questo booleano dice se la riga data è collegata con la prima riga non vuota sottostante
    for (int scroll=tmp->getCoor_y(); scroll<j; scroll++){
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
    //cout << "sono in second linking" << endl;
    if (room==NULL)
        return;

    if (room->getCoor_x()==i-1 || find_first(room->getCoor_x()+1)==NULL) {
        //se find_first restituisce NULL significa
        //che sotto la stanza room non ci sono altre
        //stanze, e la funzione termina.
        return;
    }

    if (check_row_connection(room->getCoor_x())){
        //cout << "la riga in esame è connessa con quella sottostanze; rilancio second_linking" << endl;
        return second_linking(find_first(room->getCoor_x()+1), NULL);
    } else {
        ptr_stanza tmp=find_first(room->getCoor_x()+1);
        if (known_room!=NULL)
            tmp=known_room;

        //caso 1: le stanze sono attaccate
        //non si fa niente, si convoglia nel caso 2
        if (room->getCoor_y()==tmp->getCoor_y()) { //caso 2: le stanze sono nella stessa colonna
            //stampa il tunnel
            for (int altezza = room->getCoor_x() + 1; altezza < tmp->getCoor_x(); altezza++)
                for (int a = 0; a < max_righe; a++) {
                    p[altezza][room->getCoor_y()]->punti_stanza[a][max_colonne / 2] = new item;
                    *p[altezza][room->getCoor_y()]->punti_stanza[a][max_colonne / 2] = tunnel;
                    p[altezza][room->getCoor_y()]->punti_stanza[a][max_colonne / 2]->setPositionX(altezza, room->getCoor_y(), a, max_colonne/2);
                }
            room->punti_stanza[max_righe - 1][max_colonne / 2] = new item;
            *room->punti_stanza[max_righe - 1][max_colonne / 2] = porta;
            room->punti_stanza[max_righe - 1][max_colonne / 2]->setPositionX(room->getCoor_x(), room->getCoor_y(), max_righe-1, max_colonne/2);

            tmp->punti_stanza[0][max_colonne / 2] = new item;
            *tmp->punti_stanza[0][max_colonne / 2] = porta;
            tmp->punti_stanza[0][max_colonne / 2]->setPositionX(tmp->getCoor_x(), tmp->getCoor_y(), 0, max_colonne/2);

            room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, tmp);
            tmp->lista_connessioni=tmp->aggiungi_stanza_a_lista_connessioni(tmp, room);

            return second_linking(find_first(room->getCoor_x() + 1), NULL);
        } else { //caso 3: le stanze non sono nella stessa colonna, bisogna generare una nuova stanza
            //genera la nuova stanza
            stanza nuova_stanza(tmp->getCoor_x(), room->getCoor_y(), contatore_stanze); //genero una nuova stanza nella stessa colonna di room e nella stessa riga di tmp
            nuova_stanza.setIs_emtpy(false);
            p[tmp->getCoor_x()][room->getCoor_y()] = new stanza(tmp->getCoor_x(), room->getCoor_y());
            *p[tmp->getCoor_x()][room->getCoor_y()] = nuova_stanza;
            contatore_stanze++;
            //adesso c'è una stanza sotto room, posso rilanciare second_linking (dopo aver collegato le stanze della riga di tmp)
            first_linking(find_first(nuova_stanza.getCoor_x()), true);
            //room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[tmp->coor_x][room->coor_y]);
            //tmp->lista_connessioni=tmp->aggiungi_stanza_a_lista_connessioni(p[tmp->coor_x][room->coor_y], room);
            return second_linking(room, p[tmp->getCoor_x()][room->getCoor_y()]);
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

    //cout << "la funzione second_linking è terminata" << endl;

    /*tre modi per trovare una stanza e piazzarci un oggetto*/

    arma anduril(1,5,0); //spada di Aragorn
    *first->punti_stanza[3][4]=anduril;

    arma glamdring(1,2,3); //spada di Ganjalf
    ptr_connessioni tmp=first->lista_connessioni;
    //cout << "questo è il while in generate_map" << endl;
    while(tmp->next!=NULL) {
        tmp = first->lista_connessioni->next;
    }
    *tmp->stanza_puntata->punti_stanza[2][max_colonne-3]=glamdring;

    //un modo per scoprire se una stanza esiste (cioè è formata da muri, punti etc e non da soli spazi) è tramite il booleano
    //is_empty:

    arma pugnale_morgul(4,5,6);
    pugnale_morgul.setIcon('P');

    if (!p[0][2]->isIs_emtpy())
        *p[0][2]->punti_stanza[5][6]=pugnale_morgul;

    //cout << "la funzione generate_map è terminata" << endl;
}