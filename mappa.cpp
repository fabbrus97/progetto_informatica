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
    //spawn stairs
    if (nuova_stanza.n_stanza == (int)(alfa*n_livello)){
        nuova_stanza.punti_stanza[5][19] = 'S';
    }
    return nuova_stanza;
}

bool mappa::check_room(int x, int y) {
    //cout << endl << "Sto controllando la stanza n: " << contatore_stanze << endl;
    if (x<0 || y<0 || x>i || y>j)
        return false;

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
    ptr_stanze_occupate tmp=NULL, aux=NULL;

    if (head==NULL) {
        //cout << "caso 1: lista vuota (tmp = NULL); posiziono " << x << "," << y << endl;
        head = new stanze_occupate;
        head->i = x;
        head->j = y;
        head->next = NULL;
        return;
    }

    if (x < head->i || (x == head->i && y < head->j)) {
        //cout << "caso 2: l'elemento va in testa; posiziono " << x << "," << y << endl;
        tmp = head;
        head = new stanze_occupate;
        head->i = x;
        head->j = y;
        head->next = tmp;
        return;
    }

    tmp=head;
    //cout << "caso 3: l'elemento va in mezzo alla lista; posiziono " << x << "," << y << endl;
    while (tmp->next != NULL) {
        if ((tmp->next->i > x) || (tmp->next->i==x && tmp->next->j > y)) {
            //cout << "confronto x, y: " << x << "," << y << " con " << tmp->next->i << "," << tmp->next->j << endl;
            aux = tmp->next;
            tmp->next = new stanze_occupate;
            tmp->next->i = x;
            tmp->next->j = y;
            tmp->next->next = aux;
            return;
        }
        tmp = tmp->next;
    }

    //cout << "caso 4: l'elemento va inserito in fondo; posiziono " << x << "," << y << endl;
    tmp->next = new stanze_occupate;
    tmp->next->i = x;
    tmp->next->j = y;
    tmp->next->next = NULL;
}

void mappa::print_list() {
    ptr_stanze_occupate tmp=head;
    cout << endl << "Ecco gli indici generati: " << endl;
    while (tmp != NULL /*&& tmp->next != NULL*/){
        cout << "i " << tmp->i << " j " << tmp->j << " ";
        if (p[tmp->i][tmp->j].is_link)
            cout << "stanza collegata" << endl;
        else cout << "stanza isolata" << endl;
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
            save_room(a,b);
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
        //bisogna generare prima la prima e l'ultima stanza, per evitare che tutte le posizioni della prima e dell'ultima colonna vengano occupate
        //generiamo la prima stanza
        int x, y;
        stanza new_room = initialize_room(1);
        x = (rand() % i);
        y = 0;
        save_room(x, y);
        p[x][y] = new_room;
        contatore_stanze = contatore_stanze + 1;
        //generiamo l'ultima stanza
        if (n_livello != 1) {
            new_room = initialize_room((int) (alfa * n_livello));
            y = j - 1;
            x = (rand() % i);
            save_room(x, y);
            p[x][y] = new_room;
            contatore_stanze = contatore_stanze + 1;
        }
        while (contatore_stanze <= (int) (n_livello * alfa)) {
            //genera una stanza con un numero di stanza
            int room = contatore_stanze-1;
            stanza new_room = initialize_room(room);
            //genera due numeri per posizionare la stanza nella mappa
            x = (rand() % i);
            y = (rand() % j);
            //cout << endl << "Ciclo numero: " << numero_ciclo << " Coppia x y generati casualmente: " << x << " " << y << " " << "(" << new_room.n_stanza << "/" << (int)(alfa*n_livello) << ")" << endl;
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

void mappa::print_map() {
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

void mappa::add_tunnel(ptr_stanze_occupate stanza_isolata, bool escludi_valore) {
    cout << "buongiornissimo, sono dentro add_tunnel" << endl;
    //add_doors(stanza_isolata->i, stanza_isolata->j);
    ptr_stanze_occupate aux=NULL, tmp=stanza_isolata;
    if (escludi_valore && stanza_isolata->next!=NULL)
        aux=stanza_isolata;
    else aux=head;
    //if (escludi_valore) return;
    bool flag=false;
    /*if (stanza_isolata->next != NULL && (tmp->next->i==stanza_isolata->i || tmp->next->j==stanza_isolata->j)){
        cout << "stanza_isolata: " << stanza_isolata->i << "," << stanza_isolata->j << endl << "stanza_isolata->next: " << stanza_isolata->next->i  << "," << stanza_isolata->next->j << endl;
        tmp=tmp->next;
    }
    else {*/
        while (aux != NULL && !flag) {
            cout << "confronto aux con stanza_isolata: " << aux->i << "," << aux->j << " " << stanza_isolata->i << ","
                 << stanza_isolata->j << endl;
            if (!(aux->i == stanza_isolata->i && aux->j == stanza_isolata->j) &&
                ((aux->j == stanza_isolata->j && abs(aux->i - stanza_isolata->i) > 1) ||
                 (aux->i == stanza_isolata->i && abs(aux->j - stanza_isolata->j) > 1))) {
                cout << "ok, valori compatibili" << endl;
                tmp = aux;
                flag = true;
                /*} else if (!(aux->i == stanza_isolata->i && aux->j == stanza_isolata->j) && ((aux->j == stanza_isolata->j && abs(aux->i - stanza_isolata->i)==1) || (aux->i == stanza_isolata->i && abs(aux->j-stanza_isolata->j)==1)))
                    return; // add_doors(aux->i, aux->j);*/
            }
            aux = aux->next;
        }
        if (aux == NULL && !flag) {
            cout << "non ci sono stanze nella stessa riga o nella stessa colonna" << endl;
            ADD_ROOM
            //reset
            while(tmp!=NULL) {
                p[tmp->i][tmp->j].is_link = false;
                tmp = tmp->next;
            }
            add_doors(head->i, head->j);
            cout << "bene, ecco la lista aggiornata delle stanze" << endl;
            print_list();
            return;
        }
    int x = stanza_isolata->i;
    int y = stanza_isolata->j;
        cout << "ok, inizio add_tunnel" << endl;
        //controlliamo che ci siano altre stanze sulla stessa colonna
        if (tmp->j == y) {
            if (tmp->i > x + 1) { //la stanza da agganciare è sotto
                cout << "ho trovato una stanza sotto " << tmp->i << "," << tmp->j << endl;
                void foo() {
                    for (int riga = x + 1, n = 0; n < tmp->i - x - 1; n++, riga++)
                        for (int b = 0; b < 10; b++)
                            if (!check_room(riga, y)/*p[riga][y].punti_stanza[0][0]!='#'*/) {
                                p[riga][y].punti_stanza[b][10] = 'x';
                                p[x][y].punti_stanza[9][10] = '+';
                                p[tmp->i][tmp->j].punti_stanza[0][10] = '+';
                            }
                            else {
                                n++;
                                p[riga][y].punti_stanza[0][10] = '+';
                            }
                }            } else if (tmp->i < x - 1) { //la stanza da agganciare è sopra
                cout << "ho trovato una stanza sopra " << tmp->i << "," << tmp->j << endl;
                BOTTOM_TO_TOP_TUNNEL
            } else if (!p[tmp->i][tmp->j].is_link) {
                //questa riga è problematica, perché o crea un loop o non crea porte tra stanze vicine
                //p[stanza_isolata->i][stanza_isolata->j].is_link = true;
                cout << "sono nell'else maledetto" << endl;
                add_doors(tmp->i, tmp->j);
                add_tunnel(tmp, true);
            }
            //cout << "tunnel fatto; return add_doors" << endl;
            //p[tmp->i][tmp->j].is_link = true;
            //return (add_doors(tmp->i, tmp->j));
        }
        //controlliamo che ci siano altre stanze sulla stessa riga
        if (tmp->i == x) {
            if (tmp->j > y + 1) { //la stanza da agganciare è a dx
                cout << "ho trovato una stanza a destra " << tmp->i << "," << tmp->j << endl;
                for (int colonna = y + 1, n = 0; n < tmp->j - y - 1; n++, colonna++)
                    for (int a = 0; a < 20; a++)
                        if (!check_room(x, colonna)/*p[x][colonna].punti_stanza[0][0]!='#'*/){
                            p[x][colonna].punti_stanza[5][a] = 'x';
                            p[x][y].punti_stanza[5][19] = '+';
                            p[tmp->i][tmp->j].punti_stanza[5][0] = '+';
                        } else {
                            n++;
                            p[x][colonna].punti_stanza[5][0] = '+';
                        }
            } else if (tmp->j < y - 1) { //la stanza da agganciare è a sx
                cout << "ho trovato una stanza a sinistra " << tmp->i << "," << tmp->j << endl;
                for (int colonna = y - 1, n = 0; n < y - tmp->j - 1; n++, colonna--)
                    for (int a = 0; a < 20; a++)
                        if (!check_room(x, colonna)){
                            p[x][colonna].punti_stanza[5][a] = 'x';
                            p[x][y].punti_stanza[5][0] = '+';
                            p[tmp->i][tmp->j].punti_stanza[5][19] = '+';
                        } else {
                            n++;
                            p[x][colonna].punti_stanza[5][19] = '+';
                        }
            } else if (!p[tmp->i][tmp->j].is_link) {
                //p[stanza_isolata->i][stanza_isolata->j].is_link = true;
                cout << "sono nell'else maledetto" << endl;
                add_doors(tmp->i, tmp->j);
                add_tunnel(tmp, true);
            }
            //cout << "tunnel fatto; return add_doors" << endl;
            //p[tmp->i][tmp->j].is_link = true;
        }
    if (tmp->i!=x && tmp->j!=y) {
        cout << "la salvo io la situazione" << endl;
        cout << "tmp: " << tmp->i << "," << tmp->j << " stanza(x,y): "<<  x << "," << y << endl;
        ADD_ROOM
        ptr_stanze_occupate tmp = head;
        while (tmp != NULL) {
            p[tmp->i][tmp->j].is_link = false;
            tmp = tmp->next;
        }
        add_doors(head->i, head->j);
        //nuova_stanza = initialize_room(contatore_stanze+1);
        cout << "bene, ecco la lista aggiornata delle stanze" << endl;
        print_list();
    }

    return;
}

void mappa::add_doors(int i, int j) {
    //la funzione prende in input i e j, che sono le coordinate di una stanza nella mappa

    //cout << endl << "Stanze collegate: " << stanze_collegate << " su " << (int) (1.5 * n_livello) << endl;
        cout << "sono in add_doors" << endl;

    if (check_room(i + 1, j) && !p[i + 1][j].is_link) {
        p[i][j].punti_stanza[m - 1][n / 2] = '+';
        p[i + 1][j].punti_stanza[0][n / 2] = '+';
        //p[i][j].is_link = true;
        p[i + 1][j].is_link = true;
        add_doors(i + 1, j);
    }
    if (check_room(i, j + 1) && !p[i][j + 1].is_link) {
        p[i][j].punti_stanza[m / 2][n - 1] = '+';
        p[i][j + 1].punti_stanza[m / 2][0] = '+';
        //p[i][j].is_link = true;
        p[i][j + 1].is_link = true;
        add_doors(i, j + 1);
    }
    if (check_room(i - 1, j) && !p[i - 1][j].is_link) {
        p[i][j].punti_stanza[0][n / 2] = '+';
        p[i - 1][j].punti_stanza[m - 1][n / 2] = '+';
        //p[i][j].is_link = true;
        p[i - 1][j].is_link = true;
        add_doors(i - 1, j);
    }
    if (check_room(i, j - 1) && !p[i][j - 1].is_link) {
        p[i][j].punti_stanza[m / 2][0] = '+';
        p[i][j - 1].punti_stanza[m / 2][n - 1] = '+';
        //p[i][j].is_link = true;
        p[i][j - 1].is_link = true;
        add_doors(i, j - 1);
    }

    /*if (!check_room(i+1, j) && !check_room(i, j+1) && !check_room(i-1, j) && !check_room(i, j-1) && !p[i][j].is_link) {
        ptr_stanze_occupate tmp=head, stanza_isolata=NULL;
        bool flag=false;
        while (tmp!=NULL && !flag){
            if (tmp->i == i && tmp->j == j) {
                stanza_isolata = tmp;
                flag=true;
                //return add_doors(stanza_isolata->next->i, stanza_isolata->next->j);
            }
            tmp=tmp->next;
        }
        add_tunnel(stanza_isolata);
    }*/
}

void mappa::generate_map() {
    generate_all_rooms();
    add_empty_rooms();
    print_list();
    ptr_stanze_occupate tmp=head;
    cout << "inizio add_doors" << endl;
    add_doors(head->i, head->j);
    //p[head->i][head->j].is_link=false;
    //cout << endl << "Controlliamo di non aver lasciato indietro delle stanze" << endl;
    //ptr_stanze_occupate tmp_2 = head;
    cout << "fatto;" << endl;
    while (tmp != NULL) {
        cout << "cerco una stanza is_link=false: " << tmp->i << ", " << tmp->j << " ";
        if (p[tmp->i][tmp->j].is_link)
            cout << "non è isolata" << endl;
        else cout << "è isolata" << endl;
        if (!p[tmp->i][tmp->j].is_link) {
            //if (!check_room(tmp->i+1, tmp->j)&&!check_room(tmp->i-1, tmp->j)&&!check_room(tmp->i, tmp->j+1)&&!check_room(tmp->i+1, tmp->j-1)) {
            //p[tmp->i][tmp->j].is_link=true;
            cout << endl << "Heyheyhey, c'è ancora qualcosa da fare" << endl;
            add_tunnel(tmp, false);
            add_doors(tmp->i, tmp->j);
        }
        tmp = tmp->next;
    }
}