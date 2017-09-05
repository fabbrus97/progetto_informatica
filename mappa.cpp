//
// Created by simone on 14/03/17.
//

#include <sstream>
#include "mappa.hpp"
#include "includes/gameobjects.hpp"
#include "includes/item.hpp"
#include "includes/arma.hpp"

//contatore stanze
int contatore_stanze=1;

mappa::mappa(int n) {
    n_livello=n;

    i=1; j=2;

    int n_stanze=(int)(n_livello*alfa);
    if(n_stanze < 5) {
        n_stanze = 5;
    }
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

    //bisogna generare anzitutto la prima stanza e l'ultima
    //perché occupano posizioni privilegiate
    srand(time(0));
    //la prima stanza va nella prima riga
    int x, y;

    x = (rand() % i);
    y = 0;
    stanza *prima_stanza = new stanza(x, y, 1);
    //cout << "ho allocato la prima stanza" << endl;
    prima_stanza->setIs_emtpy(false);
    if (n_livello == 1) {
        prima_stanza->punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1] = GameObjects::getNewLivPrec();
        prima_stanza->punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1]->setPositionX(prima_stanza->getCoor_x(), prima_stanza->getCoor_y(), MAX_RIGHE/2, MAX_COLONNE-1);
    }

    p[x][y] = prima_stanza;
    contatore_stanze++;
    //se non siamo nel primo livello, generiamo l'ultima stanza (che va nell'ultima colonna);
    //cout << "adesso ci occupiamo dell'ultima stanza" << endl;
    if (n_livello != 1) {
        x = (rand() % i);
        y = j - 1;
        
        stanza ultima_stanza(x, y, (int) (n_livello * alfa));

        ultima_stanza.setIs_emtpy(false);
        ultima_stanza.punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1] = GameObjects::getNewLivSucc();
        ultima_stanza.punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1]->setPositionX(ultima_stanza.getCoor_x(), ultima_stanza.getCoor_y(), MAX_RIGHE/2, MAX_COLONNE-1);

        //aggiungiamo anche la porta per tornare al livello precedente;
        prima_stanza->punti_stanza[3][0]= GameObjects::getNewLivPrec();
        prima_stanza->punti_stanza[3][0]->setPositionX(prima_stanza->getCoor_x(), prima_stanza->getCoor_y(), 3, 0);


        p[x][y] = new stanza(x, y);
        *p[x][y] = ultima_stanza;
        contatore_stanze++;
    }
    //continuiamo a generare stanze finché non raggiungiamo il massimo consentito dal livello
    while (contatore_stanze <= (int) (n_livello * alfa)) {
        x = (rand() % i);
        y = (rand() % j);

        //controlliamo che la stanza sia presente o meno;
        if (!check_room(x, y)) {
            p[x][y] = new stanza(x, y, contatore_stanze);
            p[x][y]->setIs_emtpy(false);
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
        room->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1]=GameObjects::getNewPorta();
        room->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1]->setPositionX(room->getCoor_x(), room->getCoor_y(), MAX_RIGHE/2, MAX_COLONNE-1);

        p[room->getCoor_x()][room->getCoor_y()+1]->punti_stanza[MAX_RIGHE/2][0]=GameObjects::getNewPorta();
        p[room->getCoor_x()][room->getCoor_y()+1]->punti_stanza[MAX_RIGHE/2][0]->setPositionX(room->getCoor_x(), room->getCoor_y()+1, MAX_RIGHE/2, 0);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->getCoor_x()][room->getCoor_y()+1]);
        p[room->getCoor_x()][room->getCoor_y()+1]->aggiungi_stanza_a_lista_connessioni(p[room->getCoor_x()][room->getCoor_y()+1], room);

        add_doors(p[room->getCoor_x()][room->getCoor_y()+1]);
    }

    //stanza sopra

    if (check_room(room->getCoor_x()-1, room->getCoor_y()) && !p[room->getCoor_x()-1][room->getCoor_y()]->isIs_emtpy() && !room->has_connection(p[room->getCoor_x()-1][room->getCoor_y()])){
        room->punti_stanza[0][MAX_COLONNE/2]=GameObjects::getNewPorta();
        room->punti_stanza[0][MAX_COLONNE/2]->setPositionX(room->getCoor_x(), room->getCoor_y(), 0, MAX_COLONNE/2);

        p[room->getCoor_x()-1][room->getCoor_y()]->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2]=GameObjects::getNewPorta();
        p[room->getCoor_x()-1][room->getCoor_y()]->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2]->setPositionX(room->getCoor_x()-1, room->getCoor_y(), MAX_RIGHE-1, MAX_COLONNE/2);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->getCoor_x()-1][room->getCoor_y()]);
        p[room->getCoor_x()-1][room->getCoor_y()]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->getCoor_x()-1][room->getCoor_y()], room);

        add_doors(p[room->getCoor_x()-1][room->getCoor_y()]);
    }

    //stanza sotto
    if (check_room(room->getCoor_x()+1, room->getCoor_y()) && !p[room->getCoor_x()+1][room->getCoor_y()]->isIs_emtpy() && !room->has_connection(p[room->getCoor_x()+1][room->getCoor_y()])){
        room->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2]=GameObjects::getNewPorta();
        room->punti_stanza[MAX_RIGHE-1][MAX_COLONNE/2]->setPositionX(room->getCoor_x(), room->getCoor_y(), MAX_RIGHE-1, MAX_COLONNE/2);

        p[room->getCoor_x()+1][room->getCoor_y()]->punti_stanza[0][MAX_COLONNE/2]=GameObjects::getNewPorta();
        p[room->getCoor_x()+1][room->getCoor_y()]->punti_stanza[0][MAX_COLONNE/2]->setPositionX(room->getCoor_x()+1, room->getCoor_y(), 0, MAX_COLONNE/2);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->getCoor_x()+1][room->getCoor_y()]);
        p[room->getCoor_x()+1][room->getCoor_y()]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->getCoor_x()+1][room->getCoor_y()], room);

        add_doors(p[room->getCoor_x()+1][room->getCoor_y()]);
    }

    //stanza a sinistra

    if (check_room(room->getCoor_x(), room->getCoor_y()-1) && !p[room->getCoor_x()][room->getCoor_y()-1]->isIs_emtpy() && !room->has_connection(p[room->getCoor_x()][room->getCoor_y()-1])){
        room->punti_stanza[MAX_RIGHE/2][0]=GameObjects::getNewPorta();
        room->punti_stanza[MAX_RIGHE/2][0]->setPositionX(room->getCoor_x(), room->getCoor_y(), MAX_RIGHE/2, 0);

        p[room->getCoor_x()][room->getCoor_y()-1]->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1]=GameObjects::getNewPorta();
        p[room->getCoor_x()][room->getCoor_y()-1]->punti_stanza[MAX_RIGHE/2][MAX_COLONNE-1]->setPositionX(room->getCoor_x(), room->getCoor_y()-1, MAX_RIGHE/2, MAX_COLONNE-1);

        room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[room->getCoor_x()][room->getCoor_y()-1]);
        p[room->getCoor_x()][room->getCoor_y()-1]->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(p[room->getCoor_x()][room->getCoor_y()-1], room);

        add_doors(p[room->getCoor_x()][room->getCoor_y()-1]);
    }
}

void mappa::print_map() {
    //cout << "\033[37;46m"; //cl white, bg cyano
    for (int tmp_i = 0; tmp_i < i; tmp_i++) {
        for (int x = 0; x < MAX_RIGHE; x++) {
            for (int tmp_j = 0; tmp_j < j; tmp_j++) {
                stanza tmp = *p[tmp_i][tmp_j];

                for (int y = 0; y < MAX_COLONNE; y++) {
                    //std::stringstream s;
                    //s << "\033[";
                    //s << (tmp.punti_stanza[x][y]->getColore() + 30);
                    //s << ";46m";
                    //cout << s.str();
                    cout << tmp.punti_stanza[x][y]->getIcon();
                }
            }
            cout << endl;
        }
    }
    //cout << "\033[37;40m"; //cl white, bg nero
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

    ptr_stanza tmp = NULL;

    if (room == NULL) {//condizione di arresto 1: room è NULL
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
                room->punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1] = GameObjects::getNewPorta();
                room->punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1]->setPositionX(room->getCoor_x(), room->getCoor_y(), MAX_RIGHE/2, MAX_COLONNE-1);

                tmp->punti_stanza[MAX_RIGHE / 2][0] = GameObjects::getNewPorta();
                tmp->punti_stanza[MAX_RIGHE/2][0]->setPositionX(room->getCoor_x(), room->getCoor_y(), MAX_RIGHE/2, 0);
                return first_linking(tmp, true);

            } else if (tmp->getCoor_y() == room->getCoor_y() + 1 && !force_linking) {
                return first_linking(tmp, false);

            } else if (tmp->getCoor_y() > room->getCoor_y() + 1) {
                //costruisci il tunnel solo se la stanza non risulta già connessa
                if (!room->has_connection(tmp) || !room->has_connection(room)) {
                    for (int a = room->getCoor_y() + 1; a < tmp->getCoor_y(); a++)
                        for (int b = 0; b < MAX_COLONNE; b++) {
                            p[room->getCoor_x()][a]->punti_stanza[MAX_RIGHE / 2][b] = GameObjects::getNewTunnel();
                            p[room->getCoor_x()][a]->punti_stanza[MAX_RIGHE / 2][b]->setPositionX(room->getCoor_x(), a, MAX_RIGHE/2, b);
                        }
                    tmp->punti_stanza[MAX_RIGHE / 2][0] = GameObjects::getNewPorta();
                    tmp->punti_stanza[MAX_RIGHE / 2][0]->setPositionX(tmp->getCoor_x(), tmp->getCoor_y(), MAX_RIGHE/2, 0);

                    room->punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1] = GameObjects::getNewPorta();
                    room->punti_stanza[MAX_RIGHE / 2][MAX_COLONNE - 1]->setPositionX(room->getCoor_x(), room->getCoor_y(), MAX_RIGHE/2, MAX_COLONNE-1);

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
                for (int a = 0; a < MAX_RIGHE; a++) {
                    p[altezza][room->getCoor_y()]->punti_stanza[a][MAX_COLONNE / 2] = GameObjects::getNewTunnel();
                    p[altezza][room->getCoor_y()]->punti_stanza[a][MAX_COLONNE / 2]->setPositionX(altezza, room->getCoor_y(), a, MAX_COLONNE/2);
                }
            room->punti_stanza[MAX_RIGHE - 1][MAX_COLONNE / 2] = GameObjects::getNewPorta();
            room->punti_stanza[MAX_RIGHE - 1][MAX_COLONNE / 2]->setPositionX(room->getCoor_x(), room->getCoor_y(), MAX_RIGHE-1, MAX_COLONNE/2);

            tmp->punti_stanza[0][MAX_COLONNE / 2] = GameObjects::getNewPorta();
            tmp->punti_stanza[0][MAX_COLONNE / 2]->setPositionX(tmp->getCoor_x(), tmp->getCoor_y(), 0, MAX_COLONNE/2);

            room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, tmp);
            tmp->lista_connessioni=tmp->aggiungi_stanza_a_lista_connessioni(tmp, room);

            return second_linking(find_first(room->getCoor_x() + 1), NULL);
        } else { //caso 3: le stanze non sono nella stessa colonna, bisogna generare una nuova stanza
            //genera la nuova stanza

            ptr_stanza nuova_stanza = new stanza(tmp->getCoor_x(), room->getCoor_y(), contatore_stanze); //genero una nuova stanza nella stessa colonna di room e nella stessa riga di tmp
            nuova_stanza->setIs_emtpy(false);
            p[tmp->getCoor_x()][room->getCoor_y()] = nuova_stanza;

            contatore_stanze++;
            //adesso c'è una stanza sotto room, posso rilanciare second_linking (dopo aver collegato le stanze della riga di tmp)
            first_linking(find_first(nuova_stanza->getCoor_x()), true);
            //room->lista_connessioni=room->aggiungi_stanza_a_lista_connessioni(room, p[tmp->coor_x][room->coor_y]);
            //tmp->lista_connessioni=tmp->aggiungi_stanza_a_lista_connessioni(p[tmp->coor_x][room->coor_y], room);
            return second_linking(room, p[tmp->getCoor_x()][room->getCoor_y()]);
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
    second_linking(first, NULL);
}
