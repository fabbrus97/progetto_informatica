//
// Created by simone on 14/03/17.
//

#include "mappa.hpp"

//contatore stanze
int contatore_stanze=1;

ptr_stanze_occupate head=NULL;

mappa::mappa(int n){
    //questo costruttore calcola la dimensione della mappa di un livello
    //la dimensione minima della mappa di un livello è 1x2
    i=1; j=2;
    n_livello=n;
    int n_stanze=(int)(n_livello*alfa);
    while (i*j < n_stanze) {
        i = i + 1;
        j = j + 1;
    }
    //crea l'array bidimensionale
    for(int tmp = 0; tmp < i; tmp++) {
        p[tmp] = new stanza[j];
    }
}

stanza mappa::initialize_room(int n_stanza) {
    nuova_stanza.n_stanza=n_stanza;
    //aggiungi i muri
    for (int i=0; i<n; i++){
        nuova_stanza.punti_stanza[0][i]='#';
        nuova_stanza.punti_stanza[m-1][i]='#';
    }
    for (int i=0; i<m; i++){
        nuova_stanza.punti_stanza[i][0]='#';
        nuova_stanza.punti_stanza[i][n-1]='#';
    }
    //aggiungi i punti
    for (int i=1; i<m-1; i++)
        for (int j=1; j<n-1; j++){
            nuova_stanza.punti_stanza[i][j]='.';
        }
    //spawn character
    if (nuova_stanza.n_stanza==1)
        nuova_stanza.punti_stanza[1][1]='@';
    return nuova_stanza;
}

bool mappa::check_room(int x, int y) {
    //cout << endl << "Sto controllando la stanza n: " << contatore_stanze << endl;
    ptr_stanze_occupate tmp=head;
    bool flag=false;
    tmp=head;
    while (tmp != NULL /*&& tmp->next != NULL*/){
        if (tmp->i==x && tmp->j==y)
            flag = true;
        tmp=tmp->next;
    }
    //cout << endl << "questa stanza c'è già? " << flag << endl;
    return flag;
}

void mappa::save_room(int x, int y) {
    //cout << endl << "La stanza n. " << contatore_stanze << " sarà salvata" << endl;
    ptr_stanze_occupate tmp=head;
    tmp=head;
    head=new stanze_occupate;
    head->i=x;
    head->j=y;
    head->next=tmp;
    //return head;
}

void mappa::print_list() {
    ptr_stanze_occupate tmp=head;
    cout << endl << "Ecco gli indici generati: " << endl;
    while (tmp != NULL /*&& tmp->next != NULL*/){
        cout << "i " << tmp->i << " j " << tmp->j << endl;
        tmp=tmp->next;
    }
}

int numero_ciclo=0;

void mappa::add_empty_rooms() {
    for (int a=0; a<i; a++)
        for (int b=0; b<j; b++)
            if (!check_room(a, b)){
                    for (int x=0; x<m; x++)
                        for (int y=0; y<n; y++)
                            p[a][b].punti_stanza[x][y]=' ';
                }
}


void mappa::fill_room(){
    for (int a=0; a<i; a++)
        for (int b=0; b<j; b++){
            stanza new_room=initialize_room(contatore_stanze);
            p[a][b]=new_room;
            contatore_stanze++;
        }
}

void mappa::generate_all_rooms() {
    srand(time(0));
    //bisogna generare stanze finchè non viene raggiunto il numero previsto dal livello
    //se il numero delle celle disponibili è uguale al numero di stanze da posizionare, chiama una funzione
    //che riempe direttamente la mappa senza generare numeri
    if ((n_livello*alfa)==i*j){
        fill_room();
    }
    else {
        while (contatore_stanze <= (int) (n_livello * alfa)) {
            //genera una stanza con un numero di stanza
            int room = contatore_stanze;
            stanza new_room = initialize_room(room);
            //genera due numeri per posizionare la stanza nella mappa
            int x, y;
            //la prima stanza ha una posizione speciale, ovvero nella prima colonna in una riga casuale
            if (room == 1) {
                y = 0;
                x = (rand() % i);
            } else if (room == (int) (1.5 * n_livello)) {
                //l'ultima stanza va in una riga casuale dell'ultima colonna
                y = j - 1;
                x = (rand() % i);
            } else {
                x = (rand() % i);
                y = (rand() % j);
            }
            //cout << endl << "Ciclo numero: " << numero_ciclo << " Coppia x y generati casualmente: " << x << " " << y << endl;
            numero_ciclo++;
            //controlla che i due numeri non siano già presenti nella lista
            //e in caso contrario li aggiunge
            bool flag = check_room(x, y);
            //bool flag=false;
            //se i due indici non erano presenti e sono stati salvati (flag=false), li aggiunge alla mappa
            if (!flag) {
                save_room(x, y);
                p[x][y] = new_room;
                contatore_stanze = contatore_stanze + 1;
            }
        }
        //add_empty_rooms();
    }

}

void mappa::print_all_rooms() {
    for (int tmp_i=0; tmp_i<i; tmp_i++) {
        for (int x=0; x<m; x++) {
            for (int tmp_j = 0; tmp_j < j; tmp_j++) {
                stanza tmp = p[tmp_i][tmp_j];
                //cout << tmp_i << " " << tmp_j << " ";
                for (int y = 0; y < n; y++) {
                    //print_room(tmp, tmp_j);
                    cout << tmp.punti_stanza[x][y];
                    //cout << endl;
                    //cout << "N. stanza: " << nuova_stanza.n_stanza << " coordinate i j: "<< tmp_i << " " << tmp_j << " dimensione i j: " << i << " " << j << endl;
                }
            }
            cout << endl;
        }
        //cout << endl;
    }
}

bool mappa::is_isolated(ptr_stanze_occupate room) {
    //assumiamo che la stanza sia isolata, la funzione ritorna true se è isolata, false se non lo è
    ptr_stanze_occupate tmp=head;
    bool flag = true;
    while (tmp != NULL){
        /*controlliamo se esiste la coppia di indici
         * (i_room-1, j_room)
         * (i_room+1, j_room)
         * (i_room, j_room-1)
         * (i_room, j_room +1)
         * nella lista di tutte le stanze
         * */
        if (((tmp->i == room->i-1) && (tmp->j == room->j)) || ((tmp->i == room->i+1) && (tmp->j == room->j)) || ((tmp->i == room->i) && (tmp->j == room->j-1)) || ((tmp->i == room->i) && (tmp->j == room->j + 1)))
            flag=false;
        tmp=tmp->next;
        return flag;
    }
}

