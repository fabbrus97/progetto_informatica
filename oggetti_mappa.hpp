//#include "mappa.hpp"

typedef int posizione[4];
/* posizione[0] è la coordinata x rispetto alla mappa
 * posizione[1] è la coordinata y rispetto alla mappa
 * posizione[2] è la coordinata x rispetto alla stanza
 * posizione[3] è la coordinata y rispetto alla stanza
 */

//item
class item{
protected:
    bool is_passable; //determina se si può passare attraverso l'oggetto
public:
    posizione pos;
    char carattere; //elemento fondamentale, è il carattere associato all'oggetto (cioè quello che verrà stampato sulla mappa)
    item(char c, bool b);
    item();
    void get_position(int x, int y, int xx, int yy);


    //weapons:
    int dam=0;
    virtual void damage();
};

typedef item * ptr_item;

/*
 * oggetti stanza
 *
 */

/*
 * Ogni sottoclasse può avere nuovi metodi, ma tutti i metodi vanno specificati in item (con il prefisso virtual)
 * inoltre tutti i campi di ogni sottoclasse vanno specificati nella superclasse item
 *
 */

//LE SEGUENTI CLASSI DI ARMI SONO UNA PROVA

class sword:public item{
public:
    sword(int d, char c, bool b);
    void damage();
};

class bow:public item{
public:
    bow(int d, char c, bool b);
    void damage();
};